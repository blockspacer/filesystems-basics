#include <iostream>
#include <fstream>
#include <unordered_map>
#include "tree.hpp"

Cell::Cell(int64_t _key, int64_t _value) : key(_key), value(_value), is_deleted(false) {}

void BTreeNode::insertNonFull(int64_t k, int64_t v) {
    int i = keysNumber - 1;
    if (is_leaf) {
        while (i >= 0 && cells[i]->key > k) {
            cells[i + 1] = cells[i];
            i--;
        }

        cells[i + 1] = new Cell(k, v);
        keysNumber++;
    } else {
        while (i >= 0 && cells[i]->key > k)
            i--;

        if (children[i + 1]->keysNumber == 2 * t - 1) {
            splitChild(i + 1, children[i + 1]);
            i += (cells[i + 1]->key < k);
        }
        children[i + 1]->insertNonFull(k, v);
    }
}

void BTreeNode::splitChild(int i, BTreeNode *oldChild) {
    BTreeNode *newChild = new BTreeNode(oldChild->t, oldChild->is_leaf);
    newChild->keysNumber = t - 1;

    for (auto j = 0; j < t - 1; j++)
        newChild->cells[j] = oldChild->cells[j + t];

    if (!oldChild->is_leaf) {
        for (auto j = 0; j < t; j++)
            newChild->children[j] = oldChild->children[j + t];
    }

    oldChild->keysNumber = t - 1;

    for (auto j = keysNumber; j >= i + 1; j--)
        children[j + 1] = children[j];

    children[i + 1] = newChild;

    for (auto j = keysNumber - 1; j >= i; j--)
        cells[j + 1] = cells[j];

    cells[i] = oldChild->cells[t - 1];
    keysNumber++;
}

BTreeNode::BTreeNode(int _t, bool _is_leaf) : t(_t), keysNumber(0), is_leaf(_is_leaf) {
    cells = new Cell *[2 * t - 1];
    children = new BTreeNode *[2 * t];
}

void BTreeNode::traverse(std::unordered_map <int64_t, int64_t> &nodes) {
    auto i = 0;
    for (i = 0; i < keysNumber; i++) {
        if (!is_leaf)
            children[i]->traverse(nodes);
        nodes[cells[i]->key] = cells[i]->value;
    }

    if (!is_leaf)
        children[i]->traverse(nodes);
}

Cell *BTreeNode::search(int64_t k) {
    auto i = 0;
    while (i < keysNumber && k > cells[i]->key)
        i++;

    if (cells[i] != nullptr) {
        if (cells[i]->key == k)
            return cells[i];
    }

    return (is_leaf) ? nullptr : children[i]->search(k);
}

void BTreeNode::nodeDump(std::ofstream &file) {
    file << "node_" << this << "[label = \n\t<<table border=\"0\" cellborder=\"0\">\n";
    auto port = 0;
    file << "\t\t<tr>";
    for (port = 0; port < keysNumber; port++) {
        std::string color = (cells[port]->is_deleted) ? "0 0.3 0.9" : "white";
        file << "<td port=\"port_" << port << "\" border=\"1\" bgcolor=\"" <<
             color << "\">" << cells[port]->key << ":" <<
             cells[port]->value << "</td>\n\t\t";
    }
    file << "<td port=\"" << port << "\"></td></tr>\n\t</table>>];\n";

    for (port = 0; port < keysNumber + 1; port++) {
        if (children[port] != nullptr) {
            children[port]->nodeDump(file);
            file << "node_" << this << ":port_" << port <<
                 " -> node_" << children[port] << "\n";
        }
    }
}

Cell *BTree::search(int64_t k) {
    return (root == nullptr) ? nullptr : root->search(k);
}

void BTree::traverse(std::unordered_map <int64_t, int64_t> &nodes) {
    if (root != nullptr)
        root->traverse(nodes);
}

BTree::BTree(int _t) : root(nullptr), t(_t) {};

void BTree::insert(int64_t k, int64_t v) {
    if (root == nullptr) {
        root = new BTreeNode(t, true);
        root->cells[0] = new Cell(k, v);
        root->keysNumber = 1;
    } else if (root->keysNumber == 2 * t - 1) {
        BTreeNode *newRoot = new BTreeNode(t, false);
        newRoot->children[0] = root;
        newRoot->splitChild(0, root);
        newRoot->children[(newRoot->cells[0]->key < k)]->insertNonFull(k, v);
        root = newRoot;
    } else
        root->insertNonFull(k, v);
}


void BTree::dump() {
    std::ofstream file;
    file.open("dumpFile.gv");

    file << "digraph g {\n" << "node [shape = record,height=.1];\n";
    root->nodeDump(file);
    file << "}";
    file.close();

    system("dot dumpFile.gv -Tpng -o dumpFile.png");
    system("xdot dumpFile.gv");
}


void BTree::remove(int64_t k) {
    auto cell = search(k);
    if (cell != nullptr)
        cell->is_deleted = true;
}


void BTree::merge(BTree *tree) {
    std::unordered_map <int64_t, int64_t> nodes;
    tree->traverse(nodes);
    for (auto x: nodes)
        insert(x.first, x.second);
}
