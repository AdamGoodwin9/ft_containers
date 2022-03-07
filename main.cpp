#include <iostream>
#include <cstdlib>
#include <string>
#include "tests.hpp"

int main()
{
    std::cout << "Running using namespace: ";
#ifdef USE_STD
    std::cout << "std";
#else
    std::cout << "ft";
#endif
    std::cout << std::endl << std::endl;

    vectorTest();
    stackTest();
    mapTest();

    std::cout << std::endl << std::endl;
    return 0;
}
