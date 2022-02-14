#include <vector>
#include <iostream>
#include <cstdlib>
#include "vector.hpp"
#include "Tests.hpp"

int main()
{
    std::cout << "Running using namespace: ";
#ifdef USE_STD
    std::cout << "std";
#else
    std::cout << "ft";
#endif
    std::cout << std::endl << std::endl;
    
    std::cout << "==========================TESTING VECTOR====================================\n\n";
    vectorTest();
    // std::cout << "==========================TESTING STACK=====================================\n\n";
    // stackTest();
    return 0;
}
