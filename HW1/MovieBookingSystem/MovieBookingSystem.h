#ifndef MOVIEBOOKINGSYSTEM_H_INCLUDED
#define MOVIEBOOKINGSYSTEM_H_INCLUDED
#include <iostream>
#include "Movie.h"
using namespace std;

class MovieBookingSystem
{
public:
	const static int numOfRow = 30;
	const static int numOfColumn = 26;
	MovieBookingSystem();
	~MovieBookingSystem();
	void addMovie(const long movieID, const int audienceRadius);
	void cancelMovie(const long movieID);
	void showAllMovies();
	void showMovie(const long movieID);
	int makeReservation(const long movieID, const int row, const char col);
	void cancelReservations(const int numRes, const int* resCode);
	void showReservation(const int resCode);


private:
	int numOfMovie;
	Movie** movies;
	Movie** allMovies;
	long* allMovieIds;
	long* movieIds;
	int allNumOfMovie;
};


#endif // MOVIEBOOKINGSYSTEM_H_INCLUDED
