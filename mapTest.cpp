#include "tests.hpp"

void treeTest()
{
    // ft::bst<ft::map<std::string, std::string>::value_type, std::less<std::string> > tree;
    ft::bst<ft::pair<int, std::string>, std::less<int> > tree;

    tree.insert(lib::make_pair(4, "four"));
    tree.insert(lib::make_pair(5, "five"));
    tree.insert(lib::make_pair(6, "six"));
    tree.insert(lib::make_pair(69, "sixty nine"));
    tree.insert(lib::make_pair(3, "three"));
    ft::bst<ft::pair<int, std::string>, std::less<int> >::node* deleteme = 
    tree.insert(lib::make_pair(1, "one"));
    tree.insert(lib::make_pair(2, "two"));
    tree.insert(lib::make_pair(0, "zero"));


    // tree.insert(lib::make_pair("4", "four"));
    // tree.insert(lib::make_pair("5", "five"));
    // tree.insert(lib::make_pair("6", "six"));
    // tree.insert(lib::make_pair("69", "sixty nine"));
    // tree.insert(lib::make_pair("3", "three"));
    // ft::bst<ft::map<std::string, std::string>::value_type, std::less<std::string> >::node* deleteme = 
    // tree.insert(lib::make_pair("1", "one"));
    // tree.insert(lib::make_pair("2", "two"));
    // tree.insert(lib::make_pair("0", "zero"));

    tree.erase(deleteme->val);
    //tree.erase(lib::make_pair(4, "four"));

    tree.printTree();
    
    std::cout << std::endl << std::endl;

    // ft::RedBlackTree<int> hey;
    // ft::RedBlackTree<int> bst;
    // bst.insert(55);
    // bst.insert(40);
    // bst.insert(65);
    // bst.insert(60);
    // bst.insert(75);
    // bst.insert(57);

    // bst.printTree();
    // std::cout << std::endl
    //      << "After deleting" << std::endl;
    // bst.deleteNode(40);
    // bst.printTree();
}

void mapTest()
{
    std::cout << "==========================TESTING MAP=======================================\n\n";
    
    lib::map<int, std::string> map;
    map.insert(ft::make_pair(4, "four"));
}