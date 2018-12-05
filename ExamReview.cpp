// finds any/all matches of a target value in an array,
// then removes said value(s), and shifts all array
// positions after removal back one position

int ShiftArray(Product arr[], int size, int target){
    for (int i = 0; i < size; i++){
        if (arr[i].price == target){
            for (int j = i; j < size-1; j++){
                arr[j] = arr[j+1];
            }
            size--;
       } 
    }
    return size;
}

// function that returns the most common repeating element in an array of structs

struct Freq {
    string name;
    int count;
};

string commonRepeatingElement(Product arr[], int length){
    Freq a1[length];
    int counter = 1;
    a1[0].name = arr[0].pname;
    a1[0].count = 0;
    bool match;
    for (int i = 0; i < length; i++){
        match = false;
        for (int j = 0; j < counter; j++){
            if (arr[i].pname == a1[j].name){
                a1[j].count += 1;
                match = true;
                break;
            }
        }
        if (match == false){
            a1[counter].name = arr[i].pname;
            a1[counter].count = 1;
            counter++;
        }
    }
    string best = "";
    int temp = 0;
    for (int i = 0; i < counter; i++){
        if (a1[i].count > temp){
            temp = a1[i].count;
            best = a1[i].name;
        }
    }
    return best;
}

// function to copy all elements of an array to a new array, except for a specified value, and return the new array

int *CopyArray(int ar[], int size, int value){
    int* ar1 = new int[size];
    for (int i = 0; i < size; i++){
        ar1[i] = ar[i];
    }
    for (int i = 0; i < size; i++){
        if (ar1[i] == value){
            for (int j = i; j < size-1; j++){
                ar1[j] = ar1[j+1];
            }
            i--;
            size--;
       } 
    }
    return ar1;
}

// function to find the second largest element in an array. 
// lines 80 to 88 are bubble sort algorithm

int secondLargest(int arr[], int size){
    int temp;
    for (int i = 0; i < size; i++){
        for (int j = i; j < size - i; j++){
            if (arr[j] < arr[j+1]){
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    return arr[1];
}

// function called findMax that prints the maximum value in a linked list
// doubly linked list


void findMax(){
    int temp = 0;
    Node* tmp = head;
    while (tmp != NULL){
        if (tmp->key > temp){
            temp = tmp->key;
        }
        tmp = tmp->next;
    }
    cout << temp << endl;
}

// function that enqueues a node to a singly linked list

void Queue::enqueue(node *newNode){
    node* tmp = head;
    if (head != NULL){
        while (tmp != NULL){
            if (tmp == tail){
                tmp->next = newNode;
                tail = newNode;
                newNode->next = NULL;
            }
            tmp = tmp->next;
        }
    }
    else {
        head = newNode;
        tail = newNode;
        newNode->next = NULL;
    }
}

// function to delete nodes in a linked list. The function takes two arguments
// the head of the linked list and the value to be deleted. It should delete all nodes 
// which contain the value to be deleted. It should return the head of the linked list.

node* DeleteNode(node* head, int value){
    node* temp = head;
    while (temp != NULL){
        if (temp->value == value){
            if (temp == head){
                head = head->next;
                temp->next->prev = NULL;
                delete(temp);
            }
            else if (temp->next == NULL){
                temp->prev->next = NULL;
                delete(temp);
            }
            else {
                temp->next->prev = temp->prev;
                temp->prev->next = temp->next;
                delete(temp);
            }
        }
        temp = temp->next;
    }
    return head;
}

// function that dequeues a node from a singly linked list

node* Queue::dequeue(){
    if (head != NULL && head->next != NULL){
        node* tmp = head;
        head = head->next;
        return tmp;
    }
    else if (head != NULL && head->next == NULL){
        head = NULL;
        tail = NULL;
        return head;
    }
    else {
        return NULL;
    }
}



//------------------------------------------------------------------------------------------------------------------

// Material covered in:

// Assignment 1
// 	File io
// 		sorting of a file into an array
// 	matching objects together based on opposite boolean values, appropriate int values, and matching names

// Assignment 2
// 	File io
// 		reads a huge text file and keeps track of the counts of words in said file
// 	sorts array based on frequency of count
// 	dynamically allocates memory of array

// Assignment 3
// 	Singly linked list
// 		builds, traverses, and deletes within a linked list

// Assignment 4
// 	Doubly linked list
// 		builds a network of items does linked list things

// Recitation 2
// 	File io
// 		writes to another file

// Recitation 3
// 	dynamically allocates memory

// Recitation 4
// 	singly linked list (ignore)

// Recitation 5
// 	doubly linked list (good)
// 		insertion, deletion, traversal, printing


// Question 5
// - cannot view stack/queue



Programming q1

int *makeNewArray(int inputArray[], int size, int compareNum){
    int* new = new int[size];
    for (int i = 0; i < size; i++){
        new[i] = inputArray[i];
    }
    for (int i = 0; i < size; i++){
        if (new[i] < compareNum){
            for (int j = i; j < size; j++){
                new[j] = new[j+1];
            }
            i--;
            size--;
        }
    }
    return new;
}

Programming q2

node *AddNewNodeSum(node *head, int value){
    node *newNode;
    node *temp = head;
    int prevValue = 0;
    int nextValue = 0;
    while (temp != NULL){
        if (temp->value == value){
            newNode->prev = temp;
            newNode->next = temp->next;
            temp->next->prev = newNode;
            temp->next = newNode;
            prevValue = newNode->prev->value;
            nextValue = newNode->next->value;
            newNode->value = prevValue + nextValue;
            break;
        }
        temp = temp->next;
    }
    return head;
}