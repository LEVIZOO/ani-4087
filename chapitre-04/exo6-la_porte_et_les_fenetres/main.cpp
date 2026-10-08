#include <iostream>
#include <string>

using namespace std;

// Aucun commentaire avec accent ou verbe conjugue.
// Chaque etape utilise une analyse simple et directe.

// Calcul de la profondeur de la face avant.
long long saillieAvant(long long profondeurCentre, long long epaisseur)
{
    return profondeurCentre + epaisseur / 2;
}

// Calcul de la profondeur de la face arriere.
long long saillieArriere(long long profondeurCentre, long long epaisseur)
{
    return profondeurCentre - epaisseur / 2;
}

int main()
{
    // Lecture de la taille du mur et du seuil.
    long long largeurMur = 0;
    long long hauteurMur = 0;
    long long seuil = 0;
    cin >> largeurMur >> hauteurMur >> seuil;

    // Lecture du nombre de panneaux.
    int nombrePanneaux = 0;
    cin >> nombrePanneaux;

    // Accumulation des resultats.
    int panneauxOK = 0;

    // Traitement de chaque panneau.
    for (int i = 0; i < nombrePanneaux; ++i) {
        string nom;
        long long centreLargeur = 0;
        long long centreHauteur = 0;
        long long largeur = 0;
        long long hauteur = 0;
        long long epaisseur = 0;
        long long profondeurCentre = 0;

        // Lecture du panneau.
        cin >> nom >> centreLargeur >> centreHauteur >> largeur >> hauteur
            >> epaisseur >> profondeurCentre;

        // Calcul des limites du panneau.
        long long gauche = centreLargeur - largeur / 2;
        long long droite = centreLargeur + largeur / 2;
        long long bas = centreHauteur - hauteur / 2;
        long long haut = centreHauteur + hauteur / 2;

        // Calcul des profondeurs des deux faces.
        long long faceAvant = saillieAvant(profondeurCentre, epaisseur);
        long long faceArriere = saillieArriere(profondeurCentre, epaisseur);

        // Saillie affichee pour tous les panneaux.
        long long saillie = faceAvant;

        // Verdict selon l'ordre impose.
        string verdict = "OK";

        // Debordement du mur.
        if (gauche < -largeurMur / 2 || droite > largeurMur / 2 ||
            bas < 0 || haut > hauteurMur) {
            verdict = "DEBORDE";
        } else if (saillie <= 0) {
            verdict = "INVISIBLE";
        } else if (saillie < seuil) {
            verdict = "CLIGNOTE";
        } else if (faceArriere > seuil) {
            verdict = "DECOLLE";
        }

        // Affichage du panneau, de sa saillie et de son verdict.
        cout << nom << ' ' << saillie << ' ' << verdict << '\n';

        // Compte des panneaux justes.
        if (verdict == "OK") {
            panneauxOK++;
        }
    }

    // Affichage des resultats de la verification.
    cout << "OK " << panneauxOK << '\n';
    cout << "A REPRENDRE " << nombrePanneaux - panneauxOK << '\n';

    return 0;
}
