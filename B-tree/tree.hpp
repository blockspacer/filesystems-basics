#include <fstream>
#include <unordered_map>

class Cell {
private:
    int64_t key;
    int64_t value;
    bool is_deleted;
public:
    Cell(int64_t key, int64_t value);

    friend class BTreeNode;

    friend class BTree;
};

class BTreeNode {
private:
    int t;
    int keysNumber;
    bool isLeaf;
    Cell **cells;
    BTreeNode **children;

    void nodeDump(std::ofstream &file);

    void splitChild(int i, BTreeNode *y);

    void insertNonFull(int64_t k, int64_t v);

    void traverse(std::unordered_map <int64_t, int64_t> &nodes);

    Cell *search(int64_t k);

public:
    BTreeNode(int t, bool isLeaf);

    friend class BTree;
};

class BTree {
private:
    BTreeNode *root;
    int t;

    void traverse(std::unordered_map <int64_t, int64_t> &nodes);

    Cell *search(int64_t k);

public:
    BTree(int t);

    void merge(BTree *tree);

    void insert(int64_t k, int64_t v);

    void remove(int64_t k);

    void dump();
};

