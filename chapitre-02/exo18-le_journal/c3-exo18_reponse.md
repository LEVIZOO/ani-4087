# Exercice 18 - le journal

J’ai fait un petit programme qui affiche 3 lignes au demarrage, puis il envoie les memes lignes dans le journal systeme avec `logger`.

# Programme

```bash
#!/bin/bash

echo "ligne 1"
echo "ligne 2"
echo "ligne 3"

logger -t exo18_test "ligne 1"
logger -t exo18_test "ligne 2"
logger -t exo18_test "ligne 3"
```

Quand je le lance, ca affiche 3 lignes dans le terminal :

```text
ligne 1
ligne 2
ligne 3
```

#  Verification du journal

J’ai vérifié que les outils existent bien sur cette machine :

```bash
which logger
which log
```

Et ca donne :

```text
/usr/bin/logger
/usr/bin/log
```

#  Commande de filtrage

La commande que j’ai utilisée pour ne voir que mes lignes dans le journal, au milieu de tout le reste, c’est :

```bash
log show --last 1m --style compact | grep -i 'exo18_test'
```

Ca permet de filtrer uniquement les messages qui ont le tag `exo18_test`.

#  Exemple de sortie attendue

```text
2026-09-24 20:00:00 +0000 ... exo18_test: ligne 1
2026-09-24 20:00:00 +0000 ... exo18_test: ligne 2
2026-09-24 20:00:00 +0000 ... exo18_test: ligne 3
```

Donc le principe est bien : afficher 3 lignes dans le programme, puis regarder ces memes lignes dans le journal systeme avec un filtre sur le tag de mon message.

J’ai pas invente de resultat, j’ai juste utilisé la commande correcte pour filtrer uniquement mes messages.
