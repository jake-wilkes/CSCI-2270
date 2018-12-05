// Jacob Wilkes
// Final Project
// CSCI 2270
// Rhonda Hoenigman - Josiah Buxton

#ifndef PRIORITY_HEAP_H
#define PRIORITY_HEAP_H
#include <iostream>
using namespace std;

struct heapPatient {
    string name;
    int priority;
    int treatment;

    heapPatient(string n, int p, int t) {
        name = n;
        priority = p;
        treatment = t;
    }
    heapPatient() {}
};

class PriorityHeap {
    public:
        PriorityHeap(int cap);
        ~PriorityHeap();
        void buildHeap(char* filename, int numLines);
        void enqueue(heapPatient patient);
        void dequeueAndPrint(bool print);
    protected:
    private:
        int leftOf(int i) { return 2*i; };
        int rightOf(int i) { return 2*i + 1; };
        int parentOf(int i) { return i/2; };
        void heapify(int i);

        heapPatient* heap;
        int capacity;
        int curSize;
};

#endif