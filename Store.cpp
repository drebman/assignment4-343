## /*

Store.cpp

Authors: Destiny, Chengqi, Parisa

Implements the main movie store logic.

Responsibilities of this file:
• Load customers from file
• Load movie inventory from file
• Process command file
• Maintain sorted movie inventory
• Handle borrow and return operations
• Display inventory and customer history
----------------------------------------

*/

#include "Store.h"
#include "Movie.h"

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

## /*

Store Destructor

Frees all dynamically allocated memory created in the store.
This prevents memory leaks when the program exits.
--------------------------------------------------

*/
Store::~Store()
{
// delete customers
for (auto &c : customers)
delete c.second;

```
// delete comedy movies
for (auto &m : comedyMovies)
    delete m.second;

// delete drama movies
for (auto &m : dramaMovies)
    delete m.second;

// delete classic movies
for (auto &m : classicMovies)
    delete m.second;
```

}

## /*

loadCustomers()

Reads the customer file and stores customers in the map.

File format:
ID LastName FirstName

Example:
1000 Smith John
---------------

*/
void Store::loadCustomers(string filename)
{
ifstream file(filename);

```
// verify file opened correctly
if (!file)
{
    cout << "Error opening file: " << filename << endl;
    return;
}

int id;
string last;
string first;

// read customers until end of file
while (file >> id >> last >> first)
{
    customers[id] = new Customer(id, last, first);
}
```

}

## /*

loadMovies()

Reads movie inventory file and creates movie objects.

Uses MovieFactory to determine which movie subclass
(Comedy, Drama, Classic) should be created.

## Invalid movie codes are reported and ignored.

*/
void Store::loadMovies(string filename)
{
ifstream file(filename);

```
if (!file)
{
    cout << "Error opening file: " << filename << endl;
    return;
}

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

    // ------------------------------------------------
    // Comedy movie
    // Key format: title + year
    // ------------------------------------------------
    if (type == 'F')
    {
        int year;
        ss >> year;

        Comedy* movie =
            new Comedy(stock, director, title, year);

        comedyMovies[movie->getKey()] = movie;
    }

    // ------------------------------------------------
    // Drama movie
    // Key format: title + director
    // ------------------------------------------------
    else if (type == 'D')
    {
        int year;
        ss >> year;

        Drama* movie =
            new Drama(stock, director, title, year);

        dramaMovies[movie->getKey()] = movie;
    }

    // ------------------------------------------------
    // Classic movie
    // Key format: month + year + major actor
    // ------------------------------------------------
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

    // invalid movie code
    else
    {
        cout << "Invalid movie code: " << type << endl;
    }
}
```

}

## /*

processCommands()

Reads command file and executes each command.

Commands supported:

B -> Borrow movie
R -> Return movie
I -> Display inventory
H -> Display customer history

Each movie type has a different data format,
so the key must be built differently.
-------------------------------------

*/
void Store::processCommands(string filename)
{
ifstream file(filename);

```
if (!file)
{
    cout << "Error opening file: " << filename << endl;
    return;
}

string line;

while (getline(file, line))
{
    stringstream ss(line);

    char action;
    ss >> action;

    // ------------------------------------------------
    // Inventory command
    // ------------------------------------------------
    if (action == 'I')
    {
        showInventory();
    }

    // ------------------------------------------------
    // Customer history
    // Format: H customerID
    // ------------------------------------------------
    else if (action == 'H')
    {
        int id;
        ss >> id;

        showHistory(id);
    }

    // ------------------------------------------------
    // Borrow / Return command
    // ------------------------------------------------
    else if (action == 'B' || action == 'R')
    {
        int id;
        char media;
        char type;

        ss >> id >> media >> type;

        // store only supports DVDs
        if (media != 'D')
        {
            cout << "Invalid media type" << endl;
            continue;
        }

        string key;

        // ------------------------------------------------
        // Comedy command format
        // Example:
        // B 8000 D F You've Got Mail, 1998
        // ------------------------------------------------
        if (type == 'F')
        {
            string title;
            int year;

            getline(ss, title, ',');
            ss >> year;

            key = title + to_string(year);
        }

        // ------------------------------------------------
        // Drama command format
        // Example:
        // B 1000 D D Barry Levinson, Good Morning Vietnam,
        // ------------------------------------------------
        else if (type == 'D')
        {
            string director;
            string title;

            getline(ss, director, ',');
            ss.ignore(1);

            getline(ss, title, ',');

            key = title + director;
        }

        // ------------------------------------------------
        // Classic command format
        // Example:
        // B 5000 D C 3 1971 Ruth Gordon
        // ------------------------------------------------
        else if (type == 'C')
        {
            int month;
            int year;
            string first;
            string last;

            ss >> month >> year >> first >> last;

            key = to_string(month) + " "
                + to_string(year) + " "
                + first + " " + last;
        }

        else
        {
            cout << "Invalid movie type: " << type << endl;
            continue;
        }

        // execute borrow or return
        if (action == 'B')
            borrowMovie(id, type, key);
        else
            returnMovie(id, type, key);
    }

    // ------------------------------------------------
    // Invalid command
    // ------------------------------------------------
    else
    {
        cout << "Invalid command: " << line << endl;
    }
}
```

}

## /*

showInventory()

Displays all movies currently in the store.

Movies must be displayed in this order:

1. Comedy
2. Drama
3. Classic

---

*/
void Store::showInventory()
{
cout << "Comedy Movies:" << endl;

```
for (auto &m : comedyMovies)
    m.second->display();

cout << endl << "Drama Movies:" << endl;

for (auto &m : dramaMovies)
    m.second->display();

cout << endl << "Classic Movies:" << endl;

for (auto &m : classicMovies)
    m.second->display();
```

}

## /*

showHistory()

## Displays transaction history for a specific customer.

*/
void Store::showHistory(int id)
{
if (customers.count(id) == 0)
{
cout << "Invalid customer ID: " << id << endl;
return;
}

```
customers[id]->showHistory();
```

}

## /*

borrowMovie()

Handles borrowing a movie.

Checks:
• customer exists
• movie exists
• movie is in stock
-------------------

*/
void Store::borrowMovie(int id, char type, string key)
{
if (customers.count(id) == 0)
{
cout << "Invalid customer ID: " << id << endl;
return;
}

```
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

// check if movie is available
if (!movie->borrowMovie())
{
    cout << "Out of stock" << endl;
    return;
}

// record transaction in customer history
customers[id]->borrowMovie(key);
```

}

## /*

returnMovie()

## Handles returning a movie to the store.

*/
void Store::returnMovie(int id, char type, string key)
{
if (customers.count(id) == 0)
{
cout << "Invalid customer ID" << endl;
return;
}

```
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

// check if the customer actually borrowed the movie
if (!customers[id]->returnMovie(key))
{
    cout << "Customer did not borrow this movie" << endl;
    return;
}

// return movie to inventory
movie->returnMovie();
```

}
