//
//  main.cpp
//  Project 4 - Insite Logistics
//      Calculate the best cities to place distribution centers based on the
//      average distance to all other cities.
//
//  Created by Revanth Reddy on 11/12/14.
//  Language: C, C++
//  Envir:  Mac OSX Yosemite, Xcode 6.1
//  Tested on RHEL Server 5.11
//
//  Copyright (c) 2014 Revanth Reddy. All rights reserved.
//
//  This program incorporates code from Dijkstras.cpp and combinations.cpp
//  that were made by professor and others.
 
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <string>
#include <stdio.h>
using namespace std;

#define HARD_CODED_VALUES false  // build graph using hard-coded values
#define INSERT_IN_ORDER true    // adjacency lists will have vertices in ascending order
#define MAX_INT	9999   	    // Big enough to be "big" but not overflow when used in arithmetic.
#define	MAX_VERTICES 101	    // Max. number of vertices. 101 for 100 vertices, in case numbering starts at 1

// Adjacencyvertex list Node struct, also storing weights
struct Node {
    int vertex;		// Adjacent vertex
    int weight;		// Edge weight, if anvertex
    Node *pLink;	// Next edge in list
};

// Compute the lowest average distances for each combination of cities
// @param {int} v - array holds all the combinations
// @param {int} start - first city to begin making combinations with
// @param {int} k - keeps track of how many numbers grabbed for combination of size maxk
// @param {int} maxk - number of cities to compare at a time in each combination
// @param {int} distanceMatrix - 2d array storing all the distances between cities
// @param {int} minAvg - store the lowest average distance computed among all combinations
// @param {int} bestCombin - store the city numbers of lowest average combination
void combinations (int v[], int start, int n, int k, int maxk, int nCities,
                   int **distanceMatrix, int &minAvg, int *&bestCombinNum) {
    int i, j;                           // loop counters
    int currDistance = -1;              // current distance value pulled from matrix
    int currMinInColumn = MAX_INT;      // lowest distance per column of matrix per combination
    int sumComb = 0;                    // sum of lowest distance per column of matrix per combination
    int avgComb = 0;                    // avg distance for the current combination
    
    // k here counts through positions in the maxk-element v. if k > maxk,
    //then the v is complete and we can use it.
    int *combinArr = new int[maxk+1]; //used to store combinations
    if (k > maxk) {
        for (i = 1; i <= maxk; i++) {
            combinArr[i] = v[i]; // copy combination into another array
        }
        
        // i is column of matrix, j is row of matrix
        for (i = 1; i <= nCities; i++) {
            for (j = 1; j <= maxk; j++) {
                currDistance = distanceMatrix[combinArr[j]][i]; // fetch distance for city
                if (currDistance < currMinInColumn) { // compare to min of column
                    currMinInColumn = currDistance;   // overwrite current min if lower
                }
            }
            sumComb += currMinInColumn; // accumulator to store the total distances for the comb
            currMinInColumn = MAX_INT;  // reset values for use by next comb
            currDistance = -1;
        }
        avgComb = sumComb / nCities;    // calculate the average distance for the comb
        if (avgComb < minAvg ) {        // if less than existing lowest avg
            minAvg = avgComb;           // overwrite to new lowest avg
            for (i = 1; i <= maxk; i++) // store the comb city numbers for new lowest avg
                bestCombinNum[i] = combinArr[i];
        }
        delete[] combinArr;             // free memory
        return;
    }
    
    // for this k'th element of the v, try all start..n elements in that position
    for (i=start; i<=n; i++) {
        v[k] = i;
        // recursively generate combinations of integers from i+1..n
        combinations (v, i+1, n, k+1, maxk, nCities, distanceMatrix, minAvg, bestCombinNum);
    }

}

