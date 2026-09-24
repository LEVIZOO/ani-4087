

J'ai fait 3 fichiers : `main.cpp` qui utilise `ModuleA`, et `ModuleA` qui utilise `ModuleB` (il appelle une fonction `getValueFromB()` qui est dans `ModuleB.cpp`).

D'abord j'ai construit avec les 3 fichiers, ça marchait, le programme affichait `Résultat : 43`.

Ensuite j'ai retiré `ModuleB.cpp` de la liste `files()` dans mon fichier `.jenga` (mais j'ai gardé le header `ModuleB.hpp`). J'ai relancé `jenga clean` puis `jenga build`.

# Le message d'erreur complet

```
Undefined symbols for architecture x86_64:
  "getValueFromB()", referenced from:
      getValueFromA() in src_ModuleA.o
ld: symbol(s) not found for architecture x86_64
clang++: error: linker command failed with exit code 1 (use -v to see invocation)
```

# À quelle étape ça appartient

Ça appartient à l'**édition de liens** (linker).

Ce qui m'a surpris, c'est que `ModuleA.cpp` et `main.cpp` ont compilé sans aucune erreur (`[1/2] Compiled: ModuleA.cpp`, `[2/2] Compiled: main.cpp`). Ça marche parce que le fichier `ModuleB.hpp` est toujours là, donc le compilateur sait que la fonction `getValueFromB()` existe et à quoi elle ressemble (son nom, son type de retour). Il n'a pas besoin du vrai code pour compiler, juste de la déclaration.

C'est seulement au moment de tout assembler ensemble en un seul programme (le linker) que ça casse, parce que le linker cherche le vrai code de `getValueFromB()` dans tous les fichiers `.o` compilés, et il ne le trouve nulle part puisque `ModuleB.cpp` n'a jamais été compilé.

Donc j'ai appris que compiler et lier, c'est deux choses différentes : compiler vérifie juste que le code a du sens avec les déclarations qu'il connaît, lier vérifie que tout ce qui est déclaré existe vraiment quelque part.