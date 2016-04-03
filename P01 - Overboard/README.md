###Program 1 - Overboard

---
#####Description:
Stardate 2015. You are captain on a spaceship which is losing all life-support systems.  On board, you have passengers consisting of both humans and androids operating under the illusion that they too are humans.  The thing is that the escape pod is limited in size and can only hold all the humans. You must select the passengers that will not survive. (Don’t you just hate making decisions like that?)

It just so happens that you think the humans should be saved and the androids left behind. You have to be subtle about how to do this, as the androids will all revolt if it is perceived that you are being “unfair.” What you arrange to do is sit all the passengers in a circle and begin to count, ejecting every nth passenger into outer-space through the airlock.  (You, unfortunately, will go down with the ship.)

---
#####Objectives/Algorithm:
Write a program to answer the following question: For what value of n, starting at the arrow indicated below and counting clockwise, will all the androids be ejected, leaving all the humans? (Hint: n is less than the total number of passengers) Assume that in counting you begin with the current position as 0 and move in a clockwise direction. When you reach a passenger to be thrown overboard, that node gets removed from the list.  If it still existed it would be position 0, so the next one would be counted as 1 as you begin counting again.

Here's the starting order of the passengers - the A's are androids, and the H's are humans.  

![circle sequence](https://sites.google.com/site/uiccs251/program/Overboard.JPG?attredirects=0)

The output of this program should be the value of n that solves the problem, or if there is no solution it should be a message indicating there is no solution.

To solve this problem, you must represent the passengers in a circularly linked list, where the space for the list has been allocated dynamically in your program. The H’s and A’s in the circle above should be read in from a data file called **passengers.txt** that contains all the passengers starting with the one indicated by Start, going clockwise around the circle.  For the above example, passengers.txt would look like:

	AHHHHHAAAAHHAAHAHHAHAHAAHAAHHA

(which if you read it out-loud is probably what it sounds like when someone is sent out the airlock.) 

---
#####Guidelines
For full credit your program must:

- Handle different lengths of input from the input file.  Note that the input file must be all upper case with no spaces and no other characters or numbers.
- Explicitly deallocate any memory that is removed from the circularly linked list as you go. Your program must modify the circularly linked list by removing a node each time a passenger is selected to be ejected out the airlock.