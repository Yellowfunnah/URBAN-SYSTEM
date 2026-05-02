// AgeAnalysis.cpp
// Task 4 - Age Group Categorization and Analysis
//
// what this file does:
// - groups residents into 5 age categories
// - counts transport modes used per group
// - calculates total and average emissions per group
// - shows a submenu so user can pick one group or view all
// - displays results in formatted tables

#include "AgeAnalysis.h"
#include <iostream>
#include <iomanip>
using namespace std;

// helper to find which slot in the modes array a transport name is at
// returns -1 if the mode doesnt match any known ones
int getModeIndex(string mode, string modes[], int total) {
    for (int i = 0; i < total; i++) {
        if (modes[i] == mode)
            return i;
    }
    return -1;
}

// returns a readable label based on how high the average emission is
string getEmissionLevel(double avg) {
    if (avg == 0)  return "[ ZERO EMISSION ]";
    if (avg < 20)  return "[ LOW ]";
    if (avg < 60)  return "[ MODERATE ]";
    return         "[ HIGH ]";
}

// does the analysis for ONE age group
// filters residents by groupName and counts transport + emissions
void printGroupAnalysis(Resident residents[], int size, string cityName,
    string groupName, string ageRange,
    string modes[], int NUM_MODES) {

    int modeCount[6] = { 0 };
    double modeEmit[6] = { 0.0 };
    double totalEmit = 0.0;
    int totalPeople = 0;

    // scan all residents - only process ones in this age group
    for (int i = 0; i < size; i++) {
        if (residents[i].getAgeGroup() == groupName) {
            totalPeople++;
            double em = residents[i].calculateMonthlyEmission();
            totalEmit += em;
            int idx = getModeIndex(residents[i].transportMode, modes, NUM_MODES);
            if (idx != -1) {
                modeCount[idx]++;
                modeEmit[idx] += em;
            }
        }
    }

    // group header
    cout << "  >> " << groupName << "  |  Ages " << ageRange << "\n";
    cout << "  " << string(56, '-') << "\n";

    // show clean message if nobody is in this group
    // this happens because some cities only have certain age ranges
    if (totalPeople == 0) {
        cout << "    No data available for this age group.\n";
        cout << "    (This city does not have residents in this age range)\n";
        cout << "  " << string(56, '-') << "\n";
        return;
    }

    // find the most used transport
    int topIdx = 0;
    for (int m = 1; m < NUM_MODES; m++)
        if (modeCount[m] > modeCount[topIdx]) topIdx = m;

    // find which mode has the highest total emission
    int highEmitIdx = 0;
    for (int m = 1; m < NUM_MODES; m++)
        if (modeEmit[m] > modeEmit[highEmitIdx]) highEmitIdx = m;

    // find which mode has the lowest emission
    // only check modes that have at least 1 person
    int lowEmitIdx = topIdx;
    for (int m = 0; m < NUM_MODES; m++)
        if (modeCount[m] > 0 && modeEmit[m] < modeEmit[lowEmitIdx])
            lowEmitIdx = m;

    double avgEmit = totalEmit / totalPeople;

    // table header
    cout << "  " << left
        << setw(16) << "  Mode"
        << setw(8) << "Count"
        << setw(14) << "Total CO2"
        << setw(14) << "Avg/Res"
        << "Share\n";
    cout << "  " << string(56, '-') << "\n";

    // one row per mode with at least 1 person
    for (int m = 0; m < NUM_MODES; m++) {
        if (modeCount[m] > 0) {
            double avg = modeEmit[m] / modeCount[m];
            double share = (double)modeCount[m] / totalPeople * 100.0;
            cout << "  " << left
                << setw(16) << ("  " + modes[m])
                << setw(8) << modeCount[m]
                << setw(14) << fixed << setprecision(2) << modeEmit[m]
                << setw(14) << fixed << setprecision(2) << avg
                << fixed << setprecision(1) << share << "%\n";
        }
    }

    // summary lines under the table
    cout << "  " << string(56, '-') << "\n";
    cout << "    Residents      : " << totalPeople << "\n";
    cout << "    Preferred Mode : " << modes[topIdx]
        << "  --  " << modeCount[topIdx] << " users"
        << "  (" << fixed << setprecision(1)
        << (double)modeCount[topIdx] / totalPeople * 100.0 << "%)\n";
    cout << "    Highest Emitter: " << modes[highEmitIdx]
        << "  (" << fixed << setprecision(2)
        << modeEmit[highEmitIdx] << " kg total)\n";
    cout << "    Lowest Emitter : " << modes[lowEmitIdx]
        << "  (" << fixed << setprecision(2)
        << modeEmit[lowEmitIdx] << " kg total)\n";
    cout << "    Total CO2      : " << fixed << setprecision(2)
        << totalEmit << " kg/month\n";
    cout << "    Avg CO2        : " << fixed << setprecision(2)
        << avgEmit << " kg/resident\n";
    cout << "    Emission Level : " << getEmissionLevel(avgEmit) << "\n";
    cout << "  " << string(56, '-') << "\n";
}

