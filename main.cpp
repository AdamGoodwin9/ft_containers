#include <vector>
#include <iostream>
#include <cstdlib>
#include "vector.hpp"
#include "Tests.hpp"

int main()
{
    std::cout << "Running using namespace: \n";
#ifdef USE_STD
    std::cout << "std";
#else
    std::cout << "ft";
#endif
    std::cout << std::endl;
    
    vectorTest();

    return 0;
}
