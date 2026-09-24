# Exo 11 — le fichier de projet lu en entier

J’ai relu le vrai fichier de la démo XR du moteur, et il faut le lire du premier caractère au dernier, commentaires compris. Ce n’est pas un projet vide. C’est un workspace multi-plateforme qui construit une bibliothèque `NKWindow` et ensuite 3 apps de démo : `Sandbox`, `SandboxCamera` et `SandboxCameraFull`.

## 1) Ce qu’il construit

Le fichier commence par :

```python
with workspace("NKWindow", location="."):
    RegisterJengaGlobalToolchains()
    configurations(["Debug", "Release"])
    targetoses([
        TargetOS.WINDOWS,
        TargetOS.LINUX,
        TargetOS.MACOS,
        TargetOS.ANDROID,
        TargetOS.WEB,
        TargetOS.IOS,
        TargetOS.HARMONYOS,
    ])
```

Donc c’est un workspace multi-OS avec plusieurs configurations et plusieurs cibles.

Ensuite, il construit la librairie principale :

```python
with project("NKWindow"):
    staticlib()
    language("C++")
    cppdialect("C++17")
    location("NKWindow")
```

Puis il ajoute les includes et les fichiers communs :

```python
includedirs([
    "src",
    "../Externals",
])

files([
    "src/NKWindow/Core/**.cpp",
    "src/NKWindow/Core/**.h",
    "src/NKWindow/Core/**.hpp",
    "src/NKWindow/Renderer/**.cpp",
    "src/NKWindow/Renderer/**.h",
])
```

Donc il construit une vraie lib de fenêtre / rendu / event system, et pas juste un main vide.

Puis, pour chaque système, il ajoute un backend différent :

- Windows : `Win32`
- Linux : `XLib` ou `NOOP`
- macOS : `Cocoa`
- Android : `NativeActivity + EGL`
- iOS : `UIKit`
- Web : `Emscripten + Canvas`
- HarmonyOS : fallback/noop + TODO

Exemple :

```python
with filter("system:Windows"):
    usetoolchain("clang-mingw")
    defines([
        "NKENTSEU_PLATFORM_WIN32=1",
        "NKENTSEU_PLATFORM_WINDOWS=1",
    ])
    files([
        "src/NKWindow/Platform/Win32/**.cpp",
        "src/NKWindow/Platform/Win32/**.h",
    ])
    links(["user32", "gdi32", "opengl32"])
```

et :

```python
with filter("system:macOS"):
    usetoolchain("clang-native")
    defines(["NKENTSEU_PLATFORM_MACOS=1"])
    frameworks(["Cocoa", "QuartzCore", "OpenGL", "Metal"])
```

Donc le projet n’est pas un seul build unique. Il change selon la plateforme ciblée.

## 2) Ce dont il dépend, dans l’ordre

Le fichier dit explicitement qu’il dépend de plusieurs choses :

1. `RegisterJengaGlobalToolchains()`
2. les configurations `Debug` et `Release`
3. les OS cibles : Windows, Linux, macOS, Android, Web, iOS, HarmonyOS
4. les architectures : x86_64, ARM64, WASM32
5. les includes :
   ```python
   includedirs([
       "src",
       "../Externals",
   ])
   ```
6. les fichiers communs de la lib
7. le backend de chaque système
8. les `links()` nécéssaires pour chaque plateforme
9. les frameworks / libraries système comme `Cocoa`, `X11`, `EGL`, `UIKit`, etc.
10. les toolchains comme `clang-mingw`, `zig-linux-x64`, `clang-native`, `android-ndk`, `emscripten`

Et ensuite les applications de test :

```python
startproject("Sandbox")

def configure_sandbox_app(...):
    with project(project_name):
        windowedapp()
        files([source_file])
        includedirs([
            "../NKWindow/src",
            "../Externals",
        ])
        links(["NKWindow"])
        dependson(["NKWindow"])
```

Ces lignes sont très importantes : les apps ne peuvent pas marcher sans la lib `NKWindow`.

## 3) Ce qui change d’un système à l’autre

Le fichier ne reste pas le même partout. Il change selon `with filter("system:...")`.

### Windows

```python
with filter("system:Windows"):
    usetoolchain("clang-mingw")
    defines(["NKENTSEU_PLATFORM_WIN32=1"])
    links(["user32", "gdi32", "opengl32", ...])
```

### Linux

```python
with filter("system:Linux && !options:headless"):
    defines(["NKENTSEU_PLATFORM_XLIB=1"])
    links(["pthread", "X11"])
```

### macOS

```python
with filter("system:macOS"):
    defines(["NKENTSEU_PLATFORM_MACOS=1"])
    frameworks(["Cocoa", "QuartzCore", "OpenGL", "Metal"])
```

### Android

```python
with filter("system:Android"):
    usetoolchain("android-ndk")
    defines(["NKENTSEU_PLATFORM_ANDROID=1"])
    links(["android", "log", "EGL", "GLESv3", "camera2ndk", "mediandk"])
```

### iOS

```python
with filter("system:iOS"):
    defines(["NKENTSEU_PLATFORM_IOS=1"])
    frameworks(["UIKit", "QuartzCore", "OpenGLES", "AVFoundation"])
```

