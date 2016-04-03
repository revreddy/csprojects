//
//  main.c
//  Project 1: Overboard
//      Run simulations to determine counting that will allow
//      ejecting of all Android passengers, leaving only
//      humans to escape on life pod.
//
//  Created by Revanth Reddy on 9/8/14.
//  Language: C, C++
//  Envir: Mac OSX 10.10, Xcode 6.1
//  Tested on RHEL Server 5.11
//
//  Copyright (c) 2014 Revanth Reddy. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//-----------------------------------------------------------------------------//
// Define the node struct
typedef struct Node_ {
    char letter;
    struct Node_* pNext;
} Node;



//-----------------------------------------------------------------------------//
// Prints program info. No parameters or return values.
void programInfo() {
    puts ("");
    puts ("**********************************");
    puts ("Author: Revanth Reddy");
    puts ("Project 1:  Overboard");
    puts ("**********************************\n");
}


//-----------------------------------------------------------------------------//
// Prints the circle in clockwise fashion in the same order as the input file.
// @param {Node*} pHead, pTail -  Represents start and end points for circle
void displayListForward (Node *pHead, Node *pTail) {
    while (pHead != NULL) {
        // Print letter
        printf ("%c", pHead->letter);
        
        // Avoids infinite looping through circular list
        if (pHead == pTail)
            break;
        // Increment pointer to next node
        pHead = pHead->pNext;
    }
    printf("\n");
}


//-----------------------------------------------------------------------------//
// Allocate new node and create a new circle or add to tail end of existing one.
// @param {Node**} pHead - Reference points to the very first node added
// @param {Node**} pTail - Reference point to the very last node added
// @param {char} letter - 'H' or 'A' to be stored in the node
void addNode (Node **pHead, Node **pTail, char letter) {
    // Create new node and add the data
    Node *pTemp = (Node*)malloc(sizeof(Node));
    pTemp->letter = letter;
    
    // If circle is empty, add as first node
    if (*pHead == NULL) {
        pTemp->pNext = pTemp;
        *pHead = pTemp;
        *pTail = pTemp;
    }
    // Add to tail of existing circle of nodes
    else {
        (*pTail)->pNext = pTemp;
        pTemp->pNext = *pHead;
        *pTail = pTemp;
    }
}


//-----------------------------------------------------------------------------//
// Transverse through circle by n positions.
// @param {Node*} pTemp - stores current position
// @param {int} nValue - number of nodes to traverse
// The stop position is returned to be used for next counting round.
Node* transverse(Node *pTemp, int nValue) {
    int count;
    
    // Counts through circle and stops one position before new eject position
    for (count = 1; count < nValue; count++) {
        pTemp = pTemp->pNext;
    }
    
    // Return position of ejected passenger
    return pTemp;
}


//-----------------------------------------------------------------------------//
// Deallocate single node to simulate ejection of passenger.
// Uses the stop position from previous counting as a reference point to eject the next node.
// @param {Node*} pCurrent - used as traversal pointer through the circle
// @param {Node**} pHead, pTail - head and tail are adjusted if those positions are ejected.
void deleteNode (Node *pCurrent, Node **pHead, Node **pTail) {
    Node *pTemp;
    
    // Counting stopped at one position before the passenger to be ejected,
    // the eject position is stored and removed from circle
    pTemp = pCurrent->pNext;
    pCurrent->pNext = pTemp->pNext;
    
    // Reassign head or tail if these positions are ejected
    if (pTemp == *pHead) {
        *pHead = pTemp->pNext;
    }
    if (pTemp == *pTail) {
        *pTail = pCurrent;
    }
    
    // Deallocate node
    free(pTemp);
}


//-----------------------------------------------------------------------------//
// Deallocates the entire circle.
// @param {Node*} pHead -  Use head position as starting and ending point for dealloc.
void deleteCircle (Node *pHead) {
    Node *pTemp;    //Used for transversing
    Node *pDelete;  //Used to hold the dangling node before freeing
    
    // Start at head
    pTemp = pHead;
    
    // Delete each node until come back to starting position
    while (pTemp->pNext != pHead) {
        pDelete = pTemp;
        pTemp = pTemp->pNext;
        free(pDelete);
    }
}


