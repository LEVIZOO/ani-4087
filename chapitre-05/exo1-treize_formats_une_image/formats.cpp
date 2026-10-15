#include "NKImage/Core/NkImage.h"
#include <cstdio>

using namespace nkentseu;

// Taille du fichier sur le disque, en octets (-1 si le fichier n'existe pas)
static long TailleFichier(const char* chemin) {
    FILE* f = std::fopen(chemin, "rb");
    if (!f) return -1;
    std::fseek(f, 0, SEEK_END);
    long n = std::ftell(f);
    std::fclose(f);
    return n;
}

int main() {
    NkImage photo;
    if (!photo.Load("photo.jpg") || !photo.IsValid()) {
        std::printf("Impossible de charger photo.jpg\n");
        return 1;
    }
    std::printf("Photo : %d x %d\n", (int)photo.Width(), (int)photo.Height());

    // On fait ecrire la photo par le moteur dans cinq formats
    const char* noms[5]     = {"png", "jpeg", "bmp", "tga", "qoi"};
    const char* fichiers[5] = {"sortie.png", "sortie.jpg", "sortie.bmp", "sortie.tga", "sortie.qoi"};
    bool ecrit[5];
    ecrit[0] = photo.SavePNG(fichiers[0]);
    ecrit[1] = photo.SaveJPEG(fichiers[1]);
    ecrit[2] = photo.SaveBMP(fichiers[2]);
    ecrit[3] = photo.SaveTGA(fichiers[3]);
    ecrit[4] = photo.SaveQOI(fichiers[4]);

    FILE* sortie = std::fopen("formats.txt", "w");
    if (!sortie) return 1;

    // On relit chaque fichier dans un nouveau NkImage
    for (int i = 0; i < 5; ++i) {
        long octets = TailleFichier(fichiers[i]);
        if (octets < 0) octets = 0;
        NkImage relue;
        if (ecrit[i] && relue.Load(fichiers[i]) && relue.IsValid()) {
            std::fprintf(sortie, "%s : %ld octets, %d x %d\n",
                         noms[i], octets, (int)relue.Width(), (int)relue.Height());
        } else {
            std::fprintf(sortie, "%s : %ld octets, illisible\n", noms[i], octets);
        }
    }
    std::fclose(sortie);
    return 0;
}