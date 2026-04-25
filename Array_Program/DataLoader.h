#pragma once
#ifndef DATALOADER_H
#define DATALOADER_H

#include <string>
#include "Resident.h"

using namespace std;

// function to load CSV data into array
void loadData(string filename, Resident residents[], int& size);

#endif