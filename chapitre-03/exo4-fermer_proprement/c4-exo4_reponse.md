# Exercice 4 — Fermer proprement

Le clic sur la croix déclenche `NkWindowCloseEvent` et met `running` à `false`. J'ai vérifié que la fenêtre se ferme.

La touche Échap déclenche `NkKeyPressEvent` et met aussi `running` à `false`. J'ai vérifié que la fenêtre se ferme également avec cette touche.

Dans les deux cas, la boucle s'arrête et le programme passe au même endroit : `window.Close()`, puis `return 0`. Les deux chemins se rejoignent pour que le nettoyage soit fait une seule fois, de la même façon.

![Fenêtre de l'exercice 4](Capture%20d’écran%202026-10-01%20à%2020.33.30.png)