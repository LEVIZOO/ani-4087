# Exercice 17 - l'installation

J’ai essaye d’installer mon paquet Android sur un appareil, mais dans cette machine il n’y a ni `adb`, ni appareil branche. Donc l’installation a echoue, et je ne vais pas inventer une reussite.

## Commande essayee

```bash
adb install /Users/levizoonyaba/ani-4087/chapitre-02/exo16-le_paquet_vide/AppColor.apk
```

## Resultat reel

```text
zsh: command not found: adb
```

## Verification

J’ai verifie aussi avec cette commande :

```bash
which adb
adb devices
```

Et le resultat est :

```text
adb not found
zsh: command not found: adb
```

Donc il n’y a pas d’Android Debug Bridge de disponible sur cette machine. Sans `adb`, on ne peut pas installer le paquet sur un telephone ou un emulateur. Et sans appareil, on ne peut pas prendre une photo de l’ecran non plus.

## Conclusion

L’installation a echoue, et le message exact est bien :

```text
zsh: command not found: adb
```

C’est plus instructif qu’un faux message de reussite, parce que ca dit clairement qu’il manque l’outil d’installation et qu’il n’y a pas d’appareil disponible. Je ne mets pas un resultat fantaisie, parce que ce n’est pas la bonne facon de faire un exercice de ce type.

## Point important

Le but de l’exercice n’est pas de faire semblant que ca marche. Le but est de montrer qu’on doit verifier l’environnement reel, et si l’installation ne peut pas se faire, de rendre le message d’erreur exact.
