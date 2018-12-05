// Jacob Wilkes
// Final Project
// CSCI 2270
// Rhonda Hoenigman - Josiah Buxton

#include <iostream>
#include <string>
#include <queue>
#include <fstream>
#include <chrono>
#include <ctime>
#include "priorityList.h"
#include "priorityHeap.h"
#include "stl.cpp"
using namespace std;

int main(int argc, char* argv[]) {
	int choice = 0;
	int runtimeLines[9] = {100, 200, 300, 400, 500, 600, 700, 800, 880};
	while (choice != 6) {
		cout << "1. Build and print linked list queue" << endl;
		cout << "2. Perform linked list queue runtime analysis" << endl;
		cout << "-----" << endl;
		cout << "3. Build and print heap queue" << endl;
		cout << "4. Perform heap queue runtime analysis" << endl;
		cout << "-----" << endl;
		cout << "5. Perform STL queue runtime analysis" << endl;
		cout << "-----" << endl;
		cout << "6. Quit" << endl;

		cin >> choice;

		if (choice == 1) {
				PriorityList *list = new PriorityList();
				list->buildList(argv[1], 880);
				list->printList();
				list->dequeue();
		}

		if (choice == 2) {
				ofstream output1;
				ofstream output2;
				output1.open("linkedListEnqueueAnalysis.csv");
				output2.open("linkedListDequeueAnalysis.csv");

				output1 << "100,200,300,400,500,600,700,800,880\n"; // Columns for csv.
				output2 << "100,200,300,400,500,600,700,800,880\n";

				for (int i = 0; i < 500; i++) {
					for (int j = 0; j < 9; j++) {
						PriorityList *list = new PriorityList();

						auto enqueueStart = std::chrono::system_clock::now(); // Start time for enqueuing.
						list->buildList(argv[1], runtimeLines[j]); // Pass in runtimeLines[j] to throttle how many lines are read.
						auto enqueueEnd = std::chrono::system_clock::now(); // End time for enqueuing.

						auto dequeueStart = std::chrono::system_clock::now(); // Start time for dequeuing.
						list->dequeue();
						auto dequeueEnd = std::chrono::system_clock::now(); // End time for dequeuing.

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

		if (choice == 3) {
				PriorityHeap *heap = new PriorityHeap(880);
				heap->buildHeap(argv[1], 880);
				heap->dequeueAndPrint(true);
		}

		if (choice == 4) {
				ofstream output1;
				ofstream output2;
				output1.open("heapEnqueueAnalysis.csv");
				output2.open("heapDequeueAnalysis.csv");

				output1 << "100,200,300,400,500,600,700,800,880\n";
				output2 << "100,200,300,400,500,600,700,800,880\n";

				for (int i = 0; i < 500; i++) {
					for (int j = 0; j < 9; j++) {
						PriorityHeap *heap = new PriorityHeap(runtimeLines[j]);

						auto enqueueStart = std::chrono::system_clock::now(); // Start enqueue.
						heap->buildHeap(argv[1], runtimeLines[j]);
						auto enqueueEnd = std::chrono::system_clock::now(); // End enqueue.

						auto dequeueStart = std::chrono::system_clock::now(); // Start dequeue.
						heap->dequeueAndPrint(false); // Pass in false so it doesn't print to terminal (for convenience sake).
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

		if (choice == 5) {
			stlRuntime(argv[1]); // See stl.cpp file.
		}

		if (choice == 6) {
			return 0;
		}
	}
}