#include "Sorting.h"
#include "LinkedList.h"

using namespace std;

string Sorting::getCriteriaName(int sortBy) {
    switch (sortBy) {
    case 1: return "Age";
    case 2: return "Daily Distance (km)";
    case 3: return "Monthly Carbon Emission (kg)";
    default: return "Unknown";
    }
}

PerformanceData Sorting::bubbleSort(LinkedList& list, int sortBy) {
    PerformanceData perf;
    perf.memoryBytes = list.getSize() * sizeof(Node);

    auto start = chrono::high_resolution_clock::now();

    list.bubbleSort(sortBy);

    auto end = chrono::high_resolution_clock::now();
    perf.timeMs = chrono::duration<double, milli>(end - start).count();

    return perf;
}

PerformanceData Sorting::mergeSort(LinkedList& list, int sortBy) {
    PerformanceData perf;
    perf.memoryBytes = list.getSize() * sizeof(Node);

    auto start = chrono::high_resolution_clock::now();

    list.mergeSort(sortBy);

    auto end = chrono::high_resolution_clock::now();
    perf.timeMs = chrono::duration<double, milli>(end - start).count();

    return perf;
}

void Sorting::displayPerformance(const string& algorithm, const PerformanceData& perf, int dataSize) {
    cout << "====================== PERFORMANCE REPORT ======================\n";
    cout << "Algorithm        : " << left << setw(20) << algorithm << " \n";
    cout << "Time taken       : " << left << setw(20) << fixed << setprecision(3) << perf.timeMs << " ms" << string(18, ' ') << " \n";
    cout << "Memory used      : " << left << setw(20) << perf.memoryBytes << " bytes" << string(18, ' ') << " \n";
    cout << "Data size        : " << left << setw(20) << dataSize << " records" << string(18, ' ') << " \n";
    cout << "================================================================\n";
}

void Sorting::displaySortedResults(LinkedList& list, int sortBy) {
    string criteriaName = getCriteriaName(sortBy);

    cout << "\nSORTED RESULTS (by " << criteriaName << ")\n";
    cout << string(120, '-') << "\n";
    cout << left
        << setw(15) << "Resident ID"
        << setw(8) << "Age"
        << setw(35) << "Age Group"
        << setw(25) << "Transport"
        << setw(15) << "Distance"
        << setw(18) << "Monthly CO2"
        << endl;
    cout << string(120, '-') << "\n";

    Node* current = list.getHead();
    while (current != nullptr) {
        cout << left
            << setw(15) << current->data.residentID
            << setw(8) << current->data.age
            << setw(35) << current->data.getAgeGroup()
            << setw(25) << current->data.transportMode
            << setw(15) << fixed << setprecision(2) << current->data.dailyDistance
            << setw(18) << fixed << setprecision(2) << current->data.calculateMonthlyEmission()
            << endl;
        current = current->nextAddress;
    }

    cout << string(120, '-') << "\n";
}