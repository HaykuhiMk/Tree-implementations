#include <iostream>
#include "rbt.h"

int main()
{
    RBTree rbt;
    rbt.insert(1);
    rbt.insert(2);
    rbt.insert(3);
    rbt.insert(4);
    rbt.insert(5);
    rbt.levelOrderPrint();
    rbt.rbDelete(4);
    rbt.levelOrderPrint();
}