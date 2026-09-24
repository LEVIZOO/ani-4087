J’ai lu le fichier complet de démonstration multi-plateformes du moteur, en entier, commentaires inclus :

- /Users/levizoonyaba/Documents/Jenga/Jenga/Exemples/24_all_platforms/24_all_platforms.jenga

C’est un fichier Jenga qui construit un unique projet, mais avec une configuration qui change selon la cible système et la configuration de build.

# 1) Ce qu’il construit

Le projet s’appelle `AllPlatformsApp`.

Il construit un programme unique, mais il peut produire des variantes selon la plateforme :

- Windows : `consoleapp()` avec `clang-mingw`
- Linux : `consoleapp()` avec `zig-linux-x64`
- Android : `windowedapp()` avec `android-ndk`
- Web : `consoleapp()` avec `emscripten`

Le fichier utilise donc une seule définition de projet, puis remplace le comportement avec des filtres système et des filtres de configuration.

Le point central est cette idée :

- un seul projet, un seul code source,
- mais plusieurs cibles de build selon `system` et `config`.

# 2) Ce dont il dépend

Le fichier dépend de plusieurs éléments :

- du module Jenga : `from Jenga import *`
- du registre global des toolchains : `RegisterJengaGlobalToolchains()`
- des variables d’environnement sur Android :
  - `ANDROID_SDK_ROOT`
  - `ANDROID_NDK_ROOT`
- des outils de compilation associés à chaque système :
  - `clang-mingw` pour Windows
  - `zig-linux-x64` pour Linux
  - `android-ndk` pour Android
  - `emscripten` pour le Web
- des fichiers sources dans `src/**.cpp`
- des répertoires de sortie : `Build/Obj/...` et `Build/Bin/...`

Il ne s’appuie pas sur plusieurs projets différents ; il s’appuie plutôt sur des filtres qui modifient la manière de construire un même projet.

# 3) Ce qui change d’un système à l’autre

La partie la plus importante du fichier est le bloc de filtres.

## Windows

```python
with filter("system:Windows"):
    consoleapp()
    usetoolchain("clang-mingw")
    defines(["PLATFORM_WINDOWS", "WIN32", "_UNICODE", "UNICODE"])
```

Cela remplace le comportement standard du projet par une version Windows, avec les macros Windows et le toolchain MinGW/clang adapté.

## Linux

```python
with filter("system:Linux"):
    consoleapp()
    usetoolchain("zig-linux-x64")
    defines(["PLATFORM_LINUX"])
```

Cela change le toolchain pour une cible Linux cross-compile avec Zig.

## Android

```python
with filter("system:Android"):
    windowedapp()
    usetoolchain("android-ndk")
    defines(["PLATFORM_ANDROID"])
    androidapplicationid("com.jenga.allplatforms")
    androidminsdk(24)
    androidtargetsdk(34)
    androidabis(["armeabi-v7a", "arm64-v8a", "x86", "x86_64"])
    androidnativeactivity(True)
```

Ici, le projet n’est plus un simple console app ; il devient une application Android native avec configuration du package, ABI et native activity.

## Web

```python
with filter("system:Web"):
    consoleapp()
    usetoolchain("emscripten")
    defines(["PLATFORM_WEB"])
    emscripteninitialmemory(16)
```

La cible Web s’appuie sur Emscripten, avec une mémoire initiale définie pour le runtime Web.

## Debug vs Release

```python
with filter("config:Debug"):
    defines(["_DEBUG"])
    optimize("Off")
    symbols(True)

with filter("config:Release"):
    defines(["NDEBUG"])
    optimize("Speed")
    symbols(False)
```

Les changements de configuration ne touchent pas le code source, mais le mode de compilation : debug = traces et optimisations désactivées ; release = optimisation de vitesse et pas de symboles de debug.

# 4) Les trois pièges documentés

Le fichier documente plusieurs pièges de configuration. Les trois plus clairs sont les suivants.

## Piège 1 : les plateformes macOS et iOS sont volontairement désactivées par défaut

```python
# TargetOS.MACOS,   # Uncomment on macOS
# TargetOS.IOS,     # Uncomment on macOS with Xcode
```

Ce sont des lignes commentées. Elles sont là pour prévenir : si on veut cibler macOS ou iOS, il faut les décommenter.

### Que se passerait sans cette ligne ?

Sans cette activation, le projet ne construit pas de cible macOS/ios, même si le moteur supporte ces plateformes. On obtient un build qui ne couvre que les plateformes explicitement activées et on oublie les artefacts Apple.

## Piège 2 : Android a besoin des SDK/NDK présents dans l’environnement

```python
androidsdkpath(os.getenv("ANDROID_SDK_ROOT", ""))
androidndkpath(os.getenv("ANDROID_NDK_ROOT", ""))
```

Ces lignes ne sont pas optionnelles de manière pratique : elles doivent pointer vers des chemins valides.

### Que se passerait sans cette ligne ?

Sans ces chemins, le toolchain Android ne sait pas où trouver le SDK et le NDK. Le build Android échoue ou ne produit pas de cible valide, même si le projet C++ est correct.

## Piège 3 : chaque système a son propre toolchain et ses propres macros de plateforme

Les lignes de filtres système changent la cible à chaque système :

```python
with filter("system:Windows"):
with filter("system:Linux"):
with filter("system:Android"):
with filter("system:Web"):
```

Cette séparation est essentielle : le code ne peut pas être traité comme s’il était identique partout.

### Que se passerait sans cette ligne ?

Sans le bon filtre système, le projet serait construit avec le mauvais toolchain et les mauvaises macros. Par exemple, si le bloc Windows n’était pas appliqué, on perdrait `PLATFORM_WINDOWS`, `WIN32`, `_UNICODE`, `UNICODE`, et le build ne serait plus adapté au système cible. On obtiendrait soit un build incomplet, soit un comportement incohérent entre plateformes.

# 5) Conclusion

Ce fichier est une bonne démonstration de la logique Jenga :

- un seul projet,
- plusieurs systèmes,
- plusieurs toolchains,
- des macrodefs et des fonctionnalités différenciées par filtre,
- et des pièges bien spécifiques à la cross-compilation.

La leçon principale est simple : en build multi-plateformes, les outils, les macros et les sorties sont conditionnés par le système cible, et un oubli de ligne peut changer complètement le résultat du build.
