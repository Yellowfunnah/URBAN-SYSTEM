#include <fstream>
#include <sstream>
#include <iostream>
#include "DataLoader.h"

using namespace std;

void loadData(string filename, LinkedList& list) {
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cout << "Could not open file: " << filename << endl;
        return;
    }

    
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string temp;
        Resident r;

        getline(ss, r.residentID, ',');

        getline(ss, temp, ',');
        r.age = stoi(temp);

        getline(ss, r.transportMode, ',');

        getline(ss, temp, ',');
        r.dailyDistance = stod(temp);

        getline(ss, temp, ',');
        r.emissionFactor = stod(temp);

        getline(ss, temp, ',');
        r.averageDays = stoi(temp);

        list.insertAtEnd(r);
    }

    file.close();
}