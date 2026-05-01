#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Resident.h"
#include "Sorting.h"
#include <string>

using namespace std;

void displayResidents(Resident residents[], int size);
void sortByAge(Resident residents[], int size);
void runSortingExperiment(Resident residents[], int size); //Dylan's Sorting
#endif