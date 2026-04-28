#pragma once
#include <string>
#include "Resident.h"

using namespace std;

//Carbon Emission Analysis - Array

//Shows total emissions for one city
void showTotalEmissions(Resident residents[], int size, string cityName);

//Breaks down emissions by transport mode
void showEmissionsByTransport(Resident residents[], int size, string cityName);

//Breaks down emissions by age group
void showEmissionsByAgeGroup(Resident residents[], int size, string cityName);

//Compares all three cities side by side
void compareAllCities(
    Resident cityA[], int sizeA,
    Resident cityB[], int sizeB,
    Resident cityC[], int sizeC
);

//Runs all emission analysis for one city
void runEmissionAnalysis(Resident residents[], int size, string cityName);