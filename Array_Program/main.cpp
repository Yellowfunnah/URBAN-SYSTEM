#include <iostream>
#include <iomanip>
#include "Resident.h"
#include "DataLoader.h"
using namespace std;

const int MAX_RESIDENTS = 1000;

void displayResidents(Resident residents[], int size) {
    cout << left
        << setw(15) << "Resident ID"
        << setw(8) << "Age"
        << setw(15) << "Transport"
        << setw(15) << "Distance"
        << setw(15) << "Emission"
        << endl;

    cout << "---------------------------------------------------------------------\n";

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

double calculateTotalEmission(Resident residents[], int size) {
    double total = 0;

    for (int i = 0; i < size; i++) {
        total = total + residents[i].calculateMonthlyEmission();
    }

    return total;
}

void searchByTransport(Resident residents[], int size, string mode) {
    cout << "\nSearch Result for Transport Mode: " << mode << endl;

    for (int i = 0; i < size; i++) {
        if (residents[i].transportMode == mode) {
            cout << residents[i].residentID << "  "
                << residents[i].age << "  "
                << residents[i].transportMode << "  "
                << residents[i].calculateMonthlyEmission()
                << endl;
        }
    }
}

int main() {
    Resident residents[MAX_RESIDENTS];

    int size = DataLoader::loadData("dataset1-cityA.csv", residents, MAX_RESIDENTS);

    if (size == 0) {
        cout << "No data loaded.\n";
        return 0;
    }

    int choice;

    do {
        cout << "\n===== Urban Carbon Emission System =====\n";
        cout << "1. Display all residents\n";
        cout << "2. Show total carbon emission\n";
        cout << "3. Search by transport mode\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            displayResidents(residents, size);
        }
        else if (choice == 2) {
            cout << "Total Carbon Emission: "
                << calculateTotalEmission(residents, size)
                << " kg CO2\n";
        }
        else if (choice == 3) {
            string mode;
            cout << "Enter transport mode: ";
            cin >> mode;
            searchByTransport(residents, size, mode);
        }

    } while (choice != 0);

    return 0;
}