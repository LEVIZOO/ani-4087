# Exercice 10 — Le retour de focus

J'ai testé les deux modes. J'appuie sur `R` pour choisir le mode, je clique dans une autre fenêtre, je bouge la souris dix secondes, puis je reviens dans cette fenêtre. Au retour, le terminal affiche `rawDeltaX` et le total accumulé.

## Sans remise à zéro hors focus

Pendant le dernier essai, la fenêtre a perdu le focus à 23:05:36.586 et l'a retrouvé à 23:05:48.700, soit environ 12,11 secondes. Au retour : `rawDeltaX=0`, accumulateur `=0`.

## Avec remise à zéro hors focus

Pendant l'essai avec remise à zéro, la fenêtre a perdu le focus à 23:05:23.115 et l'a retrouvé à 23:05:30.328, soit environ 7,21 secondes. Au retour : `rawDeltaX=0`, accumulateur `=0`.

## Conclusion

Les deux essais donnent zéro. Sur mon Mac, Cocoa n'envoie pas de `NkMouseRawEvent`, donc l'accumulateur ne reçoit rien : la règle de remise à zéro ne change pas le résultat. Sur une plateforme qui envoie ces événements hors focus, ne pas remettre l'accumulateur à zéro pourrait laisser un ancien total s'accumuler et le livrer au retour du focus; le remettre à zéro évite ce rattrapage. Les durées indiquées sont calculées avec les horodatages du journal, pas mesurées au chronomètre.

Je n'ai pas trouvé dans les fichiers locaux le commentaire exact du simulateur cité dans le chapitre. Mon observation rejoint le principe d'un simulateur qui ne fait avancer que les événements qu'il reçoit : sur macOS, aucun événement brut n'arrive à l'accumulateur.