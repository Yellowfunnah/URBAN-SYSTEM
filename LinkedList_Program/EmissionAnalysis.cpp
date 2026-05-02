#include <iostream>
#include <iomanip>
#include <string>
#include "EmissionAnalysis.h"

using namespace std;

//EmissionAnalysis.cpp - linked list version
//
//this file handles everything related to carbon emission
//analysis for the linked list program. instead of index
//loops, it walks through nodes using:
//Node* current = list.getHead() and current = current->nextAddress
//
//formula used throughout:
//monthly emission = dailyDistance x emissionFactor x averageDays

//all transport modes that appear across the three datasets
static const int TOTAL_MODES = 6;
static const string TRANSPORT_MODES[TOTAL_MODES] = {
    "Car", "Bus", "Bicycle", "Walking", "School Bus", "Carpool"
};


//helper - prints a divider line of a given width
static void printLine(int width) {
    for (int i = 0; i < width; i++) cout << '-';
    cout << '\n';
}


//helper - finds the index of a transport mode string
//returns -1 if not found
static int findTransportIndex(string mode) {
    for (int i = 0; i < TOTAL_MODES; i++) {
        if (TRANSPORT_MODES[i] == mode) return i;
    }
    return -1;
}


//shows the total monthly co2 emissions for one city
void showTotalEmissions(LinkedList& list, string cityName) {
    double total = 0.0;
    int count = 0;

    Node* current = list.getHead();
    while (current != nullptr) {
        total += current->data.calculateMonthlyEmission();
        count++;
        current = current->nextAddress;
    }

    cout << '\n';
    printLine(55);
    cout << "  Total Emissions - " << cityName << '\n';
    printLine(55);
    cout << fixed << setprecision(2);
    cout << "  Residents : " << count << '\n';
    cout << "  Total CO2 : " << total << " kg/month\n";
    printLine(55);
}


//shows emissions by transport mode, sorted highest to lowest
//also shows each mode's % share of the city's total emissions
void showEmissionsByTransport(LinkedList& list, string cityName) {
    double emissionPerMode[TOTAL_MODES] = { 0 };
    int countPerMode[TOTAL_MODES] = { 0 };
    double cityTotal = 0.0;

    Node* current = list.getHead();
    while (current != nullptr) {
        int idx = findTransportIndex(current->data.transportMode);
        if (idx >= 0) {
            double e = current->data.calculateMonthlyEmission();
            emissionPerMode[idx] += e;
            countPerMode[idx]++;
            cityTotal += e;
        }
        current = current->nextAddress;
    }

    //sort modes by emission descending using a simple bubble sort on indices
    int order[TOTAL_MODES] = { 0, 1, 2, 3, 4, 5 };
    for (int i = 0; i < TOTAL_MODES - 1; i++) {
        for (int j = 0; j < TOTAL_MODES - i - 1; j++) {
            if (emissionPerMode[order[j]] < emissionPerMode[order[j + 1]]) {
                int temp = order[j];
                order[j] = order[j + 1];
                order[j + 1] = temp;
            }
        }
    }

    cout << '\n';
    printLine(75);
    cout << "  Emissions by Transport Mode - " << cityName << '\n';
    printLine(75);
    cout << left
        << setw(14) << "Mode"
        << setw(10) << "Count"
        << setw(20) << "Total CO2 (kg)"
        << setw(20) << "Avg CO2/Resident"
        << setw(12) << "% of City"
        << '\n';
    printLine(75);

    for (int i = 0; i < TOTAL_MODES; i++) {
        int idx = order[i];
        if (countPerMode[idx] == 0) continue;
        double avg = emissionPerMode[idx] / countPerMode[idx];
        double pct = (cityTotal > 0) ? (emissionPerMode[idx] / cityTotal * 100.0) : 0.0;
        cout << fixed << setprecision(2) << left
            << setw(14) << TRANSPORT_MODES[idx]
            << setw(10) << countPerMode[idx]
            << setw(20) << emissionPerMode[idx]
            << setw(20) << avg
            << setw(12) << pct
            << '\n';
    }
    printLine(75);
}


