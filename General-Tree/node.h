#ifndef NODE_H
#define NODE_H
#include <vector>
#include <functional>

template <typename Func>
class Node
{
public:
    Node(const Func& val) : value{val} {}
    Func getValue() const;
    void setValue(Func);
    void addChildN(Node<Func>*);
    void print();
    void deleteChildN(Node<Func>*);
public:
    Func value;
    std::vector<Node<Func>*> children;
};

#endif  //NODE_H