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
