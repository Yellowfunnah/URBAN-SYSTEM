#include <fstream>
#include <sstream>
#include "DataLoader.h"

using namespace std;

void loadData(string filename, Resident residents[], int& size) {
    ifstream file(filename);
    string line;

    size = 0;

    
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string temp;

        getline(ss, residents[size].residentID, ',');

        getline(ss, temp, ',');
        residents[size].age = stoi(temp);

        getline(ss, residents[size].transportMode, ',');

        getline(ss, temp, ',');
        residents[size].dailyDistance = stod(temp);

        getline(ss, temp, ',');
        residents[size].emissionFactor = stod(temp);

        getline(ss, temp, ',');
        residents[size].averageDays = stoi(temp);

        size++;
    }

    file.close();
}