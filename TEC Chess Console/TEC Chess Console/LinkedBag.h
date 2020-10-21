/*/-------------------------------------------------------------------------------------//
    Filename:           LinkedBag.h
    Date:               10/19/2020
    Description:        LinkedBag ADT, with nodes implemented as 
                        instances of a private 'Node' struct type
//-------------------------------------------------------------------------------------/*/

#ifndef LINKED_BAG_
#define LINKED_BAG_

#include "BagInterface.h"
#include <cstdlib>

namespace cs_bag {

    template<class T>
    class LinkedBag : public BagInterface<T>
    {

    public:
        class ItemNotFoundError {};
        LinkedBag();
        LinkedBag(const LinkedBag<T>& aBag);
        virtual ~LinkedBag();
        int getCurrentSize() const;
        bool isEmpty() const;
        void add(const T& newEntry);
        void remove(const T& anEntry);
        void clear();
        bool contains(const T& anEntry) const;
        int getFrequencyOf(const T& anEntry) const;
        
    private:
        
        struct Node {

            Node* next;
            T item;
            Node() : item(T()), next(nullptr) {}
        };

        Node* headPtr;
        int itemCount;
    };
}

#include "LinkedBag.cpp"
#endif
