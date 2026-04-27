#pragma once
#ifndef SORTING_H
#define SORTING_H

#include "Resident.h"
#include <chrono>
#include <iostream>
#include <iomanip>

using namespace std;

struct PerformanceData {
    double timeMs;
    long long memoryBytes;
};

class Sorting {
public:
    // Bubble Sort with performance tracking
    static PerformanceData bubbleSort(Resident arr[], int size, int sortBy);

    // Quick Sort with performance tracking
    static PerformanceData quickSort(Resident arr[], int size, int sortBy);

    // Display performance results
    static void displayPerformance(const string& algorithm, const PerformanceData& perf, int dataSize);

    // Display sorted results
    static void displaySortedResults(Resident arr[], int size, int sortBy);

private:
    // Comparison functions
    static bool compareBubble(const Resident& a, const Resident& b, int sortBy);
    static bool compareQuick(const Resident& a, const Resident& b, int sortBy);

    // Quick Sort helpers
    static void quickSortHelper(Resident arr[], int low, int high, int sortBy);
    static int partition(Resident arr[], int low, int high, int sortBy);

    // Get criteria name
    static string getCriteriaName(int sortBy);
};

#endif