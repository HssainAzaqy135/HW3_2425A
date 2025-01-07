//
// Created by kingh on 07/01/2025.
//
#include <stdio.h>
#include "SortedList.h"

int main() {
    mtm::SortedList l1;

    l1.Insert(1);
    l1.Insert(2).Insert(1);

    // l1.remove(mtm::SortedList::ConstIterator());
    mtm::SortedList l2(l1);
    // should check removal
    return 0;
}