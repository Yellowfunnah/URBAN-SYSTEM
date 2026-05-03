// Recommendations.cpp - LinkedList Program
// Task 9 - Insights and Recommendations (Linked List version)
//
// what this file does:
// - shows a submenu to pick city A, B, C or all combined
// - for individual cities: shows emissions per age group,
//   top transport, and green vs car breakdown
// - for all cities: adds cross-city comparison table
//   plus written recommendations for city planners
//
// key difference from array version:
// all loops use Node* current = list.getHead()
// and current = current->nextAddress to traverse

#include "Recommendations.h"
#include <iostream>
#include <iomanip>
using namespace std;

int getModeIdxRLL(string mode, string modes[], int total) {
    for (int i = 0; i < total; i++)
        if (modes[i] == mode) return i;
    return -1;
}

int getListSizeR(LinkedList& list) {
    int count = 0;
    Node* current = list.getHead();
    while (current != nullptr) {
        count++;
        current = current->nextAddress;
    }
    return count;
}

void analyzeOneCityLL(LinkedList& list, string cityName,
    string groups[], string shortGroups[],
    string modes[], int NUM_GROUPS, int NUM_MODES) {

    double emByGroup[5] = { 0 };
    int countByGroup[5] = { 0 };
    int modeTotals[5][6] = {};

    // traverse the linked list once collecting all group data
    Node* current = list.getHead();
    while (current != nullptr) {
        for (int g = 0; g < NUM_GROUPS; g++) {
            if (current->data.getAgeGroup() == groups[g]) {
                emByGroup[g] += current->data.calculateMonthlyEmission();
                countByGroup[g]++;
                for (int m = 0; m < NUM_MODES; m++) {
                    if (current->data.transportMode == modes[m]) {
                        modeTotals[g][m]++;
                        break;
                    }
                }
            }
        }
        current = current->nextAddress;
    }

    int size = getListSizeR(list);

    int highG = 0, lowG = 0;
    double highVal = -1, lowVal = -1, cityTotal = 0;

    for (int g = 0; g < NUM_GROUPS; g++) {
        cityTotal += emByGroup[g];
        if (highVal < 0 || emByGroup[g] > highVal) { highVal = emByGroup[g]; highG = g; }
        if (lowVal < 0 || emByGroup[g] < lowVal) { lowVal = emByGroup[g]; lowG = g; }
    }

    cout << "\n  " << string(62, '=') << "\n";
    cout << "        INSIGHTS  --  " << cityName << "\n";
    cout << "        Total Residents : " << size << "\n";
    cout << "  " << string(62, '=') << "\n";

    // section 1 - emission table
    cout << "\n  [ 1 ]  Emissions by Age Group\n";
    cout << "  " << string(57, '-') << "\n";
    cout << "  " << left
        << setw(33) << "  Age Group"
        << setw(12) << "Total CO2"
        << "Avg/Person\n";
    cout << "  " << string(57, '-') << "\n";

    for (int g = 0; g < NUM_GROUPS; g++) {
        double avg = countByGroup[g] > 0 ? emByGroup[g] / countByGroup[g] : 0;
        cout << "  " << left
            << setw(33) << ("  " + shortGroups[g])
            << setw(12) << fixed << setprecision(2) << emByGroup[g]
            << fixed << setprecision(2) << avg << "\n";
    }

    cout << "  " << string(57, '-') << "\n";
    cout << "    City Total CO2  :  " << fixed << setprecision(2)
        << cityTotal << " kg/month\n";
    cout << "    City Avg CO2    :  " << fixed << setprecision(2)
        << (size > 0 ? cityTotal / size : 0) << " kg/resident\n";
    cout << "  " << string(57, '-') << "\n";
    cout << "  >> Highest emitting group : " << groups[highG]
        << " (" << fixed << setprecision(2) << highVal << " kg)\n";
    cout << "  >> Lowest  emitting group : " << groups[lowG]
        << " (" << fixed << setprecision(2) << lowVal << " kg)\n";

    // section 2 - top transport
    cout << "\n  [ 2 ]  Most Preferred Transport\n";
    cout << "  " << string(53, '-') << "\n";
    cout << "  " << left
        << setw(33) << "  Age Group"
        << setw(14) << "Top Mode"
        << "Count\n";
    cout << "  " << string(53, '-') << "\n";

    for (int g = 0; g < NUM_GROUPS; g++) {
        int top = 0;
        for (int m = 1; m < NUM_MODES; m++)
            if (modeTotals[g][m] > modeTotals[g][top]) top = m;
        cout << "  " << left
            << setw(33) << ("  " + shortGroups[g])
            << setw(14) << (modeTotals[g][top] > 0 ? modes[top] : "N/A")
            << modeTotals[g][top] << "\n";
    }
    cout << "  " << string(53, '-') << "\n";

    // section 3 - green vs cars
    int greenCount = 0, carCount = 0, totalAll = 0;
    for (int g = 0; g < NUM_GROUPS; g++) {
        greenCount += modeTotals[g][2] + modeTotals[g][3];
        carCount += modeTotals[g][0];
        for (int m = 0; m < NUM_MODES; m++) totalAll += modeTotals[g][m];
    }

    cout << "\n  [ 3 ]  Green vs High-Emission Transport\n";
    cout << "  " << string(44, '-') << "\n";
    if (totalAll > 0) {
        cout << "    Bicycle + Walking  :  " << setw(4) << greenCount
            << " residents  ("
            << fixed << setprecision(1)
            << (double)greenCount / totalAll * 100 << "%)\n";
        cout << "    Car users          :  " << setw(4) << carCount
            << " residents  ("
            << fixed << setprecision(1)
            << (double)carCount / totalAll * 100 << "%)\n";
    }
    cout << "  " << string(44, '-') << "\n";
}

