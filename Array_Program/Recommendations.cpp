// Recommendations.cpp
// Written by: Aimen Rizwan
// Task 9 - Insights and Recommendations
//
// what this file does:
// - shows a submenu to pick city A, B, C or all combined
// - for individual cities: shows emissions per age group,
//   top transport, and green vs car breakdown
// - for all cities: adds a cross-city comparison table
//   plus written recommendations for city planners

#include "Recommendations.h"
#include <iostream>
#include <iomanip>
using namespace std;

// same helper as AgeAnalysis but renamed to avoid redefinition errors
int getModeIndexR(string mode, string modes[], int total) {
    for (int i = 0; i < total; i++)
        if (modes[i] == mode) return i;
    return -1;
}

// handles insights for one specific city
void analyzeOneCity(Resident residents[], int size, string cityName,
    string groups[], string shortGroups[],
    string modes[], int NUM_GROUPS, int NUM_MODES) {

    double emByGroup[5] = { 0 };
    int countByGroup[5] = { 0 };
    int modeTotals[5][6] = {};

    // collect data from this city
    for (int i = 0; i < size; i++) {
        for (int g = 0; g < NUM_GROUPS; g++) {
            if (residents[i].getAgeGroup() == groups[g]) {
                emByGroup[g] += residents[i].calculateMonthlyEmission();
                countByGroup[g]++;
                for (int m = 0; m < NUM_MODES; m++) {
                    if (residents[i].transportMode == modes[m]) {
                        modeTotals[g][m]++;
                        break;
                    }
                }
            }
        }
    }

    // find highest and lowest emitting groups
    int highG = 0, lowG = 0;
    double highVal = -1, lowVal = -1, cityTotal = 0;

    for (int g = 0; g < NUM_GROUPS; g++) {
        cityTotal += emByGroup[g];
        if (highVal < 0 || emByGroup[g] > highVal) { highVal = emByGroup[g]; highG = g; }
        if (lowVal < 0 || emByGroup[g] < lowVal) { lowVal = emByGroup[g]; lowG = g; }
    }

    // city title
    cout << "\n  " << string(62, '=') << "\n";
    cout << "        INSIGHTS  --  " << cityName << "\n";
    cout << "        Total Residents : " << size << "\n";
    cout << "  " << string(62, '=') << "\n";

    // section 1 - emission table
    cout << "\n  [ 1 ]  Emissions by Age Group\n";
    cout << "  " << string(54, '-') << "\n";
    cout << "  " << left
        << setw(32) << "  Age Group"
        << setw(12) << "Total CO2"
        << "Avg/Person\n";
    cout << "  " << string(54, '-') << "\n";

    for (int g = 0; g < NUM_GROUPS; g++) {
        double avg = countByGroup[g] > 0 ? emByGroup[g] / countByGroup[g] : 0;
        cout << "  " << left
            << setw(32) << ("  " + shortGroups[g])
            << setw(12) << fixed << setprecision(2) << emByGroup[g]
            << fixed << setprecision(2) << avg << "\n";
    }

    cout << "  " << string(54, '-') << "\n";
    cout << "    City Total CO2  :  " << fixed << setprecision(2)
        << cityTotal << " kg/month\n";
    cout << "    City Avg CO2    :  " << fixed << setprecision(2)
        << (size > 0 ? cityTotal / size : 0) << " kg/resident\n";
    cout << "  " << string(54, '-') << "\n";
    cout << "  >> Highest emitting group : " << groups[highG]
        << " (" << fixed << setprecision(2) << highVal << " kg)\n";
    cout << "  >> Lowest  emitting group : " << groups[lowG]
        << " (" << fixed << setprecision(2) << lowVal << " kg)\n";

    // section 2 - top transport
    cout << "\n  [ 2 ]  Most Preferred Transport\n";
    cout << "  " << string(50, '-') << "\n";
    cout << "  " << left
        << setw(32) << "  Age Group"
        << setw(14) << "Top Mode"
        << "Count\n";
    cout << "  " << string(50, '-') << "\n";

    for (int g = 0; g < NUM_GROUPS; g++) {
        int top = 0;
        for (int m = 1; m < NUM_MODES; m++)
            if (modeTotals[g][m] > modeTotals[g][top]) top = m;
        cout << "  " << left
            << setw(32) << ("  " + shortGroups[g])
            << setw(14) << (modeTotals[g][top] > 0 ? modes[top] : "N/A")
            << modeTotals[g][top] << "\n";
    }
    cout << "  " << string(50, '-') << "\n";

    // section 3 - green vs cars
    // bicycle = index 2, walking = index 3, car = index 0
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
    // no closing ==== here - removed to avoid double border with submenu
}

