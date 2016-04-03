//
// Project 14 - Date
//     Determine if the date is valid and display in a formated output
//
// Created by Revanth Reddy 1/22/2015
// Language: Java
// Environ: Mac OSX 10.10, IntelliJ IDEA 14.0.3, Java 8
//
// Copyright (c) 2015 Revanth Reddy. All rights reserved.
//

import java.lang.*;

public class Date {
    // Members
    private int day, month, year;
    private static int numDays[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    private static String months[] = {"null", "January", "February", "March", "April", "May",
    "June", "July", "August", "September", "October", "November", "December"};
    
    // Constructor
    public Date(int xDay, int xMonth, int xYear) {  // uses day month, year format
        day = xDay;                                 // ex: 20 January, 2015
        month = xMonth;
        year = xYear;
    }

    // Get Day, Month, or year
    public int getDay() {return day;}
    public int getMonth() {return month;}
    public int getYear() {return year;}


    // Set Day, Month, or Year
    public void setDay(int x) {day = x;}
    public void setMonth(int x) {month = x;}
    public void setYear(int x) {year = x;}


    // Methods //
    // Determine if the date is in a leap year
    public boolean isLeapYear() {
        // Get initial values
        int yr = this.getYear();

        // Leap defined as when year is (divisible by 4 and not divisible by 100)
        // or year is (divisible by 400).
        if ((yr%4 == 0 && yr%100 != 0) || (yr%400 == 0))
            return true;
        else
            return false;
    }
    
    
    // Checks whether the date is valid
    public boolean isValidDate() {
        // Get initial values for comparison
        boolean isLeapYr = this.isLeapYear();
        int xDay = this.getDay();
        int xMonth = this.getMonth();

        // Check whether day is valid for given month
        // For all months except February, if date is btwn 1 and 30 or 1 to 31 depending on month
        if ((xDay >= 1) && (xDay <= numDays[xMonth]))
            return true;
        // For February, if day is btwn 1 to 28 or 1 to 29 depending on leap year
        else if ((xDay >= 1) && ((isLeapYr && xDay > 29) || (isLeapYr && xDay > 28)))
            return true;
        return false;
    }
    
    
    // Display valid dates is 'Month Day, Year' format
    public void prettyPrint() {
        if (this.isValidDate()) { // if valid date, then print date
            System.out.printf("%d %s, %d\n", this.getDay(), months[this.getMonth()], this.getYear());
        } else { // if not a valid date
            System.out.printf("Error: Given date %d %s, %d is invalid. Resetting date to default 1 January, 2001.\n", this.getDay(), months[this.getMonth()], this.getYear());
            this.setDay(1);
            this.setMonth(1);
            this.setYear(2001);
        }
    }
    

    // Main
    public static void main(String[] args) {
        // Create 5 test date objects
        Date d1 = new Date(1, 1, 2001);
        Date d2 = new Date(31, 2, 1998);
        Date d3 = new Date(29, 2, 2016);
        Date d4 = new Date(15, 8, 1945);
        Date d5 = new Date(31, 12, 1999);

        // Display formatted output for test dates
        d1.prettyPrint();
        d2.prettyPrint();
        d3.prettyPrint();
        d4.prettyPrint();
        d5.prettyPrint();
    }
}
