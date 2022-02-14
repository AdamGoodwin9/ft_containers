#include <iostream>
#include "Tests.hpp"

void vectorPrint(lib::vector<int> v)
{
    std::cout << "Vector contains:";
    for (lib::vector<int>::iterator it=v.begin(); it < v.end(); it++)
    {
        std::cout << " " << *it;
    }
    std::cout << '\n';
}

void vectorIterators()
{
    std::cout << "BEGIN END / RBEGIN REND TEST\n";
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
    std::cout << "-\n";

    lib::vector<int>::reverse_iterator ri;
    std::cout << "Looping from rbegin to rend: ";
    for (ri = v.rbegin(); ri != v.rend(); ri++)
    {
        std::cout << *ri << " ";
    }
    std::cout << "-\n\n";
}

void vectorCapacity()
{
    std::cout << "SIZE TEST\n";
    lib::vector<int> myints;
    std::cout << "0. size: " << myints.size() << '\n';
    for (int i=0; i<10; i++) myints.push_back(i);
    std::cout << "1. size: " << myints.size() << '\n';

    myints.insert (myints.end(),10,100);
    std::cout << "2. size: " << myints.size() << '\n';

    myints.pop_back();
    std::cout << "3. size: " << myints.size() << '\n';

    
    std::cout << "\nMAX_SIZE / CAPACITY TEST\n";
    lib::vector<int> myvector;
    // set some content in the vector:
    for (int i=0; i<100; i++) myvector.push_back(i);

    std::cout << "size: " << myvector.size() << "\n";
    std::cout << "capacity: " << myvector.capacity() << "\n";
    std::cout << "max_size: " << myvector.max_size() << "\n";


    std::cout << "\nRESIZE TEST\n";
    lib::vector<int> resizer;

    // set some initial content:
    for (int i=1;i<10;i++) resizer.push_back(i);

    resizer.resize(5);
    resizer.resize(8,100);
    resizer.resize(12);

    std::cout << "myvector contains:";
    for (size_t i = 0; i < resizer.size(); i++)
        std::cout << ' ' << resizer[i];
    std::cout << '\n';


    std::cout << "\nEMPTY TEST\n";
    lib::vector<int> emptier;
    int sum (0);

    for (int i=1;i<=10;i++) emptier.push_back(i);

    while (!emptier.empty())
    {
        sum += emptier.back();
        emptier.pop_back();
    }

    std::cout << "total: " << sum << '\n';


    std::cout << "\nRESERVE TEST\n";
    lib::vector<int>::size_type sz;

    lib::vector<int> foo;
    sz = foo.capacity();
    std::cout << "making foo grow:\n";
    for (int i = 0; i < 100; ++i) {
        foo.push_back(i);
        if (sz != foo.capacity()) {
            sz = foo.capacity();
            std::cout << "capacity changed: " << sz << '\n';
        }
    }

    lib::vector<int> bar;
    sz = bar.capacity();
    bar.reserve(100);   // this is the only difference with foo above
    std::cout << "making bar grow:\n";
    for (int i = 0; i < 100; ++i) {
        bar.push_back(i);
        if (sz!=bar.capacity()) {
            sz = bar.capacity();
            std::cout << "capacity changed: " << sz << '\n';
        }
    }
}

