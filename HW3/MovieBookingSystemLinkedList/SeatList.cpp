#include "SeatList.h"
#include <stddef.h>
SeatList::SeatList() {
    size = 0;
    head = NULL;
}
SeatList::SeatList(const SeatList& aSeatList) : size(aSeatList.size) {
    if (aSeatList.head == NULL)
        head = NULL;  // original list is empty
    else {
        // copy first node
        head = new SeatNode;
        head->check = aSeatList.head->check;
        // copy rest of list
        SeatNode* newPtr = head;  // new list ptr

        for (SeatNode* origPtr = aSeatList.head->next; origPtr != NULL; origPtr = origPtr->next) {
            newPtr->next = new SeatNode;
            newPtr = newPtr->next;
            newPtr->check = origPtr->check;
        }
        newPtr->next = NULL;
    }
}
SeatList::~SeatList() {
    SeatNode* cur = head;

    while (cur != NULL)
    {
        SeatNode* temp = cur->next;
        delete cur;
        cur = temp;
    }
    while (!isEmpty())
        remove(1);
}
bool SeatList::isEmpty() const {
    bool check = false;
    if (size != 0)
        check = true;
    return check;
}
int SeatList::getLength() const {
    return size;
}
bool SeatList::retrieve(int index, int& empty) const {
    if ((index < 1) || (index > getLength()))
        return false;
    SeatNode* cur = find(index);
    empty = cur->check;
    return true;
}
SeatList::SeatNode* SeatList::find(int index) const {
    if ((index < 1) || (index > getLength()))
        return NULL;
    else { // count from the beginning of the list
        SeatNode* cur = head;
        for (int skip = 1; skip < index; ++skip)
            cur = cur->next;
        return cur;
    }
}
bool SeatList::insert(int index, int empty) {
    int newLength = getLength() + 1;
    if ((index < 1) || (index > newLength))
        return false;

    SeatNode* newPtr = new SeatNode;
    size++;
    newPtr->check = empty;

    if (index == 1) {
        newPtr->next = head;
        head = newPtr;
    }
    else {
        SeatNode* prev = find(index - 1);
        newPtr->next = prev->next;
        prev->next = newPtr;
    }
    return true;
}
bool SeatList::remove(int index) {
    SeatNode* cur;

    if ((index < 1) || (index > getLength()))
        return false;

    --size;
    if (index == 1) {
        cur = head;
        head = head->next;
    }
    else {
        SeatNode* prev = find(index - 1);
        cur = prev->next;
        prev->next = cur->next;
    }
    cur->next = NULL;
    delete cur;
    cur = NULL;
    return true;
}
bool SeatList::update(int index, int newCheck) {
    SeatNode* newNode;
    newNode = find(index);
    newNode->check = newCheck;
    return true;
}
