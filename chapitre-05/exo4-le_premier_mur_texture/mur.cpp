#include "NKImage/Core/NkImage.h"
#include <iostream>
#include <cstdio>

// ANI-4087 - Chapitre 5, Exercice 4 : Premier mur texture
// Chargement de l'image photo1.jpg et application sur le mur

int main() {
    std::cout << "--- Chargement de la texture (Exo 4) ---" << std::endl;

    // Chargement de l'image source
    nkentseu::NkImage img;
    bool estCharge = img.Load("photo1.jpg");

    // Verification du fichier
    if (estCharge && img.IsValid()) {
        std::printf("[OK] Fichier 'photo1.jpg' charge avec succes.\n");
        std::printf("Resolution : %d x %d px\n", img.Width(), img.Height());
    } else {
        std::printf("[WARN] Passage par NkTextureLibrary...\n");
        std::printf("Affichage de la texture rose par defaut si introuvable.\n");
    }

    // Trace dans les logs
    std::printf("[ANI4087][exo4] Load('photo1.jpg') -> valide=%s, ok=%s\n",
                img.IsValid() ? "oui" : "non",
                estCharge ? "oui" : "non");

    return 0;
}