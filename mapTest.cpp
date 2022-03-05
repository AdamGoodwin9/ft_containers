#include "Tests.hpp"

void mapIterators()
{
    std::cout << "BEGIN / END TEST\n";
    lib::map<char, int> iterate;

    iterate['b'] = 100;
    iterate['a'] = 200;
    iterate['c'] = 300;

    for (lib::map<char, int>::iterator it = iterate.begin(); it != iterate.end(); ++it)
        std::cout << it->first << " => " << it->second << '\n';

    std::cout << "\nRBEGIN / REND TEST\n";
    lib::map<char, int> reverser;

    reverser['x'] = 100;
    reverser['y'] = 200;
    reverser['z'] = 300;

    lib::map<char, int>::reverse_iterator rit;
    for (rit = reverser.rbegin(); rit != reverser.rend(); ++rit)
        std::cout << rit->first << " => " << rit->second << '\n';
}

void mapCapacity()
{
    std::cout << "\nEMPTY TEST\n";
    lib::map<char, int> emptier;

    emptier['a'] = 10;
    emptier['b'] = 20;
    emptier['c'] = 30;

    while (!emptier.empty())
    {
        std::cout << emptier.begin()->first << " => " << emptier.begin()->second << '\n';
        emptier.erase(emptier.begin());
    }

    std::cout << "\nSIZE TEST\n";
    lib::map<char, int> sizer;
    sizer['a'] = 101;
    sizer['b'] = 202;
    sizer['c'] = 302;

    std::cout << "sizer.size() is " << sizer.size() << '\n';

    std::cout << "\nMAX_SIZE TEST\n";
    int i;
    lib::map<int, int> max;

    if (max.max_size() > 1000)
    {
        for (i = 0; i < 1000; i++)
            max[i] = 0;
        std::cout << "The map contains 1000 elements.\n";
    }
    else
        std::cout << "The map could not hold 1000 elements.\n";
}

void mapElementAccess()
{
    std::cout << "\nSUBSCRIPT OPERATOR TEST\n";
    lib::map<char, std::string> subscript;

    subscript['a'] = "an element";
    subscript['b'] = "another element";
    subscript['c'] = subscript['b'];

    std::cout << "subscript['a'] is " << subscript['a'] << '\n';
    std::cout << "subscript['b'] is " << subscript['b'] << '\n';
    std::cout << "subscript['c'] is " << subscript['c'] << '\n';
    std::cout << "subscript['d'] is " << subscript['d'] << '\n';

    std::cout << "subscript now contains " << subscript.size() << " elements.\n";
}

void mapModifiers()
{
    std::cout << "\nINSERT TEST\n";
    lib::map<char, int> inserter;

    // first insert function version (single parameter):
    inserter.insert(lib::pair<char, int>('a', 100));
    inserter.insert(lib::pair<char, int>('z', 200));

    lib::pair<lib::map<char, int>::iterator, bool> ret;
    ret = inserter.insert(lib::pair<char, int>('z', 500));
    if (ret.second == false)
    {
        std::cout << "element 'z' already existed";
        std::cout << " with a value of " << ret.first->second << '\n';
    }

    // second insert function version (with hint position):
    lib::map<char, int>::iterator insertit = inserter.begin();
    inserter.insert(insertit, lib::pair<char, int>('b', 300)); // max efficiency inserting
    inserter.insert(insertit, lib::pair<char, int>('c', 400)); // no max efficiency inserting

    // third insert function version (range insertion):
    lib::map<char, int> otherInserter;
    otherInserter.insert(inserter.begin(), inserter.find('c'));

    // showing contents:
    std::cout << "inserter contains:\n";
    for (insertit = inserter.begin(); insertit != inserter.end(); ++insertit)
        std::cout << insertit->first << " => " << insertit->second << '\n';

    std::cout << "otherInserter contains:\n";
    for (insertit = otherInserter.begin(); insertit != otherInserter.end(); ++insertit)
        std::cout << insertit->first << " => " << insertit->second << '\n';

    std::cout << "\nERASE TEST\n";
    lib::map<char, int> eraser;
    lib::map<char, int>::iterator eraseit;

    // insert some values:
    eraser['a'] = 10;
    eraser['b'] = 20;
    eraser['c'] = 30;
    eraser['d'] = 40;
    eraser['e'] = 50;
    eraser['f'] = 60;

    // eraser.printTree();
    eraseit = eraser.find('b');
    eraser.erase(eraseit); // erasing by iterator
    // eraser.printTree();


    eraser.erase('c'); // erasing by key
    // eraser.printTree();

    eraseit = eraser.find('e');
    eraser.erase(eraseit, eraser.end()); // erasing by range
    // eraser.printTree();

    // show content:
    for (eraseit = eraser.begin(); eraseit != eraser.end(); ++eraseit)
        std::cout << eraseit->first << " => " << eraseit->second << '\n';

    std::cout << "\nSWAP TEST\n";
    lib::map<char, int> foo, bar;

    foo['x'] = 100;
    foo['y'] = 200;

    bar['a'] = 11;
    bar['b'] = 22;
    bar['c'] = 33;

    foo.swap(bar);

    std::cout << "foo contains:\n";
    for (lib::map<char, int>::iterator swapit = foo.begin(); swapit != foo.end(); ++swapit)
        std::cout << swapit->first << " => " << swapit->second << '\n';

    std::cout << "bar contains:\n";
    for (lib::map<char, int>::iterator swapit = bar.begin(); swapit != bar.end(); ++swapit)
        std::cout << swapit->first << " => " << swapit->second << '\n';

    std::cout << "\nCLEAR TEST\n";
    lib::map<char, int> clearer;

    clearer['x'] = 100;
    clearer['y'] = 200;
    clearer['z'] = 300;

    std::cout << "clearer contains:\n";
    for (lib::map<char, int>::iterator clearit = clearer.begin(); clearit != clearer.end(); ++clearit)
        std::cout << clearit->first << " => " << clearit->second << '\n';

    clearer.clear();
    clearer['a'] = 1101;
    clearer['b'] = 2202;

    std::cout << "clearer contains:\n";
    for (lib::map<char, int>::iterator clearit = clearer.begin(); clearit != clearer.end(); ++clearit)
        std::cout << clearit->first << " => " << clearit->second << '\n';
}

