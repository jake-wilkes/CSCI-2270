// Jacob Wilkes
// Final Project
// CSCI 2270
// Rhonda Hoenigman - Josiah Buxton

#ifndef PRIORITY_LIST_H
#define PRIORITY_LIST_H
#include <iostream>
using namespace std;

struct listPatient {
    string name;
    int priority;
    int treatment;
    listPatient* next = NULL;
    listPatient* prev = NULL;

    listPatient(string n, int p, int t) {
        name = n;
        priority = p;
        treatment = t;
    }
};

class PriorityList {
    public:
        PriorityList();
        ~PriorityList();
        void buildList(char* filename, int numLines);
        void enqueue(listPatient* patient);
        void dequeue();
        void printList();
    protected:
    private:
        listPatient* head;
        listPatient* tail;
};

#endif