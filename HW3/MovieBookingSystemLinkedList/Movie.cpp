#define _CRT_SECURE_NO_WARNINGS
#include "Movie.h"
#include <iostream>
#include <ctime>
#include "SeatList.h"
#include <string>
#include <time.h>
using namespace std;
Movie::Movie(const long movieID, const int audienceRadius) {
    seats = new SeatList;
    codeList = new ResCodeList;
    codeCheck = 1;
    movieId = movieID;
    maxRow = 30;
    maxCol = 26;
    timeMovie = (time_t)movieId;
    radius = audienceRadius;
    radius++;
    column = maxCol / radius;
    row = maxRow / radius;
    checkCol = column * radius;
    checkRow = row * radius;
    if (checkCol < maxCol)
        column++;
    if (checkRow < maxRow)
        row++;
    totalSeats = column * row;//total seats
    availableSeats = column * row; //available seats
    int check = 0;
    for (int i = 1; i <= totalSeats; i++)
        seats->insert(i, check);
}
char* Movie::movieTime() {
    time_t* p = &timeMovie;
    char* dateTime = ctime(p);
    return dateTime;
}
int Movie::getAvailableSeats() {
    return availableSeats;
}
long Movie::getMovieId() {
    return movieId;
}
void Movie::show() {
    char letters[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
    int control = 0;
    cout << "    ";
    while (control < 26) {
        cout << " " << letters[control] << " ";
        control = control + radius;
    }
    cout << endl;
    int n = 1;
    int displayNum = 0;
    int show = 1;
    int check;
    for (int j = 0; j < totalSeats; j++) {
        if (displayNum % column == 0) {
            if (show >= 10) {
                cout << " " << show << " ";
                show = show + radius;
                displayNum++;
            }
            else {
                cout << " " << show << "  ";
                show = show + radius;
                displayNum++;
            }
        }
        else
            displayNum++;
        seats->retrieve(j+1, check);
        if (check == 0)
            cout << " o ";
        else
            cout << " x ";

        if (j == (column * n) - 1) {
            cout << endl;
            n++;
        }
    }
}
bool Movie::occupiableCheck(const int row, const char col) {
    int numOfCol = ((int)(col)-65); //3
    int numOfRow = (row - 1);
    if (numOfCol % radius == 0 && numOfRow % radius == 0)
        return true;
    return false;
}
bool Movie::seatCheck(const int row, const char col) {
    int numOfCol = ((int)(col)-65) / radius;//3
    int numOfRow = (row / radius);
    numOfCol++;
    int val = numOfRow * column;
    val = val + numOfCol;
    int check;
    seats->retrieve(val, check);
    if (check == 0)
        return true;
    else
        return false;
}
void Movie::addReservation(const int row, const char col) {
    //numOfReservation++;
    int numOfCol = ((int)(col)-65) / radius;//4
    numOfCol++;//5
    int numOfRow = (row / radius); //4
    //numOfRow++;//5

    int val;
    numOfRow = numOfRow * column;
    val = numOfRow + numOfCol; //30
    int check;
    seats->retrieve(val, check);
    if (check == 0) {
        int newCheck = 1;
        seats->update(val, newCheck);
        availableSeats--;
        return;
    }
     
}
long Movie::resCode(int pos, const int row, const char col) {
    int numericCol = (int)col - 65;
    int tempMovieId = ((((100 + pos) * 100) + row) * 100) + numericCol;
    codeList->insert(codeCheck, tempMovieId);
    return tempMovieId;
}
bool Movie::resCheck(const int resCode) {
    for (int i = 1; i <= codeList->getLength(); i++) {
        int tempCode;
        codeList->retrieve(i, tempCode);
        if (tempCode == resCode) {
            return true;
        }
    }
    return false;
}
void Movie::cancelRes(int resCode, int resRow, int resCol) {
    int tempCode;
    for (int i = 1; i <= codeList->getLength(); i++) {
        codeList->retrieve(i, tempCode);
        if (tempCode == resCode) {
            int numOfCol = (resCol - 65) / radius;
            numOfCol++;//4
            int numOfRow = resRow / radius;//1
            int val = numOfRow * column;//7
            val = val + numOfCol;//11
            
            codeList->remove(i);
            int check = 0;
            seats->update(val, check);
            availableSeats++;
        }
    }
}
int Movie::getRescodeSize() {
    return codeList->getLength();;
}