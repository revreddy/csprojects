package com.github.revreddy;

import java.lang.String;
import java.util.Scanner;

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


// Provide a linked list client to create the database for holding
// all the vehicles for the user
public class LList {
    // ============== Fields ==================================//
    private Node head;  // points to head of linked list
    private Node tail;  // points to tail of linked list

    // ============== Constructors =============================//
    public LList() {
        head = tail = null;
    }

    // ============== Methods ==================================//

    // Get pointer to last node
    public Node getTail(Node n) {
        while(n.getNext() != null) { // traverse through linked list to last node
            n = n.getNext();
        }
        return n;
    }


    // Create new node for vehicle and append to linked list
    public LList insert(Vehicle v) {
        if (head == null) {             // if list is empty
            head = tail = new Node(v);  // point head and tail to it
        }
        else {                          // if list has at least 1 node
            tail.setNext(new Node(v));  // append node to end of list
            tail = tail.getNext();
        }
        return this;
    }

    // Print user interface options
    public void printCmds() {
        System.out.println("\n---------------------------------------");
        System.out.println("Choose from the following options: ");
        System.out.println("\tv - Add new vehicle to database");
        System.out.println("\tc - Change vehicle status");
        System.out.println("\td - Reset database to empty state");
        System.out.println("\tl - List all vehicles in database");
        System.out.println("\ta - List all vehicles available for renting");
        System.out.println("\ts - Sort database alphabetically by make and model");
        System.out.println("\tq - Quit");
        System.out.print("Command: ");
    }


    // Prompt for use to provide new vehicle details and add to database
    public Vehicle commandV() {
        Scanner s = new Scanner(System.in);
        System.out.println("Provide the following vehicle info...");

        System.out.print("Enter make: ");     // Prompt user for input
        String make = s.next(); s.nextLine(); // Parse input and clear buffer

        System.out.print("Enter model: ");
        String model = s.next(); s.nextLine();

        System.out.print("Enter model year: ");
        int year = s.nextInt(); s.nextLine();

        System.out.print("Enter status ('available', 'rented', 'repairs'): ");
        String status = s.next(); s.nextLine();

        System.out.print("Enter vehicle ID: ");
        int id = s.nextInt(); s.nextLine();

        System.out.print("Enter daily rate: ");
        double rate = s.nextDouble(); s.nextLine();

        System.out.println("Choose type of vehicle:");
        System.out.println("\tc - Car");
        System.out.println("\tt - Truck");
        System.out.println("\tm - Minivan");
        System.out.print("Vehicle type: ");
        String type = s.next(); s.nextLine();

        Vehicle newVehicle = null;
        if (type.equals("c")) {  // For car
            // Prompt for body type, then create a car object
            System.out.print("Enter body type ('sedan', 'coupe', etc): ");
            String bodyType = s.next(); s.nextLine();
            newVehicle = new Car(make, model, year, status, id, rate, bodyType);
        } else if (type.equals("t")) { // For truck
            // Prompt for max cargo weight, then create truck object
            System.out.print("Enter max cargo weight: ");
            double maxCargoWt = s.nextDouble(); s.nextLine();
            newVehicle = new Truck(make, model, year, status, id, rate, maxCargoWt);

        } else if (type.equals("m")) { // For minivan
            // Prompt for length and width, then create minivan object
            System.out.print("Enter body length: ");
            double length = s.nextDouble(); s.nextLine();
            System.out.print("Enter body width: ");
            double width = s.nextDouble(); s.nextLine();
            newVehicle = new Minivan(make, model, year, status, id, rate, length, width);

        } else {
            System.out.println("Error: Invalid option.");
        }
        return newVehicle;
    }


    // Print details for all vehicles in the database
    public void commandL() {
        if (head == null) { // if list is empty, give feedback and do nothing
            System.out.println("Database is empty");
        }
        for (Node n = head; n != null; n = n.getNext()) { // else traverse list and print each node
            n.displayNode();
        }
    }


