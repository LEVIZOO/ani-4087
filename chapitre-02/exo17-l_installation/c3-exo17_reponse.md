
J’ai essaye d’installer mon paquet Android sur un appareil, mais dans cette machine, il n’y a ni `adb`, ni appareil branché. Donc l’installation a echoué, et je ne vais pas inventer une réussite.

# Commande essayée

```bash
adb install /Users/levizoonyaba/ani-4087/chapitre-02/exo16-le_paquet_vide/AppColor.apk
```

# Résultat réel

```text
zsh: command not found: adb
```

# Vérification

J’ai vérifié aussi avec cette commande :

```bash
which adb
adb devices
```

Et le résultat est :

```text
adb not found
zsh: command not found: adb
```

Donc il n’y a pas d’Android Debug Bridge de disponible sur cette machine. Sans `adb`, on ne peut pas installer le paquet sur un téléphone ou un émulateur. Et sans appareil, on ne peut pas prendre une photo de l’écran non plus.

# en somme 

L’installation a échoué, et le message exact est bien :

```text
zsh: command not found: adb
```

C’est plus instructif qu’un faux message de réussite, parce que ça dit clairement qu’il manque l’outil d’installation et qu’il n’y a pas d’appareil disponible. Je ne mets pas un résultat fantaisie, parce que ce n’est pas la bonne façon de faire un exercice de ce type.

# Point important

Le but de l’exercice n’est pas de faire semblant que ça marche. Le but est de montrer qu’on doit vérifier l’environnement réel, et si l’installation ne peut pas se faire, de rendre le message d’erreur exact.
