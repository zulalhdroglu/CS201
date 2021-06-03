#define _CRT_SECURE_NO_WARNINGS
#ifndef MOVIE_H_INCLUDED
#define MOVIE_H_INCLUDED
#include <ctime>
#include "SeatList.h"
#include"ResCodeList.h"
class Movie {
public:
    Movie(const long movieID, const int audienceRadius);
    char* movieTime();
    int getAvailableSeats();
    long getMovieId();
    void show();
    bool occupiableCheck(const int row, const char col);
    bool seatCheck(const int row, const char col);
    void addReservation(const int row, const char col);
    long resCode(int pos, const int row, const char col);
    bool resCheck(const int resCheck);
    void cancelRes(int resCode, int resRow, int resCol);
    int getRescodeSize();
private:
    SeatList* seats;
    ResCodeList* codeList;
    long movieId;
    int maxRow;
    int maxCol;
    time_t timeMovie;
    int radius;
    int column;
    int row;
    int checkCol;
    int checkRow;
    int totalSeats;
    int availableSeats;
    int codeCheck;
};


#endif // MOVIE_H_INCLUDED
