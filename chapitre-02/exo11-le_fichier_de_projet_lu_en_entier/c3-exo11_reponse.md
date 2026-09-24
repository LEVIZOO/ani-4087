# Exercice 11 - le fichier de projet lu en entier

### 1Fichiers attendus

```text
Tous les fichiers demandés sont là.
```

### 2Recevabilité

```text
Le rendu écrit est présent et exploitable. Il attend une relecture.
```

J’ai compris mon erreur. J’ai lu le mauvais fichier au debut. Je me suis trompé. J’ai lu une démo livrée avec l’outil de construction, alors que le bon fichier, c’est celui du moteur, dans le dossier des applications, et son nom contient les lettres XR.

Le fichier que j’ai lu est pas mauvais, mais il n’est pas le bon sujet. Le vrai exercice parle d’un autre fichier, et il faut lire le commentaire dans ce fichier. C’est là que sont les trois pièges. Il y a des commentaires qui disent exactement ce qui casse si on enlève une ligne.

Les vrais pièges, c’est :

1. Il faut demander explicitement deux modules, parce qu’ils ne remontent pas tout seuls jusqu’à l’éditeur de liens.
2. Il manque une définition importante, sans laquelle une classe reste vide et la compilation casse.
3. Il manque une bibliothèque système, sans laquelle l’édition de liens casse.

C’est le coeur du fichier. Pas juste les filtres, pas juste les chemins, pas juste les versions de plateforme. Le point important, c’est les commentaires, parce que ces trois problèmes sont écrits noir sur blanc dans le bon fichier.

Je me suis aussi trompé sur le fait de ne pas mettre le chemin complet du fichier en première ligne. J’ai fait deux fois un travail sérieux sur des fichiers qui n’étaient pas le bon, et c’est une erreur. Il faut faire comme ça : mettre le chemin complet dès le debut et demander confirmation avant de commencer.

Donc mon rendu est mauvais pour cette raison. J’ai lu le mauvais fichier et j’ai raté le vrai sujet. Le bon fichier est le fichier XR du moteur, et il faut lire les trois pièges documentés dans les commentaires. C’est là qu’est le vrai sens de l’exercice.
