// ============================================================
// Recommendations.cpp
// Task 9 - Insights & Recommendations
// Author: Aimen Rizwan
// ============================================================

#include "Recommendations.h"
#include <iostream>
#include <iomanip>
using namespace std;

void showInsightsAndRecommendations(Resident cityA[], int sizeA,
    Resident cityB[], int sizeB,
    Resident cityC[], int sizeC) {

    const int NUM_GROUPS = 5;
    const int NUM_MODES = 6;

    string groups[NUM_GROUPS] = {
        "Children & Teenagers",
        "University Students / Young Adults",
        "Working Adults (Early Career)",
        "Working Adults (Late Career)",
        "Senior Citizens / Retirees"
    };

    string modes[NUM_MODES] = {
        "Car", "Bus", "Bicycle", "Walking", "School Bus", "Carpool"
    };

    double emA[NUM_GROUPS] = { 0 }, emB[NUM_GROUPS] = { 0 }, emC[NUM_GROUPS] = { 0 };
    int cntA[NUM_GROUPS] = { 0 }, cntB[NUM_GROUPS] = { 0 }, cntC[NUM_GROUPS] = { 0 };
    int modeTotals[NUM_GROUPS][NUM_MODES] = {};

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

    // find highest and lowest emitting group
    int highG = 0, lowG = 0;
    double highVal = -1, lowVal = -1, grandTotal = 0;
    double groupTotals[NUM_GROUPS] = { 0 };

    for (int g = 0; g < NUM_GROUPS; g++) {
        groupTotals[g] = emA[g] + emB[g] + emC[g];
        grandTotal += groupTotals[g];
        if (highVal < 0 || groupTotals[g] > highVal) { highVal = groupTotals[g]; highG = g; }
        if (lowVal < 0 || groupTotals[g] < lowVal) { lowVal = groupTotals[g]; lowG = g; }
    }

    // --------------------------------------------------------
    // SECTION 1: title
    // --------------------------------------------------------
    cout << "\n";
    cout << string(80, '=') << "\n";
    cout << "   Insights & Recommendations\n";
    cout << "   All Cities Combined\n";
    cout << string(80, '=') << "\n";

    // --------------------------------------------------------
    // SECTION 2: emission table - matches teammates table style
    // --------------------------------------------------------
    cout << "\n";
    cout << string(80, '-') << "\n";
    cout << "   Emissions by Age Group - All Cities\n";
    cout << string(80, '-') << "\n";
    cout << left
        << setw(34) << "   Age Group"
        << setw(13) << "City A (kg)"
        << setw(13) << "City B (kg)"
        << setw(13) << "City C (kg)"
        << "Total (kg)"
        << "\n";
    cout << string(80, '-') << "\n";

    for (int g = 0; g < NUM_GROUPS; g++) {
        cout << left
            << setw(34) << ("   " + groups[g])
            << setw(13) << fixed << setprecision(2) << emA[g]
            << setw(13) << fixed << setprecision(2) << emB[g]
            << setw(13) << fixed << setprecision(2) << emC[g]
            << fixed << setprecision(2) << groupTotals[g]
            << "\n";
    }

    cout << string(80, '-') << "\n";
    cout << left
        << setw(34) << "   Grand Total"
        << setw(13) << "-"
        << setw(13) << "-"
        << setw(13) << "-"
        << fixed << setprecision(2) << grandTotal << " kg CO2\n";
    cout << string(80, '-') << "\n";
    cout << "   Highest Emitting Group : " << groups[highG]
        << " (" << fixed << setprecision(2) << highVal << " kg CO2)\n";
    cout << "   Lowest  Emitting Group : " << groups[lowG]
        << " (" << fixed << setprecision(2) << lowVal << " kg CO2)\n";

    // --------------------------------------------------------
    // SECTION 3: average per person - same table style
    // --------------------------------------------------------
    cout << "\n";
    cout << string(70, '-') << "\n";
    cout << "   Average CO2 per Person by Age Group\n";
    cout << string(70, '-') << "\n";
    cout << left
        << setw(34) << "   Age Group"
        << setw(12) << "City A"
        << setw(12) << "City B"
        << "City C"
        << "\n";
    cout << string(70, '-') << "\n";

    for (int g = 0; g < NUM_GROUPS; g++) {
        double aA = cntA[g] > 0 ? emA[g] / cntA[g] : 0;
        double aB = cntB[g] > 0 ? emB[g] / cntB[g] : 0;
        double aC = cntC[g] > 0 ? emC[g] / cntC[g] : 0;
        cout << left
            << setw(34) << ("   " + groups[g])
            << setw(12) << fixed << setprecision(2) << aA
            << setw(12) << fixed << setprecision(2) << aB
            << fixed << setprecision(2) << aC
            << "\n";
    }
    cout << string(70, '-') << "\n";

    // --------------------------------------------------------
    // SECTION 4: top transport per group
    // --------------------------------------------------------
    cout << "\n";
    cout << string(60, '-') << "\n";
    cout << "   Most Preferred Transport by Age Group\n";
    cout << string(60, '-') << "\n";
    cout << left
        << setw(34) << "   Age Group"
        << setw(16) << "Top Transport"
        << "Count\n";
    cout << string(60, '-') << "\n";

    for (int g = 0; g < NUM_GROUPS; g++) {
        int top = 0;
        for (int m = 1; m < NUM_MODES; m++)
            if (modeTotals[g][m] > modeTotals[g][top]) top = m;
        cout << left
            << setw(34) << ("   " + groups[g])
            << setw(16) << (modeTotals[g][top] > 0 ? modes[top] : "N/A")
            << modeTotals[g][top]
            << "\n";
    }
    cout << string(60, '-') << "\n";

    // --------------------------------------------------------
    // SECTION 5: green vs car summary
    // --------------------------------------------------------
    int greenCount = 0, carCount = 0, totalAll = 0;
    for (int g = 0; g < NUM_GROUPS; g++) {
        greenCount += modeTotals[g][2] + modeTotals[g][3];
        carCount += modeTotals[g][0];
        for (int m = 0; m < NUM_MODES; m++) totalAll += modeTotals[g][m];
    }

    cout << "\n";
    cout << string(60, '-') << "\n";
    cout << "   Green vs High-Emission Transport Summary\n";
    cout << string(60, '-') << "\n";
    if (totalAll > 0) {
        cout << "   Bicycle + Walking users : " << greenCount
            << " (" << fixed << setprecision(1)
            << (double)greenCount / totalAll * 100 << "%)\n";
        cout << "   Car users               : " << carCount
            << " (" << fixed << setprecision(1)
            << (double)carCount / totalAll * 100 << "%)\n";
    }
    cout << string(60, '-') << "\n";

    // --------------------------------------------------------
    // SECTION 6: recommendations - same plain style
    // --------------------------------------------------------
    cout << "\n";
    cout << string(80, '=') << "\n";
    cout << "   Recommendations for City Planners\n";
    cout << string(80, '=') << "\n\n";

    cout << "   1. Target Working Adults (Ages 26-60)\n";
    cout << "      Working Adults generate the most emissions due to car dependency.\n";
    cout << "      Subsidised bus passes and park-and-ride schemes would reduce this.\n\n";

    cout << "   2. Invest in Cycling Infrastructure for Youth\n";
    cout << "      Children and university students already prefer bicycles.\n";
    cout << "      Safe cycling lanes near schools will strengthen this habit.\n\n";

    cout << "   3. Expand Carpool and School Bus Schemes in City B\n";
    cout << "      University Town shows high shared transport usage.\n";
    cout << "      More organised carpool routes will lower per-head emissions.\n\n";

    cout << "   4. Improve Bus Services for Senior Citizens\n";
    cout << "      Seniors rely on buses. Higher frequency and accessible stops\n";
    cout << "      will prevent them from switching to cars.\n\n";

    cout << "   5. Address Car Dependency in Suburban City C\n";
    cout << "      Long commute distances push residents toward cars.\n";
    cout << "      Local feeder bus routes and EV incentives are the best fix.\n\n";

    cout << "   6. Run Carbon Awareness Campaigns Across All Cities\n";
    cout << "      Showing residents their personal monthly CO2 impact\n";
    cout << "      can drive behaviour change, especially among Working Adults.\n";

    cout << "\n" << string(80, '=') << "\n";
}