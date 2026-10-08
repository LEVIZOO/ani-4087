#include <iostream>
#include <string>

using namespace std;

int main()
{
    int nombreCubes = 0;
    cin >> nombreCubes;

    int cubesVisibles = 0;

    for (int i = 0; i < nombreCubes; ++i) {
        string nom;
        long long drapeaux = 0;
        long long tailleX = 0;
        long long tailleY = 0;
        long long tailleZ = 0;
        long long distance = 0;
        long long lumiere = 0;
        long long ambiante = 0;
        long long planProche = 0;

        cin >> nom;
        cin >> drapeaux;
        cin >> tailleX;
        cin >> tailleY;
        cin >> tailleZ;
        cin >> distance;
        cin >> lumiere;
        cin >> ambiante;
        cin >> planProche;

        string verdict = "VISIBLE";

        // La première cause dans l'ordre doit être affichée.
        if ((drapeaux & 2LL) == 0) {
            verdict = "RENDER3D ETEINT";
        } else if (tailleX == 0 || tailleY == 0 || tailleZ == 0) {
            verdict = "ECHELLE NULLE";
        } else {
            // La face avant est à distance - tailleZ / 2 de la caméra.
            long long faceAvant = distance - tailleZ / 2;

            if (faceAvant <= 0) {
                verdict = "CAMERA DANS LE CUBE";
            } else if (faceAvant < planProche) {
                verdict = "COUPE PAR LE PLAN PROCHE";
            } else if (lumiere == 0 && ambiante == 0) {
                verdict = "PAS DE LUMIERE";
            }
        }

        cout << nom << " " << verdict << '\n';

        if (verdict == "VISIBLE") {
            cubesVisibles++;
        }
    }

    cout << "VISIBLES " << cubesVisibles << '\n';
    cout << "EN PANNE " << nombreCubes - cubesVisibles << '\n';

    return 0;
}
