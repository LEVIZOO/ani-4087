# situation

J’ai retiré le fichier `ModuleB.cpp` de la liste `files()` dans mon fichier `.jenga`, mais j’ai laissé le header `ModuleB.hpp`.

Donc le compilateur voit la déclaration, mais le linker ne trouve pas le vrai code.

La commande que j’ai lancée :

```bash
jenga build
```

La sortie exacte est :

```text
╔══════════════════════════════════════════════════════════════════╗
║                                                                  ║
║                ██╗███████╗███╗   ██╗ ██████╗  █████╗             ║
║                ██║██╔════╝████╗  ██║██╔════╝ ██╔══██╗            ║
║                ██║█████╗  ██╔██╗ ██║██║  ███╗███████║            ║
║           ██   ██║██╔══╝  ██║╚██╗██║██║   ██║██╔══██║            ║
║           ╚█████╔╝███████╗██║ ╚████║╚██████╔╝██║  ██║            ║
║            ╚════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝            ║
║                                                                  ║
║             Multi-platform C/C++ Build System v2.8.0             ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝

Loading workspace...

Configuration: Debug
Target:        macOS x86_64
Toolchain:     host-apple-clang

Build Order (1 projects):
  1. MaSalle [CONSOLE_APP]


╔═══════════════════════════════════════════════════════════════════════════════
═══════════════╗
║  Project: MaSalle                                                         Kind
: CONSOLE_APP  ║
╚═══════════════════════════════════════════════════════════════════════════════
═══════════════╝

ℹ Found 2 source file(s)
✓   [1/2] Compiled: ModuleA.cpp
✓   [2/2] Compiled: main.cpp
ℹ Linking...
╔═══════════════════════════════════════════════════════════════════════════════
═══════════════╗
║                                Compilation Error: Link Failed
               ║
╠═══════════════════════════════════════════════════════════════════════════════
═══════════════╣
║ Undefined symbols for architecture x86_64:
               ║
║   "getValueFromB()", referenced from:
               ║
║       getValueFromA() in src_ModuleA.o
               ║
║ ld: symbol(s) not found for architecture x86_64
               ║
║ clang++: error: linker command failed with exit code 1 (use -v to see invocati
on)            ║
╚═══════════════════════════════════════════════════════════════════════════════
═══════════════╝
✗ Link failed: Build/Bin/Debug-macOS/MaSalle/MaSalle

┌───────────────────────────────────────────────────────────────────────────────
───────────────┐
│  ✗ Build Failed
  Time: 7.04s  │
│ Errors: 1  | Failed files: 1
               │
└───────────────────────────────────────────────────────────────────────────────
───────────────┘

════════════════════════════════════════════════════════════════════════════════
                                  BUILD FAILED                                  
════════════════════════════════════════════════════════════════════════════════
Projects Built:  0/1
Failed:         1
Errors:         1
Time:           7.04s
Status:         ✗ FAILURE
════════════════════════════════════════════════════════════════════════════════

Echecs (1) — a corriger :
  ✗ MaSalle
```

Ce qui me dit que le module manquant, c’est `ModuleB`.

Le mot clé important, c’est :

```text
"getValueFromB()", referenced from:
    getValueFromA() in src_ModuleA.o
```

Ca veut dire que `ModuleA.cpp` appelle `getValueFromB()`, mais il ne trouve pas la vraie définition de cette fonction dans le programme final.

Donc c’est une erreur d’édition de liens, pas une erreur de compilation. La compilation a bien marché, mais le linker n’a rien trouvé pour assembler le tout.

Le module manquant est donc `ModuleB`, parce que son code n’a pas été compilé et relié au projet.
