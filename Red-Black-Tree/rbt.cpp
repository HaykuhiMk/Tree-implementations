#include <iostream>
#include <queue>
#include <iomanip>
#include "rbt.h"

RBTree::RBTree()
{
    NIL = new Node(0);
    NIL->col = BLACK;
    root = NIL;
}

RBTree::RBTree(const RBTree& oth) 
{
    NIL = new Node(0);
    NIL->col = BLACK;
    root = nullptr;
    copyHelper(root, oth.root, *this);
}

RBTree::RBTree(RBTree&& oth) 
{
    NIL = oth.NIL;
    oth.NIL = nullptr;
    root = oth.root;
    oth.root = nullptr;
}

RBTree::~RBTree() 
{
    deleteTree(root);
    delete NIL;
}

RBTree& RBTree::operator=(const RBTree& other) 
{
    if (this == &other)
    {
        return *this;
    }
    deleteTree(root);
    NIL = new Node(0);
    NIL->col = BLACK;
    root = nullptr;
    copyHelper(root, other.root, *this);
    return *this;
}

RBTree& RBTree::operator=(RBTree&& other) 
{
    if (this == &other)
    {
        return *this;
    }
    deleteTree(root);
    delete NIL;
    NIL = other.NIL;
    other.NIL = nullptr;
    root = other.root;
    other.root = nullptr;
    return *this;
}

bool RBTree::empty() const
{
    return root == NIL;    
}

RBTree::Node* RBTree::createNode(int value)
{
    return new Node(value);
}

void RBTree::inOrderHelper(Node* node) const 
{
    if (node != NIL) 
    {
        inOrderHelper(node->left);
        std::string color = (node->col == RED) ? "Red" : "Black";
        std::cout << color[0] << node->value << " ";
        inOrderHelper(node->right);
    }
}

void RBTree::postOrderHelper(Node* node) const 
{
    if (node != NIL) 
    {
        postOrderHelper(node->left);
        postOrderHelper(node->right);
        std::string color = (node->col == RED) ? "Red" : "Black";
        std::cout << color[0] << node->value << " ";
    }
}

void RBTree::preOrderHelper(Node* node) const 
{
    if (node != NIL) 
    {
        std::string color = (node->col == RED) ? "Red" : "Black";
        std::cout << color[0] << node->value << " ";
        preOrderHelper(node->left);
        preOrderHelper(node->right);
    }
}

void RBTree::inOrderTraversal() const 
{
    inOrderHelper(root);
}

void RBTree::postOrderTraversal() const 
{
    postOrderHelper(root);
}

void RBTree::preOrderTraversal() const 
{
    preOrderHelper(root);
}

