//
//  main.c
//  Project 10 - Restaurant Wait List System
//      Keeps track of groups and their group sizes based on when they make their
//      reservation and distinguish between those that are waiting in the
//      restaurant. Can retreive the first available group of a particular size
//      when a table is ready.
//
//  Created by Revanth Reddy on 11/26/14.
//  Language: C
//  Envir:  Mac OSX Yosemite, Xcode 6.1
//  Tested on RHEL Server 5.11
//
//  Copyright (c) 2014 Revanth Reddy. All rights reserved.
//
//  This program uses source from proj4UserInputSource.c, which contains code for parsing the
//      user input and error checking. All code needed to implement the wait list
//      system using a linked list has been added on top of this source.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

typedef struct Node_ {
    char* name;
    int size;
    int isInRestaurant;
    struct Node_ *pNext;
} Node;


//---------------------------------------------------------------------------------------------------------//
// Display program information
void programInfo() {
    puts ("");
    puts ("****************************************");
    puts ("Author: Revanth Reddy");
    puts ("Project 10: Restaurant Wait List System");
    puts ("****************************************\n");
}


//--------------------------------------------------------------------------------//
// Clear input until next End of Line Character - \n
void clearToEoln() {
    int ch;
    
    do {
        ch = getc(stdin);
    } while ((ch != '\n') && (ch != EOF));
}


//--------------------------------------------------------------------------------//
// Read in until the first Non-White-Space character is Read
// The white space characters are:
//      space, tab \t, newline \n, vertical tab \v,
//      form feed \f, and carriage return \r
int getNextNWSChar () {
    int ch;
    
    ch = getc(stdin);
    if (ch == EOF)
        return ch;
    while (isspace (ch)) {
        ch = getc(stdin);
        if (ch == EOF)
            return ch;
    }
    return ch;
}


//--------------------------------------------------------------------------------//
// read in the next Positive Integer or error:
// This is based on the Mathematical definition of a Postive Integer
//    zero is not counted as a positive number
int getPosInt () {
    int value = 0;
    
    // clear white space characters
    int ch;
    ch = getc(stdin);
    while (!isdigit(ch)) {
        if ('\n' == ch)     // if \n encounter, no integer given
            return 0;       // return as error
        if (!isspace(ch)) { // if non white space encountered, integer not given next
            clearToEoln();  // clear buffer, return as error
            return 0;
        }
        ch = getc(stdin);   // get next char
    }
    
    //convert digit chars to int
    value = ch - '0';
    ch = getc(stdin);
    while (isdigit(ch)) {
        value = value * 10 + ch - '0';
        ch = getc(stdin);
    }
    
    ungetc (ch, stdin);  // put the last read character back in input stream
    
    if (0 == value)      // Integer value of 0 is an error in this program
        clearToEoln();   // clear buffer
    
    return value;        // return pos int
}


//--------------------------------------------------------------------------------//
// read in the name until the end of the input
char *getName() {
    // skip over the white space characters
    int ch;
    ch = getc(stdin);
    while (isspace(ch)) {
        if ('\n' == ch)  // if \n encountered, no integer given
            return NULL;
        ch = getc(stdin);
    }
    
    // Allocate a cstring to hold char input
    char *word;
    int size;
    size = 10;
    word = (char*) malloc (sizeof(char) * size);
    
    // read in character-by-character until the newline is encountered
    int count = 0;
    
    while (ch != '\n') {
        if (count+1 >= size) {
            // dynamically resize array when old array is full
            char* temp;
            int i;
            size = size * 2; // size of new array will be 2x longer than old
            temp = (char*) malloc (sizeof(char) * size);
            
            // copy the characters to the new array
            for (i = 0 ; i < count ; i++)
                temp[i] = word[i];
            
            free (word);      // deallocate old array
            word = temp;      // assign new array to word pointer
        }
        
        word[count] = ch;     // save char to array (overwrites null char)
        count++;              // increment index position
        word[count] = '\0';   // add null char
        
        ch = getc(stdin);     // read next character
    }
    
    if (count > 30) {         // limits name to be stored up to 30 char for brevity
        count = 30;
        word[count] = '\0';   // overwrites all additional char with null
    }
    
    // clear ending white space characters
    while (isspace (word[count-1])) {
        count--;
        word[count] = '\0';
    }
    
    return word;
}


