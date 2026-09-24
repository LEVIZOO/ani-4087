# situation

J’ai pris le meme header, et je l’ai compilé 2 fois : une fois avec le `#define`, et une fois sans.

Le header est :

```cpp
#ifndef MYCLASS_HPP
#define MYCLASS_HPP

#ifdef WITH_FULL_CLASS
class MyClass {
public:
    int getValue() { return 42; }
};
#else
class MyClass {
    // coquille vide
};
#endif

#endif
```

## Version avec le define

```cpp
#define WITH_FULL_CLASS
#include "MyClass.hpp"

int main() {
    MyClass obj;
    return obj.getValue();
}
```

La compilation :

```bash
g++ -std=c++17 -Wall -Wextra avec_define.cpp -o /tmp/avec_define
```

Sortie :

```text
OK
```

Ici, `MyClass` est la vraie classe complete, avec `getValue()`.

## Version sans le define

```cpp
#include "MyClass.hpp"

int main() {
    MyClass obj;
    return 0;
}
```

La compilation :

```bash
g++ -std=c++17 -Wall -Wextra sans_define.cpp -o /tmp/sans_define
```

Sortie :

```text
warning: unused variable 'obj'
OK
```

Ici, `MyClass` est juste une coquille vide. Il n’a pas de `getValue()`.

## Ce que ça montre

Le meme header ne declare pas la meme classe selon qu’on a activé le `#define` ou pas.

Avec le define :

```cpp
class MyClass {
public:
    int getValue() { return 42; }
};
```

Sans le define :

```cpp
class MyClass {
    // coquille vide
};
```

Ce n’est pas la meme definition. C’est pour ca que le code peut sembler pareil dans le fichier, mais pas dans la realite.

## Pourquoi c’est le lieur qui proteste, pas le compilateur

Le compilateur traite chaque fichier source une fois, de maniere separée. Il ne voit pas tout l’ensemble du programme en meme temps.

Donc dans un fichier, si `WITH_FULL_CLASS` est defini, il compile avec la vraie classe. Dans l’autre fichier, s’il n’est pas defini, il compile avec la coquille vide.

Chaque fichier compile sans erreur, parce que chaque fichier est coherent en lui meme.

Le probleme arrive quand les objets compiles sont assemblés ensemble. C’est la phase du lieur qui met tous les morceaux ensemble. A ce moment, il se rend compte que les deux fichiers n’ont pas la meme definition de `MyClass`, et il proteste.

Donc le compilateur dit : "ok, chaque fichier est correct a moi".
Le lieur dit : "mais ces deux morceaux ne forment pas la meme classe, j’ai un probleme de coherence".

C’est pour ca que le lieur est le bon endroit pour voir le vrai probleme quand on manipule des defines qui changent la declaration d’une classe.

En gros :

- le define change la declaration du type ;
- le compilateur compile chaque un a part ;
- le lieur voit la contradiction quand il assemble tout.
