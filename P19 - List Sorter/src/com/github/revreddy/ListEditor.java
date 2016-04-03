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

import java.io.FileNotFoundException;
import java.lang.String;
import java.util.Scanner;
import java.util.ArrayList;
import java.io.File;

public class ListEditor {
    // Fields
    private ArrayList<Integer> values;


    // Constructor
    public ListEditor (){
        values = new ArrayList<Integer>();
    }


    // Print user interface options
    public void printCmds() {
        System.out.println("\n---------------------------------------");
        System.out.println("Choose from the following options: ");
        System.out.println("\tc - Reset list to empty");
        System.out.println("\ta <first-int> ... <nth-int> - Append integers to front of list");
        System.out.println("\tr <filename.txt> - Append integers from file to front of list");
        System.out.println("\td - Prints entire list into standard output stream");
        System.out.println("\ts - Sort based on length of list");
        System.out.println("\tq - Quit");
        System.out.print("Command: ");
    }


    // Resets the list to empty state
    public void commandC (ListEditor list) {
        list.values = new ArrayList<Integer>();  // initializes new ArrayList, leaving old array for garbage collection
        System.out.println("List is now reset.");
    }


    // Parses ints from command line and appends to front of list
    public void commandA (String line) {
        line = line.trim();                     // removes all leading and trailing whitespace
        String[] arr = line.split(" ");         // takes each number input and saves to array index

        for (String elem : arr) {
            this.values.add(0, Integer.parseInt(elem)); // convert each number string to integer
            // and append to list.
        }
    }


    // Reads ints from file and appends to the front of list
    public void commandR (String filename) throws FileNotFoundException  {
        System.out.print("Reading integers from " + filename + "...");

        Scanner scanner = new Scanner(new File(filename));

        while(scanner.hasNextInt()) { // while there is another int in buffer
            this.values.add(0,scanner.nextInt()); // fetch next int and append to list
        }
        System.out.print("done.\n");
    }


    // Print all values current in the list to the standard output stream
    public void commandD () {

        if (this.values.size() == 0) {
            System.out.println("Nothing to display. List is empty.");
        }
        else {
            System.out.println("Displaying current list...");
            for (Integer value : this.values) {
                System.out.print(value + " ");
            }
        }
    }


    // Sorts the list using a method determined based on current list size
    // (Note: the given implementation requirements did not specify what sizes parameters to use.
    //    Therefore, I have specified the following ranges below. Kept the numbers small for simplicity.
    //    Adjust the if statement parameters as desired for custom ranges.)
    // 0 - 20 -> selection sort - O(n^2)
    // 21 - 40 -> insertion sort - O(n^2)
    // >40 -> quicksort - O(nlogn)
    public void commandS () {
        int size = this.values.size();
        System.out.println("Current list size is " + size + ".");
        if (size <= 20) {
            System.out.print("Performing Selection Sort...");
            SortMethod s = new SelectionSort();
            s.sort(this.values);
        }
        else if (size > 20 && size <= 40) {
            System.out.print("Performing Insertion Sort...");
            SortMethod s = new InsertionSort();
            s.sort(this.values);
        }
        else { // if (size > 40)
            System.out.print("Performing Quicksort...");
            SortMethod s = new QuickSort();
            s.sort(this.values);
        }
        System.out.print("done.\n");
    }


    // Client
    public static void main(String[] args) throws FileNotFoundException  {
        ListEditor list = new ListEditor();     // create list object

        System.out.println("List Sort Program");
        while (true) {
            // Print menu and parse command
            list.printCmds();
            Scanner s = new Scanner(System.in);
            String cmd = s.next();

            // Execute command (see printCmds() methods for details on what each command does)
            if (cmd.equals("q")) {
                System.out.println("Exiting List Sort Program. Goodbye.");
                System.exit(0);
            } else if (cmd.equals("c")) {
                list.commandC(list);
            } else if (cmd.equals("a")) {
                String line = s.nextLine();
                list.commandA(line);
            } else if (cmd.equals("r")) {
                String filename = s.next();
                list.commandR(filename);
            } else if (cmd.equals("d")) {
                list.commandD();
            } else if (cmd.equals("s")) {
                list.commandS();
            } else {
                System.out.println("Error: Invalid option. Retype command.");
            }
        }
    }
}
