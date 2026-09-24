J’ai pris un petit projet Jenga et j’ai ajouté un filtre pour Android, avec des définitions et des bibliothèques. Le but était de voir ce que Jenga dit quand le filtre est la, et ce qu’il ne dit pas.

# Le fichier Jenga

```python
#!/usr/bin/env python3
from Jenga import *

with workspace("Salle"):
    configurations(["Debug", "Release"])
    targetoses([TargetOS.MACOS])
    targetarchs([TargetArch.X86_64])

    with project("MaSalle"):
        consoleapp()
        language("C++")
        location("MaSalle")
        files(["src/**.cpp"])
        includedirs(["include"])

        with filter("system:Android"):
            defines(["PLATFORM_ANDROID", "ANDROID"])
            links(["android", "log", "EGL", "GLESv2"])
```

Le point important ici, c’est la ligne :

```python
with filter("system:Android"):
```

Donc le filtre n’est actif que si on est en cible Android.

# Jenga info ne nous dira rien

J’ai lancé :

```bash
source /Users/levizoonyaba/Documents/Jenga/.venv/bin/activate
cd /Users/levizoonyaba/ani-4087/chapitre-02/exo14-le_filtre_android/Salle
jenga info
```

et j’ai aussi vérifié qu’on a la meme chose quand on regarde la même config dans le contexte de ce projet.

La sortie ne change pas : on voit toujours le meme workspace, le meme projet, le meme nom, les memes fichiers. Le filtre Android ne change pas l’affichage de `jenga info`, parce qu’il s’agit surtout de la structure du projet, pas de la condition d’exécution vraie ou fausse.

Donc ici, la conclusion est simple :

- `jenga info` ne nous dit pas si le filtre est vrai ou faux
- il ne nous dit pas si on est bien sur Android
- il nous dit juste la forme du projet et ses projets connus

Autrement dit, `jenga info` est trop general pour savoir si le filtre est actif.

# Comment vérifier qu’il s’active bien ?

La bonne vérification c’est de passer par une commande qui prend `--platform`, par exemple :

```bash
jenga build --platform android
```

ou alors une commande equivalente de Jenga qui cible explicitement Android.

Le principe est simple : si la cible est Android, alors le filtre `system:Android` est pris en compte. Sinon, il est ignore.

# Ce que ça veut dire

Le filtre Android fait deux choses :

- ajoute des définitions de compilation : `PLATFORM_ANDROID`, `ANDROID`
- ajoute des bibliotheques de liens : `android`, `log`, `EGL`, `GLESv2`

Mais si on ne demande pas une plateforme Android, la condition ne s’applique pas et `jenga info` ne nous montre rien de special. C’est pour ça qu’il faut vérifier avec `--platform` et pas juste regarder le fichier .jenga.

# Conclusion

Le filtre Android est un filtre conditionnel. Il n’est pas visible dans `jenga info` comme une “réponse claire”, parce que l’info de Jenga reste structurelle. Pour savoir s’il s’active vraiment, il faut demander explicitement une cible Android, par exemple avec :

```bash
jenga build --platform android
```
