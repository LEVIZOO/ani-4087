# Exercice 9 — Le défaut, corrigé

J'ai comparé le `rawDeltaX` direct avec le total des `NkMouseRawEvent` reçus pendant chaque image. L'accumulateur est remis à zéro après chaque lecture.

## Exercice 8 : lecture directe

Sur mon Mac, les vingt lignes observées étaient toutes à `0`.

## Exercice 9 : accumulateur par image

Après avoir bougé puis arrêté la souris, voici les vingt valeurs observées côte à côte :

| Frame | Exo 8 `rawDeltaX` | Exo 9 `rawDeltaX` direct | Exo 9 accumulateur |
|---:|---:|---:|---:|
| 1 | 0 | 0 | 0 |
| 2 | 0 | 0 | 0 |
| 3 | 0 | 0 | 0 |
| 4 | 0 | 0 | 0 |
| 5 | 0 | 0 | 0 |
| 6 | 0 | 0 | 0 |
| 7 | 0 | 0 | 0 |
| 8 | 0 | 0 | 0 |
| 9 | 0 | 0 | 0 |
| 10 | 0 | 0 | 0 |
| 11 | 0 | 0 | 0 |
| 12 | 0 | 0 | 0 |
| 13 | 0 | 0 | 0 |
| 14 | 0 | 0 | 0 |
| 15 | 0 | 0 | 0 |
| 16 | 0 | 0 | 0 |
| 17 | 0 | 0 | 0 |
| 18 | 0 | 0 | 0 |
| 19 | 0 | 0 | 0 |
| 20 | 0 | 0 | 0 |

Sur mon Mac, les deux séries restent à zéro. Cocoa n'émet pas de `NkMouseRawEvent`, donc l'accumulateur ne reçoit aucun delta à additionner. Sur une plateforme qui émet ces événements, l'accumulateur additionne leurs deltas pendant l'image et remet le total à zéro après sa lecture; cela évite de perdre les événements reçus entre deux images.