/*
------------------------------------------------------------
Store.h

Authors: Destiny, Chengqi, Parisa

This class represents the movie store system.

Responsibilities:
- Store the movie inventory
- Store customer records
- Load data from files
- Process commands
- Handle borrow/return operations
- Display inventory and customer history
------------------------------------------------------------
*/

#ifndef STORE_H
#define STORE_H

#include <map>
#include <string>
#include "MovieFactory.h"
#include "Customer.h"

using namespace std;

class Store {

private:

    // Inventory of movies
    // key = unique movie key
    map<string, Movie*> inventory;

    // Customers indexed by ID
    map<int, Customer*> customers;

public:

    // Load customers from file
    void loadCustomers(string filename);

    // Load movie inventory from file
    void loadMovies(string filename);

    // Process command file
    void processCommands(string filename);

    // Display all movies in inventory
    void showInventory();

    // Show customer transaction history
    void showHistory(int id);

    // Borrow movie operation
    void borrowMovie(int id, string key);

    // Return movie operation
    void returnMovie(int id, string key);
};

#endif
