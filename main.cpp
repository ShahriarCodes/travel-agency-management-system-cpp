#include <iostream>
#include <cstring>
#include <utility>
#include <vector>

using namespace std;

class Admin {

};

class NewTravelTrip {
public:
    static vector<NewTravelTrip> travel_trips;
    int invoice_id;
    int date;
    string user_name;
    string user_address;
    string phone_no;
    string trip_start_location;
    string trip_end_location;

    NewTravelTrip(string userName, string addr, long phone, string startLoc, string endLoc) {
        user_name = userName;
        user_address = addr;
        phone_no = phone;
        trip_start_location = startLoc;
        trip_end_location = endLoc;
    }


    void EditTrip();
};

void NewTravelTrip::EditTrip() {
    cout << "Enter user_name: ";
    getline(cin,  user_name);
    cout << "Enter user_address: ";
    getline(cin, user_address);
    cout << "Enter phone_no: ";
    getline(cin, phone_no);
    cout << "Enter trip_start_location: ";
    getline(cin, trip_start_location);
    cout << "Enter trip_end_location: ";
    getline(cin, trip_end_location);
}

class ShowAllUsers {
    void deleteUser();

    void editUser();
};

void ShowAllUsers::deleteUser() {

}

void ShowAllUsers::editUser() {

}


int main() {
    cout << "Hello, World!" << endl;

    NewTravelTrip trip = NewTravelTrip("Adad", "ada ", 31313, "Add", "Adad");
    cout << trip.user_name << trip.user_address;
    trip.EditTrip();
    cout << trip.user_name << trip.user_address;
}
