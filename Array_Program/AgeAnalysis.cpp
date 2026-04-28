// ============================================================
// AgeAnalysis.cpp
// Task 4 - Age Group Categorization & Analysis
// Author: Aimen Rizwan
// ============================================================

#include "AgeAnalysis.h"
#include <iostream>
#include <iomanip>
using namespace std;

// finds index of transport mode in modes array
int getModeIndex(string mode, string modes[], int total) {
    for (int i = 0; i < total; i++)
        if (modes[i] == mode) return i;
    return -1;
}

// returns emission level label based on average
string getEmissionLevel(double avg) {
    if (avg == 0)   return "Zero Emission";
    if (avg < 20)   return "Low";
    if (avg < 60)   return "Moderate";
    return "High";
}

void analyzeAgeGroups(Resident residents[], int size, string cityName) {

    const int NUM_GROUPS = 5;
    const int NUM_MODES = 6;

    string groups[NUM_GROUPS] = {
        "Children & Teenagers",
        "University Students / Young Adults",
        "Working Adults (Early Career)",
        "Working Adults (Late Career)",
        "Senior Citizens / Retirees"
    };

    string ranges[NUM_GROUPS] = {
        "6-17", "18-25", "26-45", "46-60", "61+"
    };

    string modes[NUM_MODES] = {
        "Car", "Bus", "Bicycle", "Walking", "School Bus", "Carpool"
    };

    // title header - matches team style
    cout << "\n";
    cout << string(65, '=') << "\n";
    cout << "   Age Group Analysis\n";
    cout << "   City: " << cityName << "\n";
    cout << "   Total Residents Loaded: " << size << "\n";
    cout << string(65, '=') << "\n";

    double cityTotalEmission = 0;
    int cityTotalResidents = 0;

    // store group results for summary at end
    double groupTotals[NUM_GROUPS] = { 0 };
    int groupCounts[NUM_GROUPS] = { 0 };
    string groupTopMode[NUM_GROUPS];

    for (int g = 0; g < NUM_GROUPS; g++) {

        int modeCount[NUM_MODES] = { 0 };
        double modeEmit[NUM_MODES] = { 0.0 };
        double totalEmit = 0.0;
        int totalPeople = 0;

        for (int i = 0; i < size; i++) {
            if (residents[i].getAgeGroup() == groups[g]) {
                totalPeople++;
                double em = residents[i].calculateMonthlyEmission();
                totalEmit += em;
                cityTotalEmission += em;
                int idx = getModeIndex(residents[i].transportMode, modes, NUM_MODES);
                if (idx != -1) {
                    modeCount[idx]++;
                    modeEmit[idx] += em;
                }
            }
        }

        cityTotalResidents += totalPeople;
        groupTotals[g] = totalEmit;
        groupCounts[g] = totalPeople;

        // group header - same style as teammates
        cout << "\n";
        cout << string(65, '-') << "\n";
        cout << "   Age Group : " << groups[g]
            << " (Ages " << ranges[g] << ")\n";
        cout << string(65, '-') << "\n";

        if (totalPeople == 0) {
            cout << "   Residents : 0\n";
            cout << "   >> No residents in this group for " << cityName << "\n";
            groupTopMode[g] = "N/A";
            continue;
        }

        // find top transport
        int topIdx = 0;
        for (int m = 1; m < NUM_MODES; m++)
            if (modeCount[m] > modeCount[topIdx]) topIdx = m;

        groupTopMode[g] = modes[topIdx];

        double avgEmit = totalEmit / totalPeople;

        // transport breakdown table
        cout << left
            << setw(14) << "   Mode"
            << setw(8) << "Count"
            << setw(22) << "Total CO2 (kg)"
            << setw(20) << "Avg CO2/Resident"
            << "\n";
        cout << string(65, '-') << "\n";

        for (int m = 0; m < NUM_MODES; m++) {
            if (modeCount[m] > 0) {
                double avg = modeEmit[m] / modeCount[m];
                double share = (double)modeCount[m] / totalPeople * 100.0;
                cout << left
                    << setw(14) << ("   " + modes[m])
                    << setw(8) << modeCount[m]
                    << setw(22) << fixed << setprecision(2) << modeEmit[m]
                    << setw(20) << fixed << setprecision(2) << avg
                    << "(" << fixed << setprecision(1) << share << "%)\n";
            }
        }

        cout << string(65, '-') << "\n";
        cout << "   Residents     : " << totalPeople << "\n";
        cout << "   Top Transport : " << modes[topIdx]
            << " (" << modeCount[topIdx] << " users, "
            << fixed << setprecision(1)
            << (double)modeCount[topIdx] / totalPeople * 100.0 << "%)\n";
        cout << "   Total CO2     : " << fixed << setprecision(2)
            << totalEmit << " kg/month\n";
        cout << "   Avg CO2       : " << fixed << setprecision(2)
            << avgEmit << " kg/resident\n";
        cout << "   Emission Level: " << getEmissionLevel(avgEmit) << "\n";
    }

    // city summary - matches Cross-City table style from teammates
    cout << "\n";
    cout << string(65, '=') << "\n";
    cout << "   City Summary - " << cityName << "\n";
    cout << string(65, '=') << "\n";
    cout << left
        << setw(34) << "   Age Group"
        << setw(12) << "Residents"
        << setw(16) << "Total CO2 (kg)"
        << "Top Mode"
        << "\n";
    cout << string(65, '-') << "\n";

    for (int g = 0; g < NUM_GROUPS; g++) {
        cout << left
            << setw(34) << ("   " + groups[g].substr(0, 30))
            << setw(12) << groupCounts[g]
            << setw(16) << fixed << setprecision(2) << groupTotals[g]
            << groupTopMode[g]
            << "\n";
    }

    cout << string(65, '-') << "\n";
    cout << "   Total Residents : " << cityTotalResidents << "\n";
    cout << "   Total CO2       : " << fixed << setprecision(2)
        << cityTotalEmission << " kg/month\n";
    if (cityTotalResidents > 0)
        cout << "   Avg CO2         : " << fixed << setprecision(2)
        << cityTotalEmission / cityTotalResidents << " kg/resident\n";
    cout << string(65, '=') << "\n";
}