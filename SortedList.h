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
        SortedList(): head(nullptr), len(0) { }
        SortedList(const SortedList& otherList);
        SortedList& operator=(const SortedList& otherList);
        ~SortedList();
        SortedList& Insert(const T& newData);
        int length();
        ConstIterator begin() const;
        ConstIterator end() const;
        void remove(const ConstIterator& It);

        void listCopier(const SortedList& otherList);

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
        ~Node() {
            delete this->next;
        }
    };
}


//--------------------- SortedList  implementations ------------------------------

//    template <typename T>
mtm::SortedList::SortedList(const SortedList& otherList) {
    this->listCopier(otherList);
}

//    template <typename T>
mtm::SortedList& mtm::SortedList::operator=(const mtm::SortedList& otherList){
    if (this == &otherList) {
        return *this;
    }
    this->listCopier(otherList);
    return *this;
}

mtm::SortedList::~SortedList() {
    delete this->head;
}

mtm::SortedList& mtm::SortedList::Insert(const T& newData) {
    Node* newNode = new Node(newData);
    if (this->head == nullptr) {
        this->head = newNode;
        this->len++;
        return *this;
    } else if (newData > this->head->data) {
        newNode->next = this->head;
        this->head->prev = newNode;
        this->head = newNode;
        this->len++;
        return *this;
    }
    Node* currNode = this->head;
    Node* nextOfCurr = this->head->next;
    while(nextOfCurr!= nullptr){
        if(newNode->data > nextOfCurr->data){
            break;
        }
        currNode = currNode->next;
        nextOfCurr = nextOfCurr->next;
    }
    currNode->next = newNode;
    newNode->prev = currNode;
    if(nextOfCurr != nullptr){
        newNode->next = nextOfCurr;         //sorting next params
        nextOfCurr->prev= newNode;        //sorting prev params
    }
    this->len++;
    return *this;
}

//--------------------- SortedList ConstIterator implementations ------------------------------




//--------------------- SortedList helper functions implementations ------------------------------


void mtm::SortedList::listCopier(const mtm::SortedList &otherList) {
    if (otherList.head == nullptr) {
        this->head = nullptr;
        this->len = 0;
        return;
    }
    mtm::SortedList::Node* newHead = new mtm::SortedList::Node(otherList.head->data);
    mtm::SortedList::Node* curNode_this = newHead;
    mtm::SortedList::Node* curNode_other = otherList.head;
    while (curNode_other->next != nullptr) {
        mtm::SortedList::Node* newNode = new mtm::SortedList::Node(curNode_other->next->data);
        curNode_this->next = newNode;
        newNode->prev = curNode_this;
        curNode_this = curNode_this->next;
        curNode_other = curNode_other->next;
    }
    this->len = otherList.len;

    // ADD TRY CATCH EXCEPTION!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}