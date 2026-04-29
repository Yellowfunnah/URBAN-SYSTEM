// AgeAnalysis.cpp
// Written by: Aimen Rizwan
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
// i need this because i store counts in a fixed array indexed by mode
// returns -1 if the mode doesnt match any of the known ones
int getModeIndex(string mode, string modes[], int total) {
    for (int i = 0; i < total; i++) {
        if (modes[i] == mode)
            return i;
    }
    return -1;
}

// returns a readable label based on how high the average emission is
// i added this to make the output more meaningful than just a number
string getEmissionLevel(double avg) {
    if (avg == 0)  return "[ ZERO EMISSION ]";
    if (avg < 20)  return "[ LOW ]";
    if (avg < 60)  return "[ MODERATE ]";
    return         "[ HIGH ]";
}

// this is the core function that does the analysis for ONE age group
// it takes the full residents array and filters by groupName
// then counts how many use each transport and sums up emissions
void printGroupAnalysis(Resident residents[], int size, string cityName,
    string groupName, string ageRange,
    string modes[], int NUM_MODES) {

    // separate counters for each transport mode in this group
    int modeCount[6] = { 0 };
    double modeEmit[6] = { 0.0 };
    double totalEmit = 0.0;
    int totalPeople = 0;

    // scan all residents - only process the ones in this age group
    for (int i = 0; i < size; i++) {
        if (residents[i].getAgeGroup() == groupName) {
            totalPeople++;

            // calculateMonthlyEmission() is in Resident.h
            // formula is: dailyDistance * emissionFactor * avgDays
            double em = residents[i].calculateMonthlyEmission();
            totalEmit += em;

            // figure out which slot this transport goes in
            // and add their emission to that modes running total
            int idx = getModeIndex(residents[i].transportMode, modes, NUM_MODES);
            if (idx != -1) {
                modeCount[idx]++;
                modeEmit[idx] += em;
            }
        }
    }

    // group header
    cout << "\n  >> " << groupName << "  |  Ages " << ageRange << "\n";
    cout << "  " << string(50, '-') << "\n";

    // nothing to show if nobody is in this group for this city
    if (totalPeople == 0) {
        cout << "    No residents in this group for " << cityName << "\n";
        cout << "  " << string(50, '-') << "\n";
        return;
    }

    // find the most used transport - just look for the highest count
    int topIdx = 0;
    for (int m = 1; m < NUM_MODES; m++) {
        if (modeCount[m] > modeCount[topIdx])
            topIdx = m;
    }

    double avgEmit = totalEmit / totalPeople;

    // column headers for the transport breakdown table
    cout << "  " << left
        << setw(16) << "  Mode"
        << setw(8) << "Count"
        << setw(12) << "Total CO2"
        << setw(12) << "Avg/Res"
        << "Share\n";
    cout << "  " << string(50, '-') << "\n";

    // one row per transport mode - only show modes that have at least 1 person
    for (int m = 0; m < NUM_MODES; m++) {
        if (modeCount[m] > 0) {
            double avg = modeEmit[m] / modeCount[m];
            double share = (double)modeCount[m] / totalPeople * 100.0;
            cout << "  " << left
                << setw(16) << ("  " + modes[m])
                << setw(8) << modeCount[m]
                << setw(12) << fixed << setprecision(2) << modeEmit[m]
                << setw(12) << fixed << setprecision(2) << avg
                << fixed << setprecision(1) << share << "%\n";
        }
    }

    // summary lines under the table
    cout << "  " << string(50, '-') << "\n";
    cout << "    Residents     : " << totalPeople << "\n";
    cout << "    Top Transport : " << modes[topIdx]
        << "  --  " << modeCount[topIdx] << " users"
        << "  (" << fixed << setprecision(1)
        << (double)modeCount[topIdx] / totalPeople * 100.0 << "%)\n";
    cout << "    Total CO2     : " << fixed << setprecision(2)
        << totalEmit << " kg/month\n";
    cout << "    Avg CO2       : " << fixed << setprecision(2)
        << avgEmit << " kg/resident\n";
    cout << "    Emission Level: " << getEmissionLevel(avgEmit) << "\n";
    cout << "  " << string(50, '-') << "\n";
}

