#pragma once
#ifndef SORTING_H
#define SORTING_H

#include "LinkedList.h"
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
    // NOT TO BE CONFUSED WITH ARRAY PART, THIS IS FOR LINKED LIST PROGRAM
    // Bubble Sort with performance tracking
    static PerformanceData bubbleSort(LinkedList& list, int sortBy);

    // Merge Sort with performance tracking, because quick sort is not suitable for linked list. So yea I made 3 sorting algo in total!!
    static PerformanceData mergeSort(LinkedList& list, int sortBy);

    // Display performance results
    static void displayPerformance(const string& algorithm, const PerformanceData& perf, int dataSize);

    // Display sorted results
    static void displaySortedResults(LinkedList& list, int sortBy);

private:
    // Get criteria name
    static string getCriteriaName(int sortBy);
};

#endif