/*/-------------------------------------------------------------------------------------//
    Filename:           LinkedBag.cpp
    Date:               10/19/2020
    Description:        LinkedBag ADT, with nodes implemented as 
                        instances of a private 'Node' struct type
//-------------------------------------------------------------------------------------/*/

#include <cstddef>

namespace cs_bag {

    template<class T>
    LinkedBag<T>::LinkedBag() {
        headPtr = nullptr;
        itemCount = 0;
    }





    template<class T>
    LinkedBag<T>::LinkedBag(const LinkedBag<T>& aBag) {
        itemCount = aBag.itemCount;
        Node* origChainPtr = aBag.headPtr;

        if (origChainPtr == nullptr) {
            headPtr = nullptr;
        }
        else {
            
            headPtr = new Node();
            headPtr->item = origChainPtr->item;

            Node* newChainPtr = headPtr;
            origChainPtr = origChainPtr->next;

            while (origChainPtr != nullptr) {
                
                T nextItem = origChainPtr->item;

                Node* newNodePtr = new Node();
                newNodePtr->item = nextItem;

                newChainPtr->next = newNodePtr;

                newChainPtr = newChainPtr->next;

                origChainPtr = origChainPtr->next;
            }

            newChainPtr->next = nullptr;
        }
    }





    template<class T>
    LinkedBag<T>::~LinkedBag() {
        clear();
    }





    template<class T>
    bool LinkedBag<T>::isEmpty() const {
        return itemCount == 0;
    }





    template<class T>
    int LinkedBag<T>::getCurrentSize() const {
        return itemCount;
    }





    template<class T>
    void LinkedBag<T>::add(const T& newEntry) {
        Node* nextNodePtr = new Node();
        nextNodePtr->item = newEntry;
        nextNodePtr->next = headPtr;

        headPtr = nextNodePtr;
        itemCount++;
    }




    

    template<class T>
    void LinkedBag<T>::remove(const T& anEntry) {
        
        Node* entryNodePtr = headPtr;
        while (entryNodePtr != nullptr) {

            if (anEntry == entryNodePtr->item)
                break;
            else
                entryNodePtr = entryNodePtr->next;
        }
        
        // Remove the entry if found
        if (entryNodePtr == nullptr) {
            throw ItemNotFoundError();
        }
        else {
            
            entryNodePtr->item = headPtr->item;
            Node* nodeToDeletePtr = headPtr;
            headPtr = headPtr->next;
            delete nodeToDeletePtr;

            itemCount--;
        }
    }





    template<class T>
    void LinkedBag<T>::clear() {
        Node* nodeToDeletePtr = headPtr;
        while (headPtr != nullptr) {
            headPtr = headPtr->next;
            delete nodeToDeletePtr;
            nodeToDeletePtr = headPtr;
        }

        headPtr = nullptr;
        itemCount = 0;
    }





    template<class T>
    int LinkedBag<T>::getFrequencyOf(const T& anEntry) const {
        int frequency = 0;
        int counter = 0;
        Node* curPtr = headPtr;
        while ((curPtr != nullptr) && (counter < itemCount)) {
            if (anEntry == curPtr->item) {
                frequency++;
            }

            counter++;
            curPtr = curPtr->next;
        }

        return frequency;
    }





    template<class T>
    bool LinkedBag<T>::contains(const T& anEntry) const {

        Node* curPtr = headPtr;

        while (curPtr != nullptr) {

            if (anEntry == curPtr->item)
                return true;
            else
                curPtr = curPtr->next;
        }
        return false;
    }


}   // closes namespace


