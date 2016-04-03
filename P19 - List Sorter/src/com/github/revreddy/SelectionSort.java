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

public class SelectionSort implements SortMethod {
    // Source code: http://www.csc.depauw.edu/~dharms/CS1-Myro-Java/
    //              BlueJ_Projects-F11/SortingAndSearching/SelectionSort.java

    //Sorts an ArrayList in ascending order using selection sort
    public ArrayList<Integer> sort( ArrayList<Integer> arr )
    {
        for( int k = 0; k < arr.size()-1; k++ ) {
            // find the smallest value in arr[k..size-1]
            int minIndex = k;
            for (int j = k + 1; j < arr.size(); j++) {
                if (arr.get(j) < arr.get(minIndex)) {
                    minIndex = j;
                }
            }

            // swap arr[k] with arr[minIndex]
            int temp = arr.get(k);
            arr.set(k, arr.get(minIndex));
            arr.set(minIndex, temp);
        }
        return arr;
    }
}

