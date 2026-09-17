
# 1. Schéma de la barre temporelle (20 ms au total)

Budget total d'une trame à 50 Hz : 20.0 ms


etape	VSync 	Input 	Game Loop 	Render 	Wait 	

temps	1.0ms	4.5ms	2.5ms  	3.0ms 	 0.0ms	





1. VSync (Synchronisation verticale)
Valeur mesurée : 1,0 à 8,3 ms
Source technique : Apple Developer, iOS DisplayLink
Explication : C’est le temps d’attente du signal de l’écran pour aligner l’affichage sur la fréquence de rafraîchissement. En pratique, cela dépend surtout de la vitesse de rafraîchissement, comme 60 Hz ou 120 Hz.

2. Input (Gestion des entrées)
Valeur mesurée : 4,0 à 8,0 ms
Source technique : Google AOSP, Android Input Latency
Explication : Le système met ce temps à détecter l’action du joueur, qu’il s’agisse d’un toucher ou d’un bouton, puis à la transmettre à l’application.

3. Game Loop (Boucle de jeu)
Valeur mesurée : Introuvable
Source technique : Aucune
Explication : Il n’existe pas de valeur universelle pour cette étape, car elle dépend entièrement du code du jeu, de la physique, des collisions et de la logique de calcul.
fait : jai donc mis une qui me semble rationnelle

4. Render (Préparation du rendu)
Valeur mesurée : 3,0 à 5,0 ms
Source technique : Unreal Engine, Render Thread
Explication : Le processeur prépare les informations nécessaires au dessin, organise les commandes et les envoie ensuite à la carte graphique pour le rendu final.

5. wait ou Swap Buffers (Échange d’affichages)
Valeur mesurée : 0,1 à 2,0 ms
Source technique : NVIDIA Developer, Vulkan / OpenGL
Explication : Cette étape correspond au moment où la nouvelle image calculée remplace l’ancienne pour être affichée à l’écran.