//--------------------------------------------------------------------------------//
// Print out a list of the commands for this program
void printCommands() {
    printf ("The commands for this program are:\n\n");
    printf ("q                 Quit program.\n");
    printf ("?                 List the accepted commands.\n");
    printf ("a <size> <name>   Add a group to the wait list.\n");
    printf ("c <size> <name>   Add a call-ahead group to the wait list.\n");
    printf ("w <name>          Specify a call-ahead group is now waiting in restaurant.\n");
    printf ("r <table-size>    Retrieve the first waiting group with matching group size.\n");
    printf ("l <name>          List how many groups are ahead of the named group.\n");
    printf ("d                 Display the wait list information.\n");
}


//--------------------------------------------------------------------------------//
// Checks the queue to see if group with a given name already exists in the queue.
// @param {Node*} queue - pointer to the head of the linked list.
// @param {char*} name - cstring holding the group name to find.
// @return true/false - based on whether or not group name is found in queue.
int doesNameExist(Node *queue, char *name) {
    if (queue == NULL)                   // if list is empty
        return FALSE;                    // return false
    while (queue != NULL) {              // traverse non-empty list until last node
        if (!strcmp(queue->name,name)) { // if matching name is found, strcmp returns 0...
            return TRUE;                 // !0 is 1, branch is taken, return true
        }
        queue = queue->pNext;            // update pointer to next node
    }
    return FALSE;                      // return false if name not found in non-empty list
}


//--------------------------------------------------------------------------------//
// Adds a group that is waiting inside the restaurant to the waiting list.
// Performs input parsing for a positive integer for group size and cstring for group name.
// If group of same name is not already in list, a node will be added.
// Other than the print statements, the only other difference from this function and
//      doCallAhead() is the isInRestaurant status TRUE.
// @param {Node**} queue - pointer to the head of linked list. Modifyable.
void commandA (Node **queue) {
    // get group size from input
    int size = getPosInt();
    if (size < 1) {
        printf ("Error: Add command requires an integer value of at least 1\n");
        printf ("Add command is of form: a <size> <name>\n");
        printf ("  where: <size> is the size of the group making the reservation\n");
        printf ("         <name> is the name of the group making the reservation\n");
        return;
    }
    
    // get group name from input
    char *name = getName();
    if (NULL == name) {
        printf ("Error: Add command requires a name to be given\n");
        printf ("Add command is of form: a <size> <name>\n");
        printf ("  where: <size> is the size of the group making the reservation\n");
        printf ("         <name> is the name of the group making the reservation\n");
        return;
    }
    
    // check if group is already in queue
    if (doesNameExist(*queue, name)) {  // if true, return to avoid adding duplicate
        printf ("Group name \"%s\" is already in waiting list.\n", name);
        free(name);                    // deallocate parsed input cstring before return
        return;
    }
    
    printf ("Adding group \"%s\" of size %d.\n", name, size);
    
    // Allocate a new node and initialize
    Node *newNode = malloc(sizeof(Node));
    newNode->size = size;
    newNode->name = name;
    newNode->isInRestaurant = TRUE;                 // group is waiting in restaurant
    newNode->pNext = NULL;
    
    // Add node to end of linked list
    Node *current = *queue;                         // create a list traversal pointer
    if (current != NULL) {                          // if list not empty
        while (current->pNext != NULL) {            // traverse list until last node
            current = current->pNext;
        }
        current->pNext = newNode;                   // add node to end of list
    }
    else {                                          // else if list is empty
        *queue = newNode;                           // add as first node to list
    }
}


// Adds a group that is waiting inside the restaurant to the waiting list.
// Performs input parsing for a positive integer for group size and cstring for group name.
// If group of same name is not already in list, a node will be added.
// Other than the print statements, the only other difference from this function and
//      doAdd() is the isInRestaurant status FALSE since this is for a call-ahead.
// @param {Node**} queue - pointer to the head of linked list. Modifyable.
//--------------------------------------------------------------------------------//
void commandC (Node **queue) {
    // get group size from input
    int size = getPosInt();
    if (size < 1) {
        printf ("Error: Call-ahead command requires an integer value of at least 1\n");
        printf ("Call-ahead command is of form: c <size> <name>\n");
        printf ("  where: <size> is the size of the group making the reservation\n");
        printf ("         <name> is the name of the group making the reservation\n");
        return;
    }
    
    // get group name from input
    char *name = getName();
    if (NULL == name) {
        printf ("Error: Call-ahead command requires a name to be given\n");
        printf ("Call-ahead command is of form: c <size> <name>\n");
        printf ("  where: <size> is the size of the group making the reservation\n");
        printf ("         <name> is the name of the group making the reservation\n");
        return;
    }
    
    // check if group is already in queue
    if (doesNameExist(*queue, name)) {  // if true, return to avoid adding duplicate
        printf ("Group name \"%s\" is already in waiting list.\n", name);
        free(name);                    // deallocate parsed input cstring before return
        return;
    }
    
    printf ("Adding call-ahead group \"%s\" of size %d.\n", name, size);
    
    // Allocate a new node and initialize
    Node *newNode = malloc(sizeof(Node));
    newNode->size = size;
    newNode->name = name;
    newNode->isInRestaurant = FALSE;                // group has not arrived at restaurant
    newNode->pNext = NULL;
    
    // Add node to end of linked list
    Node *current = *queue;                         // create a list traversal pointer
    if (current != NULL) {                          // if list not empty
        while (current->pNext != NULL) {            // traverse list until last node
            current = current->pNext;
        }
        current->pNext = newNode;                   // add node to end of list
    }
    else {                                          // else if list is empty
        *queue = newNode;                           // add as first node to list
    }
}


