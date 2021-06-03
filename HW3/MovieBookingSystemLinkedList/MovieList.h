#ifndef MOVIELIST_H_INCLUDED
#define MOVIELIST_H_INCLUDED
#include "Movie.h"
class MovieList {
public:
	MovieList();
	MovieList(const MovieList& aList);
	~MovieList();
	bool isEmpty() const;
	int getLength() const;
	bool retrieve(int index, long& movieID, Movie*& movieptr) const;
	bool insert(int index, long movieID, int radius, Movie* movieptr);
	bool remove(int index);
	bool findMovie(long movieID, int& index, Movie*& tempMovie) const;
private:
	struct MovieNode {
		long movieId;
		int audienceRadius;
		Movie* movie;
		MovieNode* next;
	};
	int size;
	MovieNode* head;
	MovieNode* find(int index) const;
};
#endif
