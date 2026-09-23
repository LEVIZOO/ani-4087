# Exercice 1 - le projet minimal

# Ce qu'on demande

Il faut écrire un fichier de projet Jenga et le faire construire. Le programme ne doit rien faire, juste avoir un main qui retourne 0. Et il faut rendre le fichier + ce que jenga build affiche.

## Ce que j'ai fait

J'ai créé un workspace avec la commande `jenga workspace salle_ani_4087`, puis un projet dedans avec `jenga project MaSalle --kind console --lang C++`.

Ça a généré automatiquement le fichier `salle_ani_4087.jenga` :

```python
from Jenga import *

with workspace("salle_ani_4087"):
    configurations(['Debug', 'Release'])
    targetoses([TargetOS.WINDOWS, TargetOS.LINUX, TargetOS.MACOS])
    targetarchs([TargetArch.X86_64])

    with project("MaSalle"):
        consoleapp()
        language("C++")
        location("MaSalle")
        files(["src/**.cpp", "include/**.hpp"])
```

Je n'ai pas écrit ce fichier moi-même, c'est Jenga qui l'a généré. Je l'ai juste laissé tel quel.

Par contre le fichier `main.cpp` généré au départ affichait un message ("Hello from MaSalle"), donc je l'ai modifié pour respecter l'énoncé qui dit que le programme ne doit rien faire :

```cpp
int main() {
    return 0;
}
```

## Le build

J'ai lancé `jenga build` et ça a marché du premier coup :

```
Loading workspace...

Configuration: Debug
Target:        macOS x86_64
Toolchain:     host-apple-clang

Build Order (1 projects):
  1. MaSalle [CONSOLE_APP]

Project: MaSalle                                                         Kind: CONSOLE_APP

Found 1 source file(s)
[1/1] Compiled: main.cpp
Linking...
Built: Build/Bin/Debug-macOS/MaSalle/MaSalle

Build Successful                                                             Time: 5.27s

BUILD COMPLETED
Projects Built:  1/1
Time:           5.28s
Status:         SUCCESS
```

## Remarque

Je suis sur Mac donc ça compile en macOS x86_64 directement, avec le compilateur clang que j'avais déjà sur ma machine.  mais pour run jai du utilise #jenga run  --platform macos