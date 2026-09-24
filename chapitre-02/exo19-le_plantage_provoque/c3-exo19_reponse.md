# situation

Le rendu est réel et honnête.

Je ne peux pas faire ce vrai test sur un appareil Android, parce que mon mac n’a ni `adb`, et je n’ai pas de téléphone Android à portée de main. Je travaille sur iOS, mac et iPhone uniquement.

Commande vérifiée :

```bash
adb devices
```

Résultat réel :

```text
zsh: command not found: adb
```

Donc il n’y a pas de déploiement possible ici. Je ne peux pas faire planter un vrai programme sur un appareil Android, ni retrouver la trace dans le journal système Android, ni vérifier le crash sur un écran.

Le message exact est :

```text
zsh: command not found: adb
```

C’est la vérité, et c’est mieux que de mentir sur un faux plantage monsieur.
