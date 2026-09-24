J’ai ajouté un motif de fichier qui n’existe pas et un dossier d’inclusion qui n’existe pas. J’ai ensuite vérifié ce que `jenga info` et `jenga build` disent.

# Le fichier Jenga

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
        location("MaSalle")
        files(["src/**.cpp", "include/**.hpp", "**/fichier_inexistant_12345.cpp"])
        includedirs(["include", "dossier_absent_999"])
```

J’ai mis un fichier qui n’existe pas dans `files`, et un dossier absent dans `includedirs`.

# Ce que `jenga info` dit

```text
============================ Jenga Workspace: Salle ============================

Projects
------------------------------------------------------------
Name      Kind         Language   Test   External
=================================================
MaSalle   ConsoleApp   C++        No     No
```

Le plus important : `jenga info` ne signale pas de problème sur le motif manquant ni sur le dossier absent. Il ne semble pas trop alarmé par ces chemins qui ne désignent rien.

# Ce que `jenga build` dit

```text
ℹ Found 1 source file(s)
✓   [1/1] Compiled: main.cpp
ℹ Linking...
✓ Built: Build/Bin/Debug-macOS/MaSalle/MaSalle
```

Le build passe quand même. Jenga a trouvé le vrai fichier source `main.cpp` et a ignoré le chemin inexistant. Il n’a pas bloqué la compilation.

# Comparaison

`jenga info` est plus rapide et plus léger, mais il ne dit pas forcément que quelque chose est faux si un chemin est absent dans `files` ou `includedirs`.

`jenga build` est plus fiable, parce qu’il compile réellement et vérifie ce qui est réellement utilisé. C’est le test le plus sérieux.

# Lequel nous aurait fait gagner du temps ?

Dans ce cas précis, `jenga info` nous aurait fait gagner du temps uniquement pour un aperçu rapide de la structure du projet. Mais `jenga build` nous aurait fait gagner du temps au final, parce qu’il donne la vraie validation fonctionnelle : il confirme qu’il n’y a pas de problème réel pour les fichiers réellement présents.

En résumé :

- `jenga info` = rapide, utile pour regarder la structure ;
- `jenga build` = plus fiable et plus utile pour détecter les vrais problèmes.

C’est donc `jenga build` qui est le meilleur test dans la vraie vie.
