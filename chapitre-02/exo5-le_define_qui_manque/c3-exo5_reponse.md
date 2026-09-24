# Exercice 5

Le problème venait du `#define`.

Dans [chapitre-02/exo5-le_define_qui_manque/Salle/MaSalle/include/MyClass.hpp](chapitre-02/exo5-le_define_qui_manque/Salle/MaSalle/include/MyClass.hpp), la classe n'est complète que si `WITH_FULL_CLASS` est défini.

Sans ça, on tombe dans le `else` et la classe est vide.

Donc le compilateur dit :

```text
error: no member named 'getValue' in 'MyClass'
```

J'ai activé la définition pour que la classe contienne la méthode :

```cpp
#define WITH_FULL_CLASS
```

Ensuite, le programme a compilé et a affiché :

```text
42
```

Conclusion : le `define` manquait, donc la méthode n'existait pas dans la classe.
