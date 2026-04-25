#include <iostream>
#include "Resident.h"
#include "DataLoader.h"
#include "Functions.h"

using namespace std;

const int MAX_RESIDENTS = 1000;

int main() {
    Resident residents[MAX_RESIDENTS];
    int size = 0;

    loadData("dataset1-cityA.csv", residents, size);

    int choice;

    do {
        cout << "\n===== MENU =====";
        cout << "\n1. Display Residents";
        cout << "\n0. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            displayResidents(residents, size);
            break;

        case 0:
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}