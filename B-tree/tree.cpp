#include <iostream>
#include "tree.hpp"
#include <fstream>

BTreeNode::BTreeNode(int _t, bool _is_leaf) : t(_t), keysNumber(0), is_leaf(_is_leaf) {
    cells = new Cell *[2 * t - 1];
    children = new BTreeNode *[2 * t];
}

void BTreeNode::traverse() {
    int i = 0;
    for (i = 0; i < keysNumber; i++) {
        if (!is_leaf)
            children[i]->traverse();
        std::cout << " {" << cells[i]->key << ":" << cells[i]->value << "}";
    }

    if (!is_leaf)
        children[i]->traverse();
}

BTreeNode *BTreeNode::search(int k) {
    int i = 0;
    while (i < keysNumber && k > cells[i]->key)
        i++;

    if (cells[i]->key == k)
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
        root->cells[0] = new Cell(k, 100, false);
        root->keysNumber = 1;
    } else if (root->keysNumber == 2 * t - 1) {
        BTreeNode *newRoot = new BTreeNode(t, false);
        newRoot->children[0] = root;
        newRoot->splitChild(0, root);
        newRoot->children[(newRoot->cells[0]->key < k)]->insertNonFull(k);
        root = newRoot;
    } else
        root->insertNonFull(k);
}

void BTreeNode::insertNonFull(int k) {
    int i = keysNumber - 1;
    if (is_leaf) {
        while (i >= 0 && cells[i]->key > k) {
            cells[i + 1] = cells[i];
            i--;
        }

        cells[i + 1] = new Cell(k, 100, false);
        keysNumber++;
    } else {
        while (i >= 0 && cells[i]->key > k)
            i--;

        if (children[i + 1]->keysNumber == 2 * t - 1) {
            splitChild(i + 1, children[i + 1]);
            i += (cells[i + 1]->key < k);
        }
        children[i + 1]->insertNonFull(k);
    }
}

void BTreeNode::splitChild(int i, BTreeNode *oldChild) {
    BTreeNode *newChild = new BTreeNode(oldChild->t, oldChild->is_leaf);
    newChild->keysNumber = t - 1;

    for (int j = 0; j < t - 1; j++)
        newChild->cells[j] = oldChild->cells[j + t];

    if (!oldChild->is_leaf) {
        for (int j = 0; j < t; j++)
            newChild->children[j] = oldChild->children[j + t];
    }

    oldChild->keysNumber = t - 1;

    for (int j = keysNumber; j >= i + 1; j--)
        children[j + 1] = children[j];

    children[i + 1] = newChild;

    for (int j = keysNumber - 1; j >= i; j--)
        cells[j + 1] = cells[j];

    cells[i] = oldChild->cells[t - 1];
    keysNumber++;
}

void BTree::dump() {
    std::ofstream file;
    file.open("dumpFile.gv");

    file << "digraph g {\n";
    file << "node [shape = record,height=.1];\n";
    root->nodeDump(file);
    file << "}";
    file.close();

    system("dot dumpFile.gv -Tpng -o dumpFile.png");
    system("xdot dumpFile.gv");
}

void BTreeNode::nodeDump(std::ofstream &file) {
    file << "node_" << this << "[label = \"";
    int port = 0;
    for (port = 0; port < keysNumber; port++) {
        file << "<f_" << port << "> |" << cells[port]->key << ":" << cells[port]->value << "|";
    }
    file << "<f_" << port << ">\"];\n";

    for (port = 0; port < keysNumber + 1; port++) {
        if (children[port] != nullptr) {
            children[port]->nodeDump(file);
            file << "\"node_" << this << "\":f_" << port << " -> \"node_" << children[port] << "\"\n";
        }
    }
}