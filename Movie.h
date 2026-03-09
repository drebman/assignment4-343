#ifndef MOVIE_H
#define MOVIE_H

#include <iostream>
#include <string>

using namespace std;

/*
--------------------------------------------------------
Movie (Abstract Base Class)

By: Destiny, Chengqi, and Parisa

Represents a movie stored in the inventory.
All movie types inherit from this class.

Responsibilities:
• Store common attributes of movies
• Define common operations
• Provide virtual functions for derived classes
--------------------------------------------------------
*/

class Movie {

protected:

    int stock;          // number currently available
    int totalStock;     // total inventory
    string director;
    string title;
    int year;

public:

    Movie(int stock, string director, string title, int year);
    virtual ~Movie();

    // Decrease stock when borrowed
    bool borrowMovie();

    // Increase stock when returned
    void returnMovie();

    int getStock() const;

    // Unique key used in hash table
    virtual string getKey() const = 0;

    // Display movie info
    virtual void display() const = 0;
};

#endif