//--------------------------------------------------------------------------------//
// Updates group status for a call-ahead group that has arrived at the restaurant.
// Performs input parsing for a cstring for group name.
// @param {Node*} queue - pointer to the head of the linked list.
void commandW (Node *queue) {
    // get group name from input
    char *name = getName();
    if (name == NULL) {
        printf ("Error: Waiting command requires a name to be given\n");
        printf ("Waiting command is of form: w <name>\n");
        printf ("  where: <name> is the name of the group that is now waiting\n");
        return;
    }
    
    // check if group name is not is list
    if (!doesNameExist(queue, name)) { // if true, return since no status to change
        printf ("Group name \"%s\" is not on the waiting list.\n", name);
        free(name);                    // deallocate parsed input cstring before return
        return;
    }

    while (queue->pNext != NULL) {            // traverse list until last node
        if (!strcmp(queue->name, name))       // when matching group name found
            break;                            // stop traversing
        queue = queue->pNext;                 // else update pointer to next node
    }
    
    // Check if group is already in restaurant
    if (queue->isInRestaurant == TRUE) {      // if group in-restaurant status is true
                                              // do nothing, display feedback
        printf ("Group name \"%s\" is not a call-ahead and is already waiting in restaurant.\n", name);
    }
    else  {                                   // else if group is a call-ahead
        queue->isInRestaurant = TRUE;         // update their status and display feedback
        printf ("Call-ahead group \"%s\" is now waiting in the restaurant.\n", name);
    }
    free(name);                         // deallocate parsed input cstring before return
}


//--------------------------------------------------------------------------------//
// Gets and removes a group from the wait list when a table is available.
// Parses input for a positive integer for table size.
// @param {Node**} queue - pointer to the head of linked list. Modifyable.
void commandR (Node **queue) {
    // get table size from input
    int size = getPosInt();
    if (size < 1) {
        printf ("Error: Retrieve command requires an integer value of at least 1\n");
        printf ("Retrieve command is of form: r <size>\n");
        printf ("  where: <size> is the size of the group making the reservation\n");
        return;
    }
    clearToEoln();
    printf ("Retrieve the first group that can fit at a table of size %d.\n", size);
    
    Node *current = *queue;                        // create list traversal pointer
    
    // Check first group
    if (current->size == size && current->isInRestaurant == TRUE) {
        printf("Group \"%s\" will now be seated.\n", current->name);
        *queue = current->pNext;                   // remove group from list
        free(current->name);                       // deallocate name cstring
        free(current);                             // deallocate node
        return;                                    // return since group has been removed
    }
    // Check remaining groups
    while (current->pNext != NULL) {
        if (current->pNext->size == size && current->pNext->isInRestaurant == TRUE) {
            Node *toRemove = current->pNext;       // point to the node to be removed
            current->pNext = toRemove->pNext;      // update pNext to skip the node
            printf("Group \"%s\" will now be seated.\n", toRemove->name);
            free(toRemove->name);                  // deallocate name cstring
            free(toRemove);                        // deallocate node
            return;                                // return since group has been removed
        }
        current = current->pNext;  // if group found, update list traversal pointer to next node
    }
    
    // If no group size matches the table size
    printf ("There is no group of size %d on the waiting list.\n", size);
}


