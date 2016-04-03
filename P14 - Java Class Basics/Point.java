//
// Project 14 - Date
//     Calculate the slope and distance between two given points
//
// Created by Revanth Reddy 1/22/2015
// Language: Java
// Environ: Mac OSX 10.10, IntelliJ IDEA 14.0.3, Java 8
//
// Copyright (c) 2015 Revanth Reddy. All rights reserved.
//

import java.lang.*;

public class Point {
    
    // Members
    private double x, y;
    private static double pInf = Double.POSITIVE_INFINITY;
    private static double nInf = Double.NEGATIVE_INFINITY;

    
    // Constructors
    public Point() {
        x = 0;
        y = 0;
    }
    public Point(int a, int b) {
        x = a;
        y = b;
    }

    // Set x or y
    public void getX(double n) {
        x = n;
    }
    public void getY(double n) {
        y = n;
    }

    // Get x or y
    public double getX() {
        return x;
    }
    public double getY() {
        return y;
    }


    // Methods
    
    // Calculate slope between two points
    // Receiver is p1, argument is p2
    // slope = (Y2-Y1)/(X2-X1)
    public double slope(Point p2) {
        double deltaX = (p2.getX() - this.getX()); // find differnce between X2-X1
        double deltaY = (p2.getY() - this.getX()); // find difference between Y2-Y1

        // Compute slope
        // if deltaX is zero, cannot divide by zero, slope is +/- infinity
        // based on whether deltaY is pos or neg
        if (deltaX == 0 && deltaY > 0) {
            return pInf;
        } else if (deltaX == 0 && deltaY < 0) {
            return nInf;
        } else { // if deltaX != zero, then compute slope
            return deltaY / deltaX;
        }
    }

    // Calculate the distance between two points
    // distance = sqrt( (X2-X1)^2 + (Y2-Y1)^2 )
    public double distance(Point p2) {
        double deltaX = (p2.getX() - this.getX());
        double deltaY = (p2.getY() - this.getY());
        return Math.sqrt(Math.pow(deltaX, 2) + Math.pow(deltaY, 2));
    }

    // Display the slope and distance for point pair
    public void computePairs(Point p2) {
        System.out.println("Test 1: Point pair {(" + this.getX() + "," + this.getY()
                + "), (" + p2.getX() + "," + p2.getY() + ")}");
        System.out.println("\tSlope = " + this.slope(p2));
        System.out.println("\tDistance = " + this.distance(p2));
        System.out.println("");
    }

    // Main
    public static void main(String[] args) {
        // Create Point objects for coordinate pairs
        Point p1 = new Point(10,10);
        Point p2 = new Point(4,2);
        Point p3 = new Point(2,10);
        Point p4 = new Point(-1,-2);
        Point p5 = new Point(3,3);
        Point p6 = new Point(0,6);

        // Compute and display slope and distance for the three Point pairs
        p1.computePairs(p2);
        p3.computePairs(p4);
        p5.computePairs(p6);
    }
}
