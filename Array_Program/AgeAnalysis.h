// AgeAnalysis.h
// just the declarations for my task 4 functions
// the actual code is in AgeAnalysis.cpp

#pragma once
#ifndef AGEANALYSIS_H
#define AGEANALYSIS_H

#include "Resident.h"
#include <string>
using namespace std;

// main function - shows submenu and handles age group analysis
void analyzeAgeGroups(Resident residents[], int size, string cityName);

#endif