#include <iostream>
#include <string>
#include "Resident.h"
#include "DataLoader.h"
#include "Functions.h"

using namespace std;

const int MAX_RESIDENTS = 1000;

void runCityMenu(Resident residents[], int size) {
    int choice;

    do {
        cout << "\n===== CITY MENU =====";
        cout << "\n1. Display Residents";
        cout << "\n2. Sort by Age";
        cout << "\n3. Search by Transport";
        cout << "\n4. Search by Distance";
        cout << "\n0. Back to City Selection";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            displayResidents(residents, size);
            break;

        case 2:
            sortByAge(residents, size);
            cout << "\nSorted by Age:\n";
            displayResidents(residents, size);
            break;

        case 3: {
            string mode;
            cout << "Enter transport mode: ";
            cin >> mode;

            cin.clear();
            cin.ignore(1000, '\n'); 

            if (transportExists(residents, size, mode)) {
                searchByTransport(residents, size, mode);
            }
            else {
                cout << "Invalid transport mode for this city.\n";
            }

            break;
        }

        case 4: {
            double distance;
            cout << "Enter minimum distance (km): ";
            cin >> distance;
            searchByDistance(residents, size, distance);
            break;
        }

        case 0:
            cout << "Returning to city selection...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 0);
}

int main() {
    Resident cityA[MAX_RESIDENTS];
    Resident cityB[MAX_RESIDENTS];
    Resident cityC[MAX_RESIDENTS];

    int sizeA = 0;
    int sizeB = 0;
    int sizeC = 0;

    loadData("dataset1-cityA.csv", cityA, sizeA);
    loadData("dataset2-cityB.csv", cityB, sizeB);
    loadData("dataset3-cityC.csv", cityC, sizeC);

    int cityChoice;

    do {
        cout << "\n===== ARRAY PROGRAM MENU =====";
        cout << "\n1. City A - Metropolitan City";
        cout << "\n2. City B - University Town";
        cout << "\n3. City C - Suburban/Rural Area";
        cout << "\n0. Exit";
        cout << "\nEnter choice: ";
        cin >> cityChoice;

        switch (cityChoice) {
        case 1:
            runCityMenu(cityA, sizeA);
            break;

        case 2:
            runCityMenu(cityB, sizeB);
            break;

        case 3:
            runCityMenu(cityC, sizeC);
            break;

        case 0:
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (cityChoice != 0);

    return 0;
}