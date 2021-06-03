#include "ReservationList.h"
#include <stddef.h>
ReservationList::ReservationList() {
	size = 0;
	head = NULL;
}
ReservationList:: ReservationList(const ReservationList& aReservationList): size(aReservationList.size){
if(aReservationList.head == NULL)
head = NULL;  // original list is empty
   else {
   // copy first node
   head = new ReservationNode;
   head->Code = aReservationList.head->Code;
   // copy rest of list
   ReservationNode* newPtr = head;  // new list ptr

   for (ReservationNode* origPtr = aReservationList.head->next;origPtr != NULL; origPtr = origPtr->next) {
       newPtr->next = new ReservationNode;
       newPtr = newPtr->next;
       newPtr->Code = origPtr->Code;
   }
   newPtr->next = NULL;
   }
}
ReservationList::~ReservationList() {
    ReservationNode* cur = head;
    while (cur != NULL)
    {
        ReservationNode* temp = cur->next;
        delete cur;
        cur = temp;
    }
    while (!isEmpty())
        remove(1);
}
bool ReservationList::isEmpty() const {
    bool check = false;
    if (size != 0)
        check = true;
    return check;
}
int ReservationList::getLength() const {
    return size;
}
bool ReservationList::retrieve(int index, int& resCode) const {
    if ((index < 1) || (index > getLength()))
        return false;
    ReservationNode* cur = find(index);
    resCode = cur->Code;
    return true;
}
ReservationList::ReservationNode* ReservationList::find(int index) const {
    if ((index < 1) || (index > getLength()))
        return NULL;
    else { // count from the beginning of the list
        ReservationNode* cur = head;
        for (int skip = 1; skip < index; ++skip)
            cur = cur->next;
        return cur;
    }
}
bool ReservationList::insert(int index, int resCode) {
    int newLength = getLength() + 1;
    if ((index < 1) || (index > newLength))
        return false;
    ReservationNode* newPtr = new ReservationNode;
    size = newLength;
    newPtr->Code = resCode;

    if (index == 1) {
        newPtr->next = head;
        head = newPtr;
    }
    else {
        ReservationNode* prev = find(index - 1);
        newPtr->next = prev->next;
        prev->next = newPtr;
    }
    return true;
}
bool ReservationList::remove(int index) {
    ReservationNode* cur;

    if ((index < 1) || (index > getLength()))
        return false;

    --size;
    if (index == 1) {
        cur = head;
        head = head->next;
    }
    else {
        ReservationNode* prev = find(index - 1);
        cur = prev->next;
        prev->next = cur->next;
    }
    cur->next = NULL;
    delete cur;
    cur = NULL;
    return true;
}
