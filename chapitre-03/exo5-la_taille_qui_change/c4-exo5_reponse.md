# Exercice 5 — La taille qui change

J'ai ajouté un rappel sur `NkWindowResizeEvent`. À chaque changement, il affiche la largeur et la hauteur dans la console.

## Redimensionnement lent

Valeur observée : `1440x900`.

## Redimensionnement rapide

Valeur observée : `900x560`.

## Conclusion

La console a affiché deux nouvelles tailles, donc deux événements de redimensionnement ont été reçus pendant ce test : un pour le redimensionnement lent et un pour le redimensionnement rapide. Elle n'a pas affiché chaque déplacement intermédiaire de la souris.

Captures des deux tailles observées :

![Fenêtre avant redimensionnement](Capture%20d’écran%202026-10-01%20à%2021.11.00.png)

![Fenêtre redimensionnée](Capture%20d’écran%202026-10-01%20à%2021.11.17.png)