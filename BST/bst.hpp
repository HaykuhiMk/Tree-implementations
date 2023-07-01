#include <iostream>
#include <fstream>
#include "bst.h"

template <class T>
BST<T>::BST() : root{nullptr} {}

template <class T>
BST<T>::BST(const BST& oth) 
{
    root = copy(oth.root);
}

template <class T>
BST<T>::BST(BST&& oth) : root(nullptr) 
{
    root = oth.root;
    oth.root = nullptr;
}

template <class T>
BST<T>::~BST() 
{
    if (root)
    {
        deleteHelper(root);
    }
}

template <class T>
bool BST<T>::isEmpty() const
{
    return root == nullptr;
}

template <class T>
int BST<T>::getHeightHelper(BSTNode* node) const
{
    if (node == nullptr)
    {
        return 0;
    }
    return 1 + std::max(node->left->value, node->right->value);
}


template <class T>
int BST<T>::getHeight() const
{
    return getHeightHelper(root);
}

template <class T>
int BST<T>::getNumberOfNodesHelper(BSTNode* node) const
{
    if (node == nullptr)
    {
        return 0;
    }
    int leftC = getNumberOfNodesHelper(root->left);
    int rightC = getNumberOfNodesHelper(root->right);
    return 1 + leftC + rightC;
}

template <class T>
int BST<T>::getNumberOfNodes() const
{
    return getNumberOfNodesHelper(root);
}

template <class T>
T BST<T>::getRootData() const
{
    if (root == nullptr)
    {
        throw std::logic_error("The BST is empty!");
    }
    return root->value;
}

template <class T>
void BST<T>::setRootData(const T& val)
{
    if (root == nullptr)
    {
        root = new BSTNode(val);
    }
    else 
    {
        root->value = val;
    }
}

template <class T>
typename BST<T>::BSTNode* BST<T>::insertInorder(BSTNode* subNode, BSTNode* newNode)
{
    if (subNode == nullptr)
    {
        return newNode;
    }
    if (subNode->value > newNode->value)
    {
        subNode->left = insertInorder(subNode->left,  newNode);
    }
    else
    {
        subNode->right = insertInorder(subNode->right,  newNode);
    }
    return subNode;
}

template <class T>
bool BST<T>::add(const T& val)
{
    BSTNode* tmp = new BSTNode(val);
    root = insertInorder(root, tmp);
    return true;
}

template <class T>
void BST<T>::clear() 
{
    clearHelper(root);
    root = nullptr;
}

template <class T>
void BST<T>::clearHelper(BSTNode* node) 
{
    if (node == nullptr) 
    {
        return;
    }
    
    clearHelper(node->left);
    clearHelper(node->right);
    delete node;
}

template <class T>
void BST<T>::inorderHelper(BSTNode* root) const 
{
    if (root == nullptr) 
    {
        return;
    }
    inorderHelper(root->left);
    std::cout << root->value << " ";
    inorderHelper(root->right);
}

template <class T>
void BST<T>::preorderHelper(BSTNode* root) const 
{
    if (root == nullptr) 
    {
        return;
    }
    std::cout << root->value << " ";
    preorderHelper(root->left);
    preorderHelper(root->right);
}

template <class T>
void BST<T>::postorderHelper(BSTNode* root) const 
{
    if (root == nullptr) 
    {
        return;
    }
    postorderHelper(root->left);
    postorderHelper(root->right);
    std::cout << root->value << " ";
}

template <class T>
void BST<T>::inorder() const 
{
    if (root == nullptr) 
    {
        return;
    }
    inorderHelper(root);
}

template <class T>
void BST<T>::preorder() const 
{
    if (root == nullptr) 
    {
        return;
    }
    preorderHelper(root);
}

template <class T>
void BST<T>::postorder() const 
{
    if (root == nullptr) 
    {
        return;
    }
    postorderHelper(root);
}

template <class T>
void BST<T>::levelorder() const 
{
    int height = getHeight();
    for (int i = 0; i <= height; ++i) 
    {
        levelorder(root, i);
        std::cout << std::endl;
    }
}

template <class T>
typename BST<T>::BSTNode* BST<T>::find(BSTNode* node, const T& val) const 
{
    if (node == nullptr) 
    {
        return nullptr;
    }
    if (node->value == val) 
    {
        return node;
    }
    if (node->value > val) 
    {
        return find(node->left, val);
    }
    else 
    {
        return find(node->right, val);
    }
}

template <class T>
void BST<T>::deleteHelper(BSTNode*& node) 
{
    if (node == nullptr) 
    {
        return;
    }
    deleteHelper(node->left);
    deleteHelper(node->right);
    delete node;
    node = nullptr;
}

template <class T>
typename BST<T>::BSTNode* BST<T>::findMinNode(BSTNode* node) 
{
    if (node == nullptr) {
        return node;
    }
    if (node->left == nullptr) {
        return node;
    }
    return findMinNode(node->left);
}

template <class T>
typename BST<T>::BSTNode* BST<T>::deleteElement(BSTNode* node, const T& val) {
    if (node == nullptr) 
    {
        return nullptr;
    }
    if (val > node->value) 
    {
        node->right = deleteElement(node->right, val);
        return node;
    }
    if (val < node->value) 
    {
        node->left = deleteElement(node->left, val);
        return node;
    }
    if (!node->right && !node-> left) 
    {
        delete node;
        return nullptr;
    }
    if (!node->right) 
    {
        BSTNode* tmp = node->left;
        delete node;
        return tmp;
    }
    if (!node->left) 
    {
        BSTNode* tmp = node->right;
        delete node;
        return tmp;
    }
    const BSTNode* tmp = findMinNode(node->right);
    node->value = tmp->value;
    node->right = deleteElement(node->right, tmp->value);
    return node;
}

template <class T>
typename BST<T>::BSTNode* BST<T>::copy(BSTNode* node, BSTNode* parent)
{
    if (node == nullptr) 
    {
        return nullptr;
    }
    BST<T>::BSTNode* newNode = new BST<T>::BSTNode(node->value, parent);
    newNode->left = copy(node->left, newNode);
    newNode->right = copy(node->right, newNode);
    return newNode;
}

template <class T>
typename BST<T>::BSTNode* BST<T>::begin() const
{
    return this->root;
}

template <class T>
void BST<T>::saveHelper(BSTNode* root, std::ofstream& file)
{
    if (root == nullptr)
    {
        return;
    }
    file << root->value << " ";
    saveHelper(root->left, file);
    saveHelper(root->right, file);
}

template <class T>
void BST<T>::saveToFile(BSTNode* root, const std::string& fName) 
{
    std::ofstream file(fName);
    if (!file)
    {
        std::cout << "Failed to create file!" << std::endl;
        return;
    }
    saveHelper(root, file);
    file.close();
}

template <class T>
void BST<T>::saveFromFile(const std::string& fName) 
{
    std::ifstream file;
    file.open(fName);
    if (!file.is_open())
    {
        std::cout << "Failed to open file!" << std::endl;
        exit(0);
    }
    T tmp;
    while (file >> tmp)
    {
        this->add(tmp);
    }
    file.close();
}
