
//  main.cpp
//  Project 2: Array vs Linked List Comparison
//      This program runs a comparison between arrays and linked lists
//      when using linear sort and insertion/deletion for various sets
//      of random elements vaues. The simulation allows us to see that
//      arrays are faster than linked lists for this algorithm when using
//      large data sets.
//
//  Created by Revanth Reddy on 10/8/14.
//  Language: C, C++
//  Envir: Mac OSX 10.10, Xcode 6.1
//  Tested on RHEL Server 5.11
//
//  Copyright (c) 2014 Revanth Reddy. All rights reserved.
//
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;


//---------------------------------------------------------------------------------------------------------//
// Define the node struct
typedef struct Node_ {
    int value;
    struct Node_* pNext;
} Node;


//---------------------------------------------------------------------------------------------------------//
// Prints program info. No parameters or return values.
void programInfo() {
    puts ("");
    puts ("**********************************");
    puts ("Author: Revanth Reddy");
    puts ("Project 2: Array vs Linked List Comparison");
    puts ("**********************************\n");
}


//-----------------------------------------------------------------------------//
// Print all the elements of the array
// @param {int*} pArray - points to the array to be printed
// @param {size} size - size of the array
void displayArray (int *pArray, int size) {
    int *pCurrent = pArray;
    for(int i=0; i<size; i++) {
        cout << *pCurrent << " ";
        pCurrent++;
    }
    printf("\n");
}


//-----------------------------------------------------------------------------//
// Prints all nodes of the linked list
// @param {Node*} pHead - pointer to the first node of linked list
void displayList(Node* pHead) {
    while( pHead != NULL) {   // if linked list has at least one node and not last node
        cout << pHead->value << " ";        // print value of node
        pHead = pHead->pNext;               // go to next node
    }
    cout << "\n";
}


//-----------------------------------------------------------------------------//
// Initializes and allocates memory for the array and linked list nodes
// @param {int*&} pArray - pointer reference to array
// @param {Node**&} pArrayList - pointer reference to linked list
// @param {int} testSize - size of the array and linked list to create
void initArrays(int *&pArray, Node **&pArrayList, int testSize) {
    // Create array of ints and initialize
    pArray = NULL;
    pArray = new int[testSize] ();
    
    // Create array of node pointers and initialize
    pArrayList = NULL;
    pArrayList = new Node* [testSize] ();
    for(int i = 0; i < testSize; ++i) {
        pArrayList[i] = new Node;
        pArrayList[i]->value = 0;
        pArrayList[i]->pNext = NULL;
    }
}


//-----------------------------------------------------------------------------//
// Inserts given newNumber into array in order.
// Accepts an random int value, reference to array, and size of array.
// @param {int} newNumber - value of the number to add to array
// @param {int*&} pArray - reference to array
// @param {int&} - reference to total number of elements in array
void addToArray(int newNumber, int *&pArray, int &size) {
    int i;
    
    // Add new element into array In Order
    // when array is empty, add newNumber to index 0
    // when array is not empty
    // find index where newNumber is less than current element
    // then shift all elements to the right of current index by one
    for (i = 0; i < size-1; i++) {
        if (newNumber < pArray[i]) {
            for (int j = size; i < j; j--) {
                pArray[j] = pArray[j-1];
            }
            break;
        }
    }
    
    // Add newNumber into empty index created after the shifting
    pArray[i] = newNumber;
    
    // Update size
    ++size;
}


//-----------------------------------------------------------------------------//
// Inserts given newNumber into linked list in order
// @param {int} newNumber - value of the number to add to linked list
// @param {Node**&} pArrayList - reference to linked list
// @param {int&} index - index position of next unused node
// @param {Node*&} pHead - reference to first noe of array
void addToLList(int newNumber, Node **&pArrayList, int &index, Node *&pHead) {
    // Save address to next empty node and increment index
    Node *pTemp = pArrayList[index++];
    
    // Save newNumber to node to be added to list
    pTemp->value = newNumber;
    
    //  List is empty
    if (pHead == NULL) {
        pTemp->pNext = NULL;
        pHead = pTemp;
    }
    // List is not empty
    else {
        // Find position to add node
        Node *pCurrent = pHead;
        while (pCurrent->pNext != NULL && newNumber > pCurrent->pNext->value ) {
            pCurrent = pCurrent->pNext;
        }
        if (pCurrent->value > newNumber) { // add to front
            pTemp->pNext = pCurrent;
            pHead = pTemp;
        }
        else if (pCurrent->pNext == NULL) { // add to end
            pTemp->pNext = NULL;
            pCurrent->pNext = pTemp;
        }
        else {
            pTemp->pNext = pCurrent->pNext; // add to middle
            pCurrent->pNext = pTemp;
        }
    }
}


