# il ya  23 dépendances triées

J’ai pris la démonstration du moteur NKWindow comme base de référence. La liste ci-dessous classe les 23 dépendances en trois groupes : celles dont le rôle est immédiatement clair, celles dont j’ai une idée assez fiable, et celles que je ne comprenais pas avant d’ouvrir leur en-tête principal.

# 1) Celles dont le nom suffit à deviner le rôle

- NkWindow — la fenêtre principale du moteur.
- NkRenderer — le composant de rendu graphique.
- NkEvent — le système central des événements.
- NkSystem — le support du système d’exploitation et de ses services.
- NkCamera2D — la caméra 2D pour la vue de jeu ou d’interface.
- NkGamepadSystem — la gestion des manettes et des contrôleurs.
- NkDropSystem — la gestion des fichiers et contenus glissés dans la fenêtre.
- NkDialogs — la gestion des boîtes de dialogue système.

# 2) Celles dont j’ai une idée mais suis pas sur

- NkSurface — une surface de rendu ou de panneau de contenu.
- NkPlatformDetect — le code qui détecte la plateforme cible.
- NkWindowConfig — la configuration de la fenêtre.
- NkSafeArea — la zone de sécurité d’écran, surtout utile sur mobile.
- NkEntry — le point d’entrée du programme ou du moteur.
- NkEventSystem — le système qui distribue les événements.
- NkTypedEvents — les événements typés et structurés.
- NkEventTypes — les types enumérés et structures du système d’événements.

# 3) Celles que je ne savais pas, et que j’ai expliquées en ouvrant leur en-tête principal

- NkKeycodeMap — ce module convertit les codes clavier natifs de chaque plateforme vers un jeu de touches cross-platform, ce qui permet de traiter les entrées indépendamment du layout clavier.
- NkWindowEvents — ce fichier décrit les événements spécifiques à la fenêtre, comme création, fermeture, redimensionnement, déplacement, focus, DPI, thème et visibilité.
- NkMouseEvents — ce module encode les événements de souris, y compris déplacement, boutons, molette, entrée/sortie et capture, avec des données précises sur les coordonnées et les modificateurs.
- NkKeyboardEvents — ce module définit les événements clavier et le texte saisi, en distinguant la touche logique, le scancode matériel et le caractère Unicode produit.
- NkTouchEvents — ce fichier couvre les événements tactiles multi-touch ainsi que les gestes courants comme pinch, rotate, pan, swipe et tap.
- NkGamepadEvents — ce module formalise les événements de manette, avec informations de connexion, boutons, axes, état complet et vibration.
- NkDropEvents — ce module gère les événements de drag-and-drop, notamment fichiers, texte, images et changements de système autour du dépôt de contenu.

# d'ou

Le point important est que le moteur présente une architecture très cohérente :

- des modules “moteur” et de fondation,
- des modules “événements” très typés,
- puis des sous-structures de données qui décrivent précisément chaque type d’entrée ou de système.


