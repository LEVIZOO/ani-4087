#include <iostream>

int main() {
#ifdef FILTER_JUST_APPLIED
    std::cout << "DEFINITION_APPLIED" << std::endl;
#else
    std::cout << "DEFINITION_ABSENT" << std::endl;
#endif
    return 0;
}
