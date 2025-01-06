#pragma once

#include <iostream>
#include <stdexcept>

namespace mtm {

    using T = int;
//    template <typename T>
    class SortedList {
    private:
        class Node;
        Node* head;
        int len;

    public:
        class ConstIterator;
        ConstIterator begin() const;
        ConstIterator end() const;

        SortedList(): head(nullptr), len(0) { }
        SortedList(const SortedList& other);
        SortedList& operator=(const SortedList& other);
        ~SortedList();
        void Insert(const T& newData);
        void remove(const ConstIterator& It);
        int length();


        /**
         *
         * the class should support the following public interface:
         * if needed, use =defualt / =delete
         *
         * constructors and destructor:
         * 1. SortedList() - creates an empty list.
         * 2. copy constructor
         * 3. operator= - assignment operator
         * 4. ~SortedList() - destructor
         *
         * iterator:
         * 5. class ConstIterator;
         * 6. begin method
         * 7. end method
         *
         * functions:
         * 8. insert - inserts a new element to the list
         * 9. remove - removes an element from the list
         * 10. length - returns the number of elements in the list
         * 11. filter - returns a new list with elements that satisfy a given condition
         * 12. apply - returns a new list with elements that were modified by an operation
         */



    };


//    template <class T>
    class SortedList::ConstIterator {
    private:
        friend class SortedList;
        const Node* curNode;
        ConstIterator(const Node& It);
    public:
        ConstIterator() : curNode(nullptr) {};
        ConstIterator(const ConstIterator& It) = default;
        ~ConstIterator() = default;
        ConstIterator& operator=(const ConstIterator& It) = default;

        const T& operator*() const;
        ConstIterator& operator++();
        bool operator!=(const ConstIterator& It) const;









    /**
     * the class should support the following public interface:
     * if needed, use =defualt / =delete
     *
     * constructors and destructor:
     * 1. a ctor(or ctors) your implementation needs
     * 2. copy constructor
     * 3. operator= - assignment operator
     * 4. ~ConstIterator() - destructor
     *
     * operators:
     * 5. operator* - returns the element the iterator points to
     * 6. operator++ - advances the iterator to the next element
     * 7. operator!= - returns true if the iterator points to a different element
     *
     */
    };

//template <typename T>
    class SortedList::Node {
    public:
        T data;
        Node* next = nullptr;
        Node* prev = nullptr;
        Node(const T& data) : data(data) {}
    };
}



//--------------------- SortedList  implementations ------------------------------












//--------------------- SortedList ConstIterator implementations ------------------------------

