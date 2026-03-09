/*
------------------------------------------------------------
Drama.h

Authors: Destiny, Chengqi, Parisa

Represents Drama movies.

Sorting rule:
    Director -> Title

Example key:
    "Steven Spielberg_Schindler's List"
------------------------------------------------------------
*/

#ifndef DRAMA_H
#define DRAMA_H

#include "Movie.h"

class Drama : public Movie {

public:

    Drama(int stock, string director, string title, int year);

    string getKey() const override;

    void display() const override;
};

#endif
