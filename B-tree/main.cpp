#include <iostream>
#include "tree.hpp"

int main() {
    BTree tree(2);
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(60);
    tree.insert(70);
    tree.insert(80);

    std::cout << "Traversal of the constucted tree is ";
    tree.traverse();

    (tree.search(60) != nullptr) ? std::cout << "\nFound" : std::cout << "\nNot found";
    (tree.search(15) != nullptr) ? std::cout << "\nFound" : std::cout << "\nNot found";

    return 0;
}
