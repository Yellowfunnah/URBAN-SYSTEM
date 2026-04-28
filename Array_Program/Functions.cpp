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

void runSortingExperiment(Resident residents[], int size) {
    if (size == 0) {
        cout << "\nSomething went EXTREMELY wrong! - Check if data file is in the correct location - Dylan\n";
        return;
    }

    int sortByChoice, algorithm;
	bool exitExperiment = false;

    do {
        do {
            cout << "\n===== SORTING EXPERIMENT =====";
            cout << "\nSort by:";
            cout << "\n1. Age";
            cout << "\n2. Daily Distance (km)";
            cout << "\n3. Monthly Carbon Emission (kg)";
            cout << "\n0. Return to City Menu";
            cout << "\nEnter choice: ";
            cin >> sortByChoice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "\nInvalid input! Please enter a number (0, 1, or 2).\n";
                continue;
            }

            if (sortByChoice == 0) {
                cout << "Returning to city menu...\n";
                return;
            }
            else if (sortByChoice < 1 || sortByChoice > 3) {
                cout << "Invalid choice! Please enter the valid options.\n";
            }
        } while (sortByChoice < 1 || sortByChoice > 3);

        do
        {
            cout << "\nSelect Algorithm:";
            cout << "\n1. Bubble Sort";
            cout << "\n2. Quick Sort";
            cout << "\n0. Return to Sorting Options";
            cout << "\nEnter choice: ";
            cin >> algorithm;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "\nInvalid input! Please enter a number (0, 1, or 2).\n";
                continue;
            }

            if (algorithm == 0) {
                cout << "Returning to sorting options...\n";
                break;
            }
            else if (algorithm < 1 || algorithm > 2) {
                cout << "Invalid choice! Please enter the valid options.\n";
			}
		} while (algorithm < 1 || algorithm > 2);

            if (algorithm == 0) {
                continue;
            }
            // Create backup to preserve original order
            Resident* backup = new Resident[size];
            for (int i = 0; i < size; i++) {
                backup[i] = residents[i];
            }

            PerformanceData perf;
            string algoName;

            if (algorithm == 1) {
                algoName = "Bubble Sort";
                perf = Sorting::bubbleSort(residents, size, sortByChoice);
            }
            else if (algorithm == 2) {
                algoName = "Quick Sort";
                perf = Sorting::quickSort(residents, size, sortByChoice);
            }

            // Display sorted results
            Sorting::displaySortedResults(residents, size, sortByChoice);

            // Display performance
            Sorting::displayPerformance(algoName, perf, size);

            // Restore original order
            for (int i = 0; i < size; i++) {
                residents[i] = backup[i];
            }
            delete[] backup;

            // Reminder for documentation comparison
            cout << "\nDOCUMENTATION NOTE:";
            cout << "\nTo compare with Linked List, run the same operation";
            cout << "\nin LinkedList_Program and record the time/memory.";
            cout << "\nThen compare both results in for the report.";
            cout << "\nRunning the same type of sort and algorithm could lead to little timing offset.";
            cout << "\nHowever it appear this is normal so don't worry - Dylan\n";

            int exitExperimentOpt;
            cout << "\nDo another sorting experiment? (1 = Yes / 0 = No): ";
            cin >> exitExperimentOpt;

            while (cin.fail() || (exitExperimentOpt != 0 && exitExperimentOpt != 1)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input! Please enter 0 for No or 1 for Yes: ";
                cin >> exitExperimentOpt;
            }

            if (exitExperimentOpt == 0) {
                exitExperiment = true;
            }

    } while (!exitExperiment);

	cout << "Exiting sorting experiment... Cya!\n";
}