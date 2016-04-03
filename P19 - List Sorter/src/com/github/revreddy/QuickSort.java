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

public class QuickSort implements SortMethod {
    // Source code: http://www.csc.depauw.edu/~dharms/CS1-Myro-Java/
    //              BlueJ_Projects-F11/SortingAndSearching/QuickSort.java

    // Quick sort method used to make initial recursive call.
    public ArrayList<Integer> sort(ArrayList<Integer> arr)
    {
        quickSort( arr, 0, arr.size()-1 );
        return arr;
    }

    // Recursive quicksort function
    private void quickSort( ArrayList<Integer> arr, int lo, int hi )
    {
        int pivot;

        if( lo >= hi )
            return;

        pivot = partition( arr, lo, hi );
        quickSort( arr, lo, pivot-1 );
        quickSort( arr, pivot+1, hi );
    }

    /**
     * Partition the array segment around a pivot point
     *
     * @param arr The array containing ints
     * @param lo The index of the first element in the partition range
     * @param hi The index of the last element in the partition range
     *
     * @return The index containing the pivot point.  All elements of arr[lo..pivot-1] will
     *  be <= arr[pivot] and all elements in arr[pivot+1..hi] will be > arr[pivot]
     */
    private int partition(ArrayList<Integer> arr, int lo, int hi )
    {
        int pivotVal = arr.get( lo );
        int right = hi;
        int left = lo + 1;

        while( left <= right )
        {
            // move left toward the right until it gets to the first value
            // greater than pivot
            while( left <= hi && arr.get(left) <= pivotVal )
                left++;

            // move right toward the left until it gets to the first value
            // less than or equal to the pivot
            while( arr.get(right) > pivotVal )
                right--;

            // if left and right haven't crossed, swap the elements and increment/decrement
            // left and right
            if( left < right )
            {
                //swap( arr, left, right );
                int temp = arr.get(left);
                arr.set( left, arr.get(right) );
                arr.set( right, temp );
                left++;
                right--;
            }
        }

        // the pivot position is where right points right now, so swap the pivot value there
        //swap( arr, lo, right );
        int temp = arr.get(lo);
        arr.set( lo, arr.get(right) );
        arr.set( right, temp );

        // right contains the pivot value
        return right;
    }
}
