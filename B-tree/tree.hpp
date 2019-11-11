class BTreeNode {
private:
    int *keys;
    int t;
    BTreeNode **children;
    int keysNumber;
    bool is_leaf;
public:
    BTreeNode(int _t, bool _is_leaf);

    void insertNonFull(int k);

    void splitChild(int i, BTreeNode *y);

    void traverse();

    BTreeNode *search(int k);

    friend class BTree;
};

class BTree {
private:
    BTreeNode *root;
    int t;
public:
    BTree(int _t);

    void traverse();

    BTreeNode *search(int k);

    void insert(int k);
};

