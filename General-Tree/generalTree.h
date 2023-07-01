#ifndef GENERAL_TREE_H
#define GENERAL_TREE_H
#include <vector>
#include "node.h"

template <typename Func>
class GeneralTree
{
public:
    GeneralTree(Node<Func>* val) : root{val} {}
    void addChild(Node<Func>*, Node<Func>*);
    void deleteChild(Node<Func>*, Node<Func>*);
    void execute(Node<Func>*, int num);

private:
    Node<Func>* root;
};

#endif  //GENERAL_TREE_H