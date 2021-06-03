#ifndef MOVIE_H_INCLUDED
#define MOVIE_H_INCLUDED
#include <iostream>
using namespace std;
#include <ctime>


class Movie
{
public:
    Movie(const long movieID, const int audienceRadius);
    ~Movie();
    int showAvailableSeats();
    void movieTime();
    void addReservation(const int row, const char col);
    void show();
    bool seatCheck(const int row, const char col);
    long resCode(int pos, const int row, const char col);
    bool resCheck(const int resCheck);
    void cancelRes(int resCode, int resRow, int resCol);
    bool occupiableCheck(const int row, const char col);
    int getRescodeSize();
    void deleteReservations();


private:
    int * reservations;
    int * rescodes;
    int rescodeSize;
    int movieId;
    int availableSeats;
    int totalSeats;
    int column;
    int row;
    int maxRow;
    int maxCol;
    int checkCol;
    int checkRow;
    int radius;
    int calRadius;
    time_t tempId;
};



#endif // MOVIE_H_INCLUDED
