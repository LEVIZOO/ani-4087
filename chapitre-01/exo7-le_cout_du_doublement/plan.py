import pygame
import time

pygame.init()

ecran = pygame.display.set_mode((640, 480))

nb_img = 1000

temps_rendu = []

for i in range(nb_img):
    debut = time.perf_counter()
    ecran.fill((0, 0, 0))
    pygame.display.flip()
    pygame.display.flip()
    fin = time.perf_counter()

    duree = (fin - debut) * 1000
    temps_rendu.append(duree)

rendu_moyen = sum(temps_rendu) / len(temps_rendu)
rendu_max = max(temps_rendu)

print("Rendu moyen :", round(rendu_moyen, 2), "ms")
print("temps de rendu maximum :", round(rendu_max, 2), "ms")

budget = 11
rendu_fois_2 = rendu_moyen * 2
reste_budget = budget - rendu_fois_2
print("Ce qu'il reste pour le reste (logique, entrées, etc.) :", round(reste_budget, 2), "ms")

pygame.quit()