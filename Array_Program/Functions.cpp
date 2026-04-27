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
        cout << "\nNo data loaded!\n";
        return;
    }

    int sortBy, algorithm;

    cout << "\n===== SORTING EXPERIMENT (Task 6) =====";
    cout << "\n\nSort by:";
    cout << "\n1. Age";
    cout << "\n2. Daily Distance (km)";
    cout << "\n3. Monthly Carbon Emission (kg)";
    cout << "\nEnter choice: ";
    cin >> sortBy;

    cout << "\nSelect Algorithm:";
    cout << "\n1. Bubble Sort (O(n²) - Slower)";
    cout << "\n2. Quick Sort (O(n log n) - Faster)";
    cout << "\nEnter choice: ";
    cin >> algorithm;

    // Create backup to preserve original order
    Resident* backup = new Resident[size];
    for (int i = 0; i < size; i++) {
        backup[i] = residents[i];
    }

    PerformanceData perf;
    string algoName;

    cout << "\n========================================";
    cout << "\nSORTING IN PROGRESS...";
    cout << "\n========================================\n";

    if (algorithm == 1) {
        algoName = "Bubble Sort";
        perf = Sorting::bubbleSort(residents, size, sortBy);
    }
    else if (algorithm == 2) {
        algoName = "Quick Sort";
        perf = Sorting::quickSort(residents, size, sortBy);
    }
    else {
        cout << "Invalid algorithm choice!\n";
        delete[] backup;
        return;
    }

    // Display performance
    Sorting::displayPerformance(algoName, perf, size);

    // Display sorted results
    Sorting::displaySortedResults(residents, size, sortBy);

    // Restore original order
    for (int i = 0; i < size; i++) {
        residents[i] = backup[i];
    }
    delete[] backup;

    // Reminder for documentation comparison
    cout << "\n💡 DOCUMENTATION NOTE:";
    cout << "\n   To compare with Linked List, run the same operation";
    cout << "\n   in LinkedList_Program and record the time/memory.";
    cout << "\n   Then compare both results in your Solution Work report.\n";
}