//--------------------------------------------------------------------------------//
// Count the number of groups ahead of a given group.
// @param {Node*} queue - pointer to the head of the linked list.
// @param {char*} name - cstring holding the group name to find.
// @return {int} numGroups - total number of groups ahead.
int countGroupsAhead(Node *queue, char *name) {
    int numGroups = 0;                          // initialize counter
    while (strcmp(queue->name, name)) {         // while group name not found
        numGroups++;                            // increment counter per each node
        queue = queue->pNext;                   // update list traversal pointer
    }
    return numGroups;
}


//--------------------------------------------------------------------------------//
// Prints out the name and size of all the groups ahead of a given group.
// @param {Node*} queue - pointer to the head of the linked list.
// @param {char*} name - cstring holding the group name to find.
void displayGroupSizeAhead(Node *queue, char *name) {
    while (strcmp(queue->name, name)) {                 // while group name not found
        printf ("Group Name:  %s\n", queue->name);      // print group name
        printf ("Group Size:  %d\n\n", queue->size);    // print group size
        queue = queue->pNext;                           // update list traversal pointer
    }
}


//--------------------------------------------------------------------------------//
// Counts and lists groups ahead of a given group name.
// Parses input for a cstring to hold group name.
// @param {Node*} queue - pointer to the head of the linked list.
void commandL (Node *queue) {
    // get group name from input
    char *name = getName();
    if (name == NULL) {
        printf ("Error: List command requires a name to be given\n");
        printf ("List command is of form: l <name>\n");
        printf ("  where: <name> is the name of the group to inquire about\n");
        return;
    }
    
    // Check if group is not on the list.
    if (!doesNameExist(queue, name)) { // if true, return.
        printf ("Group name \"%s\" is not on the waiting list.\n", name);
        free(name);                    // deallocate parsed input cstring before return
        return;
    }
    
    // Count number of groups ahead and display
    int numGroupsAhead = countGroupsAhead(queue, name);
    if (numGroupsAhead == 0)
        printf ("Group \"%s\" is at the top of the wait list.\n\n", name);
    else
        printf ("Group \"%s\" is behind %d group(s).\n\n", name, numGroupsAhead);

    displayGroupSizeAhead(queue, name); // display names and sizes of groups ahead
    
    free(name);                        // deallocate parsed input cstring before return
}


//--------------------------------------------------------------------------------//
// Displays the entire wait list with group name, size, and status.
// @param {Node*} queue - pointer to the head of the linked list.
void commandD (Node *queue) {
    clearToEoln(); // clear buffer
    printf ("Displaying entire wait list...\n\n");
    
    // Check if list empty
    if (queue == NULL) {
        printf("Wait list is empty.\n");
        return;
    }
    // When list not empty, access each node and display contents
    while (queue != NULL) {
        printf ("Group Name:      %s\n", queue->name);      // print group name
        printf ("Group Size:      %d\n", queue->size);      // print group size
        if (queue->isInRestaurant == TRUE)                  // print status
            printf ("In restaurant?:  Yes\n");
        else
            printf ("In restaurant?:  No\n");
        queue = queue->pNext;                      // update list traversal pointer
    }
}


//--------------------------------------------------------------------------------//
// Deallocate entire waiting list.
// @param {Node*} queue - pointer to the head of the linked list.
void deleteQueue(Node*queue) {
    while (queue != NULL) {
        Node *toDelete = queue;
        queue = queue->pNext;
        free(toDelete->name);
        free(toDelete);
    }
    free(queue);
}


//--------------------------------------------------------------------------------//
int main (int argc, char **argv) {
    //char *input;
    int ch;              // store char from input buffer
    Node *queue = NULL;  // create pointer for linked list
    
    programInfo();
    
    // Prompt for user command
    printCommands();
    printf ("\nEnter command: ");
    while ((ch = getNextNWSChar() ) != EOF) { // get menu input
        
        if ('q' == ch) {
            printf ("Exiting program.\n");
            deleteQueue(queue);
            return 0;
        }
        else if ('?' == ch) {
            printCommands();
            clearToEoln();
        }
        else if('a' == ch) {
            commandA(&queue);
        } 
        else if('c' == ch) {
            commandC(&queue);
        } 
        else if('w' == ch) {
            commandW(queue);
        } 
        else if('r' == ch) {
            commandR(&queue);
        } 
        else if('l' == ch) {
            commandL(queue);
        } 
        else if('d' == ch) {
            commandD(queue);
        } 
        else { // command does not exist, print error, prompt again
            printf ("%c - in not a valid command\n", ch);
            printf ("For a list of valid commands, type ?\n");
            clearToEoln();
        }
        printf ("\n-------\n\nEnter command: ");
    }

    //printf ("Quiting Program - EOF reached\n");
    return 1;
}
