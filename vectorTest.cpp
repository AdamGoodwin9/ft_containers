#include <iostream>
#include <vector>
#include "vector.hpp"

void vectorIterators()
{
    lib::vector<int> v;
    for (int i = 1; i <= 5; i++)
    {
        v.push_back(i);
    }

    lib::vector<int>::iterator i;
    std::cout << "Looping from begin to end: ";
    for (i = v.begin(); i != v.end(); i++)
    {
        std::cout << *i << " ";
    }
    std::cout << std::endl;

    lib::vector<int>::reverse_iterator ri;
    std::cout << "Looping from rbegin to rend: ";
    for (ri = v.rbegin(); ri != v.rend(); ri++)
    {
        std::cout << *ri << " ";
    }
    std::cout << std::endl;
}

void vectorCapacity()
{
    lib::vector<int> v;
    for (int i = 1; i <= 20; i++)
    {
        std::cout << v.capacity() << " ";
        v.push_back(i);
    }
    std::cout << std::endl;
}

void vectorTest()
{
    vectorIterators();
    vectorCapacity();
}