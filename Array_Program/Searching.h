#pragma once
#include "Resident.h"
#include <string>

using namespace std;

void LinearSearchByTransport(Resident residents[], int size, string mode);
void LinearSearchByDistance(Resident residents[], int size, double minDistance);
void BinarySearchByTransport(Resident residents[], int size, string mode);
void SearchByAge(Resident residents[], int size, string ageGroup);