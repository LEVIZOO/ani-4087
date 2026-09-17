
1. Tableau de la chaîne « Mouvement vers Photon »
| Étape du chapitre | Durée estimée (cours) | Source / Explication |
|---|---|---|
| 1. Les capteurs mesurent le mouvement | 1 à 2 ms | Spécifications matérielles (IMU / capteurs de suivi du casque tournant entre 500 Hz et 1000 Hz). |
| 2. Le système transmet la mesure | 1 à 3 ms | Documentation Runtime / USB (Latence de transmission du bus USB/DisplayPort ou de la pile logicielle XR). |
| 3. Votre application décide et dessine | 5 à 11 ms | Non publiée par le constructeur : Dépend de la puissance du PC/casque et de l'optimisation de notre code. |
| 4. Le compositeur assemble | 1 à 2 ms | Documentation Runtime XR (Temps pris par le compositeur du système pour appliquer la déformation des lentilles et la prédiction). |
| 5. L'écran affiche la ligne | 2 à 5 ms | Spécifications de l'écran (Dépend directement du taux de rafraîchissement du casque, ex: 90 Hz ou 120 Hz, et du balayage). |
2. Remarques et justification des cases
Les étapes 1, 2, 4 et 5 sont des contraintes matérielles ou système définies par le constructeur du casque : ce sont des coûts fixes que nous ne pouvons pas réduire.
À l'inverse, la ligne « Votre application décide et dessine » (étape 3) ne se trouve dans aucune documentation constructeur. C'est tout à fait normal : cette durée dépend directement de la machine de l'utilisateur, de la complexité de notre scène 3D et de l'efficacité de notre propre code. C'est sur cette seule étape que nous avons une marge de manœuvre pour tenir le budget global sous les 20 ms.
