#include <iostream>
#include <iomanip>
#include "Searching.h"
#include <chrono>

using namespace std;

void LinearSearchByTransport(LinkedList& list, string mode)
{
	Node* current = list.getHead();
	int count = 0;
	auto start = chrono::high_resolution_clock::now();

	cout << "Searching for transport mode" << mode << "\n";
	cout << "Resident ID     Age     Transport     Distance     Emission\n";
	cout << "-------------------------------------------------------------\n";

	while (current != NULL)
	{
		if (current->data.transportMode == mode)
		{
			cout << left << setw(15) << current->data.residentID
				<< setw(8) << current->data.age
				<< setw(15) << current->data.transportMode
				<< setw(12) << current->data.dailyDistance
				<< setw(12) << current->data.calculateMonthlyEmission()
				<< "\n";
			count++;
		}
		current = current->nextAddress;
	}

	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds> (end - start);

	cout << "Total Found: " << count << "\n";
	cout << "Time Taken: " << duration.count() << " microseconds \n";

}


void LinearSearchByDistance(LinkedList& list, double minDistance)
{
	Node* current = list.getHead();
	int count = 0;
	auto start = chrono::high_resolution_clock::now();

	cout << "Searching for distance greater than:  " << minDistance << "km\n";
	cout << "Resident ID     Age     Transport     Distance     Emission\n";
	cout << "-------------------------------------------------------------\n";

	while (current != NULL)
	{
		if (current->data.dailyDistance > minDistance)
		{
			cout << left << setw(15) << current->data.residentID
				<< setw(8) << current->data.age
				<< setw(15) << current->data.transportMode
				<< setw(12) << current->data.dailyDistance
				<< setw(12) << current->data.calculateMonthlyEmission()
				<< "\n";
			count++;
		}
		current = current->nextAddress;
	}

	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds> (end - start);

	cout << "Total Found: " << count << "\n";
	cout << "Time Taken: " << duration.count() << " microseconds \n";

}

void BinarySearchByTransport(LinkedList& list, string mode)
{
	int size = list.getSize();
	auto start = chrono::high_resolution_clock::now();

	if (size == 0)
	{
		cout << "List is empty! \n";
		return;
	}

	string* modes = new string[size];
	Node* current = list.getHead();
	int index = 0;

	while (current != NULL)
	{
		modes[index++] = current->data.transportMode;
		current = current->nextAddress;
	}

	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			if (modes[j] > modes[j + 1])
			{
				string temp = modes[j];
				modes[j] = modes[j + 1];
				modes[j + 1] = temp;
			}
		}
	}

	int low = 0, high = size - 1, found = -1;

	while (low <= high)
	{
		int mid = (low + high) / 2;
		if (modes[mid] == mode)
		{
			found = mid;
			break;
		}
		else if (modes[mid] < mode)
		{
			low = mid + 1;
		}
		else
		{
			high = mid - 1;
		}
	}

	cout << "Binary searching for transport mode: " << mode << "\n";
	cout << "Resident ID     Age     Transport     Distance     Emission\n";
	cout << "-------------------------------------------------------------\n";

	if (found == -1)
	{
		cout << "No residents found with transport mode: " << mode << "\n";
		delete[] modes;
		return;
	}

	int count = 0;
	current = list.getHead();

	while (current != NULL)
	{
		if (current->data.transportMode == mode)
		{
			cout << left << setw(15) << current->data.residentID
				<< setw(8) << current->data.age
				<< setw(15) << current->data.transportMode
				<< setw(12) << current->data.dailyDistance
				<< setw(12) << current->data.calculateMonthlyEmission()
				<< "\n";
			count++;
		}
		current = current->nextAddress;
	}
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds> (end - start);

	cout << "Total Found: " << count << "\n";
	cout << "Time Taken: " << duration.count() << " microseconds \n";
	delete[] modes;

}

void SearchByAgeGroup(LinkedList& list, string ageGroup)
{
	Node* current = list.getHead();
	int count = 0;
	auto start = chrono::high_resolution_clock::now();

	cout << "Searching for age group: " << ageGroup << "\n";
	cout << "Resident ID     Age     Transport     Distance     Emission\n";
	cout << "-------------------------------------------------------------\n";

	while (current != NULL)
	{
		if (current->data.getAgeGroup() == ageGroup)
		{
			cout << left << setw(15) << current->data.residentID
				<< setw(8) << current->data.age
				<< setw(15) << current->data.getAgeGroup()
				<< setw(15) << current->data.transportMode
				<< setw(12) << current->data.dailyDistance
				<< setw(12) << current->data.calculateMonthlyEmission()
				<< "\n";
			count++;
		}
		current = current->nextAddress;
	}
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds> (end - start);

	cout << "Total Found: " << count << "\n";
	cout << "Time Taken: " << duration.count() << " microseconds \n";
}