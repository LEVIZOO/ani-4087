// ANI-4087 - Chapitre 5, Exercice 5 : Quatre filtres, une mesure
#include "NKImage/Core/NkImage.h"
#include "NKTime/NkChrono.h"
#include <cstdio>
#include <cstring>
#include <utility>

using nkentseu::NkImage;
using nkentseu::NkResizeFilter;
using nkentseu::NkChrono;

int main() {
    NkImage imageSource;
    // Chargement direct du fichier photo1.jpg sous macOS
    if (!imageSource.Load("photo1.jpg")) {
        std::printf("[ERREUR] Impossible de charger l'image photo1.jpg\n");
        return 1;
    }
    std::printf("Image d'origine : %dx%d\n", imageSource.Width(), imageSource.Height());

    // Normalisation de la source de travail en 2048x2048
    NkImage travail = imageSource.Resize(2048, 2048, NkResizeFilter::NK_BILINEAR);
    std::printf("Image de travail generee : %dx%d\n", travail.Width(), travail.Height());

    struct ProfilFiltre {
        const char *label;
        NkResizeFilter algo;
        const char *fichierSortie;
    };

    ProfilFiltre listeFiltres[4] = {
        {"NK_NEAREST",  NkResizeFilter::NK_NEAREST,  "nearest.png"},
        {"NK_BILINEAR", NkResizeFilter::NK_BILINEAR, "bilinear.png"},
        {"NK_BICUBIC",  NkResizeFilter::NK_BICUBIC,  "bicubic.png"},
        {"NK_LANCZOS3", NkResizeFilter::NK_LANCZOS3, "lanczos3.png"},
    };

    NkImage sorties[4];
    double tempsMoyensUs[4];

    for (int idx = 0; idx < 4; ++idx) {
        // Exécution de chauffe (initialisation du cache et des structures internes)
        NkImage chauffe = travail.Resize(256, 256, listeFiltres[idx].algo);

        NkChrono horloge;
        horloge.Reset();
        NkImage renduFinal;

        // Mesure sur 20 réitérations
        for (int run = 0; run < 20; ++run) {
            renduFinal = travail.Resize(256, 256, listeFiltres[idx].algo);
        }
        const double dureeTotaleUs = horloge.Elapsed().ToMicroseconds();
        tempsMoyensUs[idx] = dureeTotaleUs / 20.0;

        sorties[idx] = std::move(renduFinal);
        sorties[idx].SavePNG(listeFiltres[idx].fichierSortie);
    }

    // Comparaison matricielle avec le filtre bilinéaire (indice 1)
    const NkImage &imageRef = sorties[1];
    long comptageDiff[4] = {0, 0, 0, 0};

    for (int idx = 0; idx < 4; ++idx) {
        long ecarts = 0;
        for (int y = 0; y < 256; ++y) {
            for (int x = 0; x < 256; ++x) {
                auto pxA = sorties[idx].GetPixel(x, y);
                auto pxB = imageRef.GetPixel(x, y);
                if (pxA.r != pxB.r || pxA.g != pxB.g || pxA.b != pxB.b || pxA.a != pxB.a) {
                    ecarts++;
                }
            }
        }
        comptageDiff[idx] = ecarts;
    }

    // Affichage des résultats du benchmark
    std::printf("--- Resultats du benchmark ---\n");
    for (int idx = 0; idx < 4; ++idx) {
        std::printf("%s : %.2f us, pixels differents : %ld\n",
                    listeFiltres[idx].label, tempsMoyensUs[idx], comptageDiff[idx]);
    }

    return 0;
}