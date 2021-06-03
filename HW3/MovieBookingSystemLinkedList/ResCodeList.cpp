#include "ResCodeList.h"
#include <stddef.h>
ResCodeList::ResCodeList() {
    size = 0;
    head = NULL;
}
ResCodeList::ResCodeList(const ResCodeList& aResCodeList) : size(aResCodeList.size) {
    if (aResCodeList.head == NULL)
        head = NULL;  // original list is empty
    else {
        // copy first node
        head = new SeatNode;
        head->ResCode = aResCodeList.head->ResCode;
        // copy rest of list
        SeatNode* newPtr = head;  // new list ptr

        for (SeatNode* origPtr = aResCodeList.head->next; origPtr != NULL; origPtr = origPtr->next) {
            newPtr->next = new SeatNode;
            newPtr = newPtr->next;
            newPtr->ResCode = origPtr->ResCode;
        }
        newPtr->next = NULL;
    }
}
ResCodeList::~ResCodeList() {
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
bool ResCodeList::isEmpty() const {
    bool check = false;
    if (size != 0)
        check = true;
    return check;
}
int ResCodeList::getLength() const {
    return size;
}
bool ResCodeList::retrieve(int index,  int& rescode) const {
    if ((index < 1) || (index > getLength()))
        return false;
    SeatNode* cur = find(index);
    rescode = cur->ResCode;
    return true;
}
ResCodeList::SeatNode* ResCodeList::find(int index) const {
    if ((index < 1) || (index > getLength()))
        return NULL;
    else { // count from the beginning of the list
        SeatNode* cur = head;
        for (int skip = 1; skip < index; ++skip)
            cur = cur->next;
        return cur;
    }
}
bool ResCodeList::insert(int index, long rescode) {
    int newLength = getLength() + 1;
    if ((index < 1) || (index > newLength))
        return false;

    SeatNode* newPtr = new SeatNode;
    size++;
    newPtr->ResCode = rescode;
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
bool ResCodeList::remove(int index) {
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

