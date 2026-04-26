#include <iostream>
#include <iomanip>
#include "Functions.h"

using namespace std;

void displayResidents(Resident residents[], int size) {
    cout << left
        << setw(15) << "Resident ID"
        << setw(8) << "Age"
        << setw(15) << "Transport"
        << setw(15) << "Distance"
        << setw(15) << "Emission"
        << endl;

    cout << "-------------------------------------------------------------\n";

    for (int i = 0; i < size; i++) {
        cout << left
            << setw(15) << residents[i].residentID
            << setw(8) << residents[i].age
            << setw(15) << residents[i].transportMode
            << setw(15) << residents[i].dailyDistance
            << setw(15) << residents[i].calculateMonthlyEmission()
            << endl;
    }
}

void sortByAge(Resident residents[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (residents[j].age > residents[j + 1].age) {
                Resident temp = residents[j];
                residents[j] = residents[j + 1];
                residents[j + 1] = temp;
            }
        }
    }
}

void searchByTransport(Resident residents[], int size, string transport) {
    cout << "\nSearch Results (" << transport << "):\n";

    bool found = false;

    cout << left
        << setw(15) << "Resident ID"
        << setw(8) << "Age"
        << setw(15) << "Transport"
        << setw(15) << "Distance"
        << setw(15) << "Emission"
        << endl;

    cout << "-------------------------------------------------------------\n";

    for (int i = 0; i < size; i++) {
        if (residents[i].transportMode == transport) {
            found = true;

            cout << left
                << setw(15) << residents[i].residentID
                << setw(8) << residents[i].age
                << setw(15) << residents[i].transportMode
                << setw(15) << residents[i].dailyDistance
                << setw(15) << residents[i].calculateMonthlyEmission()
                << endl;
        }
    }

    if (!found) {
        cout << "No residents found with transport: " << transport << endl;
    }
}
bool transportExists(Resident residents[], int size, string transport) {
    for (int i = 0; i < size; i++) {
        if (residents[i].transportMode == transport) {
            return true;
        }
    }
    return false;
}

void searchByDistance(Resident residents[], int size, double threshold) {
    cout << "\nResidents with distance > " << threshold << " km:\n";

    bool found = false;

    cout << left
        << setw(15) << "Resident ID"
        << setw(8) << "Age"
        << setw(15) << "Transport"
        << setw(15) << "Distance"
        << setw(15) << "Emission"
        << endl;

    cout << "-------------------------------------------------------------\n";

    for (int i = 0; i < size; i++) {
        if (residents[i].dailyDistance > threshold) {
            found = true;

            cout << left
                << setw(15) << residents[i].residentID
                << setw(8) << residents[i].age
                << setw(15) << residents[i].transportMode
                << setw(15) << residents[i].dailyDistance
                << setw(15) << residents[i].calculateMonthlyEmission()
                << endl;
        }
    }

    if (!found) {
        cout << "No residents found with distance above " << threshold << " km.\n";
    }
}