# code

import pygame
import time

pygame.init()

ecran = pygame.display.set_mode((640, 480))

nb_img = 1000

temps_img = []

for i in range(nb_img):
    debut = time.time()
    ecran.fill((0, 0, 0))
    pygame.display.flip()
    fin = time.time()
    duree = (fin - debut) * 1000
    temps_img.append(duree)
    
    pygame.quit()
    
    pire_imge = max(temps_img)
    nb_depasment = 0
    for t in temps_img:
        if t > 11 :
            nb_depasment = nb_depasment + 1
            
            print("Image la plus longue :", round(pire_imge, 2), "ms")
print("Nombre d'images > 11 ms :", nb_depasment, "sur", nb_img) 


# resultat obtenue
Image la plus longue : 6.16 ms
Nombre d'images > 11 ms : 0 sur 1000
d'ou 
Pire image : 6,16 ms
 Images dépassant 11 ms : 0 sur 1000

# oui tiendra dans un casque 
pour ma part je connais pas beaucoup la VR mais Pour un casque qui tourne à 90 Hz, le budget par image est d'environ 11,1 ms comme on a vue a l'exo1. Comme ma pire image a pris 6,16 ms, le programme est resté ala limite 