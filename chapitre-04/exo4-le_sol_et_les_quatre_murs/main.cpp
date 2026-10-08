#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Structure de donnees d'un mur.
struct Mur {
    string nom;
    long long xmin;
    long long xmax;
    long long zmin;
    long long zmax;
};

// Calcul de l'emprise d'un mur sur le sol.
Mur empriseDuMur(long long centreX, long long centreZ,
                 long long tailleX, long long tailleZ)
{
    Mur mur;
    mur.xmin = centreX - tailleX / 2;
    mur.xmax = centreX + tailleX / 2;
    mur.zmin = centreZ - tailleZ / 2;
    mur.zmax = centreZ + tailleZ / 2;
    return mur;
}

// Test si un mur contient tout le carre de l'angle.
bool murContientAngle(const Mur& mur,
                      long long angleXmin,
                      long long angleXmax,
                      long long angleZmin,
                      long long angleZmax)
{
    return mur.xmin <= angleXmin && mur.xmax >= angleXmax &&
           mur.zmin <= angleZmin && mur.zmax >= angleZmax;
}

int main()
{
    // Lecture de la taille du sol et de l'epaisseur des murs.
    long long coteSol = 0;
    long long epaisseur = 0;
    cin >> coteSol >> epaisseur;

    // Lecture du nombre de murs.
    int nombreMurs = 0;
    cin >> nombreMurs;

    // Stockage des murs.
    vector<Mur> murs;

    // Lecture de chaque mur et calcul de son emprise.
    for (int i = 0; i < nombreMurs; ++i) {
        string nom;
        long long centreX = 0;
        long long centreZ = 0;
        long long tailleX = 0;
        long long tailleZ = 0;

        cin >> nom >> centreX >> centreZ >> tailleX >> tailleZ;

        Mur mur = empriseDuMur(centreX, centreZ, tailleX, tailleZ);
        mur.nom = nom;
        murs.push_back(mur);

        cout << nom << ' ' << mur.xmin << ' ' << mur.xmax << ' '
             << mur.zmin << ' ' << mur.zmax << '\n';
    }

    // Demi-cote du sol et coordonnees de chaque angle.
    long long demiCote = coteSol / 2;
    long long angleXmin = -demiCote - epaisseur;
    long long angleXmax = -demiCote;
    long long angleZmin = -demiCote - epaisseur;
    long long angleZmax = -demiCote;

    // Angle FOND_GAUCHE.
    bool fondGauche = false;
    for (const Mur& mur : murs) {
        if (murContientAngle(mur, angleXmin, angleXmax,
                             angleZmin, angleZmax)) {
            fondGauche = true;
            break;
        }
    }
    cout << "FOND_GAUCHE " << (fondGauche ? "BOUCHE" : "TROU") << '\n';

    // Angle FOND_DROIT.
    angleXmin = demiCote;
    angleXmax = demiCote + epaisseur;
    angleZmin = -demiCote - epaisseur;
    angleZmax = -demiCote;

    bool fondDroit = false;
    for (const Mur& mur : murs) {
        if (murContientAngle(mur, angleXmin, angleXmax,
                             angleZmin, angleZmax)) {
            fondDroit = true;
            break;
        }
    }
    cout << "FOND_DROIT " << (fondDroit ? "BOUCHE" : "TROU") << '\n';

    // Angle ENTREE_GAUCHE.
    angleXmin = -demiCote - epaisseur;
    angleXmax = -demiCote;
    angleZmin = demiCote;
    angleZmax = demiCote + epaisseur;

    bool entreeGauche = false;
    for (const Mur& mur : murs) {
        if (murContientAngle(mur, angleXmin, angleXmax,
                             angleZmin, angleZmax)) {
            entreeGauche = true;
            break;
        }
    }
    cout << "ENTREE_GAUCHE " << (entreeGauche ? "BOUCHE" : "TROU") << '\n';

    // Angle ENTREE_DROIT.
    angleXmin = demiCote;
    angleXmax = demiCote + epaisseur;
    angleZmin = demiCote;
    angleZmax = demiCote + epaisseur;

    bool entreeDroit = false;
    for (const Mur& mur : murs) {
        if (murContientAngle(mur, angleXmin, angleXmax,
                             angleZmin, angleZmax)) {
            entreeDroit = true;
            break;
        }
    }
    cout << "ENTREE_DROIT " << (entreeDroit ? "BOUCHE" : "TROU") << '\n';

    // Nombre d'angles ouverts.
    int nombreTrous = 0;
    if (!fondGauche) nombreTrous++;
    if (!fondDroit) nombreTrous++;
    if (!entreeGauche) nombreTrous++;
    if (!entreeDroit) nombreTrous++;

    cout << "TROUS " << nombreTrous << '\n';

    return 0;
}
