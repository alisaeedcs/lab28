//comsc-210 | ali saeed | lab 28
//ide used: vs code

#include <iostream>
#include <numeric>
#include <random>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <list>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);

//new options
void sort_goats(list<Goat> &trip); //by age
void shuffle_goats(list<Goat> & trip);
void delete_all_goats(list<Goat> &trip);
void goats_with_age(list<Goat> &trip);
void goats_with_color(list<Goat> &trip);
void oldest_goat(list<Goat> &trip);
void average_age(list<Goat> &trip);
void reverse_order(list<Goat> &trip);


void display_trip(list<Goat> trip);
int main_menu();

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }
    
    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 12) {
        switch (sel) {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2:    
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3:    
                cout << "Sorting goats by age.\n";
                sort_goats(trip);
                break;
            case 4:
                cout << "Shuffling goats.\n";
                shuffle_goats(trip);
                break;
            case 5:
                cout << "Delete all goats\n";
                delete_all_goats(trip);
                break;
            case 6:
                cout << "Goats with Specific Age\n";
                goats_with_age(trip);
                break;
            case 7:
                cout << "Goats with Specific Color\n";
                goats_with_color(trip);
                break;
            case 8:
                cout << "Oldest Goat\n";
                oldest_goat(trip);
                break;
            case 9:
                cout << "Average Age of Goats\n";
                average_age(trip);
                break;
            case 10:
                cout << "Reversing Order\n";
                reverse_order(trip);
                break;
            case 11:
                cout << "Displaying all goats\n";
                display_trip(trip);
                break;
            default:
                cout << "Invalid selection.\n";
                break;
        }
        sel = main_menu();
    }
    

    return 0;
}

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] Sort Goats (By Age)\n";
    cout << "[4] Shuffle Goats\n";
    cout << "[5] Delete all Goats\n";
    cout << "[6] Goats with Specific Age\n";
    cout << "[7] Goats with Specific Color\n";
    cout << "[8] Oldest Goat\n";
    cout << "[9] Average Age of Goats\n";
    cout << "[10] Reverse Order\n";
    cout << "[11] List goats\n";
    cout << "[12] Quit\n";

    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 12) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 or input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}

//sort by age least to most
void sort_goats(list<Goat> &trip) {
    if (trip.empty()) {
        cout << "No goats on trip\n";
        return;
    }
    trip.sort([](const Goat& a, const Goat& b) { return a.get_age() < b.get_age();}); 
    cout << "Goats sorted by age\n";
}

void shuffle_goats(list<Goat> & trip) {
    if (trip.empty()) {
        cout << "No goats on trip\n";
        return;
    }
    vector<Goat> temp(trip.begin(), trip.end());

    srand(time(0));
    shuffle(temp.begin(), temp.end(), default_random_engine(rand()));

    trip.assign(temp.begin(), temp.end()); //shuffle
    cout << "Goats have been shuffled\n";
}

void delete_all_goats(list<Goat> &trip) {
     if (trip.empty()) {
        cout << "List already empty\n";
        return;
    }
    trip.clear(); //clear list
    cout << "All goats deleted. New trip size: " << trip.size() << endl;
}

void goats_with_age(list<Goat> &trip) {
    if (trip.empty()) {
        cout << "No goats on trip\n";
        return;
    }
    int age;
    cout << "Age of goats to display: ";
    cin >> age;
    cout << "Goats: \n";
    bool fits_desc = false;
    for (const auto& goat : trip) {
        //if they fit age
        if (goat.get_age() == age) {
            cout << "\t" << goat.get_name() << " [" << goat.get_color() << "]\n";
            fits_desc = true;
        }
    }
    if (!fits_desc) {
        cout << "No goats with age " << age << endl;
    }
}

void goats_with_color(list<Goat> &trip) {
     if (trip.empty()) {
        cout << "No goats on trip\n";
        return;
    }
    string color;
    cout << "Color of goats to display: ";
    cin >> color;
    cout << "Goats: \n";
    bool fits_desc = false;
    for (const auto& goat : trip) {
        //if they fit description
        if (goat.get_color() == color) {
            cout << "\t" << goat.get_name() << " [" << goat.get_color() << "]\n";
            fits_desc = true;
        }
    }
    if (!fits_desc) {
        cout << "No goats with color " << color << endl;
    }
}

void oldest_goat(list<Goat> &trip) {
    if (trip.empty()) {
        cout << "No goats on trip\n";
        return;
    }
    
    //sort by age
    sort_goats(trip);

    //last goat in list
    auto oldest = prev(trip.end());

    cout << "Oldest Goat: " << oldest->get_name() << " [" << oldest->get_age() << ", " << oldest->get_color() << "]\n";
}

void average_age(list<Goat> &trip) {
    if (trip.empty()) {
        cout << "No goats on trip\n";
        return;
    }
    //total of all ages in int
    int total = accumulate(trip.begin(), trip.end(), 0, [](int sum, const Goat& goat) {return sum + goat.get_age();});
    cout << "Average age: " << static_cast<double>(total) / trip.size();
}
void reverse_order(list<Goat> &trip) {
    if (trip.empty()) {
        cout << "No goats on trip\n";
        return;
    }
    //reverse
    trip.reverse();
    cout << "Order of goats has been reversed.\n";
}