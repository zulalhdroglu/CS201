#include "MovieBookingSystem.h"
#include <iostream>
using namespace std;

MovieBookingSystem::MovieBookingSystem() {
	numOfMovie = 0;
	allNumOfMovie = 0;
    movies = new Movie* [numOfMovie];
	allMovies = new Movie* [allNumOfMovie];
	movieIds = new long [numOfMovie];
	allMovieIds = new long [allNumOfMovie];
}
MovieBookingSystem::~MovieBookingSystem() {
    if(numOfMovie!= 0){
        for( int i = 0; i< numOfMovie; i++)
            delete [] movies[i];
        delete [] movies;
    }
	delete[] movieIds;

	if(allNumOfMovie!= 0){
        for( int i = 0; i< allNumOfMovie; i++)
            delete [] allMovies[i];
        delete [] allMovies;
	}
	delete[] allMovieIds;
}
void MovieBookingSystem::addMovie(const long movieID, const int audienceRadius) {
	if (audienceRadius < 7 && audienceRadius >= 0) {
		/*firstly check if such movie exists*/
		for (int i = 0; i < numOfMovie; i++) {
			if (movieIds[i] == movieID) {
				cout << "Movie at ";
				movies[i]->movieTime();
				cout << " already exists" << endl;
				return;
			}
		}

		/*add the new flight to system*/
		numOfMovie++;
		long* tempMovieIds = new long[numOfMovie];
		Movie** tempMovies = new Movie *[numOfMovie];
		for (int i = 0; i < numOfMovie; i++) {
			tempMovieIds[i] = movieIds[i];
			tempMovies[i] = movies[i];
		}
		tempMovies[numOfMovie - 1] = new Movie(movieID, audienceRadius);
		tempMovieIds[numOfMovie - 1] = movieID;
		//It keeps all movies for producing rescode
		allNumOfMovie++;
		long * tempAllMovieIds = new long[allNumOfMovie];
		Movie** tempAllMovies = new Movie * [allNumOfMovie];
		for (int i = 0; i < allNumOfMovie; i++) {
			tempAllMovieIds[i] = allMovieIds[i];
			tempAllMovies[i] = allMovies[i];
		}
		tempAllMovies[allNumOfMovie - 1] = new Movie(movieID, audienceRadius);
		tempAllMovieIds[allNumOfMovie - 1] = movieID;
		delete[] movieIds;
		delete[] movies;
		movies = tempMovies;
		movieIds = tempMovieIds;
		delete[] allMovieIds;
		delete[] allMovies;
		allMovieIds = tempAllMovieIds;
		allMovies = tempAllMovies;
		cout << "Movie at ";
		movies[numOfMovie - 1]->movieTime();
		cout << "has been added" << endl;
	}
	else
		cout << "Enter valid audience radius" << endl;
}
void MovieBookingSystem::cancelMovie(const long movieID) {
	for (int i = 0; i < numOfMovie; i++) {
		if (movieIds[i] == movieID) {
				movies[i]->deleteReservations();
				int tempNumOfMovie = numOfMovie;
				numOfMovie--;
				Movie** tempMovie = new Movie * [numOfMovie];
				long* tempMovieIds = new long[numOfMovie];
				cout << "Movie at ";
				movies[i]->movieTime();
				cout << "has been canceled" << endl << endl;
				for (int j = 0; j < i; j++) {
					tempMovie[j] = movies[j];
					tempMovieIds[j] = movieIds[j];
				}
				for (int k = i + 1; k < numOfMovie; i++) {
					tempMovie[k] = movies[k];
					tempMovieIds[k] = movieIds[k];
				}
				delete[] movieIds;
				delete[] movies;
				movies = tempMovie;
				movieIds = tempMovieIds;
				return;
			}
		}
    cout << "Movie does not exist" << endl;
	return;
	}


void MovieBookingSystem::showAllMovies() {
	if (numOfMovie == 0) {
		cout << "No movie on show" << endl << endl;
	}
	else {
		cout << "Movies on show:" << endl;
		for (int i = 0; i < numOfMovie; i++) {
			cout << "Movie at ";
			movies[i]->movieTime();
			cout << "( " << movies[i]->showAvailableSeats() << " available seats )" << endl;
		}
	}
}
void MovieBookingSystem::showMovie(const long movieID) {
	for (int i = 0; i < numOfMovie; i++)
		if (movieIds[i] == movieID) {
			cout << "Movie at ";
			movies[i]->movieTime();
			cout << "has " << movies[i]->showAvailableSeats() << " available seats" << endl<<endl;
			movies[i]->show();
			return;
		}
	cout << "Movie does not exist " << endl ;
	return;
}
int MovieBookingSystem::makeReservation(const long movieID, const int row, const char col) {
	for (int i = 0; i < numOfMovie; i++) {
		if (movieIds[i] == movieID) {
			if (movies[i]->occupiableCheck(row, col) == true) {
				if (movies[i]->seatCheck(row, col) == true) {
					int check = -1;
					for (int k = 0; k < numOfMovie; k++) {
						if (allMovieIds[k] == movieIds[i])
							check = k;
					}
					movies[i]->addReservation(row, col);
					cout << "Reservation done for " << col << row << " in Movie at ";
					movies[i]->movieTime();
					return movies[i]->resCode(check, row, col);
				}
				else {
					cout << "Seat " << col << row << " is not available in Movie at ";
					movies[i]->movieTime();
					return NULL;
				}
			}
			else {
				cout << "Seat " << col << row << " is not occupiable in Movie at ";
				movies[i]->movieTime();
				return NULL;
			}
		}
	}
	cout << "Movie does not exist!" << endl;
	return NULL;
}
void MovieBookingSystem:: showReservation(const int resCode) {
	int rescode = resCode;
	int resCol = rescode % 100;
	resCol = resCol + 65;
	rescode = rescode / 100;
	int resRow = rescode % 100;
	rescode = rescode / 100;
	int resMovie = rescode % 100;
	for (int i = 0; i < numOfMovie; i++) {
		if (movieIds[i] == allMovieIds[resMovie]) {
			if (movies[i]->resCheck(resCode) == true) {
				cout << "Reservation on Code " << resCode << ": " << " Seat " << (char)resCol << resRow << " in ";
				movies[i]->movieTime();
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
void MovieBookingSystem::cancelReservations(const int numRes, const int* resCode) {
	int rescode;
	int tempRescode;
	int resCol = 0;
	int resRow = 0;
	int resMovie;
	int check = 0;
	for (int i = 0; i < numRes; i++) {
		for (int k = 0; k < numOfMovie; k++) {
			rescode = resCode[i];
			tempRescode = resCode[i];
			resCol = tempRescode % 100;
			resCol = resCol + 65;
			tempRescode = tempRescode / 100;
			resRow = tempRescode % 100;
			tempRescode = tempRescode / 100;
			resMovie = tempRescode % 100;
			if (movieIds[k] == allMovieIds[resMovie]){
				if (movies[k]->resCheck(rescode) == true && resCode[k] > 0) {
					cout << "Reservation on code " << resCode[i] << " canceled: Seat " << (char)resCol << resRow << " in Movie ";
					movies[k]->movieTime();
					movies[k]->cancelRes(rescode, resRow, resCol);

				}
				else {
					cout << "Some reservation codes do not exist. Cancelation failed" << endl;
					return;
				}

			}
		}
	}
}
