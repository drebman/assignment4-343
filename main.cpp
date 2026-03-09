/*
------------------------------------------------------------
main.cpp

Authors: Destiny, Chengqi, Parisa

Main driver program for the Movie Store system.

Steps:
1. Load customers
2. Load movies
3. Process command file

Commands supported:
    B -> Borrow movie
    R -> Return movie
    I -> Show inventory
    H -> Show customer history
------------------------------------------------------------
*/

#include "Store.h"

int main()
{
    // Create the store system
    Store store;

    // Load customer list
    store.loadCustomers("data4customers.txt");

    // Load movie inventory
    store.loadMovies("data4movies.txt");

    // Process command file
    store.processCommands("data4commands.txt");

    return 0;
}
