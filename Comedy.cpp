/*
------------------------------------------------------------
Comedy.cpp

Authors: Destiny, Chengqi, Parisa

Implementation of Comedy movie class.
------------------------------------------------------------
*/

#include "Comedy.h"

// Constructor simply calls base class constructor
Comedy::Comedy(int stock, string director, string title, int year)
    : Movie(stock, director, title, year) {}


// Generate unique key based on title and year
string Comedy::getKey() const
{
    return title + "_" + to_string(year);
}


// Display movie information
void Comedy::display() const
{
    cout << "F, "
         << stock << ", "
         << director << ", "
         << title << ", "
         << year << endl;
}
