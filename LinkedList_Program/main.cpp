#include <iostream>
#include <string>
#include <limits>
#include "LinkedList.h"
#include "DataLoader.h"
#include "Functions.h"
#include "EmissionAnalysis.h"
#include "AgeAnalysis.h"
#include "Recommendations.h"


using namespace std;

void runCityMenu(LinkedList& list, string cityName) {
    int choice;

    do {
        cout << "\n===== CITY MENU =====";
        cout << "\n1. Display Residents";
		cout << "\n2. Sorting Experiment";
        cout << "\n3. Search by Transport";
        cout << "\n4. Search by Distance";
        cout << "\n5. Carbon Emission Analysis";
        cout << "\n6. Age Group Analysis";
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

        case 2:
            runSortingExperiment(list, cityName);
            break;

        //case 3: {
        //    string mode;
        //    cout << "Enter transport mode: ";
        //    cin >> mode;
        //    cin.clear();
        //    cin.ignore(1000, '\n');

        //    list.searchByTransport(mode);
        //    break;
        //}

        //case 4: {
        //    double distance;
        //    cout << "Enter minimum distance (km): ";
        //    cin >> distance;

        //    if (cin.fail()) {
        //        cin.clear();
        //        cin.ignore(1000, '\n');
        //        cout << "Invalid distance!\n";
        //        break;
        //    }

        //    list.searchByDistance(distance);
        //    break;
        //}

        case 5:
            runEmissionAnalysis(list, cityName);
            break;

        case 6:
            analyzeAgeGroups(list, cityName);
            break;

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
        cout << "\n4. Compare All Cities - Emission Analysis";
        cout << "\n5. Insights & Recommendations (All Cities)";
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
            runCityMenu(cityA, "City A - Metropolitan");
            break;

        case 2:
            runCityMenu(cityB, "City B - University Town");
            break;

        case 3:
            runCityMenu(cityC, "City C - Suburban/Rural");
            break;

        case 4:
            compareAllCities(
                cityA, "City A - Metropolitan",
                cityB, "City B - University Town",
                cityC, "City C - Suburban/Rural"
            );
            break;

        case 5:
            showInsightsAndRecommendations(cityA, cityB, cityC);
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