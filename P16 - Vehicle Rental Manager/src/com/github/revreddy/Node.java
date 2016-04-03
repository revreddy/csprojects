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


// Class for creating nodes to store vehicles in a linked list
public class Node {
    // ============== Fields ==================================//
    private Vehicle veh;       // stores vehicle in node
    private Node next;         // points to next node in linked list

    // ============== Constructors =============================//
    public Node() {
        veh = null;
        next = null;
    }
    public Node(Vehicle vehicle) {
        veh = vehicle;
        next = null;
    }

    // ============== Methods ==================================//
    public Vehicle getVeh() {
        return veh;
    }
    public Node getNext() {
        return next;
    }
    public void setVeh(Vehicle newVeh) {
        veh = newVeh;
    }
    public void setNext(Node newNext) {
        next = newNext;
    }
    public void displayNode() { // print details for vehicle stored in node
        veh.display();
    }

}