//shows emissions broken down by age group
//also shows the most popular transport mode per group
void showEmissionsByAgeGroup(LinkedList& list, string cityName) {
    const int TOTAL_GROUPS = 5;
    const string GROUP_NAMES[TOTAL_GROUPS] = {
        "Children & Teenagers",
        "University Students / Young Adults",
        "Working Adults (Early Career)",
        "Working Adults (Late Career)",
        "Senior Citizens / Retirees"
    };

    double totalEmission[TOTAL_GROUPS] = { 0 };
    int count[TOTAL_GROUPS] = { 0 };
    int transportCount[TOTAL_GROUPS][TOTAL_MODES] = { {0} };

    Node* current = list.getHead();
    while (current != nullptr) {
        string group = current->data.getAgeGroup();
        int ag = -1;

        //match the age group string to an index
        for (int g = 0; g < TOTAL_GROUPS; g++) {
            if (GROUP_NAMES[g] == group) { ag = g; break; }
        }

        if (ag >= 0) {
            int tm = findTransportIndex(current->data.transportMode);
            totalEmission[ag] += current->data.calculateMonthlyEmission();
            count[ag]++;
            if (tm >= 0) transportCount[ag][tm]++;
        }

        current = current->nextAddress;
    }

    cout << '\n';
    printLine(65);
    cout << "  Emissions by Age Group - " << cityName << '\n';
    printLine(65);

    for (int ag = 0; ag < TOTAL_GROUPS; ag++) {
        if (count[ag] == 0) continue;

        //find the most used transport for this age group
        int topMode = 0;
        for (int t = 1; t < TOTAL_MODES; t++) {
            if (transportCount[ag][t] > transportCount[ag][topMode]) topMode = t;
        }

        double avg = totalEmission[ag] / count[ag];

        cout << "\n  Age Group : " << GROUP_NAMES[ag] << '\n';
        printLine(50);
        cout << fixed << setprecision(2);
        cout << "  Residents        : " << count[ag] << '\n';
        cout << "  Total CO2 (kg)   : " << totalEmission[ag] << '\n';
        cout << "  Avg CO2/Resident : " << avg << '\n';
        cout << "  Top Transport    : " << TRANSPORT_MODES[topMode]
            << " (" << transportCount[ag][topMode] << " users)\n";
        printLine(50);
    }
}


//finds and shows the highest and lowest emitting resident
//lowest only counts residents who actually produce emissions
//so bicycle and walking residents are excluded from lowest
void showHighLowEmitters(LinkedList& list, string cityName) {
    Node* highNode = nullptr;
    Node* lowNode = nullptr;
    double highVal = -1.0;
    double lowVal = -1.0;

    Node* current = list.getHead();
    while (current != nullptr) {
        double e = current->data.calculateMonthlyEmission();

        //track highest
        if (e > highVal) {
            highVal = e;
            highNode = current;
        }

        //track lowest but only if they actually emit something
        if (e > 0 && (lowVal < 0 || e < lowVal)) {
            lowVal = e;
            lowNode = current;
        }

        current = current->nextAddress;
    }

    cout << '\n';
    printLine(60);
    cout << "  Highest & Lowest Emitters - " << cityName << '\n';
    printLine(60);

    if (highNode != nullptr) {
        Resident& h = highNode->data;
        cout << fixed << setprecision(2);
        cout << "\n  Highest Emitting Resident:\n";
        cout << "  ID         : " << h.residentID << '\n';
        cout << "  Age        : " << h.age << '\n';
        cout << "  Transport  : " << h.transportMode << '\n';
        cout << "  Distance   : " << h.dailyDistance << " km/day\n";
        cout << "  Emission   : " << highVal << " kg CO2/month\n";
    }

    printLine(40);

    if (lowNode != nullptr) {
        Resident& l = lowNode->data;
        cout << "\n  Lowest Emitting Resident (Excluding Zero Emitters):\n";
        cout << "  ID         : " << l.residentID << '\n';
        cout << "  Age        : " << l.age << '\n';
        cout << "  Transport  : " << l.transportMode << '\n';
        cout << "  Distance   : " << l.dailyDistance << " km/day\n";
        cout << "  Emission   : " << lowVal << " kg CO2/month\n";
    }
    else {
        cout << "  No residents with non-zero emissions found.\n";
    }

    printLine(60);
}


