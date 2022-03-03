#include "tests.hpp"

void treeTest()
{
    // ft::bst<ft::map<std::string, std::string>::value_type, std::less<std::string> > tree;
    // ft::bst<ft::pair<int, std::string>, std::less<int> > tree;

    // tree.insert(lib::make_pair(4, "four"));
    // tree.insert(lib::make_pair(5, "five"));
    // tree.insert(lib::make_pair(6, "six"));
    // tree.insert(lib::make_pair(69, "sixty nine"));
    // tree.insert(lib::make_pair(3, "three"));
    // ft::bst<ft::pair<int, std::string>, std::less<int> >::node* deleteme = 
    // tree.insert(lib::make_pair(1, "one"));
    // tree.insert(lib::make_pair(2, "two"));
    // tree.insert(lib::make_pair(0, "zero"));

    // tree.erase(deleteme->val);
    //tree.erase(lib::make_pair(4, "four"));

    // tree.printTree();
}

void mapExtra()
{
    lib::map<int, std::string> map;
    map.insert(lib::make_pair(4, "four"));
    map.insert(lib::make_pair(3, "three"));
    map.insert(lib::make_pair(2, "two"));
    map.insert(lib::make_pair(1, "one"));

    lib::bst_iterator<lib::pair<const int, std::string> > it = map.begin();
    
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

void mapTest()
{
    std::cout << "==========================TESTING MAP=======================================\n\n";
    
    mapExtra();
}