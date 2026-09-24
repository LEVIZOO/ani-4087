


J'ai fait un filtre avec une condition fausse, puis une condition vraie.

Le but est de prouver que le filtre ne s'applique pas quand il est faux, et qu'il s'applique quand il est vrai.

# Le fichier Jenga

```python
with filter("system:Windows"):
    defines(["FILTER_JUST_APPLIED"])
```

Quand la condition est fausse, le define n'est pas ajouté.

Et quand on met :

```python
with filter("system:macOS"):
    defines(["FILTER_JUST_APPLIED"])
```

le define est ajouté.

# Le main.cpp

```cpp
#include <iostream>

int main() {
#ifdef FILTER_JUST_APPLIED
    std::cout << "DEFINITION_APPLIED" << std::endl;
#else
    std::cout << "DEFINITION_ABSENT" << std::endl;
#endif
    return 0;
}
```

Le programme affiche :

- `DEFINITION_ABSENT` si le filtre est faux
- `DEFINITION_APPLIED` si le filtre est vrai

# EXEMPLE

# Cas faux

```text
DEFINITION_ABSENT
```

# Cas vrai

```text
DEFINITION_APPLIED
```

Donc, le filtre ne s'active pas quand la condition est fausse, et il s'active quand la condition est vraie.

C'est toute la preuve de l'exercice.
