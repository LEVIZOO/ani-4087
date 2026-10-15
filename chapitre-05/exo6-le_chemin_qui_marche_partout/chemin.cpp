#include "NKFileSystem/NkPath.h"
#include "NKContainers/String/NkString.h"
#include <cstdio>

using nkentseu::NkPath;
using nkentseu::NkString;

// Recherche de ressource sur 3 niveaux (Dossier courant, Executable, Parents)
static NkString LocateResource(const NkString &cheminRelatif) {
    auto existe = [](const char *p) -> bool {
        FILE *f = std::fopen(p, "rb");
        if (!f) return false;
        std::fclose(f);
        return true;
    };

    // 1. Dossier courant
    if (existe(cheminRelatif.CStr())) {
        return cheminRelatif;
    }

    // 2. Repertoire de l'executable
    NkPath exeDir = NkPath::GetExecutableDirectory();
    NkPath candidat = exeDir / cheminRelatif.CStr();
    if (existe(candidat.CStr())) {
        return candidat.ToString();
    }

    // 3. Remontee dans les dossiers parents (jusqu'a 4 niveaux)
    NkPath remonte = exeDir;
    for (int i = 0; i < 4; ++i) {
        remonte = remonte / "..";
        NkPath c2 = remonte / cheminRelatif.CStr();
        if (existe(c2.CStr())) {
            return c2.ToString();
        }
    }

    return NkString(""); // Retourne vide si introuvable
}

int main() {
    NkString cheminTrouve = LocateResource(NkString("photo1.jpg"));
    
    if (!cheminTrouve.Empty()) {
        std::printf("[SUCCESS] Ressource trouvee : %s\n", cheminTrouve.CStr());
    } else {
        std::printf("[ERREUR] Ressource 'photo1.jpg' introuvable.\n");
    }

    return 0;
}