void analyzeAllCitiesLL(LinkedList& cityA, LinkedList& cityB,
    LinkedList& cityC,
    string groups[], string shortGroups[],
    string modes[], int NUM_GROUPS, int NUM_MODES) {

    double emA[5] = { 0 }, emB[5] = { 0 }, emC[5] = { 0 };
    int cntA[5] = { 0 }, cntB[5] = { 0 }, cntC[5] = { 0 };
    int modeTotals[5][6] = {};

    // traverse city A
    Node* current = cityA.getHead();
    while (current != nullptr) {
        for (int g = 0; g < NUM_GROUPS; g++)
            if (current->data.getAgeGroup() == groups[g]) {
                emA[g] += current->data.calculateMonthlyEmission();
                cntA[g]++;
                for (int m = 0; m < NUM_MODES; m++)
                    if (current->data.transportMode == modes[m]) {
                        modeTotals[g][m]++; break;
                    }
            }
        current = current->nextAddress;
    }

    // traverse city B
    current = cityB.getHead();
    while (current != nullptr) {
        for (int g = 0; g < NUM_GROUPS; g++)
            if (current->data.getAgeGroup() == groups[g]) {
                emB[g] += current->data.calculateMonthlyEmission();
                cntB[g]++;
                for (int m = 0; m < NUM_MODES; m++)
                    if (current->data.transportMode == modes[m]) {
                        modeTotals[g][m]++; break;
                    }
            }
        current = current->nextAddress;
    }

    // traverse city C
    current = cityC.getHead();
    while (current != nullptr) {
        for (int g = 0; g < NUM_GROUPS; g++)
            if (current->data.getAgeGroup() == groups[g]) {
                emC[g] += current->data.calculateMonthlyEmission();
                cntC[g]++;
                for (int m = 0; m < NUM_MODES; m++)
                    if (current->data.transportMode == modes[m]) {
                        modeTotals[g][m]++; break;
                    }
            }
        current = current->nextAddress;
    }

    int highG = 0, lowG = 0;
    double highVal = -1, lowVal = -1, grandTotal = 0;
    double groupTotals[5] = { 0 };

    for (int g = 0; g < NUM_GROUPS; g++) {
        groupTotals[g] = emA[g] + emB[g] + emC[g];
        grandTotal += groupTotals[g];
        if (highVal < 0 || groupTotals[g] > highVal) { highVal = groupTotals[g]; highG = g; }
        if (lowVal < 0 || groupTotals[g] < lowVal) { lowVal = groupTotals[g]; lowG = g; }
    }

    cout << "\n  " << string(62, '=') << "\n";
    cout << "        INSIGHTS & RECOMMENDATIONS  --  ALL CITIES\n";
    cout << "  " << string(62, '=') << "\n";

    // section 1 - cross city emission table
    cout << "\n  [ 1 ]  Emissions by Age Group\n";
    cout << "  " << string(74, '-') << "\n";
    cout << "  " << left
        << setw(33) << "  Age Group"
        << setw(11) << "City A"
        << setw(11) << "City B"
        << setw(11) << "City C"
        << "Total\n";
    cout << "  " << string(74, '-') << "\n";

    for (int g = 0; g < NUM_GROUPS; g++) {
        cout << "  " << left
            << setw(33) << ("  " + shortGroups[g])
            << setw(11) << fixed << setprecision(2) << emA[g]
            << setw(11) << fixed << setprecision(2) << emB[g]
            << setw(11) << fixed << setprecision(2) << emC[g]
            << fixed << setprecision(2) << groupTotals[g] << "\n";
    }

    cout << "  " << string(74, '-') << "\n";
    cout << "  " << left
        << setw(33) << "  Grand Total"
        << setw(11) << "-" << setw(11) << "-" << setw(11) << "-"
        << fixed << setprecision(2) << grandTotal << " kg CO2\n";
    cout << "  " << string(74, '-') << "\n";
    cout << "  >> Highest : " << shortGroups[highG]
        << "  --  " << fixed << setprecision(2) << highVal << " kg CO2/month\n";
    cout << "  >> Lowest  : " << shortGroups[lowG]
        << "  --  " << fixed << setprecision(2) << lowVal << " kg CO2/month\n";

    // section 2 - avg per person
    cout << "\n  [ 2 ]  Average CO2 per Person\n";
    cout << "  " << string(55, '-') << "\n";
    cout << "  " << left
        << setw(33) << "  Age Group"
        << setw(8) << "City A"
        << setw(8) << "City B"
        << "City C\n";
    cout << "  " << string(55, '-') << "\n";

    for (int g = 0; g < NUM_GROUPS; g++) {
        double aA = cntA[g] > 0 ? emA[g] / cntA[g] : 0;
        double aB = cntB[g] > 0 ? emB[g] / cntB[g] : 0;
        double aC = cntC[g] > 0 ? emC[g] / cntC[g] : 0;
        cout << "  " << left
            << setw(33) << ("  " + shortGroups[g])
            << setw(8) << fixed << setprecision(2) << aA
            << setw(8) << fixed << setprecision(2) << aB
            << fixed << setprecision(2) << aC << "\n";
    }
    cout << "  " << string(55, '-') << "\n";

    // section 3 - top transport
    cout << "\n  [ 3 ]  Most Preferred Transport by Age Group\n";
    cout << "  " << string(53, '-') << "\n";
    cout << "  " << left
        << setw(33) << "  Age Group"
        << setw(14) << "Top Mode"
        << "Count\n";
    cout << "  " << string(53, '-') << "\n";

    for (int g = 0; g < NUM_GROUPS; g++) {
        int top = 0;
        for (int m = 1; m < NUM_MODES; m++)
            if (modeTotals[g][m] > modeTotals[g][top]) top = m;
        cout << "  " << left
            << setw(33) << ("  " + shortGroups[g])
            << setw(14) << (modeTotals[g][top] > 0 ? modes[top] : "N/A")
            << modeTotals[g][top] << "\n";
    }
    cout << "  " << string(53, '-') << "\n";

    // section 4 - green vs car
    int greenCount = 0, carCount = 0, totalAll = 0;
    for (int g = 0; g < NUM_GROUPS; g++) {
        greenCount += modeTotals[g][2] + modeTotals[g][3];
        carCount += modeTotals[g][0];
        for (int m = 0; m < NUM_MODES; m++) totalAll += modeTotals[g][m];
    }

    cout << "\n  [ 4 ]  Green vs High-Emission Transport\n";
    cout << "  " << string(44, '-') << "\n";
    if (totalAll > 0) {
        cout << "    Bicycle + Walking  :  " << setw(4) << greenCount
            << " residents  ("
            << fixed << setprecision(1)
            << (double)greenCount / totalAll * 100 << "%)\n";
        cout << "    Car users          :  " << setw(4) << carCount
            << " residents  ("
            << fixed << setprecision(1)
            << (double)carCount / totalAll * 100 << "%)\n";
    }
    cout << "  " << string(44, '-') << "\n";

    // section 5 - recommendations
    cout << "\n  " << string(62, '=') << "\n";
    cout << "        RECOMMENDATIONS FOR CITY PLANNERS\n";
    cout << "  " << string(62, '=') << "\n\n";

    cout << "    [1]  Target Working Adults (Ages 26-60)\n";
    cout << "         High car usage causes most emissions in City A & C.\n";
    cout << "         Subsidised bus passes + park-and-ride schemes help.\n\n";

    cout << "    [2]  Invest in Cycling Lanes for Youth\n";
    cout << "         Children and students in City B already prefer bicycles.\n";
    cout << "         Safe lanes near schools lock in this zero-emission habit.\n\n";

    cout << "    [3]  Expand Carpool Schemes in City B\n";
    cout << "         Students use shared transport heavily already.\n";
    cout << "         More organised routes lowers per-head emissions.\n\n";

    cout << "    [4]  Better Bus Access for Senior Citizens\n";
    cout << "         Higher frequency + accessible stops prevents car switch.\n\n";

    cout << "    [5]  Fix Car Dependency in Suburban City C\n";
    cout << "         Long distances force car reliance in this area.\n";
    cout << "         Feeder bus routes and EV incentives are the best fix.\n\n";

    cout << "    [6]  Run Carbon Awareness Campaigns\n";
    cout << "         Show residents their personal monthly CO2 footprint.\n";
    cout << "         Drives behaviour change across all age groups.\n";

    cout << "\n  " << string(62, '=') << "\n";
}

