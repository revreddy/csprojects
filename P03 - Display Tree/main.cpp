//
//  main.cpp
//  Project 3:  Display Tree
//      Implement adding elements to a min heap
//      Objective is to modify the displayQueue() to print the heap as a tree
//
//  Created by Dale Reed on 10/7/14.
//  Modified by Revanth Reddy
//  Language: C, C++
//  Envir: Mac OSX 10.10, Xcode 6.1
//  Tested on RHEL Server 5.11
//
//
/*  Running this program looks like
         Starting Heap program
         To build a Heap enter positive integer values, followed by -1
         1783 1776 1492 1804 1865 1945 1963 1918 2001 1941 -1
         
         1492
         1783 1776
         1804 1865 1945 1963
         1918 2001 1941
         
         Printing heap as tree...
         
                     __________1492__________
                    /                        \
                ___1783___                 ___1776___
               /          \               /          \
             1804         1865         1945         1963
            /    \       /
         1918    2001  2001
 
         Done with program...
 */

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

// define global constants and structures
#define MAX_SIZE 1000+1    // Add 1 because we start at position 1, not 0


/* Prints program info. No parameters or return values. */
void programInfo() {
    puts ("");
    puts ("**********************************");
    puts ("Author: Revanth Reddy");
    puts ("Project 3: Display Tree");
    puts ("**********************************\n");
}

// Display the queue, one level per line
void displayQueue( int q[], int size)
{
    int i;
    
    // Print heap in one level per line
    printf ("\n");
    printf ("Printing heap per level...\n");
    for(i = 1; i<size; i++) {
        // Display newline between levels if current value is power of 2
        //    logb gives floating point log with fractional remainder, however
        //    log2 does not keep the fractional part, so these two are equal
        //    when the argument is exactly a power of 2.
        if( logb(i) == log2(i)) {
            cout << endl;
        }
        cout << q[ i] << " ";
    }
    cout << endl << endl;   // make sure output buffer is flushed
    
    //////////////// print as tree code \\\\\\\\\\\\\\\\\\\\\\\\\\\\\

    // Find number of levels in heap
    int numLevels = (int)ceil(log2(size));
    //printf ("size = %d, numLevels = %d, log2 = %lf\n", size, numLevels, log2(size));
    
    if (numLevels > 5) { // Print message if the heap is too large to build tree
        printf ("Heap is too large to print as tree format in 80x50 window.");
        return;
    }
    
    printf ("Printing heap as tree...\n\n");
    
    int lowLevelSize = size - 1; // total number of elements in heap
    switch (numLevels) { // choose the branched based on the number of levels to display
        case 1:
            /*
            
            ####............................................................................. */
            
            cout << q[1] << endl;
            break;
        case 2:
            /*
             
            ...####..........................................................................
            ../...\..........................................................................
            ####...####...................................................................... */
            
            cout << setw(6) << q[1] << endl;                    //line 1 (level 1)
            cout << setw(3) << "/" << setw (4) << "\\" << endl; //line 2
            cout << q[2];                                       //line 3 (level 2)
            if (lowLevelSize >= 3) {
                cout << setw(6) << q[3];
            }
            break;
        case 3:
            
            /*
             .......___####___...............................................................
             ....../..........\..............................................................
             ....####.........####...........................................................
             .../....\......./....\..........................................................
             ####....####..####..####........................................................ */
            
            //line 1 (level 1, root)
            cout << setw(10) << "___" << setw(4) << q[1] <<  "___" << endl;
            
            //line 2
            cout << setw(7) << "/" << setw(11) << "\\" << endl;
            
            //line 3 (level 2)
            cout << setw(8) << q[2] << setw(13) << q[3] << endl;
            
            //line 4
            cout << setw(4) << "/";
            if (lowLevelSize >= 5) {
                cout << setw(5) << "\\";
            }
            if (lowLevelSize >= 6) {
                cout << setw(9) << "/";
            }
            if (lowLevelSize >= 7) {
                cout << setw(4) << "\\";
            }
            cout << endl;
            
            //line 5 (level 3)
            cout << setw(4) << q[4];
            if (lowLevelSize >= 5) {
                cout << setw(8) << q[5];
            }
            if (lowLevelSize >= 6) {
                cout << setw(6) << q[6];
            }
            if (lowLevelSize >= 7) {
                cout << setw(7) << q[7];
            }
            break;
            
        case 4:
            /*
             ........._______####_______.....................................................
             ......../..................\....................................................
             ....__####__............__####__................................................
             .../........\........../........\...............................................
             .####.......####......####......####............................................
             ./...\...../...\...../...\...../...\............................................
             ####.####.####.####.####.####.####.####.........................................
             */
            
            //line 1 (level 1, root)
            cout << setw(16) << "_______" << setw(4) << q[1] <<  "_______" << endl;
            
            //line 2
            cout << setw(9) << "/" << setw(19) << "\\" << endl;
            
            //line 3 (level 2)
            cout << setw(6) << "__" << setw(4) << q[2] << "__" <<  setw(14) << "__" << setw(4) << q[3] << "__" << endl;
            
            //line 4
            cout << setw(4) << "/" << setw(9) << "\\" << setw(11) << "/" << setw(9) << "\\" << endl;
            
            //line 5 (level 3)
            cout << setw(5) << q[4] << setw(11) << q[5] << setw(10) << q[6] << setw(10) << q[7] << endl;
            
            //line 6
            cout << setw(2) << "/";
            for (i = 9; i <= lowLevelSize && i <= 15; i++) {
                if (i % 2) { // if odd
                    cout << setw(4) << "\\";
                }
                else {
                    cout << setw(6) << "/";
                }
            }
            cout << endl;
            
            //line 7 (level 4)
            cout << setw(4) << q[8];
            for (i = 9; i <= lowLevelSize && i <= 15; i++) {
                cout << setw(5) << q[i];
            }
            cout << endl;
 
            break;
            
            
            
        case 5:
            /* the first five lines of the diagram below overlap for both 4 and 5 levels
             
             ...................._________________####_________________......................
             .................../......................................\.....................
             .........._______####_______......................_______####_______............
             ........./..................\..................../..................\...........
             .....__####__............__####__............__####__............__####__.......
             ..../........\........../........\........../........\........../........\......
             ..####......####......####......####......####......####......####......####....
             ../...\...../...\...../...\...../...\...../...\...../...\...../...\...../...\...
             ####.####.####.####.####.####.####.####.####.####.####.####.####.####.####.####.
             
             
             */
            
            //line 1 (level 1, root)
            cout << setw(37) << "_________________" << setw(4) << q[1] << "_________________" << endl;
            
            //line 2
            cout << setw(20) << "/" << setw(39) << "\\" << endl;
            
            //line 3 (level 2)
            cout << setw(17) << "_______" << setw(4) << q[2] << "_______";
            cout << setw(29) << "_______" << setw(4) << q[3] << "_______" << endl;
            
            //line 4
            cout << setw(10) << "/" << setw(19) << "\\";
            cout << setw(21) << "/" << setw(19) << "\\" << endl;
            
            //line 5 (level 3)
            cout << setw(7) << "__" << setw(4) << q[4] << "__" << setw (14) << "__" << setw(4) <<  q[5] << "__";
            cout << setw(15) << "__" << setw(4) << q[6] << "__" << setw (14) << "__" << setw(4) << q[7] << "__" << endl;
            
            //line 6
            cout << setw(5) << "/";
            for (i = 9; i <= 15; i++) {
                if (i % 2) { // if odd
                    cout << setw(9) << "\\";
                }
                else {
                    cout << setw(11) << "/";
                }
                if (i == 11)
                    cout << " ";
            }
            cout << endl;
            
            //line 7 (level 4)
            cout << setw(6) << q[8];
            for (i = 9; i <= 15; i++) {
                cout << setw(10) << q[i];
                if (i == 11)
                    cout << " ";
            }
            cout << endl;

            //line 8
            cout << setw(3) << "/";
            for (i = 17; i <= lowLevelSize && i <= 31; i++) {
                if (i % 2) { // if odd
                    cout << setw(4) << "\\";
                }
                else {
                    cout << setw(6) << "/";
                }
            }
            cout << endl;
            
            //line 9 (level 5)
            for (i = 16; i <= lowLevelSize && i <= 31; i++) {
                cout << setw(5) << q[i];
            }
            cout << endl;
            break;
    }
    
}

