# Exercice 6 — État contre événement

J'ai appuyé sur Espace, puis je l'ai relâchée. Le terminal a affiché ces valeurs :

- Premier appui maintenu : `NkInput.IsKeyDown` = 267 frames**; `NkKeyPressEvent` = 1 événement.
- Autre appui maintenu : 451 frames; 1 événement.
- Appuis courts suivants : 6, 4, 4, 5 et 6 frames;  événement pour chaque appui.

`IsKeyDown` indique que la touche est tenue. Son compteur augmente donc à chaque frame pendant l'appui. `NkKeyPressEvent` signale le début de l'appui une seule fois; il ne se répète pas pendant que la touche reste enfoncée. C'est pourquoi le compteur de frames est beaucoup plus grand que celui des événements.

Je n'ai pas mesuré précisément la durée de chaque appui; les nombres ci-dessus sont ceux observés dans le terminal.