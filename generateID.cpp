//
// Created by sal on 29.09.21.
//

#include "iostream"
#include "ctime"
#include "string"

using namespace std;

string generateId(const string& name) {
    time_t now = time(0); // current time in seconds after 1970, 1st January
    srand (time(nullptr)); // initialize random seed
    int salt = rand() % 10000 + 1; // generate random num between 1 to 10000

    string id = name + "_" + to_string(now) + "_" + to_string(salt);

    return id;
}

int main() {
    cout << generateId("tom");
}