// main task 4 function
// shows a submenu where user picks one age group or all at once
void analyzeAgeGroups(Resident residents[], int size, string cityName) {

    const int NUM_GROUPS = 5;
    const int NUM_MODES = 6;

    // these strings must match exactly what getAgeGroup() returns in Resident.h
    // if they dont match the comparison will always be false and nothing shows
    string groups[NUM_GROUPS] = {
        "Children & Teenagers",
        "University Students / Young Adults",
        "Working Adults (Early Career)",
        "Working Adults (Late Career)",
        "Senior Citizens / Retirees"
    };

    // just for display in the header and submenu
    string ranges[NUM_GROUPS] = {
        "6-17", "18-25", "26-45", "46-60", "61+"
    };

    // all possible transport modes across all 3 cities
    string modes[NUM_MODES] = {
        "Car", "Bus", "Bicycle", "Walking", "School Bus", "Carpool"
    };

    int choice;

    do {
        // age group submenu
        cout << "\n  " << string(44, '=') << "\n";
        cout << "        AGE GROUP ANALYSIS\n";
        cout << "        City : " << cityName << "\n";
        cout << "        Total Residents : " << size << "\n";
        cout << "  " << string(44, '=') << "\n\n";
        cout << "    [1]  Children & Teenagers        (6-17)\n";
        cout << "    [2]  University Students         (18-25)\n";
        cout << "    [3]  Working Adults Early Career (26-45)\n";
        cout << "    [4]  Working Adults Late Career  (46-60)\n";
        cout << "    [5]  Senior Citizens / Retirees  (61+)\n";
        cout << "    [6]  View All Age Groups\n";
        cout << "    [0]  Back\n";
        cout << "  " << string(44, '=') << "\n";
        cout << "  Enter choice: ";
        cin >> choice;

        if (choice >= 1 && choice <= 5) {
            // user picked one group - convert choice to 0-based index
            int g = choice - 1;
            cout << "\n  " << string(44, '=') << "\n";
            cout << "        AGE GROUP ANALYSIS\n";
            cout << "        City : " << cityName << "\n";
            cout << "  " << string(44, '=') << "\n";
            printGroupAnalysis(residents, size, cityName,
                groups[g], ranges[g], modes, NUM_MODES);

        }
        else if (choice == 6) {
            // view all - loop through all 5 groups and print each one
            cout << "\n  " << string(44, '=') << "\n";
            cout << "        ALL AGE GROUPS\n";
            cout << "        City            : " << cityName << "\n";
            cout << "        Total Residents : " << size << "\n";
            cout << "  " << string(44, '=') << "\n";

            // store group results so i can build the summary table after
            double groupTotals[NUM_GROUPS] = { 0 };
            int groupCounts[NUM_GROUPS] = { 0 };
            string groupTopMode[NUM_GROUPS];
            double cityTotal = 0;

            for (int g = 0; g < NUM_GROUPS; g++) {
                // need fresh counters per group for summary calculation
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

                // find top mode for this group to use in summary table
                int topIdx = 0;
                for (int m = 1; m < NUM_MODES; m++)
                    if (modeCount[m] > modeCount[topIdx]) topIdx = m;
                groupTopMode[g] = totalPeople > 0 ? modes[topIdx] : "N/A";

                // print the full breakdown for this group
                printGroupAnalysis(residents, size, cityName,
                    groups[g], ranges[g], modes, NUM_MODES);
            }

            // figure out which group emitted the most overall
            int highG = 0;
            for (int g = 1; g < NUM_GROUPS; g++)
                if (groupTotals[g] > groupTotals[highG]) highG = g;

            // summary table at the end - one row per group
            cout << "\n  " << string(58, '=') << "\n";
            cout << "        SUMMARY  --  " << cityName << "\n";
            cout << "  " << string(58, '=') << "\n";
            cout << "  " << left
                << setw(36) << "  Age Group"
                << setw(8) << "Res"
                << setw(12) << "CO2 (kg)"
                << "Top Mode\n";
            cout << "  " << string(58, '-') << "\n";

            for (int g = 0; g < NUM_GROUPS; g++) {
                // trim the label if its too long so the table stays neat
                string label = groups[g] + " (" + ranges[g] + ")";
                if (label.length() > 33)
                    label = label.substr(0, 32) + ".";
                cout << "  " << left
                    << setw(36) << ("  " + label)
                    << setw(8) << groupCounts[g]
                    << setw(12) << fixed << setprecision(2) << groupTotals[g]
                    << groupTopMode[g] << "\n";
            }

            cout << "  " << string(58, '-') << "\n";
            cout << "    Total Residents :  " << size << "\n";
            cout << "    Total CO2       :  " << fixed << setprecision(2)
                << cityTotal << " kg/month\n";
            if (size > 0)
                cout << "    Avg CO2         :  " << fixed << setprecision(2)
                << cityTotal / size << " kg/resident\n";
            cout << "  " << string(58, '=') << "\n";

            // insight lines based on the actual data from this city
            cout << "\n  >> Insight: " << groups[highG]
                << " is the biggest emitting\n"
                << "             group with "
                << fixed << setprecision(2) << groupTotals[highG]
                << " kg CO2/month.\n";
            cout << "  >> Insight: Their preferred transport is "
                << groupTopMode[highG] << ".\n";

        }
        else if (choice != 0) {
            cout << "  Invalid choice. Please enter 0-6.\n";
        }

    } while (choice != 0); // keep showing menu until user goes back
}