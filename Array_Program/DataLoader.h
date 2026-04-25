#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Resident.h"
using namespace std;

class DataLoader {
public:
    static int loadData(string fileName, Resident residents[], int maxSize) {
        ifstream file(fileName);

        if (!file) {
            cout << "File cannot be opened: " << fileName << endl;
            return 0;
        }

        string line;
        int count = 0;

        getline(file, line); // skip header row

        while (getline(file, line) && count < maxSize) {
            stringstream ss(line);
            string temp;

            getline(ss, residents[count].residentID, ',');

            getline(ss, temp, ',');
            residents[count].age = stoi(temp);

            getline(ss, residents[count].transportMode, ',');

            getline(ss, temp, ',');
            residents[count].dailyDistance = stod(temp);

            getline(ss, temp, ',');
            residents[count].emissionFactor = stod(temp);

            getline(ss, temp, ',');
            residents[count].averageDays = stoi(temp);

            count++;
        }

        file.close();
        return count;
    }
};