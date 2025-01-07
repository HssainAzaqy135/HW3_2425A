//
// Created by kingh on 07/01/2025.
//
#include <stdio.h>
#include "SortedList.h"
using namespace mtm;

#define T double
int main() {
    mtm::SortedList<T> l1;

    l1.Insert(1.6);
    l1.Insert(2.1).Insert(1.1);

    mtm::SortedList l2(l1);
    //Before removal

    for (SortedList<T>::ConstIterator it = l1.begin(); it != l1.end(); ++it) {
        std::cout << *it << std::endl;
    }

    SortedList<T>::ConstIterator it = l1.begin();
    ++it;
    ++it;
    l1.remove(it);
    for (SortedList<T>::ConstIterator it = l1.begin(); it != l1.end(); ++it) {
        std::cout << *it << std::endl;
    }


    return 0;
}