// Implement modified Prim's algorithm to execute Dijkstra's Algorithm
// The prims portion of code is modified from Steven Skiena's "Algorithm Design Manual", 2008
//     http://www3.cs.stonvertexbrook.edu/~skiena/algorist/book/programs/prim.c
//
// This is a greedvertex algorithm that does the following:
//    Select some starting point vertex s
//    while( there are still non-tree vertices) {
//       Select the edge with min weight between a tree and non-tree vertex
//       Add the newly selected edge and vertex to the tree
void dijkstras(
               Node *graph[], 		  // Graph represented by adjacency lists
               int **distanceMatrix,
               int start, 			  // Starting node for building min spanning tree
               int nCities) // How many vertices are in tree
{
    Node *pTemp;					// temporary graph node pointer
    bool isInTree[nCities];         // Marks if vertex is in the tree
    int parent[nCities];            // Array of parents representing connection into spanning tree
    int distance[nCities];          // Min distance found so far for each vertex
    int currentVertex;				// current vertex to process
    int adjacentVertex;				// Adjacent vertex
    int weight;						// edge weight
    int shortestNewNodeDistance;	// shortest distance of some new node from current node
    
    // Initialize all vertices as not being in the tree, having max distance and no parent.
    for (int i = 1; i <= nCities; i++) {
        isInTree[i] = false;
        distance[i] = MAX_INT;
        parent[i] = -1;
    }
    
    // Set values for starting node
    distance[start] = 0;
    currentVertex = start;
    
    // main loop, continued until all vertices are handled
    while (isInTree[ currentVertex] == false) {
        isInTree[ currentVertex] = true;	// Include current vertex into tree
        
        // Examine in turn each edge incident to the current vertex
        pTemp = graph[ currentVertex];	     // Get first edge
        while (pTemp != NULL) {
            adjacentVertex = pTemp->vertex;  // Get vertex on othe end of this edge
            weight = pTemp->weight;			 // Get weight of this edge
            
            // If this is a newly reachable vertex
            /*
             //  These next few lines are the original Prim's algorithm code
             if ((distance[ adjacentVertex] > weight) && (isInTree[ adjacentVertex] == false)) {
             // Store new lower-cost distance and spanning tree connection point
             distance[ adjacentVertex] = weight;
             parent[ adjacentVertex] = currentVertex;
             }
             */
            
            // The lines below are modified from the Prim's version (see above) to
            // implement length from the start, not just local length, to become Dijkstra's.
            if (distance[ adjacentVertex] > (distance[currentVertex] + weight) ) {
                // Store new lower-cost distance and spanning tree connection point
                distance[ adjacentVertex] = distance[currentVertex] + weight;
                parent[ adjacentVertex] = currentVertex;
            }
            pTemp = pTemp->pLink;  // advance to next edge incident on currentVertex
        }
        
        // Find next vertex to be processed.  It should be the closest one not already in tree.
        currentVertex = 1;
        shortestNewNodeDistance = MAX_INT;		  // Initialize to some large number
        // Examine each vertex in graph
        for (int i=1; i<= nCities; i++) {
            if ((isInTree[i] == false) && (shortestNewNodeDistance > distance[i])) {
                // This ith vertex is not yet in tree and is closest so far
                shortestNewNodeDistance = distance[i];  // set new shortest distance
                currentVertex = i;                      // set new closest vertex
            }
        }
    }
    
    // Store distance from start to each other node
    for( int i = 1; i <= nCities; i++) {
        // Distance from city5 to city3 will be stored in row 5, column 2
        // Row and column 0 are empty
        distanceMatrix[start][i] = distance[i];
        distanceMatrix[i][start] = distance[i];
    }
    
}//end dijkstras(...)


// Display program information
void programInfo() {
    puts ("");
    puts ("**********************************");
    puts ("Author: Revanth Reddy");
    puts ("Project 4: Alibamazon");
    puts ("**********************************\n");
}

// Display adjacency lists associated with each vertex
void displayAdjacencyLists( Node *graph[], string *cityNames, int nCities) {
    Node * pTemp;   // Array of adjacency list heads
    
    cout << endl    // table formatting
    << "Vertex  City                     Adjacency List \n"
    << "------  -----------------------  -------------- \n"
    << endl;
    
    // Display adjacency lists for non-empty rows
    for( int i = 1; i <= nCities; i++) {
        if(graph[i] != NULL) {
            // Display vertex number
            printf("%3d     ", i);
            
            // Display city name
            cout << left << setw(25) << cityNames[i];
            
            // Display associated list
            pTemp = graph[i];
            while(pTemp != NULL) {
                cout << pTemp->vertex << " ";
                pTemp = pTemp->pLink;
            }//end while( pTemp...
            cout << endl;
            
        }
    }
    
    cout << endl;
}//end displayAdjacencyLists(...)


