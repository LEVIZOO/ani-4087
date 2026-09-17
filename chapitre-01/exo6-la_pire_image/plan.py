import pygame
import time

pygame.init()

ecran = pygame.display.set_mode((640, 480))
pygame.display.set_caption("Mesure des images")

nb_img = 1000
temps_img = []

for _ in range(nb_img):
    debut = time.perf_counter()
    ecran.fill((0, 0, 0))
    pygame.display.flip()
    fin = time.perf_counter()
    duree_ms = (fin - debut) * 1000
    temps_img.append(duree_ms)

pygame.quit()

pire_image = max(temps_img)
nb_depasment = sum(1 for t in temps_img if t > 11)

print(f"Image la plus longue : {pire_image:.2f} ms")
print(f"Nombre d'images > 11 ms : {nb_depasment} sur {nb_img}")