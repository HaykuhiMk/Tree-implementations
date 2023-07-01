#include <iostream>
#include <functional>
#include "generalTree.h"

template <typename Func>
void GeneralTree<Func>::addChild(Node<Func>* parent, Node<Func>* child)
{
    parent->addChildN(child);
}

template <typename Func>
void GeneralTree<Func>::deleteChild(Node<Func>* parent, Node<Func>* child)
{
    parent->deleteChildN(child);
}

template <typename Func>
void GeneralTree<Func>::execute(Node<Func>* start, int num)
{
    Func tmpFunc = start->getValue(); 
    int res = tmpFunc(num);
    std::cout << "Result: " << res << std::endl;
    for (Node<Func>* ch : start->children)
    {
        execute(ch, res);
    }
}
