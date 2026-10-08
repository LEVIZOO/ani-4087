#include <iostream>
#include <string>

using namespace std;

// Position du centre d'un objet.
struct Position {
    double x;
    double y;
    double z;
};

// Pose un objet sur le sol.
Position PoserAuSol(double x, double sy, double z)
{
    return {x, sy / 2.0, z};
}

// Pose un objet sur une surface a la hauteur H.
Position PoserSurTable(double x, double sy, double z, double H)
{
    return {x, H + sy / 2.0, z};
}

// Affiche le nom et le centre d'un objet.
void AfficherPosition(const string& nom, const Position& position)
{
    cout << nom << ' ' << position.x << ' ' << position.y << ' '
         << position.z << '\n';
}

int main()
{
    // Lit les dimensions et le centre de la table.
    double L, P, H, ep, pied, tx, tz;
    cin >> L >> P >> H >> ep >> pied >> tx >> tz;

    // Pose le plateau sur le haut des pieds.
    Position plateau = PoserSurTable(tx, ep, tz, H - ep);
    AfficherPosition("PLATEAU", plateau);

    // Calcule les ecarts entre le centre et les pieds.
    double ecartX = L / 2.0 - pied;
    double ecartZ = P / 2.0 - pied;
    double hauteurPied = H - ep;

    // Pose les pieds dans l'ordre demande.
    AfficherPosition("PIED", PoserAuSol(tx - ecartX, hauteurPied, tz - ecartZ));
    AfficherPosition("PIED", PoserAuSol(tx + ecartX, hauteurPied, tz - ecartZ));
    AfficherPosition("PIED", PoserAuSol(tx - ecartX, hauteurPied, tz + ecartZ));
    AfficherPosition("PIED", PoserAuSol(tx + ecartX, hauteurPied, tz + ecartZ));

    // Lit le nombre d'objets a poser.
    int nombreObjets;
    cin >> nombreObjets;

    // Lit et pose chaque objet.
    for (int i = 0; i < nombreObjets; ++i) {
        string nom;
        string ou;
        double sx, sy, sz, x, z;
        cin >> nom >> sx >> sy >> sz >> x >> z >> ou;

        Position position;
        if (ou == "SOL") {
            position = PoserAuSol(x, sy, z);
        } else {
            position = PoserSurTable(x, sy, z, H);
        }

        AfficherPosition(nom, position);
    }

    return 0;
}