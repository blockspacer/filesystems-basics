#include <iostream>
#include "tree.hpp"

int main() {
    BTree oddTree(2);
    for (auto key: {1, 3, 5, 7, 9, 11})
        oddTree.insert(key, 1);
    oddTree.dump();

    BTree evenTree(2);
    for (auto key: {2, 4, 6, 8, 10, 12})
        evenTree.insert(key, 1);
    evenTree.dump();

    auto newTree = oddTree.merge(&evenTree);
    newTree->dump();
}