// main task 4 function
// submenu lets user pick one age group or all
void analyzeAgeGroups(Resident residents[], int size, string cityName) {

    const int NUM_GROUPS = 5;
    const int NUM_MODES = 6;

    // must match getAgeGroup() output in Resident.h exactly
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

    // all transport modes across all 3 cities
    string modes[NUM_MODES] = {
        "Car", "Bus", "Bicycle", "Walking", "School Bus", "Carpool"
    };

    int choice;

    do {
        cout << "\n  " << string(48, '=') << "\n";
        cout << "        AGE GROUP ANALYSIS\n";
        cout << "        City : " << cityName << "\n";
        cout << "        Total Residents : " << size << "\n";
        cout << "  " << string(48, '=') << "\n\n";
        cout << "    [1]  Children & Teenagers        (6-17)\n";
        cout << "    [2]  University Students         (18-25)\n";
        cout << "    [3]  Working Adults Early Career (26-45)\n";
        cout << "    [4]  Working Adults Late Career  (46-60)\n";
        cout << "    [5]  Senior Citizens / Retirees  (61+)\n";
        cout << "    [6]  View All Age Groups\n";
        cout << "    [0]  Back\n";
        cout << "  " << string(48, '=') << "\n";
        cout << "  Enter choice: ";
        cin >> choice;

        if (choice >= 1 && choice <= 5) {
            // user picked one specific group
            int g = choice - 1;
            cout << "\n  " << string(48, '=') << "\n";
            cout << "        AGE GROUP ANALYSIS\n";
            cout << "        City : " << cityName << "\n";
            cout << "  " << string(48, '=') << "\n\n";
            printGroupAnalysis(residents, size, cityName,
                groups[g], ranges[g], modes, NUM_MODES);

        }
        else if (choice == 6) {
            // view all groups one after another
            cout << "\n  " << string(48, '=') << "\n";
            cout << "        ALL AGE GROUPS\n";
            cout << "        City            : " << cityName << "\n";
            cout << "        Total Residents : " << size << "\n";
            cout << "  " << string(48, '=') << "\n\n";

            // store results for summary table at end
            double groupTotals[NUM_GROUPS] = { 0 };
            int groupCounts[NUM_GROUPS] = { 0 };
            string groupTopMode[NUM_GROUPS];
            double cityTotal = 0;

            for (int g = 0; g < NUM_GROUPS; g++) {
                int modeCount[6] = { 0 };
                double modeEmit[6] = { 0.0 };
                double totalEmit = 0.0;
                int totalPeople = 0;

                for (int i = 0; i < size; i++) {
                    if (residents[i].getAgeGroup() == groups[g]) {
                        totalPeople++;
                        double em = residents[i].calculateMonthlyEmission();
                        totalEmit += em;
                        cityTotal += em;
                        int idx = getModeIndex(residents[i].transportMode,
                            modes, NUM_MODES);
                        if (idx != -1) {
                            modeCount[idx]++;
                            modeEmit[idx] += em;
                        }
                    }
                }

                groupTotals[g] = totalEmit;
                groupCounts[g] = totalPeople;

                // find top mode for summary table
                int topIdx = 0;
                for (int m = 1; m < NUM_MODES; m++)
                    if (modeCount[m] > modeCount[topIdx]) topIdx = m;
                groupTopMode[g] = totalPeople > 0 ? modes[topIdx] : "N/A";

                // print full breakdown then move to next group
                printGroupAnalysis(residents, size, cityName,
                    groups[g], ranges[g], modes, NUM_MODES);
            }

            // find highest emitting group
            int highG = 0;
            for (int g = 1; g < NUM_GROUPS; g++)
                if (groupTotals[g] > groupTotals[highG]) highG = g;

            // summary table - column wide enough for full group names
            cout << "\n  " << string(68, '=') << "\n";
            cout << "        SUMMARY  --  " << cityName << "\n";
            cout << "  " << string(68, '=') << "\n";
            cout << "  " << left
                << setw(46) << "  Age Group"
                << setw(8) << "Res"
                << setw(12) << "CO2 (kg)"
                << "Top Mode\n";
            cout << "  " << string(68, '-') << "\n";

            for (int g = 0; g < NUM_GROUPS; g++) {
                // build label with age range - no trimming
                string label = groups[g] + " (" + ranges[g] + ")";
                cout << "  " << left
                    << setw(46) << ("  " + label)
                    << setw(8) << groupCounts[g]
                    << setw(12) << fixed << setprecision(2) << groupTotals[g]
                    << groupTopMode[g] << "\n";
            }

            cout << "  " << string(68, '-') << "\n";
            cout << "    Total Residents :  " << size << "\n";
            cout << "    Total CO2       :  " << fixed << setprecision(2)
                << cityTotal << " kg/month\n";
            if (size > 0)
                cout << "    Avg CO2         :  " << fixed << setprecision(2)
                << cityTotal / size << " kg/resident\n";
            cout << "  " << string(68, '=') << "\n";
            cout << "  >> Insight: " << groups[highG]
                << " is the biggest emitting group\n"
                << "             with " << fixed << setprecision(2)
                << groupTotals[highG] << " kg CO2/month.\n";
            cout << "  >> Insight: Their preferred transport is "
                << groupTopMode[highG] << ".\n";

        }
        else if (choice != 0) {
            cout << "  Invalid choice. Please enter 0-6.\n";
        }

    } while (choice != 0);
}