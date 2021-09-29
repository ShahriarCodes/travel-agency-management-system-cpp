//
// Created by sal on 29.09.21.
//

#include "iostream"
#include "ctime"
#include "string"
#include "vector"

using namespace std;


string generateId(const string &name) {
    time_t now = time(nullptr); // current time in seconds after 1970, 1st January
    srand(time(nullptr)); // initialize random seed
    int salt = rand() % 10000 + 1; // generate random salt between 1 to 10000

    string id = name + "_" + to_string(now) + "_" + to_string(salt);

    return id;
}

class TravelTrip {
public:
    string invoice_id;
    basic_string<char> creation_date;
    string user_name;
    string user_address;
    string phone_no;
    string trip_start_location;
    string trip_end_location;

    TravelTrip(string name, string addr, string phone, string startLoc, string endLoc) {
        time_t now = time(0);
        creation_date = to_string(now);
        invoice_id = generateId(user_name);
        user_name = name;
        user_address = addr;
        phone_no = phone;
        trip_start_location = startLoc;
        trip_end_location = endLoc;
    }
};

class NewTravelTrip {
private:
    string name, addr, phone, startLoc, endLoc;
public:
    vector<TravelTrip> trips;

    void addTrip() {
        cout << "Enter user_name: ";
        getline(cin, name);
        cout << "Enter user_address: ";
        getline(cin, addr);
        cout << "Enter phone_no: ";
        getline(cin, phone);
        cout << "Enter trip_start_location: ";
        getline(cin, startLoc);
        cout << "Enter trip_end_location: ";
        getline(cin, endLoc);

        TravelTrip newTrip = TravelTrip(name, addr, phone, startLoc, endLoc);
        trips.push_back(newTrip);
    }

    void searchBy() {

    }

    // returns index of matched TravelTrip object
    int search() {
        int search_no;
        string search_name, search_id;
        cout << "Enter -> 1: Search by name, 2: invoice_id, 3: cancel -----> ";
        cin >> search_no;

        if (search_no == 1) {
            cout << "Enter search_name: ";
            cin >> search_name;

            int i = 0;
            while (i < trips.size()) {
                if (trips[i].user_name == search_name) {
                    return i;
                }
                i++;
            }
        }

        // if not found return -1
        return -1;
    }

    void editTrip() {
        int index = search();
        if (index >= 0) {
            cin.ignore(1, '\n');
            cout << "Enter User Name (X to not change): ";
            getline(cin, name);
            if (name != "X") {
                trips[index].user_name = name;
            }

            cout << "Enter User Address (X to not change): ";
            getline(cin, addr);
            if (addr != "X") {
                trips[index].user_address = addr;
            }

            cout << "Enter User Phone No. (X to not change): ";
            getline(cin, phone);
            if (phone != "X") {
                trips[index].phone_no = phone;
            }

            cout << "Enter Trip Start Location (X to not change): ";
            getline(cin, startLoc);
            if (startLoc != "X") {
                trips[index].trip_start_location = startLoc;
            }

            cout << "Enter Trip End Location (X to not change): ";
            getline(cin, endLoc);
            if (endLoc != "X") {
                trips[index].trip_end_location = endLoc;
            }
        } else {
            cout << "user not found" << endl;
        }
    }

    void deleteTrip() {
        int index = search();
    }


    void printTrips() {
        int i = 0;
        while (i < trips.size()) {
            cout << endl;
            cout << "trips: " << endl;

            cout << "invoice_id: " << trips[i].invoice_id << endl;
            cout << "creation_date: " << trips[i].creation_date << endl;
            cout << "user_name: " << trips[i].user_name << endl;
            cout << "user_address: " << trips[i].user_address << endl;
            cout << "phone_no: " << trips[i].phone_no << endl;
            cout << "trip_start_location: " << trips[i].trip_start_location << endl;
            cout << "trip_end_location: " << trips[i].trip_end_location << endl;

            cout << endl;
            i++;
        }
    }
};

int main() {
    NewTravelTrip newTravelTrip = NewTravelTrip();
    newTravelTrip.addTrip();
    cout << "Size of trips vector: " + to_string(newTravelTrip.trips.size()) << endl;
    newTravelTrip.addTrip();
    cout << "Size of trips vector: " + to_string(newTravelTrip.trips.size()) << endl;

    newTravelTrip.printTrips();

//    newTravelTrip.editTrip();

//    vec.erase(vec.begin() + index);
    newTravelTrip.trips.erase(newTravelTrip.trips.begin() + 0);
    newTravelTrip.printTrips();

}