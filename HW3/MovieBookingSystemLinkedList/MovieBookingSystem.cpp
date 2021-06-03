#include"MovieBookingSystem.h"
#include "MovieList.h"
#include <string>
#include <stddef.h>
using namespace std;

MovieBookingSystem::MovieBookingSystem(){
	MovieList * movies;
	MovieList* allMovies;
	check = 1;
	allMoviesCheck = 1;
}
MovieBookingSystem::~MovieBookingSystem() {


}

void MovieBookingSystem::addMovie(const long movieID, const int audienceRadius) {
	if (audienceRadius >= 0 && audienceRadius <= 7) {
		//check the movieId first
		int length = movies.getLength();
		Movie* tempMovie =NULL;
		if (length >= 1) {
			int pos;
			if (movies.findMovie(movieID, pos, tempMovie) == true) {
				cout << "Movie at "<<tempMovie->movieTime() << " already exist!"<<endl;
				return;
			}
			else {
				Movie* movie = new Movie(movieID, audienceRadius);
				movies.insert(check, movieID, audienceRadius, movie);
				allMovies.insert(allMoviesCheck, movieID, audienceRadius, movie);
				cout << "Movie at " << movie->movieTime()<< "has been added" << endl;
				check++;
				allMoviesCheck++;
				return;
			}
		}
		else {
			Movie* movie = new Movie(movieID, audienceRadius);
			movies.insert(check, movieID, audienceRadius, movie);
			allMovies.insert(allMoviesCheck, movieID, audienceRadius, movie);
			cout << "Movie at "<< movie->movieTime() << "has been added" << endl;
			check++;
			allMoviesCheck++;
			return;
		}
	}
	else {
		cout << "Enter a valid audience radius";
		return;
	}
}
void MovieBookingSystem::cancelMovie(const long movieID) {
	//firstly check if movie exists
	int tempIndex;
	Movie* tempMovie = NULL;
	int length = movies.getLength();
	if (movies.findMovie(movieID, tempIndex , tempMovie) == true) {
		cout << "Movie at "<<tempMovie->movieTime()<< "has been canceled" << endl << endl;
		movies.remove(tempIndex);
		check--;
		return;
	}
	else {
		cout << "Movie at "<< showTime(movieID)<< "does not exist!" <<endl;
		return;
	}
}
void MovieBookingSystem::showAllMovies() const {
	long tempmovieId = 0;
	Movie* tempmovie = NULL ;
	int tempIndex;
		if (movies.getLength() == 0) {
			cout << "No movies on show! "<< endl << endl;
	    }
		else {
			cout << "Movies on show:" << endl;

			for (int i = 1; i <= movies.getLength(); i++) {
				movies.retrieve(i, tempmovieId, tempmovie);
				cout << "Movie at "<< tempmovie->movieTime() << "( " << tempmovie->getAvailableSeats() << " available seats )" << endl;
			}
		}
	}
void MovieBookingSystem::showMovie(const long movieID) const {
	Movie* tempMovie=NULL;
	long tempId;
	for (int i = 1; i <= movies.getLength(); i++) {
		movies.retrieve(i, tempId, tempMovie);
		if (tempMovie->getMovieId() == movieID) {
			cout << "Movie at " << tempMovie->movieTime() << "has " << tempMovie->getAvailableSeats() << " available seats" << endl << endl;
			tempMovie->show();
			return;
		}
	}
	cout << "Movie does not exist!" << endl;
	return;
}
int MovieBookingSystem::makeReservation(const long movieID, const int row, const char col) {
	Movie* tempMovie = NULL;
	long tempId;
	for (int i = 1; i <= movies.getLength(); i++) {
		movies.retrieve(i, tempId, tempMovie);
		if (tempId == movieID) {
			if (tempMovie->occupiableCheck(row, col) == true) {
				if (tempMovie->seatCheck(row, col) == true) {
					int check = -1;
					for (int k = 1; k <= movies.getLength(); k++) {
						long temp2;
						Movie* tempId2 = NULL;
						allMovies.retrieve(k, temp2, tempId2);
						if (temp2 == tempId)
							check = k;
					}
					tempMovie->addReservation(row, col);
					cout << "Reservation done for " << col << row << " in Movie at " << tempMovie->movieTime();
					return tempMovie->resCode(check,row,col);
				}
				else {
					cout << "Seat " << col << row << " is not available in Movie at "<< tempMovie->movieTime();
					return NULL;
				}
			}
			else {
				cout << "Seat " << col << row << " is not occupiable in Movie at "<< tempMovie->movieTime();
				return NULL;
			}
		}
	}
	cout << "Movie does not exist!" << endl;
	return NULL;
	delete tempMovie;
}
void MovieBookingSystem::cancelReservations(ReservationList resCode){
	int rescode;
	int rescode2;
	int tempRescode;
	int resCol = 0;
	int resRow = 0;
	int resMovie;
	int check = 0;
	for (int i = 1; i <= resCode.getLength(); i++) {
		for (int k = 1; k <= movies.getLength(); k++) {
			resCode.retrieve(i, rescode);
			tempRescode = rescode;
			resCol = tempRescode % 100;
			resCol = resCol + 65;
			tempRescode = tempRescode / 100;
			resRow = tempRescode % 100;
			tempRescode = tempRescode / 100;
			resMovie = tempRescode % 100;
			Movie* tempMovie, * tempAllMovie = NULL;
			long tempId, tempAllIds;
			movies.retrieve(k, tempId, tempMovie);
			allMovies.retrieve(resMovie, tempAllIds, tempAllMovie);
			if (tempId== tempAllIds) {
				resCode.retrieve(k, rescode2);
				if (tempMovie->resCheck(rescode) == true && rescode2 > 0) {
					cout << "Reservation on code " << rescode << " canceled: Seat " << (char)resCol << resRow << " in Movie " << tempMovie->movieTime();
					tempMovie->cancelRes(rescode, resRow, resCol);	
				}
				else {
					cout << "Some reservation codes do not exist. Cancelation failed" << endl;
					return;
				}

			}
		}
	}
	return;
 }

void MovieBookingSystem::showReservation(const int resCode) const {
	int rescode = resCode;
	int resCol = rescode % 100;
	resCol = resCol + 65;
	rescode = rescode / 100;
	int resRow = rescode % 100;
	rescode = rescode / 100;
	int resMovie = rescode % 100;
	for (int i =1; i <= movies.getLength(); i++) {
		long tempMovieId;
		long tempallId;
		Movie* tempMovie, *tempAllMovies = NULL;
		movies.retrieve(i, tempMovieId, tempMovie);
		allMovies.retrieve(resMovie, tempallId, tempAllMovies);
		if (tempMovieId == tempallId) {
			if (tempMovie->resCheck(resCode) == true && tempMovie->getRescodeSize() > 0) {
				cout << "Reservation with Code " << resCode << ": " << " Seat " << (char)resCol << resRow << " in "<< tempMovie->movieTime();
				return;
			}
			else {
				cout << "No reservation with Code " << resCode << endl;
				return;
			}
		}
	}
	cout << "No reservation with Code " << resCode << endl;
	return;

}
char* MovieBookingSystem:: showTime(long movieId) {
	time_t temp = (time_t)movieId;
	time_t* p = &temp;
	char* dateTime = ctime(p);
	//cout << dateTime;
	return dateTime;
}