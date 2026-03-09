/*
------------------------------------------------------------
Store.cpp

Authors: Destiny, Chengqi, Parisa

Implements the main movie store logic.

This file handles:
• Reading input files
• Creating movie objects
• Managing customers
• Processing commands
• Maintaining sorted inventory
------------------------------------------------------------
*/

#include "Store.h"
#include "MovieFactory.h"

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;


/*
------------------------------------------------------------
loadCustomers()

Reads customer data file.

Format:
ID LastName FirstName
------------------------------------------------------------
*/
void Store::loadCustomers(string filename)
{
    ifstream file(filename);

    int id;
    string last;
    string first;

    while (file >> id >> last >> first)
    {
        customers[id] = new Customer(id, last, first);
    }
}


/*
------------------------------------------------------------
loadMovies()

Reads movie inventory file.

Creates movie objects using MovieFactory.

Invalid movie codes are ignored and reported.
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

        ss >> type;
        ss.ignore(2);

        ss >> stock;
        ss.ignore(2);

        string director;
        getline(ss, director, ',');

        ss.ignore(1);

        string title;
        getline(ss, title, ',');

        if (type == 'F')
        {
            int year;
            ss >> year;

            Comedy* movie =
                new Comedy(stock, director, title, year);

            comedyMovies[movie->getKey()] = movie;
        }

        else if (type == 'D')
        {
            int year;
            ss >> year;

            Drama* movie =
                new Drama(stock, director, title, year);

            dramaMovies[movie->getKey()] = movie;
        }

        else if (type == 'C')
        {
            string actorFirst;
            string actorLast;
            int month;
            int year;

            ss >> actorFirst >> actorLast >> month >> year;

            Classic* movie =
                new Classic(stock, director, title,
                            actorFirst, actorLast,
                            month, year);

            classicMovies[movie->getKey()] = movie;
        }

        else
        {
            cout << "Invalid movie code: " << type << endl;
        }
    }
}


/*
------------------------------------------------------------
processCommands()

Reads command file and executes each command.

Commands:
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

            if (media != 'D')
            {
                cout << "Invalid media type" << endl;
                continue;
            }

            string key;
            getline(ss, key);

            if (action == 'B')
                borrowMovie(id, type, key);
            else
                returnMovie(id, type, key);
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

Displays all movies in the store.

Required order:
Comedy
Drama
Classic
------------------------------------------------------------
*/
void Store::showInventory()
{
    cout << "Comedy Movies:" << endl;

    for (auto &m : comedyMovies)
        m.second->display();

    cout << endl << "Drama Movies:" << endl;

    for (auto &m : dramaMovies)
        m.second->display();

    cout << endl << "Classic Movies:" << endl;

    for (auto &m : classicMovies)
        m.second->display();
}


/*
------------------------------------------------------------
showHistory()

Prints transaction history for a customer.
------------------------------------------------------------
*/
void Store::showHistory(int id)
{
    if (customers.count(id) == 0)
    {
        cout << "Invalid customer ID: " << id << endl;
        return;
    }

    customers[id]->showHistory();
}


/*
------------------------------------------------------------
borrowMovie()

Handles borrowing operation.

Checks:
• valid customer
• movie exists
• stock available
------------------------------------------------------------
*/
void Store::borrowMovie(int id, char type, string key)
{
    if (customers.count(id) == 0)
    {
        cout << "Invalid customer ID: " << id << endl;
        return;
    }

    Movie* movie = nullptr;

    if (type == 'F' && comedyMovies.count(key))
        movie = comedyMovies[key];

    else if (type == 'D' && dramaMovies.count(key))
        movie = dramaMovies[key];

    else if (type == 'C' && classicMovies.count(key))
        movie = classicMovies[key];

    else
    {
        cout << "Movie not found" << endl;
        return;
    }

    if (!movie->borrowMovie())
    {
        cout << "Out of stock" << endl;
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
void Store::returnMovie(int id, char type, string key)
{
    if (customers.count(id) == 0)
    {
        cout << "Invalid customer ID" << endl;
        return;
    }

    Movie* movie = nullptr;

    if (type == 'F' && comedyMovies.count(key))
        movie = comedyMovies[key];

    else if (type == 'D' && dramaMovies.count(key))
        movie = dramaMovies[key];

    else if (type == 'C' && classicMovies.count(key))
        movie = classicMovies[key];

    else
    {
        cout << "Movie not found" << endl;
        return;
    }

    if (!customers[id]->returnMovie(key))
    {
        cout << "Customer did not borrow this movie" << endl;
        return;
    }

    movie->returnMovie();
}
