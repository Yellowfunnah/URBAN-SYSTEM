#include <iostream>
#include <string>
#include <limits>
#include "LinkedList.h"
#include "DataLoader.h"
#include "Functions.h"
#include "EmissionAnalysis.h"
#include "AgeAnalysis.h"
#include "Recommendations.h"
#include "Searching.h" 


using namespace std;

void runCityMenu(LinkedList& list, string cityName) {
    int choice;

    do {
        cout << "\n===== CITY MENU =====";
        cout << "\n1. Display Residents";
		cout << "\n2. Sorting Experiment";
        cout << "\n3. Search by Transport (Linear)";
        cout << "\n4. Search by Distance (Linear)";
        cout << "\n5. Binary Search by Transport";
        cout << "\n6. Search by Age Group";
        cout << "\n7. Carbon Emission Analysis";
        cout << "\n8. Age Group Analysis";
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

        case 3: {
            string mode;
            cout << "Enter transport mode: ";
            cin >> mode;
            cin.clear();
            cin.ignore(1000, '\n');
            LinearSearchByTransport(list, mode);
            break;
        }

        case 4: {
            double distance;
            cout << "Enter minimum distance (km): ";
            cin >> distance;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid distance!\n";
                break;
            }
            LinearSearchByDistance(list, distance);
            break;
        }

        case 5: {
            string mode;
            cout << "Enter transport mode: ";
            cin >> mode;
            cin.clear();
            cin.ignore(1000, '\n');
            BinarySearchByTransport(list, mode);
            break;
        }

        case 6: {
            cout << "Select Age Group:\n";
            cout << "1. Children & Teenagers\n";
            cout << "2. University Students / Young Adults\n";
            cout << "3. Working Adults (Early Career)\n";
            cout << "4. Working Adults (Late Career)\n";
            cout << "5. Senior Citizens / Retirees\n";
            cout << "Enter choice: ";
            int ageChoice;
            cin >> ageChoice;

            string ageGroup;
            if (ageChoice == 1) ageGroup = "Children & Teenagers";
            else if (ageChoice == 2) ageGroup = "University Students / Young Adults";
            else if (ageChoice == 3) ageGroup = "Working Adults (Early Career)";
            else if (ageChoice == 4) ageGroup = "Working Adults (Late Career)";
            else if (ageChoice == 5) ageGroup = "Senior Citizens / Retirees";
            else { cout << "Invalid choice!\n"; break; }

            SearchByAgeGroup(list, ageGroup);
            break;
        }

        case 7:
            runEmissionAnalysis(list, cityName);
            break;

        case 8:
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