//-----------------------------------------------------------------------------//
// Check input string for a single line of H's and A's only and no other characters in file.
// @param {char*} inputstr -
// @param {int} inputLength - total number of humans and androids
// @param {int*} nHumans - stores number of humans
// @param {int*} nAndroid - stores number of androids
// @return {int} - return 1 for error if non-H/A letters, numbers, or whitespace encountered,
//                  else return 0
int countPassengers (char *inputstr, int inputLength, int *nHumans, int *nAndroids) {
    int i;   // index location of array
    
    for (i = 0; i < inputLength; i++) {
        if (inputstr[i] != 'H' && inputstr[i] != 'A') //other char found, return error
            return 1;
        else if (inputstr[i] == 'H')
            (*nHumans)++;
        else //if (inputstr[i] == 'A')
            (*nAndroids)++;
    }
    return 0;
}


//-----------------------------------------------------------------------------//
// Creates circle, counts, ejects, and deletes circle
// @param {char*} inputstr - stores the passenger manifest sequence
// @param {int} inputLength - total number of humans and androids
// @param {int} nAndroids - total number of androids
// @param {int*} nEjections - total number of ejections performed
// @return {int} - counting value of potentially successful ejection of all androids
int countingSequence(char *inputstr, int inputLength, int nAndroids, int *nEjections) {
    int nValue;          // counting number used to transverse through circle
    int i;               // index location of array
    Node *pHead = NULL;  // counting starting position
    Node *pTail = NULL;  // one position counterclockwise of starting position
    Node *pCurrent = NULL; // current start/stop position during counting

    //  Counting Sequence
    for (nValue = 1; (nValue <= inputLength) && ((*nEjections) != nAndroids); nValue++) {
        // Create circle where i is the index position of the input char array
        for (i = 0; i < inputLength; i++) {
            addNode(&pHead, &pTail, inputstr[i]);
        }
        
        // Set initial values
        pCurrent = pHead;                           // start at the head of circle
        (*nEjections) = 0;                          // number of ejections is initially 0
        
        // Start counting and ejection
        while (1) {
            pCurrent = transverse (pCurrent, nValue);  // Count nodes
            
            if (pCurrent->pNext->letter == 'H')     // If human is chosen
                break;                              // then stop counting
            
            deleteNode(pCurrent, &pHead, &pTail);   // else if A is chosen, eject by dealloc node
            (*nEjections)++;                        // increment ejection count
        }
        
        // Dealloc remainder of circle and reset pointers, regardless of success or failure
        deleteCircle(pHead);
        pHead = NULL;
        pTail = NULL;
        pCurrent = NULL;
    }
    nValue--; //undo the last increment
    
    // Return n value
    return nValue;
}


//-----------------------------------------------------------------------------//
int main() {
    FILE *finput;
    char inputstr[100];  // passenger manifest
    int inputLength = 0; // number of passengers
    int nHumans = 0;     // number of humans on manifest
    int nAndroids = 0;   // number of androids on manifest
    int nEjections = 0;  // number of ejections
    int nValue = 0;      // counting number used to transverse through circle
    int errorCode = 0;   // error code
    
    // Print program information
    programInfo();
    
    // Open file
    finput = fopen("passengers.txt", "r");
    if (finput == NULL) {
        puts ("Error: Unable to open source file or does not exist.\n");
        return 1;
    }
    
    // Open file, parse input to char array, and close file
    if (fgets (inputstr, 100, finput) == NULL ) {
        puts("Error: input file empty.\n");
        puts(inputstr);
    }
    fclose(finput);
    
    // Find total number of passengers onboard
    inputLength = strlen(inputstr);
    printf("Number of passengers onboard = %d\n", inputLength);
    
    // Check if input is valid; count number of humans and android passengers
    errorCode = countPassengers (inputstr, inputLength, &nHumans, &nAndroids);
    if (errorCode == 1)
        puts ("Error: Input contains characters (letters, numbers, or whitespace) other than 'H' or 'A'");
    else
        printf ("Number Humans/Androids = %d/%d\n", nHumans, nAndroids);
    
    // Begin counting simulations to find value of n
    nValue = countingSequence(inputstr, inputLength, nAndroids, &nEjections);
    
    // Print result, n value exists only if number of ejections equals number of androids
    if (nEjections != nAndroids)
        puts ("There is no value of n that will allow only humans to survive.\n\n");
    else
        printf ("Value of n = %d will allow only humans to survive.\n\n", nValue);
    
    return 0;
}
