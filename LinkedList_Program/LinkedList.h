#pragma once
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Resident.h"
#include <string>

using namespace std;

struct Node {
    Resident data;
    Node* nextAddress;
};

class LinkedList {
    Node* head = nullptr;
    Node* tail = nullptr;
    int size = 0;
    string list_name = "";

public:
    LinkedList();
    LinkedList(string);
    ~LinkedList();
    void display();

    void insertAtEnd(Resident r);
    //void searchByTransport(string transport);
    //void searchByDistance(double threshold);

    // Dylan's sorting functions
    int getSize();
    LinkedList copyList();
    void bubbleSort(int);
    void mergeSort(int);
    Node* getHead() const { return head; }

private:
    void swapNodes(Node*, Node*);
    bool compare(const Resident&, const Resident&, int);

    Node* mergeSortHelper(Node*, int);
    Node* merge(Node*, Node*, int);
    void splitList(Node*, Node**, Node**);
};

#endif