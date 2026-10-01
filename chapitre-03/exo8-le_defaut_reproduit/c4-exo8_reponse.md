# Exercice 8 — Le défaut, reproduit

J'ai affiché `NkInput.MouseRawDeltaX()` à chaque image, sans additionner sa valeur. Après avoir bougé la souris et arrêté ma main, voici les vingt lignes suivantes du terminal :

```text
[2026-10-01 22:22:28.522] [INF] [default] [main.cpp:31 in nkmain] -> [Exo8] rawDeltaX=0
[2026-10-01 22:22:28.538] [INF] [default] [main.cpp:31 in nkmain] -> [Exo8] rawDeltaX=0
[2026-10-01 22:22:28.555] [INF] [default] [main.cpp:31 in nkmain] -> [Exo8] rawDeltaX=0
[2026-10-01 22:22:28.571] [INF] [default] [main.cpp:31 in nkmain] -> [Exo8] rawDeltaX=0
[2026-10-01 22:22:28.588] [INF] [default] [main.cpp:31 in nkmain] -> [Exo8] rawDeltaX=0
[2026-10-01 22:22:28.605] [INF] [default] [main.cpp:31 in nkmain] -> [Exo8] rawDeltaX=0
[2026-10-01 22:22:28.622] [INF] [default] [main.cpp:31 in nkmain] -> [Exo8] rawDeltaX=0
[2026-10-01 22:22:28.638] [INF] [default] [main.cpp:31 in nkmain] -> [Exo8] rawDeltaX=0
[2026-10-01 22:22:28.655] [INF] [default] [main.cpp:31 in nkmain] -> [Exo8] rawDeltaX=0
[2026-10-01 22:22:28.671] [INF] [default] [main.cpp:31 in nkmain] -> [Exo8] rawDeltaX=0
[2026-10-01 22:22:28.688] [INF] [default] [main.cpp:31 in nkmain] -> [Exo8] rawDeltaX=0
[2026-10-01 22:22:28.707] [INF] [default] [main.cpp:31 in nkmain] -> [Exo8] rawDeltaX=0
[2026-10-01 22:22:28.724] [INF] [default] [main.cpp:31 in nkmain] -> [Exo8] rawDeltaX=0
[2026-10-01 22:22:28.740] [INF] [default] [main.cpp:31 in nkmain] -> [Exo8] rawDeltaX=0
[2026-10-01 22:22:28.757] [INF] [default] [main.cpp:31 in nkmain] -> [Exo8] rawDeltaX=0
[2026-10-01 22:22:28.774] [INF] [default] [main.cpp:31 in nkmain] -> [Exo8] rawDeltaX=0
[2026-10-01 22:22:28.791] [INF] [default] [main.cpp:31 in nkmain] -> [Exo8] rawDeltaX=0
[2026-10-01 22:22:28.807] [INF] [default] [main.cpp:31 in nkmain] -> [Exo8] rawDeltaX=0
[2026-10-01 22:22:28.824] [INF] [default] [main.cpp:31 in nkmain] -> [Exo8] rawDeltaX=0
[2026-10-01 22:22:28.840] [INF] [default] [main.cpp:31 in nkmain] -> [Exo8] rawDeltaX=0
```

Cocoa est le backend utilisé par Nkentseu pour les fenêtres macOS. Il envoie les mouvements de souris comme des `NkMouseMoveEvent`, qui donnent la position, mais il ne produit pas de `NkMouseRawEvent`. Or `NkInput.MouseRawDeltaX()` est mis à jour seulement à la réception de ce dernier type d'événement.

Ces vingt lignes prouvent donc que, sur mon Mac, `rawDeltaX` reste à zéro après l'arrêt du mouvement : Cocoa ne fournit pas l'événement brut qui permettrait de lui donner une autre valeur.