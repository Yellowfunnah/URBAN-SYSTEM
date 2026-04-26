#pragma once
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Resident.h"

struct Node {
    Resident data;
    Node* next;
};

class LinkedList {
public:
    Node* head;

    LinkedList();              
    void insertAtEnd(Resident r);
    void display();

    void searchByTransport(string transport);
    void searchByDistance(double threshold);
};

#endif