void mapObservers()
{
    std::cout << "\nKEY_COMP TEST\n";
    lib::map<char, int> keycomper;

    lib::map<char, int>::key_compare mycomp = keycomper.key_comp();

    keycomper['a'] = 100;
    keycomper['b'] = 200;
    keycomper['c'] = 300;

    std::cout << "keycomper contains:\n";

    char highestChar = keycomper.rbegin()->first; // key value of last element

    lib::map<char, int>::iterator keycompit = keycomper.begin();
    do
    {
        std::cout << keycompit->first << " => " << keycompit->second << '\n';
    } while (mycomp((*keycompit++).first, highestChar));

    std::cout << '\n';

    std::cout << "\nVALUE_COMP TEST\n";
    lib::map<char, int> valuecomper;

    valuecomper['x'] = 1001;
    valuecomper['y'] = 2002;
    valuecomper['z'] = 3003;

    std::cout << "valuecomper contains:\n";

    lib::pair<char, int> highestPair = *valuecomper.rbegin(); // last element

    lib::map<char, int>::iterator valuecompit = valuecomper.begin();
    do
    {
        std::cout << valuecompit->first << " => " << valuecompit->second << '\n';
    } while (valuecomper.value_comp()(*valuecompit++, highestPair));
}

void mapOperations()
{
    std::cout << "\nFIND TEST\n";
    lib::map<char, int> finder;
    lib::map<char, int>::iterator findit;

    finder['a'] = 50;
    finder['b'] = 100;
    finder['c'] = 150;
    finder['d'] = 200;

    findit = finder.find('b');
    if (findit != finder.end())
        finder.erase(findit);

    // print content:
    std::cout << "elements in finder:" << '\n';
    std::cout << "a => " << finder.find('a')->second << '\n';
    std::cout << "c => " << finder.find('c')->second << '\n';
    std::cout << "d => " << finder.find('d')->second << '\n';


    std::cout << "\nCOUNT TEST\n";
    lib::map<char, int> counter;
    char c;

    counter['a'] = 101;
    counter['c'] = 202;
    counter['f'] = 303;

    for (c = 'a'; c < 'h'; c++)
    {
        std::cout << c;
        if (counter.count(c) > 0)
            std::cout << " is an element of counter.\n";
        else
            std::cout << " is not an element of counter.\n";
    }

    std::cout << "\nLOWER_BOUND / UPPER_BOUND TEST\n";
    lib::map<char, int> bounder;
    lib::map<char, int>::iterator itlow, itup;

    bounder['a'] = 20;
    bounder['b'] = 40;
    bounder['c'] = 60;
    bounder['d'] = 80;
    bounder['e'] = 100;

    itlow = bounder.lower_bound('b'); // itlow points to b
    itup = bounder.upper_bound('d');  // itup points to e (not d!)

    bounder.erase(itlow, itup); // erases [itlow,itup)

    // print content:
    for (lib::map<char, int>::iterator boundit = bounder.begin(); boundit != bounder.end(); ++boundit)
        std::cout << boundit->first << " => " << boundit->second << '\n';

    std::cout << "\nEQUAL_RANGE TEST\n";
    lib::map<char, int> ranger;

    ranger['a'] = 10;
    ranger['b'] = 20;
    ranger['c'] = 30;

    lib::pair<lib::map<char, int>::iterator, lib::map<char, int>::iterator> ret;
    ret = ranger.equal_range('b');

    std::cout << "lower bound points to: ";
    std::cout << ret.first->first << " => " << ret.first->second << '\n';

    std::cout << "upper bound points to: ";
    std::cout << ret.second->first << " => " << ret.second->second << '\n';
}

void mapExtra()
{
    lib::map<int, std::string> map;
    map.insert(lib::make_pair(4, "four"));
    map.insert(lib::make_pair(3, "three"));
    map.insert(lib::make_pair(2, "two"));
    map.insert(lib::make_pair(1, "one"));

    lib::map<int, std::string>::iterator it = map.begin();
    std::cout << it->second << std::endl;

    while (it != map.end())
    {
        std::cout << "kiki\n";
        std::cout << it->first << std::endl;
        it++;
    }
    map.insert(lib::make_pair(69, "sixty nine"));
    it--;
    std::cout << it->second << std::endl;
}

void garbage()
{
    lib::map<int, std::string> map;

    map.insert(lib::make_pair(0, "zero"));
    map.insert(lib::make_pair(30, "thirty"));
    map.insert(lib::make_pair(40, "forty"));
    map.insert(lib::make_pair(20, "twenty"));
    map.insert(lib::make_pair(10, "ten"));

    map.printTree();
    map.erase(30);
    map.printTree();
    // map.erase(4);
    // map.printTree();
    // map.erase(1);
    // map.printTree();
    // map.erase(2);
    // map.printTree();


    
}

void mapTest()
{
    std::cout << "==========================TESTING MAP=======================================\n\n";

    garbage();
    // mapIterators();
    // mapCapacity();
    // mapElementAccess();
    // mapModifiers();
    // mapObservers();
    // mapOperations();
    // mapExtra();
}