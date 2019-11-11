#include <fstream>

class Cell {
private:
    uint64_t key;
    uint64_t value;
    bool is_deleted;
public:
    Cell(int64_t _key, int64_t _value);

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

    void insertNonFull(int64_t k, int64_t v);

    void splitChild(int i, BTreeNode *y);

    void traverse();

    Cell *search(int64_t k);

    friend class BTree;
};

class BTree {
private:
    BTreeNode *root;
    int t;
public:
    BTree(int _t);

    void traverse();

    Cell *search(int64_t k);

    void insert(int64_t k, int64_t v);

    void remove(int64_t k);

    void dump();
};

