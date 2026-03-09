/*
------------------------------------------------------------
Movie.h

Authors: Destiny, Chengqi, Parisa

Base class for all movie types in the store inventory.

This class stores common information for every movie:
- stock count
- director
- title
- release year

Derived classes:
    Comedy
    Drama
    Classic

Each derived class must implement:
- getKey()   -> unique identifier used for lookup
- display()  -> prints movie information
------------------------------------------------------------
*/

#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include <iostream>

using namespace std;

class Movie {

protected:

    // Number of copies currently available
    int stock;

    // Total copies owned by the store
    int totalStock;

    // Movie information
    string director;
    string title;
    int year;

public:

    // Constructor
    Movie(int stock, string director, string title, int year);

    // Virtual destructor
    virtual ~Movie();

    // Borrow a movie
    // Decreases stock if available
    bool borrowMovie();

    // Return a movie
    // Increases stock
    void returnMovie();

    // Get current stock
    int getStock() const;

    // Each movie type generates a unique key
    virtual string getKey() const = 0;

    // Print movie information
    virtual void display() const = 0;
};

#endif
