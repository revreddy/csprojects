//
//  main.c
//  Project 8 - Linear vs Binary Search
//      This program takes a series of integers to compare
//      how what position and how many comparisons are necessary
//      to find a particular integer using linear and binary search.
//
//  Created by Revanth Reddy on 10/22/14.
//  Language: C
//  Envir:  Mac OSX Yosemite, Xcode 6.1
//  Tested on RHEL Server 5.11
//
//  Copyright (c) 2014 Revanth Reddy. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0


//--------------------------------------------------------------------------------//
// Display program information
void programInfo() {
    puts ("");
    puts ("***********************************");
    puts ("Author: Revanth Reddy");
    puts ("Project 8: Linear vs Binary Search");
    puts ("***********************************\n");
}

//--------------------------------------------------------------------------------//
// Copies the elements of array 1 to array 2
// @param {int[]} fromArray - array with the integer values
// @param {int[]} toArray - empty array to copy integer values to
// @param {int} size - size of both arrays
void arrayCopy (int fromArray[], int toArray[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        toArray[i] = fromArray[i];
    }
}


//--------------------------------------------------------------------------------//
// Selection sort algorithm
// @param {int[]} arr - array with the integer values to sort
// @param {int} size - size of array.
void sort (int arr[], int size) {
    int i, j, tmp;
    for (i = 0; i < size-1; i++) {
        for (j = 0; j < (size - i - 1); j++) {
            if (arr[j] > arr[j+1]) {
                tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }
}


//--------------------------------------------------------------------------------//
// Linear search algorithm
// @param {int[]} arr - unsorted array of integers to search for the target value
// @param {int} size - size of the array
// @param {int} target - integer value to find.
// @param {int*} numComparisons - pointer to a variable that serves as a counter.
// @return - the current index i position if found. If not found, -1. These values serve
//      as booleans for choosing the appropriate output statements in main().
int linSearch (int arr[], int size, int target, int* numComparisons) {
    int i;
    for (i = 0; i < size; i++) {     // for every index in array
        if (arr[i] == target) {      // if current element equals the search target value
            *numComparisons = i + 1; // example: index 100 takes 101 comparisons, hence i+1
            return i;                // if found, return current index position
        }
    }
    return -1;                       // if not found
    
}


//--------------------------------------------------------------------------------//
// Binary search algorithm
// @param {int[]} arr - sorted array of integers to search for the target value
// @param {int} size - size of the array
// @param {int} target - integer value to find.
// @param {int*} numComparisons - pointer to a variable that serves as a counter.
// @return - the index mid value if found. If not found, -1. These values serve
//      as booleans for choosing the appropriate output statements in main()
int binSearch (int arr[], int size, int target, int* numComparisons) {
    int i = 0;                       // counter to keep track of halfing of window
    int high = size - 1;             // array size of 100 would give high = 99
    int low = 0;                     // low is always index 0
    int mid;                         // index to check if element matches target
    
    while (low <= high) {
        i++;                         // increment counter
        mid = (high + low)/2;        // mid is the index in the middle of the current window
        if (arr[mid] == target) {    // if mid element value matches the target, then found
            *numComparisons = i;     // save number of comparisons before return
            return mid;              // if found, return current index position
        }
        else if (arr[mid] > target)  // if mid element value is greater than search target
            high = mid - 1;          // adjust window to bottom half
        else
            low = mid + 1;           // adjust window to top half
    }
    return -1;                       // if not found
}


//--------------------------------------------------------------------------------//
// Display the array contents
// @param {int[]} array - holds array of ints.
// @param {int} size - size of array.
void displayArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf ("%d ", arr[i]);
    }
    printf ("\n");
}


//--------------------------------------------------------------------------------//
int main(int argc, char *argv[]) {
    int *arr1, *arr2;
    int val, sizeList, sizeArray, lComp, bComp, resultLinear, resultBinary;
    
    // Display program info
    programInfo();
    
    // Allocate memory for arrays to hold upto 100 integers
    sizeArray = 5; //initial array size
    arr1 = (int*) malloc (sizeof(int)*sizeArray);
    
    // Get input values and store in array
    val = 0;         // set initial values
    sizeList = 0;
    while (val != -999) {
        // Parse input
        printf ("Enter an integer. Use -999 to end input:  ");
        if (scanf("%d", &val) != 1) {  // keep prompting for valid input until int given
            while (getchar() != '\n'); // clear input buffer if input is invalid
            printf ("Error: Input contains non-integer characters. Try again.\n");
            continue; // start from top of while loop to prompt for input again
        }
        
        // Check for exit value
        if (val == -999)
            break;
        
        // Resize array if full
        if (sizeList == sizeArray) { // If array is full, then copy values to larger array, delete old array
            // Allocate new array
            int *temp;
            sizeArray = sizeList * 2; // double the array size
            temp = (int*) malloc(sizeof(int) * sizeArray);
            
            // Copy values to new array from old
            for (int i = 0 ; i < sizeList ; i++)
                temp[i] = arr1[i];
            
            free (arr1); // deallocate old array
            arr1 = temp; // set pointer to new array
        }
        
        // Add value to array and increment size
        arr1[sizeList] = val;
        sizeList++;
    }
    
    // If exit value given without entering any values entered to list
    if (sizeList == 0) {
        puts ("List is empty. Cannot perform any comparisons. Exiting program.");
        return 0;
    }
    
    // Copy elements to second array and sort the second array
    arr2 = (int*) malloc (sizeof(int) * sizeList);
    arrayCopy(arr1, arr2, sizeList);
    sort(arr2, sizeList);
    
    // Get integer value to search for and run search algos
    val = 0; // reset value
    while (val != -999) {
        // Get search value
        printf ("Enter an integer to perform linear and binary search. Use -999 to end searching:\n");
        if (scanf("%d", &val) != 1) {
            while (getchar() != '\n');
            printf ("Error: Input contains non-integer characters. Try again.\n");
        }
        
        // Check for exit value
        if (val == -999) {
            printf ("Exit code %d provided.\n", val);
            printf ("Done.\n");
            break;
        }
        
        // Perform linear and binary searches:
        // Both arrays have same set of values. If search value is not found via binary search, then linear search
        // can be skipped to save time. Furthermore, binary search is performed first since it is more efficient
        // (requires fewer comparisons) to determine if search value is in list.
        lComp = bComp = 0;
        resultBinary = binSearch(arr2, sizeList, val, &bComp);
        if (resultBinary != -1)
            resultLinear = linSearch(arr1, sizeList, val, &lComp);
        
        // Print comparison output
        if (resultBinary == -1) {
            printf ("Searching for %d...\n", val);
            printf ("Not found in this list.\n");
            printf ("\n");
        }
        else  {
            printf ("Searching for %d...\n", val);
            printf ("Linear search: index %d in %d comparisons.\n", resultLinear, lComp);
            printf ("Binary search: index %d in %d comparisons.\n", resultBinary, bComp);
            printf ("\n");
        }
    }
    
    // Deallocate arrays to free memory
    free (arr1);
    free (arr2);
    return 0;
}