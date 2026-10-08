#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Structure de donnees d'un objet.
struct Objet {
    string nom;
    long long x;
    long long y;
    long long z;
    long long ecart;
};

// Calcul de la position obtenue avec l'ordre inverse.
// La multiplication et la division sont faites sur chaque axe.
Objet positionMauvaise(long long translationX,
                      long long translationY,
                      long long translationZ,
                      long long echelleX,
                      long long echelleY,
                      long long echelleZ)
{
    Objet objet;
    objet.x = (echelleX * translationX) / 1000;
    objet.y = (echelleY * translationY) / 1000;
    objet.z = (echelleZ * translationZ) / 1000;
    return objet;
}

// Calcul de la valeur absolue d'un nombre entier.
long long valeurAbsolue(long long nombre)
{
    if (nombre < 0) {
        return -nombre;
    }

    return nombre;
}

int main()
{
    // Lecture du nombre d'objets.
    int nombreObjets = 0;
    cin >> nombreObjets;

    // Accumulation des resultats.
    int objetsDeplaces = 0;
    long long pireEcart = 0;

    // Traitement de chaque objet.
    for (int i = 0; i < nombreObjets; ++i) {
        string nom;
        long long translationX = 0;
        long long translationY = 0;
        long long translationZ = 0;
        long long echelleX = 0;
        long long echelleY = 0;
        long long echelleZ = 0;

        // Lecture du nom et des huit valeurs de l'objet.
        cin >> nom >> translationX >> translationY >> translationZ
            >> echelleX >> echelleY >> echelleZ;

        // Position obtenue par le mauvais ordre.
        Objet objet = positionMauvaise(
            translationX,
            translationY,
            translationZ,
            echelleX,
            echelleY,
            echelleZ);

        // Position attendue par le bon ordre.
        long long bonneX = translationX;
        long long bonneY = translationY;
        long long bonneZ = translationZ;

        // Ecart de chaque axe en valeur absolue.
        long long ecartX = valeurAbsolue(bonneX - objet.x);
        long long ecartY = valeurAbsolue(bonneY - objet.y);
        long long ecartZ = valeurAbsolue(bonneZ - objet.z);

        // L'ecart retenu est le plus grand des trois ecarts.
        long long ecart = ecartX;
        if (ecartY > ecart) {
            ecart = ecartY;
        }
        if (ecartZ > ecart) {
            ecart = ecartZ;
        }

        // Affichage de la position obtenue et de l'ecart.
        cout << nom << ' ' << objet.x << ' ' << objet.y << ' ' << objet.z
             << ' ' << ecart << '\n';

        // Compte des objets dont la position est modifiee.
        if (ecart != 0) {
            objetsDeplaces++;
        }

        // Mise a jour du plus grand ecart.
        if (ecart > pireEcart) {
            pireEcart = ecart;
        }
    }

    // Affichage des deux lignes de bilan.
    cout << "DEPLACES " << objetsDeplaces << '\n';
    cout << "PIRE " << pireEcart << '\n';

    return 0;
}
