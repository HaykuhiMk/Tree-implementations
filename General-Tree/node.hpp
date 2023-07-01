#include <iostream>
#include "node.h"

template <typename Func>
Func Node<Func>::getValue() const
{
    return this->value;
}

template <typename Func>
void Node<Func>::setValue(Func val)
{
    value = val;
}

template <typename Func>
void Node<Func>::addChildN(Node<Func>* child)
{
    this->children.push_back(child);
}

template <typename Func>
void Node<Func>::print()
{
    std::cout << this->value << std::endl;
    for (auto nd : children)
    {
        std::cout << nd->value << std::endl;
    }
}

template <typename Func>
void Node<Func>::deleteChildN(Node<Func>* nd)
{
    int ind = 0;
    for (auto ch : children)
    {
        if (ch->value == nd->value)
        {
            this->children.erase(children.begin() + ind);
            return;
        }
        ++ind;
    }
}
