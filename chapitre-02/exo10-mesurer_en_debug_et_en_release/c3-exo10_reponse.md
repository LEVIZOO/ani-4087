J’ai écrit une boucle simple mais calculatoirement lourde, puis j’ai compilé le projet en Debug puis en Release pour mesurer le temps d’exécution.

# Code testé

```cpp
#include <chrono>
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

# Résultat réel sur mon Mac

## Debug

```text
total=868407512.970346
time_us=1713889
```

Soit environ 1,71 ms.

## Release

```text
total=868407512.970346
time_us=1567371
```

Soit environ 1,57 ms.

# Comparaison

- Debug : environ 1,71 ms
- Release : environ 1,57 ms

La version Release est plus rapide, comme attendu.

# Mauvaise décision

Une image de casque dure 11 ms.

Ici, les deux valeurs sont bien inférieures à 11 ms. Donc, sur cette mesure, ni Debug ni Release ne dépasse la limite. Mais la mauvaise décision serait d’utiliser la mesure Debug comme base pour dire que le système est trop lent en production. Debug est plus pessimiste et ne reflète pas la vraie performance du programme optimisé.

# Conclusion

- Debug sert surtout au développement et au débogage,
- Release sert à la performance réelle,
- et si on doit prendre une décision sur le temps réel, il faut se baser sur Release, pas sur Debug.
