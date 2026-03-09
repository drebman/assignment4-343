/*
------------------------------------------------------------
Classic.h

Authors: Destiny, Chengqi, Parisa

Represents Classic movies.

Extra data stored:
    Major actor
    Release month

Sorting rule:
    Year -> Month -> Actor
------------------------------------------------------------
*/

#ifndef CLASSIC_H
#define CLASSIC_H

#include "Movie.h"

class Classic : public Movie {

private:

    // Actor information
    string actorFirst;
    string actorLast;

    // Release month
    int month;

public:

    Classic(int stock,
            string director,
            string title,
            string actorFirst,
            string actorLast,
            int month,
            int year);

    string getKey() const override;

    void display() const override;
};

#endif
