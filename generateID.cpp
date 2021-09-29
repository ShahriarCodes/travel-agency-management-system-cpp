//
// Created by sal on 29.09.21.
//

#include "iostream"
#include "ctime"
#include "string"

using namespace std;

string generateId(string name) {
    time_t now = time(nullptr); // current time in seconds after 1970, 1st January
    srand (time(nullptr)); // initialize random seed
    int salt = rand() % 10000 + 1; // generate random salt between 1 to 10000

    string id = name + "_" + to_string(now) + "_" + to_string(salt);

    return id;
}

