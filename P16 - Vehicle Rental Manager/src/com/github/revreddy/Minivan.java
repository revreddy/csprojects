package com.github.revreddy;

//
// Project 16 - Vehicle Rental Manager
//     Store vehicle details and status for a rental car facility
//     using a command line inferface and linked list
//     to manipulate the data.
//
// Created by Revanth Reddy 2/15/2015
// Language: Java
// Environ: Mac OSX 10.10, IntelliJ IDEA 14.0.3, Java 8
//
// Copyright (c) 2015 Revanth Reddy. All rights reserved.
//


// Subclass for Minivans
public class Minivan extends Vehicle {
    // ============== Fields ==================================//
    private double length;      // body length of minivan
    private double width;       // body width of minivan

    // ============== Constructors =============================//
    public Minivan() {
        super();
        length = width = -1;
    }
    public Minivan(String mk, String mod, int yr, String stat, int ID, double rte, double Length, double Width) {
        super(mk,mod,yr,stat,ID,rte);
        length = Length;
        width = Width;
    }

    // ============== Methods ==================================//
    public Vehicle display() {
        System.out.println("\nMinivan details: ");
        super.displayBasics();
        System.out.println("\tLength:    " + length);
        System.out.println("\tWidth:     " + width);
        return this;
    }
}
