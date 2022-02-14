#include <vector>
#include <iostream>
#include <cstdlib>
#include "vector.hpp"
#include "Tests.hpp"

int main()
{
    std::cout << "==========================TESTING VECTOR====================================\n\n";
    vectorTest();
    std::cout << "\n\n==========================TESTING STACK====================================\n\n";
    stackTest();
    return 0;
}
