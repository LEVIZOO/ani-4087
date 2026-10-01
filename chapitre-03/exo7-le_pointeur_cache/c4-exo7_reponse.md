# Exercice 7 — Le pointeur caché

J'ai caché le pointeur et demandé son confinement dans la fenêtre. Le programme affiche `x`, `y` et `rawDelta` dans le terminal à chaque image.

## Avant le bord

Positions différentes relevées : `(0,0)`, `(897,139)`, puis `(1263,352)`. Le `rawDelta` est resté à `(0,0)`.

## Au bord

Dernière position relevée : `(1271,33)`. Ensuite, la position n'a plus changé et le `rawDelta` est resté à `(0,0)`. Le journal contenait 6 330 lignes.

## Conclusion

La position `x,y` s'arrête au bord, car elle décrit l'endroit où se trouve le pointeur. En principe, c'est le `rawDelta` qu'il faut utiliser pour continuer à lire un mouvement relatif quand le pointeur atteint le bord. Mais sur mon Mac, le backend Cocoa ne produit pas de `NkMouseRawEvent` : le `rawDelta` est resté à zéro, donc cette expérience ne montre pas le mouvement brut attendu. De plus, `ClipMouseToClient` découple le curseur sur macOS au lieu de le confiner strictement.

Voici la capture avec le pointeur caché :

![Fenêtre avec le pointeur caché](Capture%20d’écran%202026-10-01%20à%2022.02.03.png)