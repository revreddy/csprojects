package com.github.revreddy;

//
// Project 19 - List sorter
//      A simple command line interface to allow user to
//      choose options to create and sort a list of integers.
//      This program implements the Strategy Pattern approach
//      involving one main client class and three sort classes
//      implementing an interface.
//
// Created by Revanth Reddy 3/12/2015
// Language: Java
// Environ: Mac OSX 10.10, IntelliJ IDEA 14.0.3, Java 8
//
// Copyright (c) 2015 Revanth Reddy. All rights reserved.
//

import java.util.ArrayList;

public class InsertionSort implements SortMethod{
    // Source code: http://www.csc.depauw.edu/~dharms/CS1-Myro-Java/
    //              BlueJ_Projects-F11/SortingAndSearching/InsertionSort.java
    
    public ArrayList<Integer> sort(ArrayList<Integer> arr) {
        int val;
        int holePos;

        // At the beginning of each iteration arr[0..k-1] has been sorted, and the loop then
        // inserts element k into its proper place
        for( int k=1; k<arr.size(); k++ )
        {
            // make a copy of the value to insert
            val = arr.get(k);

            // The kth position is where the "hole" starts
            holePos = k;

            // Move the "hole" left until we either get the the end of the array
            // or the element left of the hole is <= to the value we're inserting
            while( holePos > 0 && arr.get(holePos-1) > val )
            {
                // move the hole to the left
                arr.set( holePos, arr.get(holePos-1) );
                holePos--;
            }

            // copy the value into the hole
            arr.set( holePos, val );
        }
        return arr;
    }
}
