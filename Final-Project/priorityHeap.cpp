// Jacob Wilkes
// Final Project
// CSCI 2270
// Rhonda Hoenigman - Josiah Buxton

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include "priorityHeap.h"

// Overloaded operator for comparing two patients to each other.
bool operator < (heapPatient& p1, heapPatient& p2){
    if (p1.priority == p2.priority){
        return p1.treatment < p2.treatment;
    }
    return p1.priority < p2.priority;
}

PriorityHeap::PriorityHeap(int cap){
    heap = new heapPatient[cap+1]; // Need an extra index because we index at 1 instead of 0.
    capacity = cap+1;
    curSize = 0;
}

void PriorityHeap::buildHeap(char* filename, int numLines){
    ifstream file;
    file.open(filename);

    if (file.is_open()){
        string line;
        int count = 0;

        getline(file, line, '\r'); // Ignore first line.

        while (getline(file, line, '\r') && count < numLines){ // Only read X number of lines.
            stringstream ss(line);

            string name, priority, treatment;

            getline(ss, name, ',');
            getline(ss, priority, ',');
            getline(ss, treatment, '\r');

            enqueue(heapPatient(name, stoi(priority), stoi(treatment)));

            count ++;
        }
    }
    else {
        cout << "File not opened." << endl;
    }
    file.close();
}

void PriorityHeap::enqueue(heapPatient newPatient){
	curSize++;
	int thisIndex = curSize;
	int parentIndex = parentOf(thisIndex);
	heap[thisIndex] = newPatient; // Insert at end.

	while (thisIndex > 1 && heap[thisIndex] < heap[parentIndex]){ // Swap upwards into place.
		heapPatient temp = heap[parentIndex]; 
		heap[parentIndex] = newPatient;
		heap[thisIndex] = temp;

		thisIndex = parentIndex;
		parentIndex = parentOf(thisIndex); // Get new parent.
	}
}

void PriorityHeap::dequeueAndPrint(bool print){
	// Need to print as we dequeue to get names in order.
	if (curSize == 0){
		cout << "Nothing in queue." << endl;
		return;
	}

	int i = 1;
	if (print){
		cout << "Rank, Name, Priority, Treatment" << endl;
	}
	while (curSize > 0){
		if (print){
			// Print thing at "top" of heap.
			cout << i << ": " << heap[1].name << ",\t" << heap[1].priority << ",\t" << heap[1].treatment << endl;
		}
		i++;

		heap[1] = heap[curSize]; // Place last item at top.
		curSize--;

		heapify(1); // Fix the heap.
	}
}

void PriorityHeap::heapify(int i){
	// Swap downwards into place.
	int thisIndex = i;
	int leftChild = leftOf(thisIndex);
	int rightChild = rightOf(thisIndex);
	int highestPriority = thisIndex;

	// Find which child has a higher "priority" (smaller values) to swap with.
	if (leftChild < curSize && heap[leftChild] < heap[thisIndex]){
		highestPriority = leftChild;
	}
	if (rightChild < curSize && heap[rightChild] < heap[thisIndex] && heap[rightChild] < heap[leftChild]){
		highestPriority = rightChild;
	}

	if (highestPriority != thisIndex){
		heapPatient temp = heap[highestPriority]; 
		heap[highestPriority] = heap[thisIndex];
		heap[thisIndex] = temp;

		heapify(highestPriority);
	}
	else {
		return;
	}
}