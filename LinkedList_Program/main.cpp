#include <iostream>
#include <string>
#include <limits>
#include "LinkedList.h"
#include "DataLoader.h"

using namespace std;

void runCityMenu(LinkedList& list) {
    int choice;

    do {
        cout << "\n===== CITY MENU =====";
        cout << "\n1. Display Residents";
        cout << "\n2. Search by Transport";
        cout << "\n3. Search by Distance";
        cout << "\n0. Back to City Selection";
        cout << "\nEnter choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid choice!\n";
            continue;
        }

        switch (choice) {
        case 1:
            list.display();
            break;

        case 2: {
            string mode;
            cout << "Enter transport mode: ";
            cin >> mode;
            cin.clear();
            cin.ignore(1000, '\n');

            list.searchByTransport(mode);
            break;
        }

        case 3: {
            double distance;
            cout << "Enter minimum distance (km): ";
            cin >> distance;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid distance!\n";
                break;
            }

            list.searchByDistance(distance);
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
    LinkedList cityA;
    LinkedList cityB;
    LinkedList cityC;

    loadData("dataset1-cityA.csv", cityA);
    loadData("dataset2-cityB.csv", cityB);
    loadData("dataset3-cityC.csv", cityC);

    int cityChoice;

    do {
        cout << "\n===== LINKED LIST PROGRAM MENU =====";
        cout << "\n1. City A - Metropolitan City";
        cout << "\n2. City B - University Town";
        cout << "\n3. City C - Suburban/Rural Area";
        cout << "\n0. Exit";
        cout << "\nEnter choice: ";
        cin >> cityChoice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid choice!\n";
            continue;
        }

        switch (cityChoice) {
        case 1:
            runCityMenu(cityA);
            break;

        case 2:
            runCityMenu(cityB);
            break;

        case 3:
            runCityMenu(cityC);
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