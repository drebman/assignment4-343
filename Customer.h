/*
------------------------------------------------------------
Customer.h

Authors: Destiny, Chengqi, Parisa

Represents a movie store customer.

Stores:
    - Customer ID
    - Name
    - Borrowed movies
    - Transaction history

History records all borrow and return operations.
------------------------------------------------------------
*/

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Customer {

private:

    int id;
    string first;
    string last;

    // List of transactions
    vector<string> history;

    // Map of borrowed movies
    unordered_map<string,int> borrowed;

public:

    Customer(int id,string last,string first);

    int getID() const;

    void borrowMovie(string key);

    bool returnMovie(string key);

    void showHistory() const;
};

#endif