// all cities combined view
void analyzeAllCities(Resident cityA[], int sizeA,
    Resident cityB[], int sizeB,
    Resident cityC[], int sizeC,
    string groups[], string shortGroups[],
    string modes[], int NUM_GROUPS, int NUM_MODES) {

    double emA[5] = { 0 }, emB[5] = { 0 }, emC[5] = { 0 };
    int cntA[5] = { 0 }, cntB[5] = { 0 }, cntC[5] = { 0 };
    int modeTotals[5][6] = {};

    // collect city A
    for (int i = 0; i < sizeA; i++)
        for (int g = 0; g < NUM_GROUPS; g++)
            if (cityA[i].getAgeGroup() == groups[g]) {
                emA[g] += cityA[i].calculateMonthlyEmission();
                cntA[g]++;
                for (int m = 0; m < NUM_MODES; m++)
                    if (cityA[i].transportMode == modes[m]) { modeTotals[g][m]++; break; }
            }

    // collect city B
    for (int i = 0; i < sizeB; i++)
        for (int g = 0; g < NUM_GROUPS; g++)
            if (cityB[i].getAgeGroup() == groups[g]) {
                emB[g] += cityB[i].calculateMonthlyEmission();
                cntB[g]++;
                for (int m = 0; m < NUM_MODES; m++)
                    if (cityB[i].transportMode == modes[m]) { modeTotals[g][m]++; break; }
            }

    // collect city C
    for (int i = 0; i < sizeC; i++)
        for (int g = 0; g < NUM_GROUPS; g++)
            if (cityC[i].getAgeGroup() == groups[g]) {
                emC[g] += cityC[i].calculateMonthlyEmission();
                cntC[g]++;
                for (int m = 0; m < NUM_MODES; m++)
                    if (cityC[i].transportMode == modes[m]) { modeTotals[g][m]++; break; }
            }

    // find highest lowest and grand total
    int highG = 0, lowG = 0;
    double highVal = -1, lowVal = -1, grandTotal = 0;
    double groupTotals[5] = { 0 };

    for (int g = 0; g < NUM_GROUPS; g++) {
        groupTotals[g] = emA[g] + emB[g] + emC[g];
        grandTotal += groupTotals[g];
        if (highVal < 0 || groupTotals[g] > highVal) { highVal = groupTotals[g]; highG = g; }
        if (lowVal < 0 || groupTotals[g] < lowVal) { lowVal = groupTotals[g]; lowG = g; }
    }

    // title
    cout << "\n  " << string(62, '=') << "\n";
    cout << "        INSIGHTS & RECOMMENDATIONS  --  ALL CITIES\n";
    cout << "  " << string(62, '=') << "\n";

    // section 1 - cross city emission table
    cout << "\n  [ 1 ]  Emissions by Age Group\n";
    cout << "  " << string(71, '-') << "\n";
    cout << "  " << left
        << setw(30) << "  Age Group"
        << setw(11) << "City A"
        << setw(11) << "City B"
        << setw(11) << "City C"
        << "Total\n";
    cout << "  " << string(71, '-') << "\n";

    for (int g = 0; g < NUM_GROUPS; g++) {
        cout << "  " << left
            << setw(30) << ("  " + shortGroups[g])
            << setw(11) << fixed << setprecision(2) << emA[g]
            << setw(11) << fixed << setprecision(2) << emB[g]
            << setw(11) << fixed << setprecision(2) << emC[g]
            << fixed << setprecision(2) << groupTotals[g] << "\n";
    }

    cout << "  " << string(71, '-') << "\n";
    cout << "  " << left
        << setw(30) << "  Grand Total"
        << setw(11) << "-" << setw(11) << "-" << setw(11) << "-"
        << fixed << setprecision(2) << grandTotal << " kg CO2\n";
    cout << "  " << string(71, '-') << "\n";
    cout << "  >> Highest : " << shortGroups[highG]
        << "  --  " << fixed << setprecision(2) << highVal << " kg CO2/month\n";
    cout << "  >> Lowest  : " << shortGroups[lowG]
        << "  --  " << fixed << setprecision(2) << lowVal << " kg CO2/month\n";

    // section 2 - avg per person
    // fairer comparison since cities have different resident counts
    cout << "\n  [ 2 ]  Average CO2 per Person\n";
    cout << "  " << string(52, '-') << "\n";
    cout << "  " << left
        << setw(30) << "  Age Group"
        << setw(8) << "City A"
        << setw(8) << "City B"
        << "City C\n";
    cout << "  " << string(52, '-') << "\n";

    for (int g = 0; g < NUM_GROUPS; g++) {
        // check count before dividing to avoid divide by zero
        double aA = cntA[g] > 0 ? emA[g] / cntA[g] : 0;
        double aB = cntB[g] > 0 ? emB[g] / cntB[g] : 0;
        double aC = cntC[g] > 0 ? emC[g] / cntC[g] : 0;
        cout << "  " << left
            << setw(30) << ("  " + shortGroups[g])
            << setw(8) << fixed << setprecision(2) << aA
            << setw(8) << fixed << setprecision(2) << aB
            << fixed << setprecision(2) << aC << "\n";
    }
    cout << "  " << string(52, '-') << "\n";

    // section 3 - top transport combined from all cities
    cout << "\n  [ 3 ]  Most Preferred Transport by Age Group\n";
    cout << "  " << string(50, '-') << "\n";
    cout << "  " << left
        << setw(30) << "  Age Group"
        << setw(14) << "Top Mode"
        << "Count\n";
    cout << "  " << string(50, '-') << "\n";

    for (int g = 0; g < NUM_GROUPS; g++) {
        int top = 0;
        for (int m = 1; m < NUM_MODES; m++)
            if (modeTotals[g][m] > modeTotals[g][top]) top = m;
        cout << "  " << left
            << setw(30) << ("  " + shortGroups[g])
            << setw(14) << (modeTotals[g][top] > 0 ? modes[top] : "N/A")
            << modeTotals[g][top] << "\n";
    }
    cout << "  " << string(50, '-') << "\n";

    // section 4 - green vs car across all cities
    int greenCount = 0, carCount = 0, totalAll = 0;
    for (int g = 0; g < NUM_GROUPS; g++) {
        greenCount += modeTotals[g][2] + modeTotals[g][3]; // bicycle + walking
        carCount += modeTotals[g][0];                    // car
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

    // section 5 - written recommendations based on data patterns
    cout << "\n  " << string(62, '=') << "\n";
    cout << "        RECOMMENDATIONS FOR CITY PLANNERS\n";
    cout << "  " << string(62, '=') << "\n\n";

    // working adults are the biggest problem based on the data
    cout << "    [1]  Target Working Adults (Ages 26-60)\n";
    cout << "         High car usage causes most emissions in City A & C.\n";
    cout << "         Subsidised bus passes + park-and-ride schemes help.\n\n";

    // city B already has good habits - just need infrastructure
    cout << "    [2]  Invest in Cycling Lanes for Youth\n";
    cout << "         Children and students in City B already prefer bicycles.\n";
    cout << "         Safe lanes near schools lock in this zero-emission habit.\n\n";

    // carpool already popular in city B so worth expanding
    cout << "    [3]  Expand Carpool Schemes in City B\n";
    cout << "         Students use shared transport heavily already.\n";
    cout << "         More organised routes lowers per-head emissions.\n\n";

    // seniors need to stay on public transport
    cout << "    [4]  Better Bus Access for Senior Citizens\n";
    cout << "         Higher frequency + accessible stops prevents car switch.\n\n";

    // city C hardest to fix because of long distances
    cout << "    [5]  Fix Car Dependency in Suburban City C\n";
    cout << "         Long distances force car reliance in this area.\n";
    cout << "         Feeder bus routes and EV incentives are the best fix.\n\n";

    // awareness can drive change even without policy
    cout << "    [6]  Run Carbon Awareness Campaigns\n";
    cout << "         Show residents their personal monthly CO2 footprint.\n";
    cout << "         Drives behaviour change across all age groups.\n";

    cout << "\n  " << string(62, '=') << "\n";
}

// entry point for task 9
// submenu for city selection
void showInsightsAndRecommendations(Resident cityA[], int sizeA,
    Resident cityB[], int sizeB,
    Resident cityC[], int sizeC) {

    const int NUM_GROUPS = 5;
    const int NUM_MODES = 6;

    // must match getAgeGroup() output exactly
    string groups[NUM_GROUPS] = {
        "Children & Teenagers",
        "University Students / Young Adults",
        "Working Adults (Early Career)",
        "Working Adults (Late Career)",
        "Senior Citizens / Retirees"
    };

    // shorter versions for tight table columns
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
        // no leading \n so there is no gap after returning from a city view
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
            analyzeOneCity(cityA, sizeA, "City A - Metropolitan",
                groups, shortGroups, modes, NUM_GROUPS, NUM_MODES);
        else if (choice == 2)
            analyzeOneCity(cityB, sizeB, "City B - University Town",
                groups, shortGroups, modes, NUM_GROUPS, NUM_MODES);
        else if (choice == 3)
            analyzeOneCity(cityC, sizeC, "City C - Suburban/Rural",
                groups, shortGroups, modes, NUM_GROUPS, NUM_MODES);
        else if (choice == 4)
            analyzeAllCities(cityA, sizeA, cityB, sizeB, cityC, sizeC,
                groups, shortGroups, modes, NUM_GROUPS, NUM_MODES);
        else if (choice != 0)
            cout << "  Invalid choice. Please enter 0-4.\n";

    } while (choice != 0);
}