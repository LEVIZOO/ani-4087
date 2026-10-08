#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Conversion de la hauteur du centre en hauteur du bas.
long long hauteurDuBas(long long taille, long long centre)
{
    return centre - taille / 2;
}

// Conversion de la hauteur du centre en hauteur du haut.
long long hauteurDuHaut(long long taille, long long centre)
{
    return centre + taille / 2;
}

// Choix du verdict selon l'ordre impose.
string verdictDuCube(long long haut, long long bas)
{
    if (haut <= 0) {
        return "SOUS LE SOL";
    }

    if (bas < 0) {
        return "ENTERRE";
    }

    if (bas == 0) {
        return "POSE";
    }

    return "FLOTTE";
}

// Calcul de la hauteur du centre pour poser le cube.
long long hauteurPourPoser(long long taille)
{
    return taille / 2;
}

int main()
{
    // Lecture du nombre de cubes.
    int nombreCubes = 0;
    cin >> nombreCubes;

    // Accumulation des resultats.
    int cubesACorriger = 0;
    long long pireDistance = 0;

    // Traitement de chaque cube.
    for (int i = 0; i < nombreCubes; ++i) {
        string nom;
        long long taille = 0;
        long long centre = 0;

        // Lecture du nom, de l'echelle et de la hauteur du centre.
        cin >> nom;
        cin >> taille;
        cin >> centre;

        // Calcul des hauteurs du bas et du haut.
        long long bas = hauteurDuBas(taille, centre);
        long long haut = hauteurDuHaut(taille, centre);
        string verdict = verdictDuCube(haut, bas);

        // Affichage d'une ligne par cube.
        cout << nom << ' ' << bas << ' ' << haut << ' ' << verdict << ' '
             << hauteurPourPoser(taille) << '\n';

        // Compte des cubes qui ne sont pas poses sur le sol.
        if (verdict != "POSE") {
            cubesACorriger++;
        }

        // Distance entre le bas du cube et le sol en valeur absolue.
        long long distanceAuSol = abs(bas);
        if (distanceAuSol > pireDistance) {
            pireDistance = distanceAuSol;
        }
    }

    // Affichage des bilans.
    cout << "A CORRIGER " << cubesACorriger << '\n';
    cout << "PIRE " << pireDistance << '\n';

    return 0;
}
