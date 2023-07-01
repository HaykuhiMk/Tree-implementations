#include <iostream>
#include <functional>
#include "node.hpp"
#include "generalTree.hpp"

int main()
{
    Node<std::function<int(int)>> root([](int x){ return x + 1; });
    Node<std::function<int(int)>> n2([](int x){ return x - 2; });
    Node<std::function<int(int)>> n3([](int x){ return x * 3; });
    Node<std::function<int(int)>> n4([](int x){ return x / 4; });
    Node<std::function<int(int)>> n5([](int x){ return x * x; });
    GeneralTree<std::function<int(int)>> tree(&root);
    root.addChildN(&n2);
    root.addChildN(&n3);
    n2.addChildN(&n4);
    n3.addChildN(&n5);
    tree.execute(&root, 5);
    return 0;
}
