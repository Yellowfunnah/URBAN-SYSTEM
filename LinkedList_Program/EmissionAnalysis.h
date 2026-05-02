#pragma once
#include <string>
#include "LinkedList.h"

using namespace std;

//EmissionAnalysis.h - linked list version
//
//this file declares all the functions used for carbon emission
//analysis in the linked list program. if you need to add a
//new analysis function, declare it here first then define it
//in EmissionAnalysis.cpp
//
//traversal in this program works by walking node pointers:
//Node* current = list.head and current = current->next

//shows a summary of total emissions for one city
void showTotalEmissions(LinkedList& list, string cityName);

//shows emissions broken down by transport mode, sorted highest to lowest
//also shows each mode's percentage contribution to the city total
void showEmissionsByTransport(LinkedList& list, string cityName);

//shows emissions broken down by age group
//also shows the most popular transport mode per group
void showEmissionsByAgeGroup(LinkedList& list, string cityName);

//shows the single highest and lowest emitting resident in a city
//lowest excludes residents with zero emissions (bicycle/walking)
void showHighLowEmitters(LinkedList& list, string cityName);

//compares all three cities side by side
//also highlights the most and least polluting city at the bottom
void compareAllCities(
    LinkedList& cityA, string nameA,
    LinkedList& cityB, string nameB,
    LinkedList& cityC, string nameC
);

//master function - shows a submenu so the user can pick
//which analysis they want instead of dumping everything at once
void runEmissionAnalysis(LinkedList& list, string cityName);