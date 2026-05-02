#include <iostream>
#include <iomanip>
#include "Functions.h"
#include "Sorting.h"

using namespace std;

void runSortingExperiment(LinkedList& list, const string& cityName) {
    if (list.getHead() == nullptr) {
        cout << "\nNo data loaded for " << cityName << "!\n";
        return;
    }

    int sortByChoice, algorithm;
    bool exitExperiment = false;
    int dataSize = list.getSize();

    do {
        do {
            cout << "\n===== SORTING EXPERIMENT (LINKED LIST) =====";
            cout << "\n\nSort by:";
            cout << "\n1. Age";
            cout << "\n2. Daily Distance (km)";
            cout << "\n3. Monthly Carbon Emission (kg)";
            cout << "\n0. Return to City Menu";
            cout << "\nEnter choice: ";
            cin >> sortByChoice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "\nInvalid input! Please enter a number.\n";
                continue;
            }

            if (sortByChoice == 0) {
                cout << "Returning to city menu...\n";
                return;
            }
            else if (sortByChoice < 1 || sortByChoice > 3) {
                cout << "Invalid choice! Please enter 1, 2, 3, or 0.\n";
            }
        } while (sortByChoice < 1 || sortByChoice > 3);

        do {
            cout << "\nSelect Algorithm:";
            cout << "\n1. Bubble Sort";
            cout << "\n2. Merge Sort";
            cout << "\n0. Return to Sorting Options";
            cout << "\nEnter choice: ";
            cin >> algorithm;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "\nInvalid input! Please enter a number.\n";
                continue;
            }

            if (algorithm == 0) {
                cout << "Returning to sorting options...\n";
                break;
            }
            else if (algorithm < 1 || algorithm > 2) {
                cout << "Invalid choice! Please enter 1, 2, or 0.\n";
            }
        } while (algorithm < 1 || algorithm > 2);

        if (algorithm == 0) {
            continue;
        }

        LinkedList backup = list.copyList();
        PerformanceData perf;
        string algoName;

        if (algorithm == 1) {
            algoName = "Bubble Sort";
            perf = Sorting::bubbleSort(list, sortByChoice);
        }
        else {
            algoName = "Merge Sort";
            perf = Sorting::mergeSort(list, sortByChoice);
        }

        Sorting::displayPerformance(algoName, perf, dataSize);
        Sorting::displaySortedResults(list, sortByChoice);

        list = backup;

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

    cout << "Exiting sorting experiment...\n";
}