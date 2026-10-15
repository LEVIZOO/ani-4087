#include "NKImage/Core/NkImage.h"
#include <cstdio>

int main() {
    nkentseu::NkImage img;
    bool charge = img.Load("phoyo.jpg");
    std::printf("charge : %d, valide : %d, largeur : %d, hauteur : %d\n",
                charge ? 1 : 0, img.IsValid() ? 1 : 0, img.Width(), img.Height());
    return 0;
}