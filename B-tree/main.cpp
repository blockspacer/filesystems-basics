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
    tree.insert(81);
    tree.insert(82);
    tree.insert(83);
    tree.insert(84);
    tree.insert(85);
    tree.insert(86);
    tree.insert(87);

    tree.remove(60);
    tree.remove(70);
    tree.remove(80);

    tree.dump();

    return 0;
}
