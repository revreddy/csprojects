###Program 4 - Insite Logistics

---
#####Description: 
You form a start-up company called Insite providing business logistics advice. Insite has just been hired by Chinese e-commerce giant Alibaba, who wants to compete with Amazon for items shipped via truck from warehouses directly to customers in the lower-48 states. Alibaba wants to limit shipping fuel costs, which are directly related to the distance from distribution warehouses to other cities.

To minimize shipping costs how many warehouses should Alibaba build, and in which cities should they be located?  What is the average shipping distance over all US cities in each case?  Write the program to figure this out.

After the descriptive header (see syllabus online and example below), your output must be in the form of a table showing the:

- Number of distribution centers
- The average distance over all cities for this number of distribution centers
- The list of cities where the distribution centers will be built

For example your output should look like the following (though this is made-up data):

	Please enter the maximum number of cities: 3

            Avg City    
       #    Distance   Cities
      ---   ---------  --------------------
        1      953     Kansas City
        2      700     Nashville, Salt Lake City 
        3      585     Cincinnati, Oklahoma City, Reno 

Note that your program prompts for the number of cities to be considered. In the above case the user provides 3 as the maximum number of cities. (Your input will not show up in bold, that is just a highlight for this description.) Providing input of 5 would instead look like the following (though this is again made-up data):

	Please enter the maximum number of cities: 5

            Avg City    
       #    Distance   Cities
      ---   ---------  --------------------
        1      953     Kansas City
        2      718     Nashville, Salt Lake City
        3      597     Cincinnati, Oklahoma City, Reno 
        4      495     Las Vegas, Little Rock, Rapid City, Roanoke
        5      438     Atlanta, Butte, Flagstaff, Pittsburgh, Wichita,  
---
#####Details:

While you may get algorithmic ideas from research on the web, you must write this program yourself.  You may use all the sample code I have provided as-is to help you. It will be helpful for you to be familiar with the sample code for Dijkstra's algorithm. The solution to Lab 10 gives some helpful code you can modify to read in from a file, but you can ignore the rest of that program.

To do this analysis use a list of 248 cities (in file called CityNames.txt) and the set of 711 distances in file CityDistancesSanitized.txt where the city numbers correspond to the cities file. The first line of each of the files gives the number of following entries in the file. This data is based off of this map. Note that the city distances file only contains "half" of the links of the original.  Where the original had both the entry for A to B and B to A, the new sanitized file from Joseph has only A to B. This means that when you read in each line A B distance you have to create both entries (A to B and B to A) from it.

(For practice you can also use the smaller set of 30 cities in cityNames.txt with the accompanying 124 distancePairsSome.txt as your respective city name and distances files. You may also want to create a really small set of your own to use in debugging, say 5 cities and a set of corresponding distances.) The one difference is that you should make the data "1-based", that is index values should start from 1 and go up to n, which will affect your program loop values.

The list of cities displayed on each row of your output table must be in alphabetical order so that it is easier for us to verify your output.

---
#####Program Stages and Points:

This task is much less daunting if you break it down. Work up to the solution by being able to write code to answer questions such as the following:

1. For a particular city, can you calculate the distance to one other city?
2. For a particular city, can you calculate and store the sum of distances to all other cities?  (Dijkstra's algorithm)
3. Then divide by the total number of cities to get the average distance.
4. Repeat and store for all cities. The one with the lowest average distance is the best location for a single distribution center.

For two cities repeat the above steps for all pairs of cities. Likewise for 3 cities repeat for all sets of cities, and so on. Regardless of the number of distribution centers, always divide by the total number of cities to find the average distance, assuming that delivery centers also ship to people in their own city (distance of 0).

---

#####Grading

If your program achieves the minimum required level of performance (see below) then you will be awarded 50 points for programming style as described in the course syllabus. Out of the 50 points for program execution described in the course syllabus, points will be awarded for the following performance levels:

- (up to 15 points)  Regardless of user input your program computes and displays only the location for the single best location for one distribution center. You must complete at least this level to get any points on this program. Your program must work for n=1 on the full dataset.
- (up to 25 points)  Program hard-codes the maximum number of cities where distribution centers will be placed for some value between 5-10 for some dataset smaller than the full one. Note that you will not have enough time and memory to do this for the entire dataset. We will be testing this program with a smaller dataset than the full one.
- (up to 50 points) Program dynamically allocates space for arrays used in program, to handle any number of cities which will have distribution centers. Note that you will not have enough time and memory to do this for the entire dataset. We will be testing this program with a smaller dataset than the full one.