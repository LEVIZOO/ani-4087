#include <cstdint>
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Valeur de chaque drapeau simple.
const unordered_map<string, uint32_t> DRAPEAUX = {
    {"RENDER2D", 1u},
    {"ANIMATION", 128u},
    {"RENDER3D", 2u},
    {"OVERLAY", 256u},
    {"TEXT", 4u},
    {"SIMULATION", 512u},
    {"UI", 8u},
    {"OFFSCREEN", 1024u},
    {"SHADOW", 16u},
    {"RAYTRACING", 2048u},
    {"POST_PROCESS", 32u},
    {"GPU_CULLING", 4096u},
    {"VFX", 64u},
    {"NONE", 0u},
    {"2D_ESSENTIALS", 1u | 4u},
    {"3D_BASE", 2u | 16u | 32u},
    {"DEBUG", 256u | 512u},
    {"ALL", 4294967295u},
};

// Liste des dependances dans l'ordre impose.
struct Dependance {
    string drapeau;
    vector<string> attentes;
};

// Nombre de bits actifs dans les drapeaux simples.
int compterDrapeauxActifs(uint32_t valeur)
{
    int nombre = 0;

    for (const auto& drapeau : DRAPEAUX) {
        if (drapeau.first == "NONE" || drapeau.first == "2D_ESSENTIALS" ||
            drapeau.first == "3D_BASE" || drapeau.first == "DEBUG" ||
            drapeau.first == "ALL") {
            continue;
        }

        if ((valeur & drapeau.second) != 0) {
            nombre++;
        }
    }

    return nombre;
}

// Verification si une dependance manque.
bool manqueDrapeau(uint32_t valeur, const string& drapeau)
{
    auto resultat = DRAPEAUX.find(drapeau);
    if (resultat == DRAPEAUX.end()) {
        return false;
    }

    return (valeur & resultat->second) == 0;
}

int main()
{
    // Lecture du nombre de noms fournis.
    int nombreNoms = 0;
    cin >> nombreNoms;

    // La valeur commence a zero.
    uint32_t valeur = 0u;

    // Lecture et ajout de chaque nom.
    for (int i = 0; i < nombreNoms; ++i) {
        string nom;
        cin >> nom;

        auto resultat = DRAPEAUX.find(nom);
        if (resultat == DRAPEAUX.end()) {
            cout << "INCONNU " << nom << '\n';
        } else {
            valeur |= resultat->second;
        }
    }

    // Le cas vide garde la valeur ALL.
    if (nombreNoms == 0) {
        valeur = 4294967295u;
    }

    // Affichage decimal et hexadecimal.
    cout << "VALEUR " << dec << valeur << '\n';
    cout << "HEXA 0x" << hex << uppercase << setw(8) << setfill('0')
         << static_cast<unsigned int>(valeur) << '\n';

    cout << dec;

    // Liste des dependances dans l'ordre impose.
    const vector<Dependance> dependances = {
        {"TEXT", {"RENDER2D"}},
        {"UI", {"RENDER2D", "TEXT"}},
        {"SHADOW", {"RENDER3D"}},
        {"OVERLAY", {"RENDER2D", "TEXT"}},
    };

    // Chaque drapeau allume ne reclame rien si sa dependance est presente.
    for (const Dependance& dependance : dependances) {
        if (manqueDrapeau(valeur, dependance.drapeau)) {
            continue;
        }

        for (const string& attente : dependance.attentes) {
            if (manqueDrapeau(valeur, attente)) {
                cout << "MANQUE " << dependance.drapeau << ' ' << attente << '\n';
            }
        }
    }

    // Nombre de drapeaux simples allumes.
    int allumes = compterDrapeauxActifs(valeur);
    int eteints = 13 - allumes;

    cout << "ALLUMES " << allumes << '\n';
    cout << "ETEINTS " << eteints << '\n';

    return 0;
}
