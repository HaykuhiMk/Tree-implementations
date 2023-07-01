#ifndef RED_BLACK_TREE
#define RED_BLACK_TREE

enum Color 
{
    RED,
    BLACK
};

class RBTree
{
public:
    RBTree();
    RBTree(const RBTree&);
    RBTree(RBTree&&);
    ~RBTree();

public:
    RBTree& operator=(const RBTree&);
    RBTree& operator=(RBTree&&);

private:
    struct Node
    {
        int value;
        Color col;
        Node* left;
        Node* right;
        Node* parent;
        explicit Node(int val) : 
        value(val), 
        col(RED), 
        left(nullptr), 
        right(nullptr), 
        parent(nullptr) 
        {}
        int getValue() const;
    };
    Node* root;
    Node* NIL;

private:
    void insertFixup(Node*);
    void deleteFixup(Node*);
    Node* findHelper(Node*, int);
    Node* createNode(int);
    void transplant(Node*, Node*);
    void inOrderHelper(Node*) const;
    void postOrderHelper(Node*) const;
    void preOrderHelper(Node*) const;
    void copyHelper(Node*, Node*, RBTree&);

public:
    bool empty() const;
    void deleteTree(Node*);
    void leftRotate(Node*);
    void rightRotate(Node*);
    void insert(int);
    void rbDelete(int);
    Node* minimum(Node*);
    Node* find(int);
    void transplantValues(int, int);
    void levelOrderPrint() const;
    void inOrderTraversal() const;
    void postOrderTraversal() const;
    void preOrderTraversal() const;
    

};

#endif  //RED_BLACK_TREE


