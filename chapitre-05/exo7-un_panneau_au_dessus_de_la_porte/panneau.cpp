// ANI-4087 - Chapitre 5, Exercice 7 : Un panneau au-dessus de la porte
// Génération et rastérisation manuelle du texte "Sortie" à partir de l'atlas de police Inter (32px).

#include "NKFont/NkFont.h"
#include "NKFont/Embedded/NkFontEmbedded.h"
#include "NKImage/Core/NkImage.h"
#include <cstdio>

using namespace nkentseu;

int main() {
    // 1. Initialisation de l'atlas de police Inter
    NkFontAtlas atlas;
    NkFont *police = NkFontEmbedded::AddToAtlas(atlas, NkEmbeddedFontId::Inter, 32.f);
    if (!police || !atlas.Build()) {
        std::fprintf(stderr, "[ERREUR] Impossible d'initialiser l'atlas avec la police Inter.\n");
        return 1;
    }

    // 2. Extraction du tampon de la texture (Alpha 8 bits)
    uint8 *atlasPixels = nullptr;
    int32 atlasW = 0, atlasH = 0;
    atlas.GetTexDataAsAlpha8(&atlasPixels, &atlasW, &atlasH);
    if (!atlasPixels || atlasW <= 0 || atlasH <= 0) {
        std::fprintf(stderr, "[ERREUR] Données d'atlas invalides.\n");
        return 1;
    }
    std::printf("atlas : %d x %d\n", atlasW, atlasH);

    // 3. Calcul des métriques pour le mot "Sortie"
    const char *mot = "Sortie";
    const int32 nbLettres = 6;

    float32 largeurCumulee = 0.f;
    for (int32 i = 0; i < nbLettres; ++i) {
        const NkFontGlyph *g = police->FindGlyph((NkFontCodepoint)(unsigned char)mot[i]);
        if (!g) {
            std::fprintf(stderr, "[ERREUR] Glyphe non trouvé pour '%c'\n", mot[i]);
            return 1;
        }
        largeurCumulee += g->advanceX;
    }

    const int32 largeur = (int32)(largeurCumulee + 0.5f);
    const int32 hauteur = (int32)(police->ascent - police->descent + 0.5f);
    std::printf("image : %d x %d\n", largeur, hauteur);

    // 4. Création de l'image du panneau (Fond bleu nuit / Texte blanc cassé)
    const math::NkColor fond(0x10, 0x20, 0x3C, 0xFF);
    const math::NkColor texte(0xF2, 0xF2, 0xF0, 0xFF);
    const uint32 fondPacked = 0x10203CFFu;

    NkImage panneau = NkImage::Create((uint32)largeur, (uint32)hauteur, 4, fondPacked);
    if (!panneau.IsValid()) {
        return 1;
    }

    // 5. Copie pixel par pixel de chaque lettre dans l'image
    const float32 ligneDeBase = police->ascent;
    float32 curseurX = 0.f;

    for (int32 i = 0; i < nbLettres; ++i) {
        const NkFontGlyph *g = police->FindGlyph((NkFontCodepoint)(unsigned char)mot[i]);

        const float32 rx0 = curseurX + g->x0;
        const float32 ry0 = ligneDeBase + g->y0;
        const float32 rx1 = curseurX + g->x1;
        const float32 ry1 = ligneDeBase + g->y1;
        const float32 rw = rx1 - rx0;
        const float32 rh = ry1 - ry0;

        if (rw > 0.f && rh > 0.f) {
            const int32 xStart = (int32)rx0;
            const int32 yStart = (int32)ry0;
            const int32 xEnd = (int32)(rx1 + 0.999f);
            const int32 yEnd = (int32)(ry1 + 0.999f);

            for (int32 py = yStart; py < yEnd; ++py) {
                if (py < 0 || py >= hauteur) continue;
                for (int32 px = xStart; px < xEnd; ++px) {
                    if (px < 0 || px >= largeur) continue;

                    const float32 fx = ((float32)px + 0.5f - rx0) / rw;
                    const float32 fy = ((float32)py + 0.5f - ry0) / rh;

                    const float32 u = g->u0 + fx * (g->u1 - g->u0);
                    const float32 v = g->v0 + fy * (g->v1 - g->v0);

                    int32 ax = (int32)(u * (float32)atlasW);
                    int32 ay = (int32)(v * (float32)atlasH);

                    if (ax < 0) ax = 0;
                    if (ax >= atlasW) ax = atlasW - 1;
                    if (ay < 0) ay = 0;
                    if (ay >= atlasH) ay = atlasH - 1;

                    const uint8 alpha = atlasPixels[ay * atlasW + ax];
                    const float32 factor = (float32)alpha / 255.f;

                    math::NkColor pixelCouleur(
                        (uint8)(fond.r + factor * ((float32)texte.r - (float32)fond.r)),
                        (uint8)(fond.g + factor * ((float32)texte.g - (float32)fond.g)),
                        (uint8)(fond.b + factor * ((float32)texte.b - (float32)fond.b)),
                        255);

                    panneau.SetPixel(px, py, pixelCouleur);
                }
            }
        }
        curseurX += g->advanceX;
    }

    // Sauvegarde du fichier final
    if (!panneau.SavePNG("panneau.png")) {
        std::fprintf(stderr, "[ERREUR] Échec lors de la création de 'panneau.png'\n");
        return 1;
    }

    std::printf("panneau.png généré avec succès : %d x %d\n", largeur, hauteur);
    return 0;
}