void vectorElementAccess()
{
    std::cout << "OPERATOR[] TEST\n";
    lib::vector<int> subscriptor (10);   // 10 zero-initialized elements

    lib::vector<int>::size_type sz = subscriptor.size();

    // assign some values:
    for (unsigned i=0; i<sz; i++) subscriptor[i]=i;

    // reverse vector using operator[]:
    for (unsigned i=0; i<sz/2; i++)
    {
        int temp;
        temp = subscriptor[sz-1-i];
        subscriptor[sz-1-i]=subscriptor[i];
        subscriptor[i]=temp;
    }

    std::cout << "myvector contains:";
    for (unsigned i=0; i<sz; i++)
        std::cout << ' ' << subscriptor[i];
    std::cout << "-\n\n";


    std::cout << "AT TEST\n";
    lib::vector<int> myvector (10);   // 10 zero-initialized ints

    // assign some values:
    for (unsigned i=0; i<myvector.size(); i++)
        myvector.at(i)=i;

    std::cout << "myvector contains:";
    for (unsigned i=0; i<myvector.size(); i++)
        std::cout << ' ' << myvector.at(i);
    std::cout << "-\n\n";


    std::cout << "FRONT TEST\n";
    lib::vector<int> fronter;

    fronter.push_back(78);
    fronter.push_back(16);
    // now front equals 78, and back 16

    fronter.front() -= fronter.back();
    std::cout << "myvector.front() is now " << fronter.front() << "\n\n";


    std::cout << "BACK TEST\n";
    lib::vector<int> backer;

    backer.push_back(10);

    while (backer.back() != 0)
    {
        backer.push_back ( backer.back() -1 );
    }

    std::cout << "myvector contains:";
    for (unsigned i=0; i<backer.size() ; i++)
        std::cout << ' ' << backer[i];
    std::cout << "-\n\n";
}

void vectorModifiers()
{
    std::cout << "ASSIGN TEST\n";
    lib::vector<int> first;
    lib::vector<int> second;
    lib::vector<int> third;

    first.assign (7,100);             // 7 ints with a value of 100

    lib::vector<int>::iterator assignit;
    assignit=first.begin()+1;

    second.assign (assignit,first.end()-1); // the 5 central values of first

    int myints[] = {1776,7,4};
    third.assign (myints,myints+3);   // assigning from array.

    std::cout << "Size of first: " << int (first.size()) << '\n';
    std::cout << "Size of second: " << int (second.size()) << '\n';
    std::cout << "Size of third: " << int (third.size()) << "\n\n";


    std::cout << "PUSH_BACK TEST\n";
    lib::vector<int> push_backer;
    int myint;

    std::cout << "Please enter some integers (enter 0 to end):\n";

    do {
        std::cin >> myint;
        push_backer.push_back (myint);
    } while (myint);
    std::cout << "myvector stores " << int(push_backer.size()) << " numbers.\n\n";


    std::cout << "POP_BACK TEST\n";
    lib::vector<int> pop_backer;
    int sum (0);
    pop_backer.push_back (100);
    pop_backer.push_back (200);
    pop_backer.push_back (300);

    while (!pop_backer.empty())
    {
        sum+=pop_backer.back();
        pop_backer.pop_back();
    }

    std::cout << "The elements of myvector add up to " << sum << '\n';


    std::cout << "INSERT TEST\n";
    lib::vector<int> myvector (3, 100);
    // 100 100 100
    lib::vector<int>::iterator insertit;

    vectorPrint(myvector);

    insertit = myvector.begin();
    insertit = myvector.insert (insertit, 200);
    // 200 100 100 100
    vectorPrint(myvector);

    myvector.insert (insertit, 2, 300);
    // 300 300 200 100 100
    vectorPrint(myvector);

    // "it" no longer valid, get a new one:
    insertit = myvector.begin();

    lib::vector<int> anothervector (2, 400);
    myvector.insert (insertit + 2, anothervector.begin(), anothervector.end());
    //300 300 400 400 200 100 100 100
    vectorPrint(myvector);

    int myarray [] = { 501,502,503 };
    myvector.insert (myvector.begin(), myarray, myarray + 3);
    //501 502 503 300 300 400 400 200 100 100 100
    vectorPrint(myvector);
    std::cout << "\n";

    std::cout << "ERASE TEST\n";



    std::cout << "SWAP TEST\n";



    std::cout << "CLEAR TEST\n";
}

void vectorTest()
{
    // vectorIterators();
    // vectorCapacity();
    //vectorElementAccess();
    vectorModifiers();
}