#include <iostream>
#include "tree.hpp"

int main() {
    BTree tree(2);
    for (auto key: {1, 3, 5, 7, 9, 11, 13, 15, 17, 19})
        tree.insert(key, key % 4);

    BTree newTree(2);
    for (auto key: {2, 4, 6, 8, 10, 12, 14, 16, 18, 20})
        newTree.insert(key, key % 4);

    tree.merge(&newTree);

    for (auto key: {3, 5, 12, 17})
        tree.remove(key);

    tree.dump();

    for (auto i = 0; i < 10; i++) {
        tree.insert(3, i);
        tree.remove(3);
    }

    tree.insert(3, 10);

    tree.dump();
}
