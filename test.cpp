//
// Created by sal on 29.09.21.
//

#include "iostream"
#include "ctime"
#include "string"
#include <sstream>
#include "vector"

using namespace std;


string generateId(const string &name) {
    time_t now = time(nullptr); // current time in seconds after 1970, 1st January
    srand(now); // initialize random seed
    int salt = rand() % 10000 + 1; // generate random salt between 1 to 10000

    string id = name + "_" + to_string(now) + "_" + to_string(salt);

    return id;
}

class TravelTrip {
public:
    string invoice_id;
    string creation_date;
    string user_name;
    string user_address;
    string phone_no;
    string trip_start_location;
    string trip_end_location;

    TravelTrip(string name, string addr, string phone, string date, string startLoc, string endLoc) {
        time_t now = time(nullptr);
//        creation_date = to_string(now);
        creation_date = date;
        invoice_id = generateId(user_name);
        user_name = name;
        user_address = addr;
        phone_no = phone;
        trip_start_location = startLoc;
        trip_end_location = endLoc;
    }
};

vector<TravelTrip> trips;

class NewTravelTrip {
private:
    string name, addr, phone, date, startLoc, endLoc;
    vector<TravelTrip> added_trips;
public:

    void newTravelTrip();

    void searchBy() {

    }

    // returns index of matched TravelTrip object
    static int search() {
        cout << " \n <----------- Please search before you edit or delete ------------> \n";
        char op;
        string search_name, search_id;

        SearchMenu:
        cout << "1: Search by name \n";
        cout << "2: Search by invoice_id \n";
        cout << "3: Cancel Search \n";
        cout << "Enter your choice: ";
        cin >> op;

        int option = op - '0';

        if (option == 1) {
            cout << "Enter search_name: ";
            cin.ignore(1, '\n');
            getline(cin, search_name);

            int i = 0;
            while (i < trips.size()) {
                if (trips[i].user_name == search_name) {
                    return i;
                }
                i++;
            }
        } else if (option == 2) {
            cout << "Enter search_invoice_id: ";
            cin.ignore(1, '\n');
            getline(cin, search_id);

            int i = 0;
            while (i < trips.size()) {
                if (trips[i].invoice_id == search_id) {
                    return i;
                }
                i++;
            }
        } else {
            cout << " \n <----------- Error: Invalid Input Choice------------> \n \n";;
            goto SearchMenu;
        }

        // if not found return -1
        return -1;
    }


    void deleteTrip();

    void addTrip();

