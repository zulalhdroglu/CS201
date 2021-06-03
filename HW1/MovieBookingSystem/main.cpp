#include <iostream>
#include "MovieBookingSystem.h"
using namespace std;
#include <ctime>

int main()
{
MovieBookingSystem M;
	int* codes = new int[2];
	M.showAllMovies();
	cout << endl;
	M.addMovie(1614791273, 0);
	M.addMovie(1614801273, 3);
	M.addMovie(1615801273, 1);
	cout << endl;
	M.showAllMovies();
	cout << endl;
	M.addMovie(1614791273, 2);
	cout << endl;
	codes[1] = M.makeReservation(1614801273, 1, 'A');
	codes[0] = M.makeReservation(1614801273, 9, 'A');
	cout << endl;
	M.showMovie(1614801273);
	cout << endl;
	M.showReservation(codes[0]);
	cout << endl;
	M.cancelReservations(2, codes);
	cout << endl;
	codes[0] = M.makeReservation(1614801273, 1, 'A');
	M.makeReservation(1614801273, 1, 'A');
	M.makeReservation(1614801273, 5, 'E');
	M.makeReservation(1614801273, 5, 'M');
	cout << endl;
	codes[1] = -1;
	M.cancelReservations(2, codes);
	M.showReservation(codes[0]);
	cout << endl;
	M.makeReservation(1614801273, 12, 'D');
	cout << endl;
	M.showMovie(1614801273);
	cout << endl;
	M.cancelMovie(1614801273);
	M.showReservation(codes[0]);
	cout << endl;
	M.cancelMovie(1614801273);
	M.addMovie(1614801273, 4);
	M.showMovie(1614801273);
	delete[] codes;
	return 0;
}
