/*
------------------------------------------------------------
Comedy.h

Authors: Destiny, Chengqi, Parisa

Represents Comedy movies in the store.

Sorting rule:
    Title -> Year

Example key:
    "Annie Hall_1977"
------------------------------------------------------------
*/

#ifndef COMEDY_H
#define COMEDY_H

#include "Movie.h"

class Comedy : public Movie {

public:

    // Constructor
    Comedy(int stock, string director, string title, int year);

    // Unique key for lookup
    string getKey() const override;

    // Display movie information
    void display() const override;
};

#endif
