J’ai lancé la commande et j’ai recupéré ce que Jenga me dit sur ma machine.

```bash
source /Users/levizoonyaba/Documents/Jenga/.venv/bin/activate && cd /Users/levizoonyaba/Documents/Jenga/Jenga/Exemples/24_all_platforms && jenga info -v
```

Voila le tableau complet `Available Toolchains` :

```text
Available Toolchains
------------------------------------------------------------
Name               Family        Target OS   Arch     Env
===========================================================
host-apple-clang   apple-clang   macOS       x86_64   gnu
clang-mingw        clang         Windows     x86_64   mingw
```

# Ce qu’il y a sur mon Mac

J’ai bien :

- `host-apple-clang`
  - c’est le toolchain natif du Mac
  - il cible `macOS`
  - architecture : `x86_64`

- `clang-mingw`
  - c’est un toolchain pour `Windows`
  - architecture : `x86_64`
  - il est present, donc Jenga sait faire un peu de Windows aussi

# Ce qu’il manque

Il manque quand meme les cibles plus specifiques qui ne sont pas la machine hote ni le Windows minimal.

Il manque notamment :

- `zig-linux-x64` pour Linux
- `android-ndk` pour Android
- `emscripten` pour le Web

Donc si je veux compiler les projets pour Linux, Android ou Web, il me faut installer les bons toolchains.

# Ce que ça veut dire

Mon ordi est un Mac, donc il a bien le toolchain du Mac. Il a aussi un peu de support pour Windows via `clang-mingw`.

Mais il n’a pas les outils pour faire du Linux cross-compile, pas de NDK Android, et pas d’Emscripten pour le Web. Donc le projet multi-plateforme ne peut pas tout construire d’un coup sur cette machine sans installer des choses supplementaires.

# Conclusion

Le tableau est assez parlant. Il dit bien ce qu’il y a et ce qu’il manque. Sur ma machine, il y a juste le Mac et un peu de Windows. Il manque le Linux, le Android et le Web.

Donc, si tout manque, il faut installer les toolchains correspondants. Ici, ce n’est pas tout qui manque, mais il manque quand meme les outils pour les autres plateformes.

J’ai aussi vu qu’on est sur macOS, donc le point important c’est que Jenga a bien detecte la machine hote, et il sait qu’on est pas sur Windows ou Linux natif. C’est pour ça qu’on ne voit pas tout.
