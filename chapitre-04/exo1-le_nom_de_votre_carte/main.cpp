#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

// Cette fonction reçoit la plateforme et les interfaces disponibles.
// Elle retourne la premiere interface de la plateforme qui est disponible.
string choisirInterface(const string& plateforme, const vector<string>& interfaces)
{
    // L'ordre depend de la plateforme.
    vector<string> ordre;

    if (plateforme == "WINDOWS") {
        ordre = {"VULKAN", "DX12", "DX11", "OPENGL", "SOFTWARE"};
    } else if (plateforme == "MACOS") {
        ordre = {"METAL", "OPENGL", "SOFTWARE"};
    } else if (plateforme == "IOS") {
        ordre = {"METAL", "SOFTWARE"};
    } else if (plateforme == "ANDROID") {
        ordre = {"VULKAN", "OPENGL", "SOFTWARE"};
    } else {
        // Pour une plateforme inconnue, on utilise l'ordre par défaut.
        ordre = {"VULKAN", "OPENGL", "SOFTWARE"};
    }

    // On cherche les interfaces dans l'ordre donné.
    for (const string& api : ordre) {
        for (const string& interfaceDisponible : interfaces) {
            if (api == interfaceDisponible) {
                return api;
            }
        }
    }

    // Si aucune interface n'est disponible, on utilise le rendu logiciel.
    return "SOFTWARE";
}

// Cette fonction transforme le nom technique en nom lisible.
string nomLisible(const string& api)
{
    if (api == "VULKAN") return "Vulkan";
    if (api == "DX12") return "DirectX 12";
    if (api == "DX11") return "DirectX 11";
    if (api == "OPENGL") return "OpenGL";
    if (api == "METAL") return "Metal";
    return "Software";
}

int main()
{
    // On lit le nombre de machines que le programme doit traiter.
    int nombreMachines = 0;
    cin >> nombreMachines;

    // Ces variables accumulent les resultats finaux.
    int interfacesIgnorees = 0;
    int machinesLogiciel = 0;
    set<string> nomsDistincts;

    // On traite chaque machine une par une.
    for (int i = 0; i < nombreMachines; ++i) {
        string nomMachine;
        string plateforme;
        int nombreInterfaces = 0;

        // Lecture du nom de la machine de sa plateforme et du nombre d'API.
        cin >> nomMachine;
        cin >> plateforme;
        cin >> nombreInterfaces;

        // Lecture de toutes les interfaces disponibles sur cette machine.
        vector<string> interfaces;
        for (int j = 0; j < nombreInterfaces; ++j) {
            string interfaceCourante;
            cin >> interfaceCourante;
            interfaces.push_back(interfaceCourante);
        }

        // On determine l'ordre des interfaces pour cette plateforme.
        vector<string> ordre;
        if (plateforme == "WINDOWS") {
            ordre = {"VULKAN", "DX12", "DX11", "OPENGL", "SOFTWARE"};
        } else if (plateforme == "MACOS") {
            ordre = {"METAL", "OPENGL", "SOFTWARE"};
        } else if (plateforme == "IOS") {
            ordre = {"METAL", "SOFTWARE"};
        } else if (plateforme == "ANDROID") {
            ordre = {"VULKAN", "OPENGL", "SOFTWARE"};
        } else {
            ordre = {"VULKAN", "OPENGL", "SOFTWARE"};
        }

        // On compte une interface ignore si elle existe mais n'est pas dans
        // l'ordre de la plateforme.
        for (const string& interfaceCourante : interfaces) {
            bool interfaceDansOrdre = false;

            for (const string& api : ordre) {
                if (interfaceCourante == api) {
                    interfaceDansOrdre = true;
                    break;
                }
            }

            if (!interfaceDansOrdre) {
                interfacesIgnorees++;
            }
        }

        // On choisit l'interface de la machine avec la fonction precedente.
        string interfaceChoisie = choisirInterface(plateforme, interfaces);
        string nomAffiche = nomLisible(interfaceChoisie);

        // On affiche le nom de la machine et l'interface choisie.
        cout << nomMachine << " " << nomAffiche << '\n';

        // On enregistre le nom affiche pour compter les noms différents.
        nomsDistincts.insert(nomAffiche);

        // On compte les machines qui utilise le rendu logiciel.
        if (interfaceChoisie == "SOFTWARE") {
            machinesLogiciel++;
        }
    }

    // On affiche les trois résultats finaux.
    cout << "IGNOREES " << interfacesIgnorees << '\n';
    cout << "LOGICIEL " << machinesLogiciel << '\n';
    cout << "DIFFERENTES " << nomsDistincts.size() << '\n';

    return 0;
}
