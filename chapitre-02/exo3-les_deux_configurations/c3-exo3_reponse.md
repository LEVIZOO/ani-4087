
J'ai construit mon projet deux fois, une fois en Debug et une fois en Release, pour voir la différence.

# Debug

```
jenga build --config Debug
```

Ça a pris 5.52 secondes.

# Release

```
jenga build --config Release
```

Ça a pris 4.18 secondes. Un peu plus rapide.

# La taille des fichiers

J'ai regardé la taille exacte des deux exécutables avec `stat -f%z` :

```
Debug   : 20880 octets
Release : 20880 octets
```

Les deux font exactement la même taille, au byte près.

# Ce que je remarque

Avant cet exercice je ne savais même pas que "Release" existait, je connaissais juste "Debug". En comparant les deux, je vois que le temps de construction change un peu (Release un peu plus rapide), mais la taille du fichier reste exactement pareille dans les deux cas.

Je ne sais pas trop pourquoi la taille ne change pas, peut-être parce que mon programme est trop simple (il ne fait juste `return 0;`) pour qu'il y ait une différence.

Les 4 nombres demandés :
- Debug : 5.52s, 20880 octets
- Release : 4.18s, 20880 octets