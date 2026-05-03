#pragma once
#include "LinkedList.h"
#include <string>

using namespace std;

void LinearSearchByTransport(LinkedList& list, string mode);
void LinearSearchByDistance(LinkedList& list, double minDistance);
void BinarySearchByTransport(LinkedList& list, string mode);
void SearchByAgeGroup(LinkedList& list, string ageGroup);