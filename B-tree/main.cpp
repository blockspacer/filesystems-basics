#include <iostream>
#include <vector>
#include "tree.hpp"
#include <numeric>

int main() {
    BTree tree(2);

    std::vector<int> v(20);
    std::iota(v.begin(), v.end(), 1);
    for (auto key: v)
        tree.insert(key, 1);

    for (auto key: {4, 7, 14, 17})
        tree.remove(key);

    tree.dump();

}
