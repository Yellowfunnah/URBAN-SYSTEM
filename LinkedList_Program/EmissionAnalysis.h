#pragma once
#include <string>
#include "LinkedList.h"

using namespace std;

//Carbon Emission Analysis - Linked List

//Shows total emissions for one city
void showTotalEmissions(LinkedList& list, string cityName);

//Breaks down emissions by transport mode
void showEmissionsByTransport(LinkedList& list, string cityName);

//Breaks down emissions by age group
void showEmissionsByAgeGroup(LinkedList& list, string cityName);

//Compares all three cities side by side
void compareAllCities(
    LinkedList& cityA, string nameA,
    LinkedList& cityB, string nameB,
    LinkedList& cityC, string nameC
);

//Runs all emission analysis for one city
void runEmissionAnalysis(LinkedList& list, string cityName);