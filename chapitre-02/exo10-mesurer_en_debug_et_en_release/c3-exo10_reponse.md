J’ai écrit une boucle simple mais calculatoirement lourde, puis j’ai compilé le projet en Debug et en Release pour mesurer le temps d’exécution. J’ai corrigé deux erreurs importantes : il fallait inclure `<cmath>` pour `std::sqrt`, et il fallait que le fichier Jenga distingue vraiment Debug et Release avec `optimize` et `symbols`.

# Code testé

```cpp
#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>

int main() {
    const int iterations = 5000000;
    double total = 0.0;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < iterations; ++i) {
        total += std::sqrt(static_cast<double>(i + 1));
        total *= 1.00001;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "total=" << total << "\n";
    std::cout << "time_us=" << elapsed << "\n";
    return 0;
}
```

# Ce que le programme affiche

Le libellé `time_us` veut dire microsecondes.

Donc, si le programme dit `time_us=80049`, cela ne veut pas dire 80 049 ms. La conversion est :

```text
80 049 µs / 1000 = 80.049 ms
```

L’erreur venait du fait qu’on avait confondu microsecondes et millisecondes. La conversion correcte est :

```text
microsecondes / 1000 = millisecondes
```

# Fichier Jenga corrigé

```python
with project("MaSalle"):
    consoleapp()
    language("C++")
    location("MaSalle")
    files(["src/**.cpp"])

    with filter("config:Debug"):
        optimize("Off")
        symbols(True)

    with filter("config:Release"):
        optimize("Speed")
        symbols(False)
```

Sans cela, Debug et Release étaient à peu près identiques, ce qui ne permettait pas de comparer correctement.

# Résultat réel sur mon Mac

## Debug

```text
time_us=80049
```

Conversion :

```text
80049 µs / 1000 = 80.049 ms
```

Donc environ 80,0 ms.

## Release

```text
time_us=17872
```

Conversion :

```text
17872 µs / 1000 = 17.872 ms
```

Donc environ 17,9 ms.

# Comparaison

- Debug : environ 80,0 ms
- Release : environ 17,9 ms

On voit bien que la version Release est plus rapide. Mais elle n’est pas inférieure à 11 ms. Les deux valeurs dépassent 11 ms.

# Vérification sur plusieurs exécutions

J’ai relancé 5 fois la même exécution pour voir si le résultat bouge beaucoup.

## Debug

```text
77609 µs
151523 µs
114526 µs
110359 µs
131693 µs
```

## Release

```text
17137 µs
22423 µs
15307 µs
20245 µs
15783 µs
```

Le Release reste plus rapide, mais il y a du bruit d’exécution. Ce n’est pas une différence de 1 000 fois ; c’est une vraie différence de performance, mais pas une mesure “parfaite”.

# Conclusion

- `time_us` veut dire microsecondes, pas millisecondes ;
- la conversion correcte est : `µs / 1000 = ms` ;
- Debug et Release doivent être explicitement différenciés dans le fichier Jenga ;
- ici, Release est bien plus rapide, mais les deux valeurs sont au-dessus de 11 ms, donc la limite n’est pas respectée sur cette mesure.

C’est pour ça qu’il faut toujours garder l’unité collée au nombre et vérifier l’ordre de grandeur à la fin.
