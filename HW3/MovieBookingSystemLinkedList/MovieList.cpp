#include "MovieList.h"
#include <stddef.h>
MovieList::MovieList() {
    size = 0;
    head = NULL;
}
MovieList::MovieList(const MovieList& aMovieList) : size(aMovieList.size) {
    if (aMovieList.head == NULL)
        head = NULL;  // original list is empty
    else {
        // copy first node
        head = new MovieNode;
        head->movieId = aMovieList.head->movieId;
        head->audienceRadius = aMovieList.head->audienceRadius;
        head->movie = aMovieList.head->movie;
        // copy rest of list
        MovieNode* newPtr = head;  // new list ptr

        for (MovieNode* origPtr = aMovieList.head->next; origPtr != NULL; origPtr = origPtr->next) {
            newPtr->next = new MovieNode;
            newPtr = newPtr->next;
            newPtr->movieId = origPtr->movieId;
            newPtr->audienceRadius = origPtr->audienceRadius;
            newPtr->movie = origPtr->movie;
        }
        newPtr->next = NULL;
    }
}
MovieList::~MovieList() {
    MovieNode* cur = head;

    while (cur != NULL)
    {
        MovieNode* temp = cur->next;
        delete cur;
        cur = temp;
    }
    while (!isEmpty())
        remove(1);
}
bool MovieList::isEmpty() const {
    bool check = false;
    if (size != 0)
        check = true;
    return check;
}
int MovieList::getLength() const {
    return size;
}
bool MovieList::retrieve(int index, long& movieID, Movie*& movieptr) const {
    if ((index < 1) || (index > getLength()))
        return false;
    MovieNode* cur = find(index);
    movieID = cur->movieId;
    movieptr = cur->movie;
    return true;
}
MovieList::MovieNode* MovieList::find(int index) const {
    if ((index < 1) || (index > getLength()))
        return NULL;
    else { // count from the beginning of the list
        MovieNode* cur = head;
        for (int skip = 1; skip < index; ++skip)
            cur = cur->next;
        return cur;
    }
}
bool MovieList::insert(int index, long movieID, int radius, Movie* movieptr) {
    int newLength = getLength() + 1;
    if ((index < 1) || (index > newLength))
        return false;
    MovieNode* newPtr = new MovieNode;
    size = newLength;
    newPtr->movie = movieptr;
    newPtr->movieId = movieID;
    newPtr->audienceRadius = radius;

    if (index == 1) {
        newPtr->next = head;
        head = newPtr;
    }
    else {
        MovieNode* prev = find(index - 1);
        newPtr->next = prev->next;
        prev->next = newPtr;
    }
    return true;
}
bool MovieList::remove(int index) {
    MovieNode* cur;

    if ((index < 1) || (index > getLength()))
        return false;

    --size;
    if (index == 1) {
        cur = head;
        head = head->next;
    }
    else {
        MovieNode* prev = find(index - 1);
        cur = prev->next;
        delete prev->movie;
        prev->next = cur->next;
    }
    cur->next = NULL;
    delete cur;
    cur = NULL;
    return true;
}
bool MovieList::findMovie(long movieID, int& index, Movie*& tempMovie) const {
    MovieNode* temp = NULL;
    for (int i = 1; i <= size; i++) {
        temp = find(i);
        if (temp->movie->getMovieId() == movieID) {
           index = i;
           tempMovie = temp->movie;
            return true;
        }
    }
    return false;
}