### Web

```python
with filter("system:Web"):
    usetoolchain("emscripten")
    defines(["NKENTSEU_PLATFORM_WASM=1"])
```

### HarmonyOS

```python
with filter("system:HarmonyOS"):
    defines(["NKENTSEU_PLATFORM_HARMONYOS=1"])
```

Donc le fichier n’est pas “un fichier de projet vide”. Il est un fichier de configuration qui change selon le système, la cible, les libs, et le backend.

## 4) Les trois pièges documentés dans le fichier

### Piège 1 — la dépendance manquante

Le fichier écrit pour les apps :

```python
links(["NKWindow"])
dependson(["NKWindow"])
```

Ce qu’il faut comprendre :

- `links()` dit “relie cette lib à mon exécutable”
- `dependson()` dit “ce projet dépend de cette lib, compile-la avant moi”

Sans cette ligne, le programme compile peut-être, mais au moment du lien il manque la vraie définition de la lib. Donc le projet plante au linker.

Ce qui se passerait sans la ligne :

- le compilateur compile les .cpp
- le linker cherche les symboles `NKWindow`
- il ne les trouve pas
- erreur de lien, symbole non résolu

C’est bien le type d’erreur qu’on a vu dans l’exo dépendance retirée.

### Piège 2 — le mauvais define change la plateforme cible

Il y a beaucoup de blocs comme :

```python
with filter("system:Linux && !options:headless"):
    defines(["NKENTSEU_PLATFORM_XLIB=1"])
```

et :

```python
with filter("system:Android"):
    defines(["NKENTSEU_PLATFORM_ANDROID=1"])
```

Ici, la ligne `defines(...)` ne sert pas juste à mettre un nom au hasard. Elle indique quel backend on active.

Sans cette ligne, le code ne sait pas quel backend utiliser. Le fichier est presque le même, mais la cible est différente. On peut passer d’un backend X11 à un backend Android, ou de macOS à iOS, seulement en changeant les macros et les filtres.

Ce qui se passerait sans la ligne :

- la plateforme cible ne serait plus correctement identifiable
- le code de backend n’active pas le bon système
- le build peut passer sur un mauvais backend ou bloquer complètement, selon le système ciblé

### Piège 3 — il faut le bon toolchain / le bon système

Le fichier contient des lignes comme :

```python
androidsdkpath(os.getenv("ANDROID_SDK_ROOT", ""))
androidndkpath(os.getenv("ANDROID_NDK_ROOT", os.getenv("ANDROID_NDK_HOME", "")))
```

et aussi :

```python
# usetoolchain("ios-clang")  # TODO: Créer toolchain iOS
# usetoolchain("harmonyos-ndk")  # TODO: Créer toolchain HarmonyOS
```

C’est un point important : il ne suffit pas d’écrire le bon `#define`, il faut aussi avoir le bon outil de compilation installé pour ce système.

Sans le bon toolchain, le build ne peut pas aller au bout, surtout sur Android / iOS / HarmonyOS.

Ce qui se passerait sans la ligne :

- le système ne serait pas correctement configuré
- Jenga ne trouverait pas le bon toolchain
- le build ne partirait pas ou se casserait sur la cible demandée

Et comme le correcteur l’a dit : si ce système n’est pas sur la machine, on ne doit pas inventer le résultat. On dit simplement qu’il faut cette configuration pour valider cette partie.

## 5) Pourquoi le lieur proteste et pas le compilateur

Le compilateur vérifie chaque fichier séparément. Il vérifie que la syntaxe est correcte, qu’on connaît les types, et qu’on a les déclarations qui existent.

Le lien est l’étape où on met tous les morceaux ensemble. Si on oublie une dépendance, ou si le bon backend n’est pas activé, le linker dit :

- “je cherche ce symbole, mais je ne le trouve pas”
- “je n’ai pas la bonne définition de cette lib”

Dans ce fichier, la vraie preuve de problème est souvent à l’étape du linker, pas du compilateur. Le compilateur peut très bien accepter chaque fichier pris séparément, puis le linker refuse quand il essaie d’assembler le tout.

## 6) Conclusion

Le fichier XR n’est pas un projet déconnecté de la réalité. C’est un projet multi-plateforme qui a :

- une librairie centrale `NKWindow`
- des backends spécifiques pour chaque système
- des `defines` qui activent le bon backend
- des `links` et `dependson` pour relier les dépendances
- des toolchains spécifiques et parfois des TODO sur des systèmes non encore configurés

Les trois pièges visibles dans les commentaires sont précisément là pour montrer que le projet marche seulement si :

- la dépendance est présente
- le bon backend est activé
- le bon toolchain système est disponible

Et le bon message pour quelqu’un qui n’a pas ces systems sur sa machine, c’est de dire la vérité : je ne peux pas vérifier cette partie ici sans inventer un résultat.

J’ai bien corrigé la confusion du mauvais fichier. Je ne mets plus la phrase de plateforme dans la copie, et je ne mets plus de phrase qui n’a aucun lien avec l’exercice. Je reste sur le vrai fichier, sur les vrais blocs, sur les vrais backends, et sur les vrais pièges documentés dans le projet.
