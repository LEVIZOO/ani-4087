# demo1 – info contre build

J’ai volontairement mis une erreur dans le fichier Jenga.

Le fichier de projet est celui-ci :

```python
#!/usr/bin/env python3
# -*- coding: utf-8 -*-
from Jenga import *

with workspace("Salle"):
    configurations(['Debug'])
    targetoses([TargetOS.MACOS])
    targetarchs([TargetArch.X86_64])

    with project("MaSalle"):
        consoleapp()
        language("C++")
        location("MauvaisDossier")
        files(["src/**.cpp"])
```

Le vrai problème, c’est que `location("MauvaisDossier")` pointe vers un dossier qui n’existe pas.

## Ce que dit `jenga info`

```text
============================ Jenga Workspace: Salle ============================

Location: /Users/levizoonyaba/ani-4087/chapitre-02/demo1-info_contre_build/Salle
Entry file: /Users/levizoonyaba/ani-4087/chapitre-02/demo1-info_contre_build/Salle/Salle.jenga
Configurations: Debug
Platforms: Windows
Target OSes: macOS
Target Architectures: x86_64

Projects
------------------------------------------------------------
Name      Kind         Language   Test   External
=================================================
MaSalle   ConsoleApp   C++        No     No
```

`jenga info` ne montre pas la vraie cause. Il voit juste le projet et le fichier de configuration. Il ne dit pas que le dossier cible est invalide.

## Ce que dit `jenga build`

```text
Loading workspace...

Configuration: Debug
Target:        macOS x86_64
Toolchain:     host-apple-clang

Build Order (1 projects):
  1. MaSalle [CONSOLE_APP]

jenga: error executing command 'build': Not a directory: /Users/levizoonyaba/ani-4087/chapitre-02/demo1-info_contre_build/Salle/MauvaisDossier
```

La vraie cause est ici :

```text
Not a directory: .../MauvaisDossier
```

C’est `jenga build` qui montre le vrai problème. `jenga info` ne le montre pas, il donne juste une vue globale du projet.

## Conclusion pour la classe

La sortie qui désigne la cause, c’est `jenga build`.

`jenga info` sert à regarder la structure du projet, mais pas à diagnostiquer le bug réel d’un chemin invalide. Le vrai message d’erreur vient de `jenga build`.
