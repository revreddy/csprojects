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


// Subclass for Cars
public class Car extends Vehicle{
    // ============== Fields ==================================//
    private String bodyType; // stores body style (e.g. sedan, coupe)

    // ============== Constructors =============================//
    public Car() {
        super();
        bodyType = null;
    }
    public Car(String mk, String mod, int yr, String stat, int ID, double rte, String bdyType) {
        super(mk,mod,yr,stat,ID,rte);
        bodyType = bdyType;
    }

    // ============== Methods ==================================//
    public Vehicle display() {
        System.out.println("\nCar details: ");
        super.displayBasics();
        System.out.println("\tBody Type: " + bodyType);
        return this;
    }
}
