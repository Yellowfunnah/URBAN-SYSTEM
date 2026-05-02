#include <iostream>
#include <iomanip>
#include "LinkedList.h"

using namespace std;

LinkedList::LinkedList() {
    head = nullptr;
    tail = nullptr;
    size = 0;
    list_name = "";
}

LinkedList::LinkedList(string list_name) {
    this->list_name = list_name;
    head = nullptr;
    tail = nullptr;
    size = 0;
}

LinkedList::~LinkedList() {
    // Destructor
}

void LinkedList::insertAtEnd(Resident r) {
    Node* newNode = new Node;
    newNode->data = r;
    newNode->nextAddress = nullptr;

    if (head == nullptr) {
        head = tail = newNode;
    }
    else {
        tail->nextAddress = newNode;
        tail = newNode;
    }
    size++;
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

        current = current->nextAddress;
    }
}

//void LinkedList::searchByTransport(string transport) {
//    Node* current = head;
//    bool found = false;
//
//    cout << "\nSearch Results (" << transport << "):\n";
//
//    cout << left
//        << setw(15) << "Resident ID"
//        << setw(8) << "Age"
//        << setw(15) << "Transport"
//        << setw(15) << "Distance"
//        << setw(15) << "Emission"
//        << endl;
//
//    cout << "-------------------------------------------------------------\n";
//
//    while (current != NULL) {
//        if (current->data.transportMode == transport) {
//            found = true;
//
//            cout << left
//                << setw(15) << current->data.residentID
//                << setw(8) << current->data.age
//                << setw(15) << current->data.transportMode
//                << setw(15) << current->data.dailyDistance
//                << setw(15) << current->data.calculateMonthlyEmission()
//                << endl;
//        }
//
//        current = current->next;
//    }
//
//    if (!found) {
//        cout << "No residents found with transport: " << transport << endl;
//    }
//}
//
//void LinkedList::searchByDistance(double threshold) {
//    Node* current = head;
//    bool found = false;
//
//    cout << "\nResidents with distance > " << threshold << " km:\n";
//
//    cout << left
//        << setw(15) << "Resident ID"
//        << setw(8) << "Age"
//        << setw(15) << "Transport"
//        << setw(15) << "Distance"
//        << setw(15) << "Emission"
//        << endl;
//
//    cout << "-------------------------------------------------------------\n";
//
//    while (current != NULL) {
//        if (current->data.dailyDistance > threshold) {
//            found = true;
//
//            cout << left
//                << setw(15) << current->data.residentID
//                << setw(8) << current->data.age
//                << setw(15) << current->data.transportMode
//                << setw(15) << current->data.dailyDistance
//                << setw(15) << current->data.calculateMonthlyEmission()
//                << endl;
//        }
//
//        current = current->next;
//    }
//
//    if (!found) {
//        cout << "No residents found with distance above " << threshold << " km.\n";
//    }
//}

int LinkedList::getSize() {
    return size;
}

LinkedList LinkedList::copyList() {
    LinkedList newList(list_name + "_copy");

    Node* temp = head;

    while (temp != nullptr) {
        newList.insertAtEnd(temp->data);
        temp = temp->nextAddress;
    }

    return newList;
}

bool LinkedList::compare(const Resident& a, const Resident& b, int sortBy) {
    switch (sortBy) {
    case 1: return a.age < b.age;
    case 2: return a.dailyDistance < b.dailyDistance;
    case 3: return a.calculateMonthlyEmission() < b.calculateMonthlyEmission();
    default: return false;
    }
}

void LinkedList::swapNodes(Node* a, Node* b) {
    Resident temp = a->data;
    a->data = b->data;
    b->data = temp;
}

void LinkedList::bubbleSort(int sortBy) {
    if (head == nullptr || head->nextAddress == nullptr) {
        cout << list_name << " has no records to sort!" << endl;
        return;
    }

    for (int i = 0; i < size - 1; i++) {
        Node* current = head;
        Node* nextNode = head->nextAddress;

        for (int j = 0; j < size - i - 1; j++) {
            if (!compare(current->data, nextNode->data, sortBy)) {
                swapNodes(current, nextNode);
            }
            current = nextNode;
            nextNode = nextNode->nextAddress;
        }
    }

}

void LinkedList::splitList(Node* source, Node** frontRef, Node** backRef) {
    if (source == nullptr || source->nextAddress == nullptr) {
        *frontRef = source;
        *backRef = nullptr;
        return;
    }

    Node* slow = source;
    Node* fast = source->nextAddress;

    while (fast != nullptr) {
        fast = fast->nextAddress;
        if (fast != nullptr) {
            slow = slow->nextAddress;
            fast = fast->nextAddress;
        }
    }

    *frontRef = source;
    *backRef = slow->nextAddress;
    slow->nextAddress = nullptr;
}

Node* LinkedList::merge(Node* left, Node* right, int sortBy) {
    if (left == nullptr) return right;
    if (right == nullptr) return left;

    Node* result = nullptr;

    if (compare(left->data, right->data, sortBy)) {
        result = left;
        result->nextAddress = merge(left->nextAddress, right, sortBy);
    }
    else {
        result = right;
        result->nextAddress = merge(left, right->nextAddress, sortBy);
    }

    return result;
}

Node* LinkedList::mergeSortHelper(Node* headRef, int sortBy) {
    if (headRef == nullptr || headRef->nextAddress == nullptr) {
        return headRef;
    }

    Node* front = nullptr;
    Node* back = nullptr;
    splitList(headRef, &front, &back);

    front = mergeSortHelper(front, sortBy);
    back = mergeSortHelper(back, sortBy);

    return merge(front, back, sortBy);
}

void LinkedList::mergeSort(int sortBy) {
    if (head == nullptr || head->nextAddress == nullptr) {
        cout << list_name << " has no records to sort!" << endl;
        return;
    }

    head = mergeSortHelper(head, sortBy);

    Node* temp = head;
    while (temp->nextAddress != nullptr) {
        temp = temp->nextAddress;
    }
    tail = temp;

}