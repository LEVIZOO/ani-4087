#include "MyClass.hpp"
#include <iostream>

#define WITH_FULL_CLASS

int main() {
    MyClass obj;
    std::cout << obj.getValue() << std::endl;
    return 0;
}