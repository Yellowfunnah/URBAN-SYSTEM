#include <iostream>
#include <iomanip>
#include "LinkedList.h"

using namespace std;

LinkedList::LinkedList() {
    head = NULL;
}

void LinkedList::insertAtEnd(Resident r) {
    Node* newNode = new Node;
    newNode->data = r;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    }
    else {
        Node* current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void LinkedList::display() {
    Node* current = head;

    cout << left
        << setw(15) << "Resident ID"
        << setw(8) << "Age"
        << setw(15) << "Transport"
        << setw(15) << "Distance"
        << setw(15) << "Emission"
        << endl;

    cout << "-------------------------------------------------------------\n";

    while (current != NULL) {
        cout << left
            << setw(15) << current->data.residentID
            << setw(8) << current->data.age
            << setw(15) << current->data.transportMode
            << setw(15) << current->data.dailyDistance
            << setw(15) << current->data.calculateMonthlyEmission()
            << endl;

        current = current->next;
    }
}

void LinkedList::searchByTransport(string transport) {
    Node* current = head;
    bool found = false;

    cout << "\nSearch Results (" << transport << "):\n";

    cout << left
        << setw(15) << "Resident ID"
        << setw(8) << "Age"
        << setw(15) << "Transport"
        << setw(15) << "Distance"
        << setw(15) << "Emission"
        << endl;

    cout << "-------------------------------------------------------------\n";

    while (current != NULL) {
        if (current->data.transportMode == transport) {
            found = true;

            cout << left
                << setw(15) << current->data.residentID
                << setw(8) << current->data.age
                << setw(15) << current->data.transportMode
                << setw(15) << current->data.dailyDistance
                << setw(15) << current->data.calculateMonthlyEmission()
                << endl;
        }

        current = current->next;
    }

    if (!found) {
        cout << "No residents found with transport: " << transport << endl;
    }
}

void LinkedList::searchByDistance(double threshold) {
    Node* current = head;
    bool found = false;

    cout << "\nResidents with distance > " << threshold << " km:\n";

    cout << left
        << setw(15) << "Resident ID"
        << setw(8) << "Age"
        << setw(15) << "Transport"
        << setw(15) << "Distance"
        << setw(15) << "Emission"
        << endl;

    cout << "-------------------------------------------------------------\n";

    while (current != NULL) {
        if (current->data.dailyDistance > threshold) {
            found = true;

            cout << left
                << setw(15) << current->data.residentID
                << setw(8) << current->data.age
                << setw(15) << current->data.transportMode
                << setw(15) << current->data.dailyDistance
                << setw(15) << current->data.calculateMonthlyEmission()
                << endl;
        }

        current = current->next;
    }

    if (!found) {
        cout << "No residents found with distance above " << threshold << " km.\n";
    }
}