    // Change status for particular vehicle of given id
    public void commandC() {
        // Prompt for vehicle id
        System.out.print("Enter vehicle id: ");
        Scanner s = new Scanner(System.in);
        int id = s.nextInt(); s.nextLine();

        // Search for vehicle id in database
        Node n;                                      // n stores the node of vehicle to change status
        for (n = head; n != null; n = n.getNext()) { // traverse list until node with matching id is found
            if (n.getVeh().getId() == id)
                break;
        }
        if (n == null) { // if ID not found, display error and return
            System.out.println("Vehicle ID not found.");
            return;
        }

        // Prompt and set new status
        System.out.print("Enter new status ('available', 'rented', 'repairs'): ");
        String newStatus = s.next(); s.nextLine();
        n.getVeh().setStatus(newStatus);
    }


    // Reset linked list database to empty state
    public void commandD() {
        head = tail = null;
    }


    // Find and print all vehicles with 'available' status
    public void commandA() {
        for (Node n = head; n != null; n = n.getNext()) {
            if (n.getVeh().getStatus().equals("available"))
                n.getVeh().display();
        }
    }


    // Take nodes from unsorted linked list and create a new list
    public void commandS() {
        Node node = head;
        if (node == null) {
            System.out.println("Error: Cannot sort empty database.");
            return;
        }
        // Make the first node the start of the sorted list.
        Node sortedList = node;
        node = node.getNext();
        sortedList.setNext(null);

        while(node != null) {
            // Advance the nodes.
            Node current = node;
            node = node.getNext();

            // Find where current belongs.
            // First check compare the head
            int x; // store result of compare
            if ((x = current.getVeh().getMake().compareToIgnoreCase(sortedList.getVeh().getMake())) < 0) {
                // If current has a make less than the sorted list head then...
                current.setNext(sortedList); // Set current as new sorted head
                sortedList = current;
            }
            else if ((x == 0) && (current.getVeh().getModel().compareToIgnoreCase(sortedList.getVeh().getModel())) < 0) {
                // If current has same make as sorted list head, and model is less than sorted list head then...
                current.setNext(sortedList); // Set current as new sorted head
                sortedList = current;
            }
            else { // Traverse sorted list for correct position of current and insert into middle or end of sorted list
                Node search = sortedList;
                // Compare makes until it reaches a vehicle of same make or greater alphabetically
                while(search.getNext() != null && (x = current.getVeh().getMake().compareToIgnoreCase(search.getVeh().getMake())) > 0) {
                    search = search.getNext();
                } // Compare models until it reaches a vehicle of same model or greater alphabetically
                while (search.getNext() != null && x == 0 && current.getVeh().getModel().compareToIgnoreCase(sortedList.getVeh().getModel()) > 0) {
                    search = search.getNext();
                }

                // Current inserted after search position.
                current.setNext(search.getNext());
                search.setNext(current);
            }
        }

        head = tail = null;   // delete old unsorted list
        head = sortedList;    // set head to first node of sorted list
        tail = getTail(head); // set tail to last node of sorted list
    }

    // Client
    public static void main(String[] args) {
        LList list = new LList();     // create linked list object

        System.out.println("Virtual Rental Manager (VRM)");
        while (true) {
            // Print menu and parse command
            list.printCmds();
            Scanner s = new Scanner(System.in);
            String cmd = s.next();

            // Execute command (see printCmds() methods for details on what each command does)
            if (cmd.equals("q")) {
                System.out.println("Exiting VRM. Goodbye.");
                System.exit(0);
            } else if (cmd.equals("v")) {
                list.insert(list.commandV());
            } else if (cmd.equals("c")) {
                list.commandC();
            } else if (cmd.equals("d")) {
                list.commandD();
            } else if (cmd.equals("l")) {
                list.commandL();
            } else if (cmd.equals("a")) {
                list.commandA();
            } else if (cmd.equals("s")) {
                list.commandS();
            } else {
                System.out.println("Error: Invalid option.");
            }
        }
    }
}
