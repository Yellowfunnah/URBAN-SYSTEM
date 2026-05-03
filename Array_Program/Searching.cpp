#include <iostream>
#include <iomanip>
#include "Searching.h"
#include <chrono>

using namespace std;

void LinearSearchByTransport(Resident residents[], int size, string mode) 
{
	int count = 0;
	auto start = chrono::high_resolution_clock::now();

	cout << "Searching for transport mode: " << mode << "\n";

	cout << "Resident ID    Age     Transport      Distance    Emission\n";
	cout << "--------------------------------------------------------------\n";

	for (int i = 0; i < size; i++) 
	{
		if (residents[i].transportMode == mode) 
		{
			cout << left << setw(15) << residents[i].residentID
				<< setw(8) << residents[i].age
				<< setw(15) << residents[i].transportMode
				<< setw(12) << residents[i].dailyDistance
				<< setw(12) << residents[i].calculateMonthlyEmission()
				<< "\n";
			count++;
		}
	}

	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds> (end - start);

	cout << "Total Found: " << count << "\n";
	cout << "Time Taken: " << duration.count() << " microseconds \n";
}

void LinearSearchByDistance(Resident residents[], int size, double minDistance) 
{
	int count = 0;
	auto start = chrono::high_resolution_clock::now();

	cout << "Searching for distance greater than: " << minDistance << "km\n";

	cout << "Resident ID    Age     Transport      Distance    Emission\n";
	cout << "--------------------------------------------------------------\n";

	for (int i = 0; i < size; i++) 
	{
		if (residents[i].dailyDistance > minDistance) 
		{
			cout << left << setw(15) << residents[i].residentID
				<< setw(8) << residents[i].age
				<< setw(15) << residents[i].transportMode
				<< setw(12) << residents[i].dailyDistance
				<< setw(12) << residents[i].calculateMonthlyEmission()
				<< "\n";
			count++;
		}
	}

	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds> (end - start);

	cout << "Total Found: " << count << "\n";
	cout << "Time Taken: " << duration.count() << " microseconds \n";
}

void BinarySearchByTransport(Resident residents[], int size, string mode) 
{
	int low = 0;
	int high = size - 1;
	int found = -1;
	int count = 0;
	auto start = chrono::high_resolution_clock::now();


	cout << "Binary Searching for transport mode: " << mode << "\n";

	while (low <= high) 
	{
		int mid = (high + low) / 2;

		if (residents[mid].transportMode == mode) 
		{
			found = mid;
			break;
		}
		else if (residents[mid].transportMode < mode) 
		{
			low = mid + 1;
		}
		else 
		{
			high = mid - 1;
		}
	}

	if (found == -1) 
	{
		cout << "No residents found with transport mode: " << mode << "\n";
		return;
	}

	int left = found;
	while (left > 0 && residents[left - 1].transportMode == mode) left--;

	int right = found;
	while (right < size - 1 && residents[right + 1].transportMode == mode) right++;

	cout << "Resident ID    Age     Transport      Distance    Emission\n";
	cout << "--------------------------------------------------------------\n";

	for (int i = left; i <= right; i++) 
	{
		cout << setw(15) << residents[i].residentID
			<< setw(8) << residents[i].age
			<< setw(15) << residents[i].transportMode
			<< setw(12) << residents[i].dailyDistance
			<< setw(12) << residents[i].calculateMonthlyEmission()
			<< "\n";
		count++;
	}

	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds> (end - start);

	cout << "Total Found: " << count << "\n";
	cout << "Time Taken: " << duration.count() << " microseconds \n";

}

void SearchByAge(Resident residents[], int size, string ageGroup)
{
	int count = 0;
	auto start = chrono::high_resolution_clock::now();

	cout << "Searching for age group: " << ageGroup << "\n";

	cout << "Resident ID    Age     Transport      Distance    Emission\n";
	cout << "--------------------------------------------------------------\n";

	for (int i = 0; i < size; i++) 
	{
		if (residents[i].getAgeGroup() == ageGroup) 
		{
			cout << left << setw(15) << residents[i].residentID
				<< setw(8) << residents[i].age
				<< setw(15) << residents[i].getAgeGroup()
				<< setw(15) << residents[i].transportMode
				<< setw(12) << residents[i].dailyDistance
				<< setw(12) << residents[i].calculateMonthlyEmission()
				<< "\n";
			count++;
		}
	}

	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds> (end - start);

	cout << "Total Found: " << count << "\n";
	cout << "Time Taken: " << duration.count() << " microseconds \n";
}