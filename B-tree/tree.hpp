#include <fstream>

class Cell {
private:
    int key;
    int value;
    bool is_deleted;
public:
    Cell(int _key, int _value, bool _is_deleted) : key(_key), value(_value), is_deleted(_is_deleted) {}

    friend class BTreeNode;

    friend class BTree;
};

class BTreeNode {
private:
    Cell **cells;
    BTreeNode **children;
    int t;
    int keysNumber;
    bool is_leaf;
public:
    BTreeNode(int _t, bool _is_leaf);

    void nodeDump(std::ofstream &file);

    void insertNonFull(int k);

    void splitChild(int i, BTreeNode *y);

    void traverse();

    Cell *search(int k);

    friend class BTree;
};

class BTree {
private:
    BTreeNode *root;
    int t;
public:
    BTree(int _t);

    void traverse();

    Cell *search(int k);

    void insert(int k);

    void remove(int k);

    void dump();
};

