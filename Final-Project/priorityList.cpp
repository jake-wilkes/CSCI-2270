// Jacob Wilkes
// Final Project
// CSCI 2270
// Rhonda Hoenigman - Josiah Buxton

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include "priorityList.h"

// Overloaded operator for comparing two patients to each other.
bool operator < (listPatient& p1, listPatient& p2){
    if (p1.priority == p2.priority){ // If priorities are the same, get smallest treatment.
        return p1.treatment < p2.treatment;
    }
    return p1.priority < p2.priority;
}

PriorityList::PriorityList(){
    head = NULL;
    tail = NULL;
}

void PriorityList::buildList(char* filename, int numLines){
    ifstream file;
    file.open(filename);

    if (file.is_open()){
        string line;
        int count = 0;

        getline (file, line, '\r'); // Ignore first line.

        while (getline (file, line, '\r') && count < numLines){ // Only read X number of lines.
            stringstream ss(line);

            string name, priority, treatment;

            getline (ss, name, ',');
            getline (ss, priority, ',');
            getline (ss, treatment, '\r');

            enqueue (new listPatient(name, stoi(priority), stoi(treatment)));

            count ++;
        }
    }
    else {
        cout << "File not opened." << endl;
    }
    file.close ();
}

void PriorityList::enqueue (listPatient* newPatient){
    if (!head){
        head = newPatient;
        tail = newPatient;
        return;
    }

    listPatient* nextP = head;
    // Find what the next patient should be after new one.
    while (nextP && *nextP < *newPatient){ // Pointers used here for operator overload.
        nextP = nextP->next;
    }

    if (!nextP){ // Insert as tail.
        tail->next = newPatient;
        newPatient->prev = tail;
        tail = newPatient;
        return;
    }
    else if (nextP == head){ // Insert as head.
        nextP->prev = newPatient;
        newPatient->next = nextP;
        head = newPatient;
        return;
    }
    else { // Insert in the middle.
        newPatient->prev = nextP->prev;
        newPatient->prev->next = newPatient;
        nextP->prev = newPatient;
        newPatient->next = nextP;
        return;
    }
}

void PriorityList::dequeue (){
    if (!head){
        cout << "Nothing in queue." << endl;
        return;
    }

    while (head){
        listPatient* temp = head;
        head = head->next;
        delete temp;
    }
}

void PriorityList::printList(){
    if (!head){
        cout << "Nothing in queue." << endl;
        return;
    }

    listPatient* temp = head;
    int i = 1;
    cout << "Rank, Name, Priority, Treatment" << endl;
    while (temp){
        cout << i << ": " << temp->name << ",\t" << temp->priority << ",\t" << temp->treatment << endl;
        temp = temp->next;
        i++;
    }
}