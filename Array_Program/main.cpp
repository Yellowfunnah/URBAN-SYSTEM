#include <iostream>
#include <string>
#include "Resident.h"
#include "DataLoader.h"
#include "Functions.h"
#include "Searching.h"
#include "EmissionAnalysis.h"
#include "AgeAnalysis.h"
#include "Recommendations.h"

//commit issue test

using namespace std;

const int MAX_RESIDENTS = 1000;

void runCityMenu(Resident residents[], int size, string cityName) {
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

        switch (choice) {
        case 1:
            displayResidents(residents, size);
            break;

        case 2:
            runSortingExperiment(residents, size);
            break;

        case 3: {
            string mode;
            cout << "Enter transport mode: ";
            cin >> mode;
            cin.clear();
            cin.ignore(1000, '\n');
            LinearSearchByTransport(residents, size, mode);
            break;
        }
        case 4: {
            double distance;
            cout << "Enter minimum distance (km): ";
            cin >> distance;
            LinearSearchByDistance(residents, size, distance);
            break;
        }
        case 5: {
            string mode;
            cout << "Enter transport mode: ";
            cin >> mode;
            cin.clear();
            cin.ignore(1000, '\n');
            for (int i = 0; i < size - 1; i++) {
                for (int j = 0; j < size - i - 1; j++) {
                    if (residents[j].transportMode > residents[j + 1].transportMode) {
                        Resident temp = residents[j];
                        residents[j] = residents[j + 1];
                        residents[j + 1] = temp;
                    }
                }
            }
            BinarySearchByTransport(residents, size, mode);
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

            SearchByAge(residents, size, ageGroup);
            break;
        }

        case 7:
            runEmissionAnalysis(residents, size, cityName);
            break;

        case 8:
            analyzeAgeGroups(residents, size, cityName);
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
        cout << "\n4. Compare All Cities - Emission Analysis";
        cout << "\n5. Insights & Recommendations (All Cities)";
        cout << "\n0. Exit";
        cout << "\nEnter choice: ";
        cin >> cityChoice;

        switch (cityChoice) {
        case 1:
            runCityMenu(cityA, sizeA, "City A - Metropolitan");
            break;

        case 2:
            runCityMenu(cityB, sizeB, "City B - University Town");
            break;

        case 3:
            runCityMenu(cityC, sizeC, "City C - Suburban/Rural");
            break;

        case 4:
            compareAllCities(cityA, sizeA, cityB, sizeB, cityC, sizeC);
            break;

        case 5:
            showInsightsAndRecommendations(cityA, sizeA, cityB, sizeB, cityC, sizeC);
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