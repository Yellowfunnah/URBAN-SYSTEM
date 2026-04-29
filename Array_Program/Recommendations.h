// Recommendations.h
// Written by: Aimen Rizwan
// declarations for my task 9 functions
// actual code is in Recommendations.cpp

#pragma once
#ifndef RECOMMENDATIONS_H
#define RECOMMENDATIONS_H

#include "Resident.h"
using namespace std;

// main function - shows submenu for city selection then runs insights
void showInsightsAndRecommendations(Resident cityA[], int sizeA,
    Resident cityB[], int sizeB,
    Resident cityC[], int sizeC);

#endif