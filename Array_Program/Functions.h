#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Resident.h"
#include <string>

using namespace std;

void displayResidents(Resident residents[], int size);
void sortByAge(Resident residents[], int size);
void searchByTransport(Resident residents[], int size, string transport);
void searchByDistance(Resident residents[], int size, double threshold);
bool transportExists(Resident residents[], int size, string transport);
#endif