// return the index of the parent of index p
int parent( int p)
{
    // verify we're not trying to get the parent of the root
    if( p==1) {
        return -1;  // value signifying an error
    }
    else {
        return p / 2;  // integer division truncates
    }
}// end parent(...)


// return the index of the left child of index p
int leftChild( int p)
{
    return p * 2;
}//end leftChild(...)


// return the index of the right child of index p
int rightChild( int p)
{
    return (p * 2) + 1;
}// end rightChild(...)


// Swap values in queue at positions s and t
// This is a utility function for bubbleUp(...) shown below.
void swap( int q[],    // The queue, implemented as an array
          int s,      // Index of 1st element to be swapped
          int t)      // Index of 2nd element to be swapped
{
    int temp = q[ s];
    q[s] = q[t];
    q[t] = temp;
}//end swap(...)


// Take recently added element at end of the queue (at position qSize-1)
// and bubble it up the tree until its parent is smaller than it is.
void bubbleUp(int q[],     // The queue, implemented as an array
              int qSize)   // Size of the queue
{
    int p = qSize-1;       // Index of last actual element, since qSize is
    //    index of next open spot to store a value.
    // While we haven't bubbled all the way up to the root and
    //    current value at p is less than its parent
    while( (parent(p) != -1) && (q[p] < q[parent(p)]) ) {
        swap( q, p, parent(p));  // Swap elements p and parent(p) in queue q
        p = parent( p);          // Update current location of p, to keep
        //    bubbling upwards.
    }
}//end bubbleUp(...)


// insert element x into q, updating the size of the queue
void qInsert( int q[],     // The queue, implemented as an array
             int &qSize,  // Size of the queue; Gets updated
             int x)       // element to be inserted
{
    // Sanity check for maximium size
    if( qSize >= MAX_SIZE) {
        cout << "***Error: queue size exceeded.  Exiting program." << endl;
        exit( -1);
    }
    else {
        q[ qSize] = x;        // add element to end of queue
        qSize++;              // incrementing queue size
        bubbleUp( q, qSize);  // Bubble it up into place
    }
}// end qInsert(...)


int main() {
    programInfo();
    
    // declare the priority queue
    int q[ MAX_SIZE];
    int inputValue;
    
    int qSize = 1;  // Position to insert next element.  We'll ignore position 0
    
    cout << "Starting Heap program \n";
    cout << "To build a Heap enter positive integer values, followed by -1 \n";
    while (inputValue != -1) {
        cin >> inputValue;
        if( inputValue != -1) {
            qInsert( q, qSize, inputValue);
        }
    }
    
    // Display the values in the queue, by level
    displayQueue(q, qSize);
    
    cout << "\n\nDone with program...\n";
    return 0;
}//end main()
