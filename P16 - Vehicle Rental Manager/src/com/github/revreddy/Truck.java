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


// Subclass for Trucks
public class Truck extends Vehicle{
    // ============== Fields ==================================//
    private double maxCargoWt;  // max cargo weight

    // ============== Constructors =============================//
    public Truck() {
        super();
        maxCargoWt = -1;
    }
    public Truck(String mk, String mod, int yr, String stat, int ID, double rte, double maxCargoWeight) {
        super(mk,mod,yr,stat,ID,rte);
        maxCargoWt = maxCargoWeight;
    }

    // ============== Methods ==================================//
    public Vehicle display() {
        System.out.println("\nTruck details: ");
        super.displayBasics();
        System.out.println("\tMax Cargo Wt: " + maxCargoWt);
        return this;
    }
}
