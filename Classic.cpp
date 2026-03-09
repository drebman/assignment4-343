/*
------------------------------------------------------------
Classic.cpp

Authors: Destiny, Chengqi, Parisa

Implementation of Classic movie class.
------------------------------------------------------------
*/

#include "Classic.h"

// Constructor initializes extra classic movie data
Classic::Classic(int stock,
                 string director,
                 string title,
                 string actorFirst,
                 string actorLast,
                 int month,
                 int year)
    : Movie(stock, director, title, year)
{
    this->actorFirst = actorFirst;
    this->actorLast = actorLast;
    this->month = month;
}


// Key uses release date and actor
string Classic::getKey() const
{
    return to_string(year) + "_" +
           to_string(month) + "_" +
           actorLast + "_" +
           actorFirst;
}


// Display movie information
void Classic::display() const
{
    cout << "C, "
         << stock << ", "
         << director << ", "
         << title << ", "
         << actorFirst << " "
         << actorLast << " "
         << month << " "
         << year << endl;
}