// Display the adjacency matrix
// @param {int} distanceMatrix - 2d array storing all the distances between cities
// @param {int} nCities - total number of cities
void displayAdjacencyMatrix( int **distanceMatrix, int nCities) {
    int i, j;
    for (i = 1; i <= nCities; i++) {
        cout << setw(3)<< left << i << ":  " ;
        for ( j = 1; j <= nCities; j++) {
            cout << setw(5) << distanceMatrix[i][j];
        }
        cout << endl;
    }
    cout << endl;
} // end displayAdjacencyMatrix(...)


// Sorts the best combination of cityNames to be printed in alpha order
// @param: {string} arr - pass by reference array containing city names to sort
// @param: {int} n - size of array
void selectionSort(string *&arr, int n) {
    int i, j, minIndex, result;
    string temp;
    for (i = 1; i < n; i++) {
        minIndex = i;
        for (j = i + 1; j < n+1; j++) {
            // use c_str() to convert string to c-string in order to be able to use strcmp
            // strcmp will return a negative value when str1 is lower than str2
            result = strcmp(arr[j].c_str(), arr[minIndex].c_str());
            if (result < 0) {
                minIndex = j;
            }
        }
        // swap values
        if (minIndex != i) {
            temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
} // end selectionSort(...)


// Store a node into an adjacency list in ascending order.
// This code is only used if  INSERT_IN_ORDER  is set to true at the top
// of the program, and is then called from function:  storePairIntoAdjacencyLists(...)
void insertIntoListInOrder(
                           Node *pNewNode,    // New Node to be inserted in order into list
                           Node * &pHead)     // Head of the list, which may change
{
    Node *pTemp = pHead;
    int newVertex = pNewNode->vertex;
    
    // Check to see if list is empty
    if (pHead == NULL)  {
        // list is empty, so make this the first node
        pHead = pNewNode;
    }
    else  {
        // list is not empty
        pTemp = pHead;
        
        // Iterate through list to find insertion location
        while ( (pTemp->pLink != NULL) && (newVertex > pTemp->pLink->vertex) )  {
            pTemp = pTemp->pLink;        // advance to next node
        }
        
        // See if number goes at front of list
        if ( newVertex < pHead->vertex)  {
            // insert at front of list
            pNewNode->pLink = pHead;
            pHead = pNewNode;
        }
        else {
            // Node goes in the middle or at the end of list
            // Insert after node pointed to by pTemp
            pNewNode->pLink = pTemp->pLink;   // Redundant assignment of NULL
            //    if appending to end of list
            pTemp->pLink = pNewNode;
        }
    } // end else
}//end insertIntoListInOrder(...)


// Store vertex1 into the adjacency list for vertex2.
//    The macro  INSERT_IN_ORDER  defined at the top of the program determines
// whether vertices on each adjacency list are stored in LIFO order or in
// ascending order.
void storePairIntoAdjacencyLists(
                                 Node *graph[],  // Array of adjacency list heads
                                 int vertex1,    // First vertex of edge being added
                                 int vertex2,    // Second vertex of edge being added
                                 int weight)     // Weight of edge being added
{
    // Place vertex 1 in vertex 2's adjacency list
    Node *pTemp = (Node *) malloc( sizeof( Node) );
    pTemp->vertex = vertex1; // Store vertex number
    pTemp->weight = weight;  // Store the weight
    pTemp->pLink = NULL;     // If this will be 1st node, ensure NULL termination
    
    // The macro at the top of the program determines which of the following
    // two get executed.  When first deciphering this program I recommend
    // you use the code in the "else" part.
    if( INSERT_IN_ORDER) {
        // Vertices on adjacency lists are stored in ascending order.
        insertIntoListInOrder( pTemp, graph[ vertex2]);
    }
    else {
        // Vertex vertex1 (now stored in pTemp) is prepended to front of the
        // adjacency list for vertex2, giving LIFO order.
        pTemp->pLink = graph[ vertex2]; // Set link to current head of adj. list
        graph[ vertex2] = pTemp;        // New node becomes new head of list
    }
}//end storePairIntoAdjacencyLists(...)


// Store vertex1 into the adjacency list for vertex2, and vertex2 into the
// adjacency list for vertex1.
void storeEdgeIntoGraph(
                        Node *graph[],   // Array of adjacency list heads
                        int vertex1,     // First vertex of edge being added
                        int vertex2,     // Second vertex of edge being added
                        int weight)      // Weight of edge
{
    // Store vertex 1 onto the adjacency list for vertex 2.
    storePairIntoAdjacencyLists( graph, vertex1, vertex2, weight);
    
    // Store vertex 2 onto the adjacency list for vertex 1.
    storePairIntoAdjacencyLists( graph, vertex2, vertex1, weight);
}//end storeEdgeIntoAdjacencyLists(...)


// Create graph adjacency lists, either using user input or hard-coding.
void createAdjacencyLists(
                          Node *graph[], // Array of adjacency lists, representing the graph
                          int &nCities)	 // Number of vertices in the graph.
{
    // Initialize all adjacency lists to NULL
    for (int i = 0; i < nCities; i++) {
        graph[i] = NULL;
    }
    if( HARD_CODED_VALUES) {
        // Each pair added to the graph contains vertex1, vertex2, weight
        storeEdgeIntoGraph( graph, 1,2,4);
        storeEdgeIntoGraph( graph, 2,3,4);
        storeEdgeIntoGraph( graph, 3,4,4);
        storeEdgeIntoGraph( graph, 4,5,1);
        storeEdgeIntoGraph( graph, 5,6,4);
        storeEdgeIntoGraph( graph, 6,1,6);
        storeEdgeIntoGraph( graph, 1,7,5);
        storeEdgeIntoGraph( graph, 2,7,7);
        storeEdgeIntoGraph( graph, 3,7,2);
        storeEdgeIntoGraph( graph, 3,5,2);
        storeEdgeIntoGraph( graph, 5,7,6);
        storeEdgeIntoGraph( graph, 6,7,3);
    }
    else {
        // File input to fetch city names
        ifstream inStream;
        inStream.open( "cityDistancesFull.txt"); // USER MAY CHANGE INPUT FILE NAME IF NEEDED
//        inStream.open( "cityDistancesSmall.txt");
        assert(!inStream.fail() );  // make sure file open was OK
        
        // First read the number of distance pairs from the first line
        int howManyPairs;
        int fromCity, toCity, distance;
        inStream >> howManyPairs;
        
        // Now read the distance pairs and store in adjacency lists
        string strTemp;
        getline(inStream, strTemp);
        for( int i = 0; i < howManyPairs; i++) {
            inStream >> fromCity >> toCity >> distance;
            //cout << fromCity << " " << toCity << " " << distance << endl;
            storeEdgeIntoGraph(graph, fromCity, toCity, distance);
        }
        inStream.close();
    }
}//end createAdjacencyLists(...)


// Reads the input files
// @param {string} cityNames - array to store the list of city names from input file
// @param {string} nCities - int variable to store the total number of cities
void createCityList (string *&cityNames, int &nCities) {
    ifstream inStream;
    inStream.open( "cityNamesFull.txt");            // USER MAY CHANGE INPUT FILE NAME IF NEEDED
//    inStream.open( "cityNamesSmall.txt");
    assert( ! inStream.fail() );
    
    // First read the number of cities from the first line, then read the city names.
    inStream >> nCities;
    
    // Allocate cityNames array based on number of cities
    cityNames = new string[nCities+1];          // n+1 indices, index 0 empty, index 1 is city 1
                                                // matches cityNames[1] ::: graph[1]

    // Read the city names and store in array
    // clears first line with number of cities
    string strTemp;
    getline(inStream, strTemp);                 // skips the first line with the number
    for( int i = 1; i <= nCities; i++) {        // starts reading city names from second line
        getline(inStream, strTemp);
        strTemp.erase(remove(strTemp.begin(), strTemp.end(), '\r'), strTemp.end() ); // removes '\r'
        cityNames[i] = strTemp;                 // stores parsed string into the list
    }
    inStream.close();
} //end createCityList(...)


//-----------------------------------------------------------------------------//
int main()
{
    // Display program info
    programInfo();
    
    // Create array list of cities names
    int i, k;
    int nCities = 0;                    // Number of cities on the list
    string *cityNames;
    createCityList (cityNames, nCities);
    
    // Create map of cities in form of adjacency list
    Node **graph = new Node*[nCities+1];
    for (i = 0; i <= nCities; i++)
        graph[i] = NULL;
    createAdjacencyLists(graph, nCities); // cities stored in indices 1 through nCities+1
    //displayAdjacencyLists(graph, cityNames, nCities); // use to print list of city names

    // Allocate 2d array to hold the distances for all combinations of city1 to city2
    int **distanceMatrix = new int*[nCities+1];  // n + 1 rows
    for(i = 1; i <= nCities; i++)                // start i = 1 = city1, so row 0 is unused
        distanceMatrix[i] = new int[nCities+1];  // n + 1 columns (column 0 will be empty)
    
    // Create the min cost spanning tree using Dijkstra's algorithm for each city
    // and store values in an adjacency matrix
    for (i = 1; i <= nCities; i++) {
         dijkstras(graph, distanceMatrix, i, nCities);
    }
    //displayAdjacencyMatrix(distanceMatrix, nCities); // use to print matrix
    
    // User input prompt
    int maxk, minAvg, start;
    start = 1;
    minAvg = MAX_INT;               // set to 9999, so it will become lower during use
    
    cout << "Enter the maximum number of cities to compute: ";
    cin >> maxk;                    // max combination of cities to compute
    //maxk = 5;                     // hardcoded value for debugging
    cout << endl;
    
    // Prepare output table
    cout << setw(2) << "#" << setw(7) << "Avg" << setw(10)<<  "Cities" << endl; // table formatting
    cout << "---  ------  -----------------" << endl;;                          // table formatting
    
    // Create arrays to hold best combination
    int *bestCombinNum = new int[maxk+1];           // array to hold combination of city nums for lowest avg
    string *bestCombinCities = new string[maxk+1];  // array to hold combination of city names that
                                                                            // correspond to bestCombin
    // Find best cities based on avg distance for k=1 city to maxk cities
    for (k = 1; k <= maxk; k++) {
        int *v = new int[250000]; // allocate memory for v
        for (i = 0; i < 250000; i++) {
            v[i] = 0;
        }
        
        // Compute lowest average distance for each k cities and print the avg distance value
        combinations(v, start, nCities, start, k, nCities, distanceMatrix, minAvg, bestCombinNum);
        cout << " " << k << "    " << setw(7) << left << minAvg;
        
        // Match each combination city nums to their city names and store in an array
        for (i = 1; i <= k; i++) {
            bestCombinCities[i] = cityNames[bestCombinNum[i]];
        }
        // Sort the city names in alpha order
        selectionSort(bestCombinCities, k);
        for (i = 1; i <= k; i++) {
            cout << bestCombinCities[i] << "; "; // print the city names in combination
        }
        cout << endl;
        delete []v; // free memory for v
    }
    
    
    //Free memory
    delete[] bestCombinNum;
    for(i = 1; i <= nCities; i++) // frees adjacency matrix holding all the distances for each city
        delete[] distanceMatrix[i];
    delete[] distanceMatrix;
    
    Node *currHead;
    for (i = 1; i <= nCities; i++) { // frees linked list nodes of the adjacency list for each city
        Node *toDelete;         // must declare inside loop b/c free will remove the pointer as well
        currHead = toDelete = graph[i];
        while (currHead != NULL) {
            currHead = currHead->pLink;
            free(toDelete);
            toDelete = currHead;
        }
    }
    free(graph);
    
    cout << "Done." << endl << endl;
    return 0;
}//end main()
