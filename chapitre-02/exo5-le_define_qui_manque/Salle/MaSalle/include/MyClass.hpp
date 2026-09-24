#ifndef MYCLASS_HPP
#define MYCLASS_HPP

// Decommente la ligne suivante pour avoir la classe complete
#define WITH_FULL_CLASS

#ifdef WITH_FULL_CLASS
class MyClass {
public:
    int getValue() { return 42; }
};
#else
class MyClass {
    // coquille vide : pas de membres
};
#endif

#endif