    void editTrip();


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

NewTravelTrip mNewTravelTrip = NewTravelTrip();

void menu(NewTravelTrip newTravelTrip = mNewTravelTrip, vector<TravelTrip> trips_vec = trips);


void NewTravelTrip::newTravelTrip() {
    cout << " \n <----------- Creating new travel trip ------------> \n";
    cin.ignore(1, '\n');
    cout << "Enter user_name: ";
    getline(cin, name);
    cout << "Enter user_address: ";
    getline(cin, addr);
    cout << "Enter phone_no: ";
    getline(cin, phone);
    cout << "Enter trip date: ";
    getline(cin, date);
    cout << "Enter trip_start_location: ";
    getline(cin, startLoc);
    cout << "Enter trip_end_location: ";
    getline(cin, endLoc);

    TravelTrip newTrip = TravelTrip(name, addr, phone, date, startLoc, endLoc);
    trips.push_back(newTrip);

    cout << " \n <----------- New travel trip saved successfully ------------> \n";
    cout << " <----------- Going back to main menu ------------> \n \n";
    menu();
}

void NewTravelTrip::editTrip() {
    int index = search();
    if (index >= 0) {
        cout << "\n <----------- Editing Trip of invoice_id: " << trips[index].invoice_id << " ------------> ";
        cin.ignore(1, '\n');
//        cout << "Enter User Name (X to not change): ";
//        getline(cin, name);
//        if (name != "X" || name != "x" || name != "\n") {
//            trips[index].user_name = name;
//        }
//
//        cout << "Enter User Address (X to not change): ";
//        getline(cin, addr);
//        if (addr != "X" || name != "x" || name != "\n") {
//            trips[index].user_address = addr;
//        }
//
//        cout << "Enter User Phone No. (X to not change): ";
//        getline(cin, phone);
//        if (phone != "X") {
//            trips[index].phone_no = phone;
//        }

        cout << "Enter Trip Date  (X to not change): ";
        getline(cin, date);
        if (date != "X") {
            trips[index].creation_date = date;
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

        cout << " \n <----------- trip of invoice_id: " << trips[index].invoice_id
             << " edited successfully ------------> \n";
        cout << " <----------- Going back to main menu ------------> \n \n";
        menu();
    } else {
        cout << "\n <----------- Trip not found. Please enter valid input ------------> \n";
        cout << " <----------- Going back to main menu ------------> \n \n";
        menu();
    }
}

void NewTravelTrip::deleteTrip() {
    int index = search();
    if (index >= 0) {
        string deleted_id = trips[index].invoice_id;
        trips.erase(trips.begin() + index);
        cout << " \n <----------- trip of invoice_id: " << deleted_id
             << " deleted successfully ------------> \n";
        cout << " <----------- Going back to main menu ------------> \n \n";
        menu();
    } else {
        cout << "\n <----------- Trip of invoice_id: not found. Please enter valid input ------------> \n";
        cout << " <----------- Going back to main menu ------------> \n \n";
        menu();
    }
}

void NewTravelTrip::addTrip() {
    int index = search();
    if (index >= 0) {
        string added_id = trips[index].invoice_id;
        TravelTrip selected_trip = trips[index];

        added_trips.push_back(selected_trip);
        cout << " \n <----------- trip of invoice_id: " << added_id
             << " added to trips successfully ------------> \n";
        cout << " <----------- Going back to main menu ------------> \n \n";
        menu();
    } else {
        cout << "\n <----------- Trip not found. Please enter valid input ------------> \n";
        cout << " <----------- Going back to main menu ------------> \n \n";
        menu();
    }
}

class ShowAllUsers {
public:
    static void showAllUsers(NewTravelTrip newTravelTrip, vector<TravelTrip> &trips) {

        if (trips.size() == 0) {
            cout << "\n <----------- No users found ------------> \n";
            cout << " <----------- Going back to main menu ------------> \n \n";
            menu(newTravelTrip, trips);
        } else {
            cout << " \n <----------- Viewing all users ------------> \n";
            for (int i = 0; i < trips.size(); i++) {
                cout << i + 1 << ". " << trips[i].user_name
                     << " ,  invoice_id: " << trips[i].invoice_id
                     << " ,  creation_date: " << trips[i].creation_date
                     << " ,  user_name: " << trips[i].user_name
                     << " ,  user_address: " << trips[i].user_address
                     << " ,  phone_no: " << trips[i].phone_no
                     << " ,  trip_start_location: " << trips[i].trip_start_location
                     << " ,  trip_end_location: " << trips[i].trip_end_location << endl;
            }
            cout << " \n <----------- Going back to main menu ------------> \n \n";
            menu(newTravelTrip, trips);
        }


    }

    static void editUser(vector<TravelTrip> &trips) {
        int index = NewTravelTrip::search();
        string name, addr, phone;
        if (index >= 0) {
            cout << "\n <----------- Editing user: " << trips[index].user_name << " ------------> \n";
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

            cout << "Enter Phone Number (X to not change): ";
            getline(cin, phone);
            if (addr != "X") {
                trips[index].user_address = addr;
            }
            cout << "\n <----------- User of username: " << trips[index].user_name
                 << " edited successfully ------------> \n";
            cout << " <----------- Going back to main menu ------------> \n \n";
            menu();

        } else {
            cout << "\n <----------- No user found. Please enter a valid input ------------> \n";
            cout << " <----------- Going back to main menu ------------> \n \n";
            menu();
        }
    }

    static void deleteUser(vector<TravelTrip> &trips) {
        int index = NewTravelTrip::search();

        if (index >= 0) {
            string deleted_user = trips[index].user_name;
            trips.erase(trips.begin() + index);
            cout << " \n <----------- user_name of: " << deleted_user << " deleted successfully ------------> \n";
            cout << " <----------- Going back to main menu ------------> \n \n";
            menu();
        } else {
            cout << "\n <----------- User not found. Please enter valid input ------------> \n";
            cout << " <----------- Going back to main menu ------------> \n \n";
            menu();
        }
    }
};

void menu(NewTravelTrip newTravelTrip, vector<TravelTrip> trips_vec) {
    char op;

    ExitMenu:
    cout << " <----------- Main menu ------------> \n \n";
    cout << "\t1. New Travel Trip\n";
    cout << "\t2. Show All Users\n";
    cout << "\t3. Edit User\n";
    cout << "\t4. Delete User\n";
    cout << "\t5. Add Trip\n";
    cout << "\t6. Edit Trip\n";
    cout << "\t7. Delete Trip\n";
    cout << "\t\n Enter your choice: ";

    cin >> op;
    int option = op - '0';

    if (option == 1) {
        newTravelTrip.newTravelTrip();

    } else if (option == 2)
        ShowAllUsers::showAllUsers(newTravelTrip, trips_vec);

    else if (option == 3)
        ShowAllUsers::editUser(trips_vec);

    else if (option == 4)
        ShowAllUsers::deleteUser(trips_vec);

    else if (option == 5)
        newTravelTrip.addTrip();

    else if (option == 6)
        newTravelTrip.editTrip();

    else if (option == 7)
        newTravelTrip.deleteTrip();

    else {
        cout << " \n <----------- Error: Invalid Input Choice ------------> \n \n";;
        goto ExitMenu;
    }
//            break;
}

//    cout<< "Press 0 to enter menu again: ";
//    cin >> option;
//    if(option == 0) {
//        return menu(newTravelTrip, trips);
//    }


int main() {

//    newTravelTrip.newTravelTrip();
//    cout << "Size of trips vector: " + to_string(newTravelTrip.trips.size()) << endl;
//    newTravelTrip.addTrip();
//    cout << "Size of trips vector: " + to_string(newTravelTrip.trips.size()) << endl;
//
//    newTravelTrip.printTrips();
//
////    newTravelTrip.editTrip();
//
////    vec.erase(vec.begin() + index);
//    newTravelTrip.trips.erase(newTravelTrip.trips.begin() + 0);
//    newTravelTrip.printTrips();
    menu(mNewTravelTrip, trips);

}