void RBTree::leftRotate(Node* x)
{
    Node* y = x->right;
    x->right = y->left;
    if (y->left != NIL)
    {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NIL)
    {
        root = y;
    }
    else if (x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void RBTree::rightRotate(Node* y)
{
    Node* x = y->left;
    y->left = x->right;
    if (x->right != NIL)
    {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == NIL)
    {
        root = x;
    }
    else if (y->parent->left == y)
    {
        y->parent->left = x;
    }
    else
    {
        y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
}

void RBTree::insert(int value)
{
    Node* z = createNode(value);
    Node* x = root;
    Node* y = NIL;
    while (x != NIL)
    {
        y = x;
        if (z->value < x->value)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == NIL)
    {
        root = z;
    }
    else if (z->value < y->value)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }
    z->left = NIL;
    z->right = NIL;
    z->col = RED;
    insertFixup(z);
}

RBTree::Node* RBTree::minimum(Node* node)
{
    while (node->left != NIL)
    {
        node = node->left;
    }
    return node;
}


void RBTree::insertFixup(Node* z)
{
    while (z->parent != nullptr && z->parent->col == RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            Node* y = z->parent->parent->right;
            if (y != nullptr && y->col == RED)
            {
                z->parent->col = BLACK;
                y->col = BLACK;
                z->parent->parent->col = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->col = BLACK;
                z->parent->parent->col = RED;  
                rightRotate(z->parent->parent);
            }
        }
        else
        {
            Node* y = z->parent->parent->left;
            if (y != nullptr && y->col == RED)
            {
                z->parent->col = BLACK;
                y->col = BLACK;
                z->parent->parent->col = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->col = BLACK;
                z->parent->parent->col = RED;
                leftRotate(z->parent->parent);
            }
        }
    }   
    root->col = BLACK;
}

void RBTree::levelOrderPrint() const
{
    if (root == NIL) 
    {
        return;
    }
    std::queue<Node*> nodeQueue;
    nodeQueue.push(root);
    while (!nodeQueue.empty()) 
    {
        int levelSize = nodeQueue.size();
        for (int i = 0; i < levelSize; i++) 
        {
            Node* node = nodeQueue.front();
            nodeQueue.pop();
            std::string color = (node->col == RED) ? "Red" : "Black";
            std::cout << std::setw(6) << color[0] << node->value << "  ";
            if (node->left != NIL) 
            {
                nodeQueue.push(node->left);
            }
            if (node->right != NIL) 
            {
                nodeQueue.push(node->right);
            }
        }
        std::cout << std::endl;
    }
}

void RBTree::transplant(Node* u, Node* v)
{
    if (u->parent == NIL)
    {
        root = v;
    }
    else if (u == u->parent->left)
    {
        u->parent->left = v;
    }
    else
    {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

void RBTree::deleteFixup(Node* x)
{
    while (x != root && x->col == BLACK)
    {
        if (x == x->parent->left)
        {
            Node* w = x->parent->right;
            if (w->col == RED)
            {
                w->col = BLACK;
                x->parent->col = RED;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if (w->left->col == BLACK && w->right->col == BLACK)
            {
                w->col = RED;
                x = x->parent;
            }
            else
            {
                if (w->right->col == BLACK)
                {
                    w->left->col = BLACK;
                    w->col = RED;
                    rightRotate(w);
                    w = x->parent->right;
                }
                w->col = x->parent->col;
                x->parent->col = BLACK;
                w->right->col = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        }
        else
        {
            Node* w = x->parent->left;

            if (w->col == RED)
            {
                w->col = BLACK;
                x->parent->col = RED;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            if (w->right->col == BLACK && w->left->col == BLACK)
            {
                w->col = RED;
                x = x->parent;
            }
            else
            {
                if (w->left->col == BLACK)
                {
                    w->right->col = BLACK;
                    w->col = RED;
                    leftRotate(w);
                    w = x->parent->left;
                }
                w->col = x->parent->col;
                x->parent->col = BLACK;
                w->left->col = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->col = BLACK;
}

void RBTree::rbDelete(int value)
{
    Node* z = find(value);
    if (z == nullptr)
    {
        return;
    }
    Node* y = z;
    Node* x = nullptr;
    Color yOrigCol = y->col;
    if (z->left == NIL)
    {
        x = z->right;
        transplant(z, z->right);
    }
    else if (z->right == NIL)
    {
        x = z->left;
        transplant(z, z->left);
    }
    else
    {
        y = minimum(z->right);
        yOrigCol = y->col;
        x = y->right;
        if (y->parent == z)
        {
            x->parent = y;
        }
        else
        {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->col = z->col;
    }
    delete z;
    if (yOrigCol == BLACK)
    {
        deleteFixup(x);
    }
}

RBTree::Node* RBTree::findHelper(Node* node, int value)
{
    if (node == NIL || node->value == value)
    {
        return node;
    }
    if (value < node->value)
    {
        return findHelper(node->left, value);
    }
    else
    {
        return findHelper(node->right, value);
    }
}

RBTree::Node* RBTree::find(int value)
{
    return findHelper(root, value);
}

int RBTree::Node::getValue() const
{
    return this->value;
}

void RBTree::transplantValues(int value1, int value2)
{
    Node* node1 = find(value1);
    Node* node2 = find(value2);
    if (node1 == nullptr || node2 == nullptr)
    {
        std::cout << "One or both values not found in the tree." << std::endl;
        return;
    }
    transplant(node1, node2);
}

void RBTree::copyHelper(Node* destNode, Node* srcNode, RBTree& destTree) 
{
    if (srcNode == nullptr || srcNode == NIL) 
    {
        destNode = NIL;
        return;
    }
    destNode = destTree.createNode(srcNode->value);
    destNode->col = srcNode->col;
    if (srcNode->left != nullptr && srcNode->left != NIL) 
    {
        copyHelper(destNode->left, srcNode->left, destTree);
        destNode->left->parent = destNode;
    }
    if (srcNode->right != nullptr && srcNode->right != NIL) 
    {
        copyHelper(destNode->right, srcNode->right, destTree);
        destNode->right->parent = destNode;
    }
}

void RBTree::deleteTree(Node* node) 
{
    if (node == NIL)
    {
        return;
    }
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}