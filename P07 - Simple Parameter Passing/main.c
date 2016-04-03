//
//  main.c
//  Project 7 - Simple Parameter Passing
//      This program uses some basic programming concepts
//      such as creating function, passing parameters, returning
//      values, and printing output.
//
//  Created by Revanth Reddy on 10/21/14.
//  Language: C
//  Envir:  Mac OSX Yosemite, Xcode 6.1
//  Tested on RHEL Server 5.11
//
//  Copyright (c) 2014 Revanth Reddy. All rights reserved.
//

/* Sample output:
 Revanth Reddy
 UIN ###
 
 Provide two integers for comparison.
 Enter a value for integer 1: 11
 Enter a value for integer 2: 22
 
 Max integer value:	 22
 Given integers:     int1 = 11, int2 = 22
 Swapped integers:	 int1 = 22, int2 = 11
 
 Provide 10 integers for an array.
 Enter a value for integer 1: 1
 Enter a value for integer 2: 2
 Enter a value for integer 3: 3
 Enter a value for integer 4: 4
 Enter a value for integer 5: 5
 Enter a value for integer 6: 6
 Enter a value for integer 7: 7
 Enter a value for integer 8: 8
 Enter a value for integer 9: 9
 Enter a value for integer 10: 10
 
 Sum of 10 ints:  55
 
 Array values before adjustment: 1 2 3 4 5 6 7 8 9 10
 Array values after adjustment:	 65 11 39 33 105 31 24 38 12 30
 
 Done
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//--------------------------------------------------------------------------------//
// Display program information
void programInfo() {
    puts ("");
    puts ("************************************");
    puts ("Author: Revanth Reddy");
    puts ("Project 7: Simple Parameter Passing");
    puts ("************************************\n");
}


//--------------------------------------------------------------------------------//
// Find the max integer.
// Accepts two integers value
// Returns the max integer value.
int max(int x1, int x2) {
    if (x1 > x2)
        return x1;
    return x2;
}


//--------------------------------------------------------------------------------//
// Swaps the integers between two variables.
// Accepts two pointers to integers for swapping their values
void swap(int *s1, int *s2) {
    int tmp;
    
    tmp = *s1;
    *s1 = *s2;
    *s2 = tmp;
}


//--------------------------------------------------------------------------------//
// Compute the sum of array of integers.
// @param {int[]} array - holds array of ints to add together.
// @param {int} size - size of array.
// @return {int} sum - sum of the integers.
int sum (int array[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }

    return sum;
}


//--------------------------------------------------------------------------------//
// Compute the sum of array of integers.
// @param {int[]} array - holds array of ints to randomize.
// @param {int} size - size of array.
void adjust (int array[], int size) {
    // Generate seed for rand()
    srand(time(NULL));
    
    // Add a random number from 1-100 to each integer and overwrite existing value
    for (int i = 0; i < size; i++) {
        array[i] += rand() % 100 + 1;
    }
}


//--------------------------------------------------------------------------------//
// Prompt and parse integer value from input.
// @param {int} counter - counter value to display to use prompt statement
// @return {int} value - returns the input value
int promptForInts(int counter) {
    int value;
    
    printf ("Enter a value for integer %d: ", counter);
    scanf ("%d", &value);
    return value;
}


//--------------------------------------------------------------------------------//
int main(int argc, const char *argv[]) {
    programInfo();
    
    // Print program info
    puts ("Revanth Reddy");
    puts ("UIN ###\n");
    
    // Prompt for two integers
    int int1, int2;
    
    puts ("Provide two integers for comparison.");
    int1 = promptForInts(1);
    int2 = promptForInts(2);
    
    // Find max between the two ints
    int result = max(int1, int2);
    puts ("");
    printf ("Max integer value:\t\ %d\n", result);
    
    // Swap integers and print values before and after changes
    printf("Given integers:\t\t int1 = %d, int2 = %d\n", int1, int2);
    swap(&int1, &int2);
    printf ("Swapped integers:\t int1 = %d, int2 = %d\n\n", int1, int2);
    
    // Create array of 10 integers
    int size = 10;
    int array[size];
    
    // Prompt and store integers in array
    puts ("Provide 10 integers for an array.");
    for (int i = 0; i < size; i++) {
        //printf ( "Enter integer %d:  ", i+1);
        array[i] = promptForInts(i+1);
    }
    printf ("\n");

    // Find sum of 10 integers
    result = sum (array, size);
    printf ("Sum of 10 ints:  %d\n\n", result);
    
    // Print array before changes
    printf ("Array values before adjustment:\t");
    for (int i = 0; i < size; i++) {
        printf ("%d ", array[i]);
    }
    printf("\n");
    
    // Increment integers by random amount
    adjust (array, size);
    
    // Print array after changes
    printf ("Array values after adjustment:\t");
    for (int i = 0; i < size; i++) {
        printf ("%d ", array[i]);
    }
    printf("\n");
    
    puts("Done\n");
    return 0;
}
