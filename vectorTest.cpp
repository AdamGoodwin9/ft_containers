#include <iostream>
#include "Tests.hpp"
#include "stack.hpp"

void vectorPrint(lib::vector<int> v)
{
    std::cout << "Vector contains:";
    for (lib::vector<int>::iterator it = v.begin(); it < v.end(); it++)
    {
        std::cout << " " << *it;
    }
    std::cout << '\n';
}

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

void vectorModifiers()
{
    lib::vector<int> myvector(3, 100);
    lib::vector<int> myvector2(3, 100);
    // 100 100 100
    lib::vector<int>::iterator it;

    vectorPrint(myvector);

    it = myvector.begin();
    it = myvector.insert(it, 200);
    // 200 100 100 100
    vectorPrint(myvector);

    myvector.insert(it, 2, 300);
    // 300 300 200 100 100
    vectorPrint(myvector);

    // "it" no longer valid, get a new one:
    it = myvector.begin();

    lib::vector<int> anothervector(2, 400);
    myvector.insert(it + 2, anothervector.begin(), anothervector.end());
    // 300 300 400 400 200 100 100 100
    vectorPrint(myvector);

    int myarray[] = {501, 502, 503};
    myvector.insert(myvector.begin(), myarray, myarray + 3);
    // 501 502 503 300 300 400 400 200 100 100 100
    vectorPrint(myvector);
    std::cout << (myvector2 > myvector) << "\n";
    std::cout << (myvector2 >= myvector) << "\n";
    std::cout << (myvector2 < myvector) << "\n";
    std::cout << (myvector2 <= myvector) << "\n";
    std::cout << (myvector2 == myvector) << "\n";
}

void vectorTest()
{
    vectorModifiers();
    // vectorIterators();
    // vectorCapacity();
}

