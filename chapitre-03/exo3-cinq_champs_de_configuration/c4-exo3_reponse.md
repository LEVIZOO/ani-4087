# Exercice 3 — Cinq champs de configuration

Le chapitre montre déjà `title`, `width`, `height`, `centered` et `resizable`. J'ai essayé cinq autres champs de `NkWindowConfig` :

1. `config.hasShadow = false;`
   - Attendu : la fenêtre n'a pas d'ombre portée.
   - Observé : je ne vois pas d'ombre autour de la fenêtre.

2. `config.transparent = true;`
   - Attendu : le fond de la fenêtre est transparent.
   - Observé : je vois l'autre application à travers le fond de la fenêtre.

3. `config.opacity = 0.75f;`
   - Attendu : la fenêtre est partiellement transparente.
   - Observé : la fenêtre est translucide.

4. `config.alwaysOnTop = true;`
   - Attendu : la fenêtre reste au-dessus des autres fenêtres.
   - Observé : elle reste devant l'autre application.

5. `config.minimizable = false;`
   - Attendu : la fenêtre ne peut pas être minimisée avec le bouton jaune.
   - Observé : le bouton jaune ne permet pas de minimiser la fenêtre.

Voici la capture :

![Fenêtre translucide de l'exercice 3](Capture%20d’écran%202026-10-01%20à%2020.12.50.png)