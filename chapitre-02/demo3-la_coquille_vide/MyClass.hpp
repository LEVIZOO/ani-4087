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
