#include <iostream>
#include <iomanip>
#include <string>
#include "EmissionAnalysis.h"

using namespace std;

//Carbon Emission Analysis - Linked List
//Traverses the linked list with Node* current = head, moving via current->next

static const int TOTAL_MODES = 6;
static const string TRANSPORT_MODES[TOTAL_MODES] = {
    "Car", "Bus", "Bicycle", "Walking", "School Bus", "Carpool"
};

//Prints a divider line to keep the tables tidy
static void printLine(int width) {
    for (int i = 0; i < width; i++) cout << '-';
    cout << '\n';
}

//Finds the index of a transport mode in our list, returns -1 if not found
static int findTransportIndex(string mode) {
    for (int i = 0; i < TOTAL_MODES; i++) {
        if (TRANSPORT_MODES[i] == mode) return i;
    }
    return -1;
}

//Helper that counts how many nodes are in the list
static int countNodes(LinkedList& list) {
    int count = 0;
    Node* current = list.head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

//Shows the total monthly CO2 emissions for one city
void showTotalEmissions(LinkedList& list, string cityName) {
    double total = 0.0;
    int count = 0;

    Node* current = list.head;
    while (current != nullptr) {
        total += current->data.calculateMonthlyEmission();
        count++;
        current = current->next;
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

//Breaks down emissions by each transport mode for one city
void showEmissionsByTransport(LinkedList& list, string cityName) {
    double emissionPerMode[TOTAL_MODES] = { 0 };
    int countPerMode[TOTAL_MODES] = { 0 };

    Node* current = list.head;
    while (current != nullptr) {
        int idx = findTransportIndex(current->data.transportMode);
        if (idx >= 0) {
            emissionPerMode[idx] += current->data.calculateMonthlyEmission();
            countPerMode[idx]++;
        }
        current = current->next;
    }

    cout << '\n';
    printLine(65);
    cout << "  Emissions by Transport Mode - " << cityName << '\n';
    printLine(65);
    cout << left
        << setw(14) << "Mode"
        << setw(10) << "Count"
        << setw(22) << "Total CO2 (kg)"
        << setw(20) << "Avg CO2/Resident"
        << '\n';
    printLine(65);

    for (int i = 0; i < TOTAL_MODES; i++) {
        if (countPerMode[i] == 0) continue;
        double avg = emissionPerMode[i] / countPerMode[i];
        cout << fixed << setprecision(2) << left
            << setw(14) << TRANSPORT_MODES[i]
            << setw(10) << countPerMode[i]
            << setw(22) << emissionPerMode[i]
            << setw(20) << avg
            << '\n';
    }
    printLine(65);
}

//Breaks down emissions by age group for one city
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

    Node* current = list.head;
    while (current != nullptr) {
        string group = current->data.getAgeGroup();
        int ag = -1;

        for (int g = 0; g < TOTAL_GROUPS; g++) {
            if (GROUP_NAMES[g] == group) { ag = g; break; }
        }

        if (ag >= 0) {
            int tm = findTransportIndex(current->data.transportMode);
            totalEmission[ag] += current->data.calculateMonthlyEmission();
            count[ag]++;
            if (tm >= 0) transportCount[ag][tm]++;
        }

        current = current->next;
    }

    cout << '\n';
    printLine(65);
    cout << "  Emissions by Age Group - " << cityName << '\n';
    printLine(65);

    for (int ag = 0; ag < TOTAL_GROUPS; ag++) {
        if (count[ag] == 0) continue;

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

//Compares total emissions across all three cities
void compareAllCities(
    LinkedList& cityA, string nameA,
    LinkedList& cityB, string nameB,
    LinkedList& cityC, string nameC)
{
    double totalA = 0, totalB = 0, totalC = 0;
    int cntA = 0, cntB = 0, cntC = 0;

    for (Node* c = cityA.head; c != nullptr; c = c->next) { totalA += c->data.calculateMonthlyEmission(); cntA++; }
    for (Node* c = cityB.head; c != nullptr; c = c->next) { totalB += c->data.calculateMonthlyEmission(); cntB++; }
    for (Node* c = cityC.head; c != nullptr; c = c->next) { totalC += c->data.calculateMonthlyEmission(); cntC++; }

    double grandTotal = totalA + totalB + totalC;
    int grandCount = cntA + cntB + cntC;

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
    cout << setw(28) << nameA << setw(12) << cntA << setw(18) << totalA << setw(14) << (cntA > 0 ? totalA / cntA : 0) << '\n';
    cout << setw(28) << nameB << setw(12) << cntB << setw(18) << totalB << setw(14) << (cntB > 0 ? totalB / cntB : 0) << '\n';
    cout << setw(28) << nameC << setw(12) << cntC << setw(18) << totalC << setw(14) << (cntC > 0 ? totalC / cntC : 0) << '\n';
    printLine(70);
    cout << setw(28) << "Grand Total" << setw(12) << grandCount << setw(18) << grandTotal << setw(14) << (grandCount > 0 ? grandTotal / grandCount : 0) << '\n';
    printLine(70);
}

//Calls all analyses for one city
void runEmissionAnalysis(LinkedList& list, string cityName) {
    cout << "\n========================================\n";
    cout << "  Carbon Emission Analysis\n";
    cout << "  City: " << cityName << "\n";
    cout << "========================================\n";
    showTotalEmissions(list, cityName);
    showEmissionsByTransport(list, cityName);
    showEmissionsByAgeGroup(list, cityName);
}