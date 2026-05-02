#pragma once
#include <string>
#include "Resident.h"

using namespace std;

//EmissionAnalysis.h - Array version
//this file declares all the functions used for carbon emission analysis in the array program

//shows a summary of total emissions for one city
void showTotalEmissions(Resident residents[], int size, string cityName);

//shows emissions broken down by transport mode, sorted highest to lowest
//also shows each mode's percentage contribution to the city total
void showEmissionsByTransport(Resident residents[], int size, string cityName);

//shows emissions broken down by age group
//also shows the most popular transport mode per group
void showEmissionsByAgeGroup(Resident residents[], int size, string cityName);

//shows the single highest and lowest emitting resident in a city
//lowest excludes residents with zero emissions (bicycle/walking)
void showHighLowEmitters(Resident residents[], int size, string cityName);

//compares all three cities side by side
//also highlights the most and least polluting city at the bottom
void compareAllCities(
    Resident cityA[], int sizeA,
    Resident cityB[], int sizeB,
    Resident cityC[], int sizeC
);

//master function - shows a submenu so the user can pick
//which analysis they want to see instead of dumping everything at once
void runEmissionAnalysis(Resident residents[], int size, string cityName);