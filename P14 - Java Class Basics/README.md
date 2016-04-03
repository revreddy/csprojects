###Project 14 - Java Class Basics

---
#####Description

You are to code the following two classes in the Java language. For each class, make sure to implement all the fields and methods, whether static or non-static, according to the specifications below. Also, make sure to choose appropriate access levels, according to the principle of information hiding, for each field and method. Information hiding requires a class to prevent access to implementation of the class (i.e., the fields of the class) from clients of the class. You wil be creating two classes:  <em>Point</em> and <em>Date</em>.

---
##### Implementation of Point Class

Define a public class <em>Point</em> modeling a point in a 2-dimensional reference system. Class Point defines two integer fields, x and y, with appropriate getter and setter methods.
 Class Point also defines two methods slope() and distance(). Method <em>slope()</em> takes as input a <em>Point</em> instance and returns a double number, which is the slope between the method receiver and the argument point. The slope is defined as the ratio of the difference between the y coordinates of the two points and the difference of their x coordinates. (Hint: Class Double defines static fields <em>POSITIVE INFINITY</em> and <em>NEGATIVE INFINITY</em>. Method <em>slope()</em> may return the constant <em>Double.POSITIVE INFINITY</em> or <em>Double.NEGATIVE INFINITY</em> when the slope is infinite.)
Similarly, method <em>distance()</em> returns the Euclidean distance between the method receiver and the argument <em>Point</em> as a double. Use Pitagoras’s theorem to compute this distance. (Hints: Static method <em>Math.sqrt()</em> returns the square root of its argument.)Write also a no-arg constructor for class Point and a constructor that takes two integers, which are used to initialize x and y.
Class <em>Point</em> defines a public static method main(), which creates a number of <em>Point</em> instances for the purpose of testing the class. In main() code three test cases in which the slope and distance functions are computed for the following pairs of points {(10, 10), (4, 2)}, {(2, 10), (-1, -2)}, and {(3, 3), (0, 6)}. Print the results of those computations on the IDE console using appropriate output statements.
---

##### Implementation of Date Class

Define a public class <em>Date</em>, which models dates in the Gregorian calendar system. Each date has three integer nonstatic fields, namely <em>day, month</em> and <em>year</em>. In addition, <em>Date</em> has a static field <em>daysInMonth</em>, an integer array with the length of the months of the year in days (e.g., { <em>31, 28, 31, 30,</em> . . . }).
One constructor that takes as input three integer parameters that are used to initial- ize the three non-static fields. The constructor uses the static field and method <em>isLeapYear()</em> below to check that this is a valid day/month combination, for instance, printing an error message if someone is tries to define the date February 31, 2015. When an error is detected, the new instance is set to the default value of January 1, 2001 after the error message is printed.
Defines a static method <em>isLeapYear()</em>, that takes as input a non-negative integer number and checks whether the argument number is a leap year. The method returns a boolean value depending on whether the argument is a leap year or not.Define a nonstatic method <em>prettyPrint()</em> that returns a string formatting the receiver with the full month name (e.g., as in “20 January 2015”).Write five test cases in static method <em>main()</em>, constructing, formatting (with method <em>prettyPrint()</em>) and printing on the Eclipse console the following input cases 1/1/2001, 2/31/1998, 2/29/2016, 8/15/1945, and 12/31/1999. (Hint: Use a static field to hold the names of the months in class <em>Date</em>.)
