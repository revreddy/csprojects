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


// Superclass for vehicles
public abstract class Vehicle {
    // ============== Fields ==================================//
    private String make;    // e.g. Ford, Toyota
    private String model;   // e.g. Focus, Camry
    private int year;       // Model year
    private String status;  // available, rented, repairs
    private int id;         // vehicle identification number
    private double rate;    // daily rental rate

    // ============== Constructors =============================//
    public Vehicle() {
        make = model = null;
        year = 1900;
        status = null;
        id = -1;
        rate = -1.0;
    }
    public Vehicle(String mk, String mod, int yr, String stat, int ID, double rte) {
        make = mk;
        model = mod;
        year = yr;
        status = stat;
        id = ID;
        rate = rte;
    }

    // ============== Methods ==================================//
    public String getMake(){
        return make;
    }
    public String getModel() {
        return model;
    }
    public int getId() {
        return id;
    }
    public String getStatus(){
        return status;
    }
    public void setStatus(String newStatus) {
        status = newStatus;
    }

    public abstract Vehicle display();

    // Prints common information of a vehicle
    public void displayBasics() {
        System.out.println("\tMake:      " + make);
        System.out.println("\tModel:     " + model);
        System.out.println("\tYear:      " + year);
        System.out.println("\tStatus:    " + status);
        System.out.println("\tID:        " + id);
        System.out.println("\tRate:      " + rate);
    }

}
