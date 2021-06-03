#ifndef MOVIEBOOKINGSYSTEM_H_INCLUDED
#define MOVIEBOOKINGSYSTEM_H_INCLUDED
#include "ReservationList.h"
#include "Movie.h"
#include "MovieList.h"
#include <iostream>
class MovieBookingSystem {
public:
	const static int numOfRow = 30;
	const static int numOfColumn = 26;
	MovieBookingSystem();
	~MovieBookingSystem();
	void addMovie(const long movieID, const int audienceRadius);
	void cancelMovie(const long movieID);
	void showAllMovies() const; 
	void showMovie(const long movieID) const;
	int makeReservation(const long movieID, const int row, const char
		col);
	void cancelReservations(ReservationList resCode);
	void showReservation(const int resCode) const;
	char* showTime(long movieId);
private:
	ReservationList reservationCodes;
	MovieList movies;
	MovieList allMovies;
	int check;
	int allMoviesCheck;
};
#endif