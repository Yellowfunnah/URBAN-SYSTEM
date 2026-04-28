#include "Sorting.h"

using namespace std;

// Bubble Sort
bool Sorting::compareBubble(const Resident& a, const Resident& b, int sortBy) {
    // sortBy: 1 = Age, 2 = Daily Distance, 3 = Monthly Emission
    switch (sortBy) {
    case 1: return a.age > b.age;  // Descending for bubble sort swap condition
    case 2: return a.dailyDistance > b.dailyDistance;
    case 3: return a.calculateMonthlyEmission() > b.calculateMonthlyEmission();
    default: return false;
    }
}

// Quick Sort
bool Sorting::compareQuick(const Resident& a, const Resident& b, int sortBy) {
    switch (sortBy) {
    case 1: return a.age < b.age;  // Ascending for quick sort
    case 2: return a.dailyDistance < b.dailyDistance;
    case 3: return a.calculateMonthlyEmission() < b.calculateMonthlyEmission();
    default: return false;
    }
}

string Sorting::getCriteriaName(int sortBy) {
    switch (sortBy) {
    case 1: return "Age";
    case 2: return "Daily Distance (km)";
    case 3: return "Monthly Carbon Emission (kg)";
    default: return "Unknown";
    }
}

PerformanceData Sorting::bubbleSort(Resident arr[], int size, int sortBy) {
    PerformanceData perf;
    perf.memoryBytes = size * sizeof(Resident);

    auto start = chrono::high_resolution_clock::now();

    // Bubble sort algorithm
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (compareBubble(arr[j], arr[j + 1], sortBy)) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();
    perf.timeMs = chrono::duration<double, milli>(end - start).count();

    return perf;
}

int Sorting::partition(Resident arr[], int low, int high, int sortBy) {
    Resident pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (compareQuick(arr[j], pivot, sortBy)) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void Sorting::quickSortHelper(Resident arr[], int low, int high, int sortBy) {
    if (low < high) {
        int pi = partition(arr, low, high, sortBy);
        quickSortHelper(arr, low, pi - 1, sortBy);
        quickSortHelper(arr, pi + 1, high, sortBy);
    }
}

PerformanceData Sorting::quickSort(Resident arr[], int size, int sortBy) {
    PerformanceData perf;
    perf.memoryBytes = size * sizeof(Resident);

    auto start = chrono::high_resolution_clock::now();

    quickSortHelper(arr, 0, size - 1, sortBy);

    auto end = chrono::high_resolution_clock::now();
    perf.timeMs = chrono::duration<double, milli>(end - start).count();

    return perf;
}

void Sorting::displayPerformance(const string& algorithm, const PerformanceData& perf, int dataSize) {
    cout << "====================== PERFORMANCE REPORT ======================\n";
    cout << "Algorithm        : " << left << setw(33) << algorithm << " \n";
    cout << "Time taken       : " << right << setw(10) << fixed << setprecision(3) << perf.timeMs << " ms" << string(18, ' ') << " \n";
    cout << "Memory used      : " << right << setw(10) << perf.memoryBytes << " bytes" << string(18, ' ') << " \n";
    cout << "Data size        : " << right << setw(10) << dataSize << " records" << string(18, ' ') << " \n";
    cout << "================================================================\n";
}

void Sorting::displaySortedResults(Resident arr[], int size, int sortBy) {
    string criteriaName = getCriteriaName(sortBy);

    cout << "\nSORTED RESULTS (by " << criteriaName << ")\n";
    cout << string(100, '-') << "\n";
    cout << left
        << setw(15) << "Resident ID"
        << setw(8) << "Age"
        << setw(25) << "Age Group"
        << setw(18) << "Transport"
        << setw(15) << "Distance"
        << setw(17) << "Monthly CO2"
        << endl;
    cout << string(100, '-') << "\n";

    // Diplay all of em
    for (int i = 0; i < size; i++) {
        cout << left
            << setw(15) << arr[i].residentID
            << setw(8) << arr[i].age
            << setw(25) << arr[i].getAgeGroup()
            << setw(15) << arr[i].transportMode
            << setw(15) << fixed << setprecision(2) << arr[i].dailyDistance
            << setw(15) << fixed << setprecision(2) << arr[i].calculateMonthlyEmission()
            << endl;
    }

    cout << string(100, '-') << "\n";
}