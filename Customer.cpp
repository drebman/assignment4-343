#include "Customer.h"
#include <iostream>

using namespace std;

// Constructor
Customer::Customer(int id, string last, string first) {
    this->id = id;
    this->last = last;
    this->first = first;
}

// Return customer ID
int Customer::getID() const {
    return id;
}

// Borrow a movie
void Customer::borrowMovie(string key) {

    // Increase count of borrowed movie
    borrowed[key]++;

    // Record transaction in history
    history.push_back("Borrowed: " + key);
}

// Return a movie
bool Customer::returnMovie(string key) {

    // Check if the customer borrowed this movie
    if (borrowed.find(key) == borrowed.end() || borrowed[key] == 0) {
        return false;
    }

    // Decrease borrowed count
    borrowed[key]--;

    // Record transaction
    history.push_back("Returned: " + key);

    return true;
}

// Show transaction history
void Customer::showHistory() const {

    cout << "Customer: " << first << " " << last << " (ID: " << id << ")" << endl;
    cout << "History:" << endl;

    for (const string &record : history) {
        cout << record << endl;
    }
}
