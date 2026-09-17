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