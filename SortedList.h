#pragma once

#include <iostream>
#include <stdexcept>

namespace mtm {

    // using T = int;
template <typename T>
class SortedList {
    private:
        class Node;
        Node* head;
        unsigned int len;

    public:
        class ConstIterator;
        SortedList(): head(nullptr), len(0) { }
        SortedList(const SortedList& otherList);
        SortedList& operator=(const SortedList& otherList);
        ~SortedList();
        SortedList& Insert(const T& newData);
        SortedList& remove(const ConstIterator& it);
        unsigned int length() const;
        ConstIterator begin() const;
        ConstIterator end() const;

        // Esoteric stuff
        template<typename Cond>
        SortedList filter(const Cond& filterFunc) const;
        template <typename Transformer>
        SortedList apply(const Transformer& transformer) const;

        //helper function
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


    template <class T>
    class SortedList<T>::ConstIterator {
        private:
            friend class SortedList;
            Node* currNode; // Maybe no need for const here
            ConstIterator(Node* nodeToPointAt): currNode(nodeToPointAt){}
        public:
            ConstIterator() : currNode(nullptr) {}
            ConstIterator(const ConstIterator& it) = default;
            ~ConstIterator() = default;
            ConstIterator& operator=(const ConstIterator& it) = default;

            const T& operator*() const;
            ConstIterator& operator++();
            bool operator!=(const ConstIterator& it) const;


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

template <typename T>
    class SortedList<T>::Node {
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

using namespace mtm;
//--------------------- SortedList  implementations ------------------------------

template <typename T>
SortedList<T>::SortedList(const SortedList& otherList): head(nullptr), len(0) {
    this->listCopier(otherList);
}

template <typename T>
SortedList<T>& SortedList<T>::operator=(const SortedList& otherList){
    if (this == &otherList) {
        return *this;
    }
    this->listCopier(otherList);
    return *this;
}
template <typename T>
SortedList<T>::~SortedList() {
    delete this->head;
}
template <typename T>
SortedList<T>& SortedList<T>::Insert(const T& newData) {
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
template <typename T>
SortedList<T>& SortedList<T>::remove(const SortedList<T>::ConstIterator& it) {
    // edge cases
    if(this->head == nullptr || it.currNode == nullptr){
        return *this;
    }
    if(this->head == it.currNode){
        this->head = head->next;
        this->head->prev = nullptr;
        it.currNode->next = nullptr;
    }else if(it.currNode->next == nullptr && it.currNode->prev != nullptr){
        it.currNode->prev->next = nullptr;
    } else if(it.currNode->next != nullptr && it.currNode->prev != nullptr){
        it.currNode->prev->next = it.currNode->next;
        it.currNode->next->prev = it.currNode->prev;
        it.currNode->next = nullptr;
    }
    delete it.currNode;
    this->len--;
    return *this;
}
template <typename T>
unsigned int SortedList<T>::length() const{
    return this->len;
}
template <typename T>
typename SortedList<T>::ConstIterator SortedList<T>::begin() const{
    return ConstIterator(this->head);
}
template <typename T>
typename SortedList<T>::ConstIterator SortedList<T>::end() const{
    return ConstIterator(nullptr);
}
// -------------------- SortedList Esoteric functions -----------------------------------------
template<typename T>
template<typename Cond>
typename SortedList<T> SortedList<T>::filter(const Cond& filterFunc) const {
    SortedList<T> retList;
    for(SortedList::ConstIterator it = this->begin(); it != this->end(); ++it) {
        if(filterFunc(*it) == true) {
            retList.Insert(*it);
        }
    }
    return retList;
}

template<typename T>
template <typename Transformer>
typename SortedList<T> SortedList<T>::apply(const Transformer& transformer) const {
    SortedList<T> retList;
    for(SortedList::ConstIterator it = this->begin(); it != this->end(); ++it) {
        T newElement = transformer(*it);
        retList.Insert(newElement);
    }
    return retList;
}


//--------------------- SortedList ConstIterator implementations ------------------------------
template <typename T>
const T& SortedList<T>::ConstIterator::operator*() const {
    if (this->currNode == nullptr) {
        throw std::out_of_range("Dereferencing nullptr");
    }
    return this->currNode->data;
}
template <typename T>
typename SortedList<T>::ConstIterator& SortedList<T>::ConstIterator::operator++() {
    if (this->currNode == nullptr) {
        throw std::out_of_range("Out of range");
    }
    this->currNode = this->currNode->next;
    return *this;
}
template <typename T>
bool SortedList<T>::ConstIterator::operator!=(const SortedList<T>::ConstIterator& it) const {
    return this->currNode != it.currNode;
}

//--------------------- SortedList helper functions implementations ------------------------------
template <typename T>
void SortedList<T>::listCopier(const SortedList &otherList) {
    if (otherList.head == nullptr) {
        this->head = nullptr;
        this->len = 0;
        return;
    }
    try {
        SortedList<T>::Node* newHead = new SortedList<T>::Node(otherList.head->data);
        SortedList<T>::Node* curNode_this = newHead;
        SortedList<T>::Node* curNode_other = otherList.head;
        while (curNode_other->next != nullptr) {
            SortedList<T>::Node* newNode = new SortedList<T>::Node(curNode_other->next->data);
            curNode_this->next = newNode;
            newNode->prev = curNode_this;
            curNode_this = curNode_this->next;
            curNode_other = curNode_other->next;
        }
        Node *prevHead = this->head;
        this->head = newHead;
        delete prevHead;
        this->len = otherList.len;
    } catch (...) {
        delete this->head;
        throw;
    }
}