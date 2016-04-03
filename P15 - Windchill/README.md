### Project 15 - Windchill

---
#####Objective
This F# program is an introduction into proper syntax and formatting as well as accepting user input, creating functions, using lists, and displaying output.

---
#####Part 1

Write a program to compute windchills for a temperature of 10 degrees F by hardcoding temperature T in function windchill, across the range of wind speeds 1-20 mph. The equation for computing windchill, given a temperature T (in degrees F) and a wind speed W (in mph), is as follows:

	￼WC = 35.7 + 0.6*T - 35.7W^(0.16) + 0.43TW^(0.16)
	
The output is a list of 20 windchills: W=1, W=2, W=3, ..., W=20. For example, for T=10 and W=4, the windchill is roughly 2.5 degrees F. For W=10, the windchill is roughly -9.0 degrees F.

Modify the program to input the temperature from the user, and output the windchills based on that temperature T; assume the user will enter a valid temperature in degrees F. Implement the following code:

	printf "Please enter temperature (degrees F): "
 	let input = System.Console.ReadLine()	let T = System.Convert.ToDouble(input)
Modify your code to provide the map with a lambda expression that takes an element W from the list, and calls windchill with the two parameters T and W. This will allow the program to use the passed value of T.