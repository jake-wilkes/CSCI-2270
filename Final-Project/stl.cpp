// Jacob Wilkes
// Final Project
// CSCI 2270
// Rhonda Hoenigman - Josiah Buxton

#include <iostream>
#include <string>
#include <queue>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <stdlib.h>
#include <vector>

using namespace std;

// This file just runs the STL runtime stuff.
// Didn't want to clog up main with a bunch of extra code.

struct stlPatient {
    string name;
    int priority;
    int treatment;

    stlPatient(string n, int p, int t) {
        name = n;
        priority = p;
        treatment = t;
    }
    stlPatient() {}
};

struct compare { // Used for the STL library - same operator overload as other files.
	bool operator () (const stlPatient& p1, const stlPatient& p2) {
		 if (p1.priority == p2.priority) {
	        return p1.treatment < p2.treatment;
	    }
	    return p1.priority < p2.priority;
	}
};

void stlRuntime(char* filename) {
	int runtimeLines[9] = {800, 200, 300, 400, 500, 600, 700, 800, 880};

	ofstream output1;
	ofstream output2;
	output1.open("stlEnqueueAnalysis.csv");
	output2.open("stlDequeueAnalysis.csv");

	output1 << "100,200,300,400,500,600,700,800,880\n";
	output2 << "100,200,300,400,500,600,700,800,880\n";

	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < 1; j++) {
			priority_queue <stlPatient, vector<stlPatient>, compare> stlHeap; // Make STL queue.
			ifstream file;
		    file.open(filename);

		    auto enqueueStart = std::chrono::system_clock::now(); // Start enqueue.
		    if (file.is_open()) {
		        string line;
		        int count = 0;
		        getline(file, line, '\r'); // Ignore first line.

		        while (getline(file, line, '\r') && count < runtimeLines[j]) { // Only read X number of lines.
		            stringstream ss(line);

		            string name, priority, treatment;

		            getline(ss, name, ',');
		            getline(ss, priority, ',');
		            getline(ss, treatment, '\r');

		            stlHeap.push(stlPatient(name, stoi(priority), stoi(treatment)));

		            count ++;
		        }
		    }
		    else {
		        cout << "File not opened." << endl;
		    }
		    file.close();
		    auto enqueueEnd = std::chrono::system_clock::now(); // End enqueue.

		    auto dequeueStart = std::chrono::system_clock::now(); // Start dequeue.
		    while (!stlHeap.empty()) {
		    	stlPatient p;
		    	p = stlHeap.top();
		    	cout << p.name << ", " << p.priority << ", " << p.treatment << endl;
		    	stlHeap.pop();
		    }
		    auto dequeueEnd = std::chrono::system_clock::now(); // End dequeue.

		    std::chrono::duration<double> elapsed_seconds_e = enqueueEnd-enqueueStart;
			std::chrono::duration<double> elapsed_seconds_d = dequeueEnd-dequeueStart;

			output1 << elapsed_seconds_e.count() << ",";
			output2 << elapsed_seconds_d.count() << ",";
		}
		output1 << "\n";
		output2 << "\n";
	}

	output1.close();
	output2.close();

}