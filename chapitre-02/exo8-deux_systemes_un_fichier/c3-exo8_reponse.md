

Je suis sur Mac, donc je ne peux pas tester sur un vrai Windows ou un vrai Linux. J'ai quand même écrit les deux filtres, comme demandé, et j'ai fait tous les tests que je pouvais faire depuis mon Mac.

# Ce que j'ai écrit dans  .jenga

```python
with project("MaSalle"):
    consoleapp()
    language("C++")
    location("MaSalle")
    files(["src/**.cpp", "include/**.hpp"])

    with filter("system:Windows"):
        links(["user32", "gdi32"])
        defines(["PLATFORM_WINDOWS"])

    with filter("system:Linux"):
        links(["pthread", "dl"])
        defines(["PLATFORM_LINUX"])
```

Mon `main.cpp` ne fait rien du tout :

```cpp
int main() {
    return 0;
}
```

# Test 1 : build normal sur mon Mac

```
jenga build
```

Ça marche, parce que je suis sur macOS et qu'aucun des deux filtres (Windows, Linux) ne concerne macOS. Donc ils sont juste ignorés.

```
Target:        macOS x86_64
Build Successful   Time: 5.38s
```

# Test 2 : essayer quand même Windows

En tapant `jenga info`, j'ai vu que j'ai quand même un compilateur pour Windows installé sur mon Mac (ça s'appelle `clang-mingw`). Donc j'ai essayé :

```
jenga build --platform windows
```

Le fichier s'est bien compilé, mais ça a planté après, au moment de tout assembler ensemble (le "linkage") :

```
ld: unknown options: -Bdynamic --start-group --end-group
clang++: error: linker command failed with exit code 1
```

# Test 3 : essayer Linux

```
jenga build --platform linux
```

Là ça n'a même pas essayé, il n'y a pas de compilateur Linux du tout sur mon Mac :

```
Cannot create workspace: No suitable toolchain found for Linux x86_64
```

# Les difficultés que j'ai recontre

Le plus dur c'était de comprendre que mon Mac a bien un "faux" compilateur Windows installé (mingw), mais qu'il n'est pas complet : il peut compiler le code mais pas le linker jusqu'au bout, parce que l'outil qui assemble tout à la fin (le linker) sur mon Mac ne comprend pas certaines options que mingw lui envoie. C'est un problème de mon ordinateur, pas de mon fichier `.jenga`.

# Ce que je n'ai pas pu vérifie

Je n'ai pas de vrai PC Windows ni de machine Linux sous la main, donc je ne peux pas être sûr à 100% que mes bibliothèques (`user32`, `gdi32` pour Windows, `pthread`, `dl` pour Linux) sont les bonnes et que tout se lie correctement sur ces systèmes. Je n'ai vérifié que la partie compilation pour Windows, pas le linkage complet, et rien du tout pour Linux. Il faudrait qu'un camarade avec un vrai Windows ou un vrai Linux teste mon fichier tel quel pour confirmer.