//-----------------------------------------------------------------------------//
// Deletes a value from random-valued array.
// @param {int} index - nth element of array to delete
// @param {int*&} pArray - reference to array
// @param {int&} size - number of elements in array
void deleteFromArray(int index, int *&pArray, int &size) {
    
    // Shifts all values to the right of chosen index
    // one position to left, overwriting the value to delete
    for (int i = index; i < size; i++) {
        pArray[i] = pArray[i+1];
    }
    
    // Update size
    --size;
}


//-----------------------------------------------------------------------------//
// Deletes a value from random-valued linked list.
// @param {int} position - find the nth node to delete
// @param {Node*&} pHead - reference to the head node
// @param {int&} position - number of nodes in linked list
void deleteFromLList(int position, Node *&pHead, int &size) {
    Node *pTemp = pHead;
    int stop = position - 1; // nth node to stop at after traversal
    
    // Start at the first node, then traverse through list until stop position.
    for (int i = 0; i < stop; i++) {
        pTemp = pTemp->pNext;
    }
    if (position == size) { // if the desired node is the last node
        pTemp->pNext = NULL;
        if (size == 1)
            pHead = NULL;
    }
            // if desired node is not first or last node
    else if (pTemp->pNext->pNext == NULL && size > 2) {
        pTemp->pNext = NULL;
    }
    else {  // if 
        pTemp->pNext = pTemp->pNext->pNext;
    }
    
    // Update size
    --size;
}


//-----------------------------------------------------------------------------//
// Deallocates the linked list array and its nodes
// @param {Node**&} - reference to the linked list array
// @param {int} - size of linked list
void deleteLL (Node **&pArrayList, int size) {
    // Dealloc linked list
    for (int i = 0; i < size; i++) {
        delete (pArrayList[i]);
    }
    delete []pArrayList;
}



//-----------------------------------------------------------------------------//
int main () {
    int testSize = 3000;       // USE TO SET STARTING SIZE
    int increment = 4000;   // USE TO ADJUST SIZE OF INCREMENTS TO TEST
    int maxSize = 16000;    // USE TO ADJUST END SIZE
    int i;
    int size;
    int index;
    int *pArray = NULL;
    Node **pArrayList = NULL;
    Node *pHead = NULL;
    clock_t start, stop, progStart, progLap;
    double time_array, time_llist, time_elapsed;
    
    // Print program information and start program timer
    progStart = clock();
    programInfo();
    printf ("Size\t Time elapsed\t Array\t\t Linked List   (time in seconds)\n\n");
    
    do {
        // Dyanmically allocate array and linked list nodes
        initArrays(pArray, pArrayList, testSize);
        
        // ### ARRAY ###
        // Start timer for array
        start = clock();
        
        // Fill array with random values values
        size = 0;
        srand(time(NULL));
        for (i = 0; i < testSize; i++) {
            addToArray(rand() % 1000000 + 1, pArray, size);
        }
        // displayArray(pArray, size-1); // use to print values in ordered array
        
        // Delete values at random indices of array until empty
        for (i = 0; i != 0; i++) {
            deleteFromArray(rand() % size, pArray, size);
        }
        
        // Stop timer and save time elapsed for array
        stop = clock();
        time_array = ((double)(stop-start))/CLOCKS_PER_SEC;
        
        // Dealloc array to free memory
        delete []pArray;
        
        // ### LINKED LIST ###
        // Start timer for linked list
        start = clock();
        
        // Create array of size n and initialize with random values values
        index = 0; // represents the current position in pArrayList with next unused Node
        for (i = 0; i < testSize; i++) {
            addToLList(rand() % 1000000 + 1, pArrayList, index, pHead);
        }
        // displayList(pHead); // use to print ordered linked list
        
        // Delete values at random positions in linked list until empty
        size = index;
        for (i = 0; i < testSize; i++) {
            deleteFromLList(rand() % size + 1, pHead, size);
        }
        
        // Stop timer and save time elapsed for linked list
        stop = clock();
        time_llist = ((double)(stop-start))/CLOCKS_PER_SEC;
        
        // Dealloc linked list
        deleteLL(pArrayList, index);
        
        // Save current time elapsed thus far
        progLap = clock();
        time_elapsed = ((double)(progLap-progStart))/CLOCKS_PER_SEC;
        
        // Print time results (formatting of columns vary between xcode and linux
        printf ("%d\t %lf\t %lf\t %lf\t\n", testSize, time_elapsed, time_array, time_llist);
        
        testSize = testSize + increment;
    } while (testSize <= maxSize);
    
    cout << "Done" << endl;
    return 0;
}
