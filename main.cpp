#include <vector>
#include <iostream>
#include <cstdlib>
#include "vector.hpp"
#include "Tests.hpp"
#include "bst.hpp"


int main()
{
    std::cout << "Running using namespace: ";
#ifdef USE_STD
    std::cout << "std";
#else
    std::cout << "ft";
#endif
    std::cout << std::endl << std::endl;

    ft::bst<int> tree;

    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(69);
    tree.insert(3);
    tree.insert(1);
    tree.insert(2);
    tree.insert(0);
    tree.erase(4);


    tree.printTree();
    
    std::cout << std::endl << std::endl;
    // vectorTest();
    // stackTest();
    // mapTest();

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

    return 0;
}
