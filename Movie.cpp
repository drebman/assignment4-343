/*
------------------------------------------------------------
Movie.cpp

Authors: Destiny, Chengqi, Parisa

Implementation of the base Movie class.
------------------------------------------------------------
*/

#include "Movie.h"

// Constructor initializes movie data
Movie::Movie(int stock, string director, string title, int year)
{
    this->stock = stock;
    this->totalStock = stock;
    this->director = director;
    this->title = title;
    this->year = year;
}

// Destructor
Movie::~Movie() {}


// Borrow movie if stock is available
bool Movie::borrowMovie()
{
    if (stock <= 0)
        return false;

    stock--;
    return true;
}


// Increase stock when movie is returned
void Movie::returnMovie()
{
    stock++;
}


// Return current stock value
int Movie::getStock() const
{
    return stock;
}
