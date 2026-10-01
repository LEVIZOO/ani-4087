# Exercice 2 — La fenêtre qui ne répond pas

J'ai remplacé `PollEvents()` par un commentaire dans la boucle. La fenêtre ne traite donc plus les événements.

J'ai ajouté un appel à `PollEvents()` avant la boucle pour laisser macOS afficher la fenêtre au démarrage. Dans la boucle, `PollEvents()` n'est toujours pas appelé.

Jenga a construit les 12 projets en 7,72 secondes. Lors du dernier lancement, le chronomètre a mesuré 9,79 secondes jusqu'à l'arrêt forcé du programme (code 143).

Après l'arrêt forcé, macOS a affiché le message « Vous avez forcé Ani4087Exo2Fenetre à quitter », avec le bouton « Signaler » :

![Message macOS après l'arrêt forcé de la fenêtre](Capture%20d’écran%202026-10-01%20à%2017.06.17.png)