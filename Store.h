/*
------------------------------------------------------------
Store.h

Authors: Destiny, Chengqi, Parisa

Main system class for the Movie Store.

Responsibilities:
• Load movie inventory from file
• Load customer records
• Process command file
• Handle borrow and return operations
• Display sorted inventory
• Display customer history

Inventory is stored in three separate containers
to maintain the required sorting order:

Comedy  -> sorted by title then year
Drama   -> sorted by director then title
Classic -> sorted by release date then actor
------------------------------------------------------------
*/

#ifndef STORE_H
#define STORE_H

#include <vector>
#include <map>
#include "Comedy.h"
#include "Drama.h"
#include "Classic.h"
#include "Customer.h"

class Store {

private:

    // Inventory containers separated by movie type
    map<string, Comedy*> comedyMovies;
    map<string, Drama*> dramaMovies;
    map<string, Classic*> classicMovies;

    // Customers stored by ID
    map<int, Customer*> customers;

public:

    void loadCustomers(string filename);

    void loadMovies(string filename);

    void processCommands(string filename);

    void showInventory();

    void showHistory(int id);

    void borrowMovie(int id, char type, string key);

    void returnMovie(int id, char type, string key);
};

#endif