//compares all three cities side by side
//highlights the most and least polluting city at the bottom
void compareAllCities(
    LinkedList& cityA, string nameA,
    LinkedList& cityB, string nameB,
    LinkedList& cityC, string nameC)
{
    double totalA = 0, totalB = 0, totalC = 0;
    int cntA = 0, cntB = 0, cntC = 0;

    for (Node* c = cityA.getHead(); c != nullptr; c = c->nextAddress) { totalA += c->data.calculateMonthlyEmission(); cntA++; }
    for (Node* c = cityB.getHead(); c != nullptr; c = c->nextAddress) { totalB += c->data.calculateMonthlyEmission(); cntB++; }
    for (Node* c = cityC.getHead(); c != nullptr; c = c->nextAddress) { totalC += c->data.calculateMonthlyEmission(); cntC++; }

    double grandTotal = totalA + totalB + totalC;
    int grandCount = cntA + cntB + cntC;

    double avgA = cntA > 0 ? totalA / cntA : 0;
    double avgB = cntB > 0 ? totalB / cntB : 0;
    double avgC = cntC > 0 ? totalC / cntC : 0;

    cout << '\n';
    printLine(70);
    cout << "  Cross-City Emission Comparison (Linked List)\n";
    printLine(70);
    cout << fixed << setprecision(2) << left
        << setw(28) << "City"
        << setw(12) << "Residents"
        << setw(18) << "Total CO2 (kg)"
        << setw(14) << "Avg CO2/Res"
        << '\n';
    printLine(70);
    cout << setw(28) << nameA << setw(12) << cntA << setw(18) << totalA << setw(14) << avgA << '\n';
    cout << setw(28) << nameB << setw(12) << cntB << setw(18) << totalB << setw(14) << avgB << '\n';
    cout << setw(28) << nameC << setw(12) << cntC << setw(18) << totalC << setw(14) << avgC << '\n';
    printLine(70);
    cout << setw(28) << "Grand Total"
        << setw(12) << grandCount
        << setw(18) << grandTotal
        << setw(14) << (grandCount > 0 ? grandTotal / grandCount : 0) << '\n';
    printLine(70);

    //figure out which city is most and least polluting by avg per resident
    double avgs[3] = { avgA, avgB, avgC };
    string names[3] = { nameA, nameB, nameC };

    int mostIdx = 0, leastIdx = 0;
    for (int i = 1; i < 3; i++) {
        if (avgs[i] > avgs[mostIdx]) mostIdx = i;
        if (avgs[i] < avgs[leastIdx]) leastIdx = i;
    }

    cout << '\n';
    cout << "  Most Polluting City : " << names[mostIdx]
        << " (" << fixed << setprecision(2) << avgs[mostIdx] << " kg avg/resident)\n";
    cout << "  Cleanest City       : " << names[leastIdx]
        << " (" << fixed << setprecision(2) << avgs[leastIdx] << " kg avg/resident)\n";
    printLine(70);
}


//the main entry point for task 5
//shows a submenu so the user picks what they want to see
//instead of dumping everything all at once
void runEmissionAnalysis(LinkedList& list, string cityName) {
    int choice;

    do {
        cout << "\n========================================\n";
        cout << "  Carbon Emission Analysis\n";
        cout << "  City: " << cityName << "\n";
        cout << "========================================\n";
        cout << "1. Total Emissions Summary\n";
        cout << "2. Breakdown by Transport Mode\n";
        cout << "3. Breakdown by Age Group\n";
        cout << "4. Highest & Lowest Emitting Resident\n";
        cout << "5. Run Full Analysis\n";
        cout << "0. Back\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            showTotalEmissions(list, cityName);
            break;
        case 2:
            showEmissionsByTransport(list, cityName);
            break;
        case 3:
            showEmissionsByAgeGroup(list, cityName);
            break;
        case 4:
            showHighLowEmitters(list, cityName);
            break;
        case 5:
            showTotalEmissions(list, cityName);
            showEmissionsByTransport(list, cityName);
            showEmissionsByAgeGroup(list, cityName);
            showHighLowEmitters(list, cityName);
            break;
        case 0:
            break;
        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 0);
}