void showInsightsAndRecommendations(LinkedList& cityA,
    LinkedList& cityB,
    LinkedList& cityC) {

    const int NUM_GROUPS = 5;
    const int NUM_MODES = 6;

    string groups[NUM_GROUPS] = {
        "Children & Teenagers",
        "University Students / Young Adults",
        "Working Adults (Early Career)",
        "Working Adults (Late Career)",
        "Senior Citizens / Retirees"
    };

    string shortGroups[NUM_GROUPS] = {
        "Children & Teenagers",
        "Univ Students / Young Adults",
        "Working Adults Early Career",
        "Working Adults Late Career",
        "Senior Citizens / Retirees"
    };

    string modes[NUM_MODES] = {
        "Car", "Bus", "Bicycle", "Walking", "School Bus", "Carpool"
    };

    int choice;

    do {
        cout << "  " << string(44, '=') << "\n";
        cout << "        INSIGHTS & RECOMMENDATIONS\n";
        cout << "  " << string(44, '=') << "\n\n";
        cout << "    [1]  City A - Metropolitan City\n";
        cout << "    [2]  City B - University Town\n";
        cout << "    [3]  City C - Suburban/Rural Area\n";
        cout << "    [4]  All Cities Combined\n";
        cout << "    [0]  Back\n";
        cout << "  " << string(44, '=') << "\n";
        cout << "  Enter choice: ";
        cin >> choice;

        if (choice == 1)
            analyzeOneCityLL(cityA, "City A - Metropolitan",
                groups, shortGroups, modes, NUM_GROUPS, NUM_MODES);
        else if (choice == 2)
            analyzeOneCityLL(cityB, "City B - University Town",
                groups, shortGroups, modes, NUM_GROUPS, NUM_MODES);
        else if (choice == 3)
            analyzeOneCityLL(cityC, "City C - Suburban/Rural",
                groups, shortGroups, modes, NUM_GROUPS, NUM_MODES);
        else if (choice == 4)
            analyzeAllCitiesLL(cityA, cityB, cityC,
                groups, shortGroups, modes, NUM_GROUPS, NUM_MODES);
        else if (choice != 0)
            cout << "  Invalid choice. Please enter 0-4.\n";

    } while (choice != 0);
}