#include <iostream>
#include "tree.hpp"

BTreeNode::BTreeNode(int _t, bool _is_leaf) : t(_t), keysNumber(0), is_leaf(_is_leaf) {
    keys = new int[2 * t - 1];
    children = new BTreeNode *[2 * t];
}

void BTreeNode::traverse() {
    int i = 0;
    for (i = 0; i < keysNumber; i++) {
        if (!is_leaf)
            children[i]->traverse();
        std::cout << " " << keys[i];
    }

    if (!is_leaf)
        children[i]->traverse();
}

BTreeNode *BTreeNode::search(int k) {
    int i = 0;
    while (i < keysNumber && k > keys[i])
        i++;

    if (keys[i] == k)
        return this;

    return (is_leaf) ? nullptr : children[i]->search(k);
}

BTreeNode *BTree::search(int k) {
    return (root == nullptr) ? nullptr : root->search(k);
}

void BTree::traverse() {
    if (root != nullptr)
        root->traverse();
}

BTree::BTree(int _t) : root(nullptr), t(_t) {};

void BTree::insert(int k) {
    if (root == nullptr) {
        root = new BTreeNode(t, true);
        root->keys[0] = k;
        root->keysNumber = 1;
    } else if (root->keysNumber == 2 * t - 1) {
        BTreeNode *newRoot = new BTreeNode(t, false);
        newRoot->children[0] = root;
        newRoot->splitChild(0, root);
        newRoot->children[(newRoot->keys[0] < k)]->insertNonFull(k);
        root = newRoot;
    } else
        root->insertNonFull(k);
}

void BTreeNode::insertNonFull(int k) {
    int i = keysNumber - 1;
    if (is_leaf) {
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }

        keys[i + 1] = k;
        keysNumber++;
    } else {
        while (i >= 0 && keys[i] > k)
            i--;

        if (children[i + 1]->keysNumber == 2 * t - 1) {
            splitChild(i + 1, children[i + 1]);
            i += (keys[i + 1] < k);
        }
        children[i + 1]->insertNonFull(k);
    }
}

void BTreeNode::splitChild(int i, BTreeNode *oldChild) {
    BTreeNode *newChild = new BTreeNode(oldChild->t, oldChild->is_leaf);
    newChild->keysNumber = t - 1;

    for (int j = 0; j < t - 1; j++)
        newChild->keys[j] = oldChild->keys[j + t];

    if (!oldChild->is_leaf) {
        for (int j = 0; j < t; j++)
            newChild->children[j] = oldChild->children[j + t];
    }

    oldChild->keysNumber = t - 1;

    for (int j = keysNumber; j >= i + 1; j--)
        children[j + 1] = children[j];

    children[i + 1] = newChild;

    for (int j = keysNumber - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    keys[i] = oldChild->keys[t - 1];
    keysNumber++;
}

void BTree::dump() {
    FILE *file = fopen("dumpFile.gv", "w");
    assert(file);

    fprintf(file, "digraph g {\n");
    fprintf(file, "node [shape = record,height=.1];\n");
    root->nodeDump(file);
    fprintf(file, "}");
    fclose(file);

    system("dot dumpFile.gv -Tpng -o dumpFile.png");
    system("xdot dumpFile.gv");
}

void BTreeNode::nodeDump(FILE *file) {
    fprintf(file, "node_%p[label = \"", this);

    for (int i = 0; i < keysNumber; i++) {
        fprintf(file, "<f_%p> |%d|", this, keys[i]);
    }
    fprintf(file, "\"];\n");

    for (int i = 0; i < keysNumber + 1; i++) {
        if (children[i] != nullptr) {
            children[i]->nodeDump(file);
            fprintf(file, "\"node_%p\":f_%p -> \"node_%p\"\n", this, children[i], children[i]);
        }
    }
}