/*
------------------------------------------------------------
Store.cpp

Authors: Destiny, Chengqi, Parisa

Implementation of the Store class.

This file performs most of the system work:
- reading input files
- managing inventory
- managing customers
- executing commands
------------------------------------------------------------
*/

#include "Store.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;


/*
------------------------------------------------------------
loadCustomers()

Reads the customer file and creates Customer objects.
Each line format:
    ID LastName FirstName
------------------------------------------------------------
*/
void Store::loadCustomers(string filename)
{
    ifstream file(filename);

    int id;
    string last, first;

    while (file >> id >> last >> first)
    {
        customers[id] = new Customer(id, last, first);
    }
}


/*
------------------------------------------------------------
loadMovies()

Reads the movie file and creates Movie objects using
the MovieFactory.

Handles three movie types:
F - Comedy
D - Drama
C - Classic
------------------------------------------------------------
*/
void Store::loadMovies(string filename)
{
    ifstream file(filename);
    string line;

    while (getline(file, line))
    {
        stringstream ss(line);

        char type;
        int stock;

        string director;
        string title;

        ss >> type;

        ss.ignore(2); // skip ", "

        ss >> stock;
        ss.ignore(2);

        getline(ss, director, ',');

        ss.ignore(1);

        getline(ss, title, ',');

        if (type == 'F' || type == 'D')
        {
            int year;
            ss >> year;

            Movie* movie =
                MovieFactory::createMovie(type, stock,
                                          director, title,
                                          "", "", 0, year);

            if (movie)
                inventory[movie->getKey()] = movie;
        }

        else if (type == 'C')
        {
            string actorFirst, actorLast;
            int month, year;

            ss >> actorFirst >> actorLast >> month >> year;

            Movie* movie =
                MovieFactory::createMovie(type, stock,
                                          director, title,
                                          actorFirst, actorLast,
                                          month, year);

            if (movie)
                inventory[movie->getKey()] = movie;
        }

        else
        {
            cout << "Invalid movie type: " << type << endl;
        }
    }
}


/*
------------------------------------------------------------
processCommands()

Reads the command file and executes each command.

Supported commands:
B -> Borrow
R -> Return
I -> Inventory
H -> History
------------------------------------------------------------
*/
void Store::processCommands(string filename)
{
    ifstream file(filename);

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);

        char action;
        ss >> action;

        if (action == 'I')
        {
            showInventory();
        }

        else if (action == 'H')
        {
            int id;
            ss >> id;

            showHistory(id);
        }

        else if (action == 'B' || action == 'R')
        {
            int id;
            char media;
            char type;

            ss >> id >> media >> type;

            string key;
            getline(ss, key);

            if (action == 'B')
                borrowMovie(id, key);

            else
                returnMovie(id, key);
        }

        else
        {
            cout << "Invalid command: " << line << endl;
        }
    }
}


/*
------------------------------------------------------------
showInventory()

Prints all movies currently in the store inventory.
------------------------------------------------------------
*/
void Store::showInventory()
{
    cout << "Inventory:" << endl;

    for (auto& item : inventory)
    {
        item.second->display();
    }
}


/*
------------------------------------------------------------
showHistory()

Displays the transaction history for a specific customer.
------------------------------------------------------------
*/
void Store::showHistory(int id)
{
    if (customers.count(id) == 0)
    {
        cout << "Customer not found: " << id << endl;
        return;
    }

    customers[id]->showHistory();
}


/*
------------------------------------------------------------
borrowMovie()

Handles the borrow operation:
- verify customer exists
- verify movie exists
- decrease stock
- update customer record
------------------------------------------------------------
*/
void Store::borrowMovie(int id, string key)
{
    if (customers.count(id) == 0)
    {
        cout << "Invalid customer ID: " << id << endl;
        return;
    }

    if (inventory.count(key) == 0)
    {
        cout << "Movie not found." << endl;
        return;
    }

    Movie* movie = inventory[key];

    if (!movie->borrowMovie())
    {
        cout << "Movie out of stock." << endl;
        return;
    }

    customers[id]->borrowMovie(key);
}


/*
------------------------------------------------------------
returnMovie()

Handles returning a movie.
------------------------------------------------------------
*/
void Store::returnMovie(int id, string key)
{
    if (customers.count(id) == 0)
    {
        cout << "Invalid customer ID." << endl;
        return;
    }

    if (inventory.count(key) == 0)
    {
        cout << "Movie not found." << endl;
        return;
    }

    if (!customers[id]->returnMovie(key))
    {
        cout << "Customer did not borrow this movie." << endl;
        return;
    }

    inventory[key]->returnMovie();
}
