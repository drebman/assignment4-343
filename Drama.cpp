/*
------------------------------------------------------------
Drama.cpp

Authors: Destiny, Chengqi, Parisa

Implementation of Drama movie class.
------------------------------------------------------------
*/

#include "Drama.h"

// Constructor
Drama::Drama(int stock, string director, string title, int year)
    : Movie(stock, director, title, year) {}


// Key uses director and title
string Drama::getKey() const
{
    return director + "_" + title;
}


// Display movie information
void Drama::display() const
{
    cout << "D, "
         << stock << ", "
         << director << ", "
         << title << ", "
         << year << endl;
}
