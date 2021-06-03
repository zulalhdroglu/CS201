
#include "Movie.h"
#include <string>
#include <iostream>
#include <ctime>
#include <time.h>
using namespace std;


Movie::Movie(const long movieID, const int audienceRadius) {
    movieId = movieID;
    maxRow = 30;
    maxCol = 26;

    tempId = (time_t) movieID;
    calRadius = audienceRadius; //add reservation
    radius = audienceRadius;
    radius++;//showing seating plan
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
    reservations = new int[totalSeats];
    for (int i = 0; i < totalSeats; i++)
        reservations[i] = 0;
    rescodeSize = 0;
    rescodes = NULL;
    //	numOfReservation = 0;
}
Movie:: ~Movie() {
    delete[] reservations;
    delete[] rescodes;

}
int Movie::showAvailableSeats() {
    return availableSeats;
}
void Movie::movieTime() {
    time_t* p = &tempId;
    char* dateTime = ctime(p);
    cout << dateTime;
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

    val--;//26
    if (reservations[val] == 0) {
        reservations[val] = 1;
        availableSeats--;
        return;
    }
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
        if (reservations[j] == 1)
            cout << " x ";
        else
            cout << " o ";

        if (j == (column * n) - 1) {
            cout << endl;
            n++;
        }
    }
}
bool Movie::seatCheck(const int row, const char col) {
    int numOfCol = ((int)(col)-65) / radius;//3
    int numOfRow = (row / radius);
    numOfCol++;
    int val = numOfRow * column;
    val = val + numOfCol;
    val--;
    if (reservations[val] == 0)
        return true;
    else
        return false;
}
long Movie::resCode(int pos, const int row, const char col) {
    rescodeSize++;
    int numericCol = (int)col - 65;
    int tempMovieId = ((((100 + pos) * 100) + row) * 100) + numericCol;

    int* tempRescodes = new int[rescodeSize];
    if (rescodeSize == 1) {
        rescodes = new int[rescodeSize];
        tempRescodes[rescodeSize - 1] = tempMovieId;
    }
    else
    {
        for (int i = 0; i < rescodeSize; i++)
            tempRescodes[i] = rescodes[i];
        tempRescodes[rescodeSize - 1] = tempMovieId;
    }
    delete[] rescodes;
    rescodes = tempRescodes;
    return tempMovieId;
}
bool Movie::resCheck(const int resCode) {
    for (int i = 0; i < rescodeSize; i++) {
        if (rescodes[i] == resCode) {
            return true;
        }
    }
    return false;
}
bool Movie::occupiableCheck(const int row, const char col) {
    int numOfCol = ((int)(col)-65); //3
    int numOfRow = (row - 1);
    if (numOfCol % radius == 0 && numOfRow % radius == 0)
        return true;
    return false;
}
void Movie::cancelRes(int resCode, int resRow, int resCol) {
    for (int i = 0; i < rescodeSize; i++) {
        if (rescodes[i] == resCode) {
            int numOfCol = (resCol - 65) / radius;
            numOfCol++;//4
            int numOfRow = resRow / radius;//1
            int val = numOfRow * column;//7
            val = val + numOfCol;//11
            val--;//10
            reservations[val] = 0;
            rescodeSize--;
            availableSeats++;
            int* tempResCode = new int[rescodeSize];
            for (int k = 0; k < i; k++)
                tempResCode[k] = rescodes[k];
            for (int j = i + 1; j < rescodeSize; j++)
                tempResCode[j] = rescodes[j];

            delete[] rescodes;
            rescodes = tempResCode;
        }
    }
}
int Movie::getRescodeSize() {
    return rescodeSize;
}
void Movie::deleteReservations() {
    reservations = NULL;
    rescodeSize = 0;
}
