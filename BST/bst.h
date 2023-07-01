#ifndef BST_H
#define BST_H

template <class T>
class BST
{
public:
    BST();
    BST(const BST&);
    BST(BST&&);
    ~BST();
    
private:
    struct BSTNode
    {
        T value;
        BSTNode* left;
        BSTNode* right;
        BSTNode(const T& val, BSTNode* l = nullptr, BSTNode* r = nullptr) :
        value(val),
        left(l),
        right(r)
        {}
    };
    BSTNode* root;
    
public:
    bool isEmpty() const;
    int getHeight() const;
    int getNumberOfNodes() const;
    T getRootData() const;
    void setRootData(const T&);
    bool add(const T&);
    BSTNode* insertInorder(BSTNode*, BSTNode*);
    void clear();
    void inorder() const;
    void preorder() const;
    void postorder() const;
    void levelorder() const;
    BSTNode* begin() const;
    BSTNode* find(BSTNode*, const T&) const;
    BSTNode* deleteElement(BSTNode*, const T&);
    BSTNode* copy(BSTNode*, BSTNode*);
    void deleteHelper(BSTNode*&);
    BSTNode* findMinNode(BSTNode*);
    void saveHelper(BSTNode*, std::ofstream&);
    void saveToFile(BSTNode*, const std::string&);
    void saveFromFile(const std::string&);
    
private:
    int getHeightHelper(BSTNode*) const;
    int getNumberOfNodesHelper(BSTNode*) const;
    void clearHelper(BSTNode*);
    void inorderHelper(BSTNode*) const; 
    void preorderHelper(BSTNode*) const; 
    void postorderHelper(BSTNode*) const; 

};

#endif  //BST_H
