### Program 2 - Array vs Linked List Comparison

---
Bjarne Stroustrup, creator of C++ has an [8-minute presentation](https://www.youtube.com/watch?v=YQs6IC-vgmo)  where he compares performance of two versions of a program, one using an array and the second using a linked list.  In both cases he inserts a large number of integers into sorted order and then deletes them at random.  Something happened during his presentation, though, and his graph didn't show up.  Your job is to create the missing graph that compares the performance of the two versions.

Conventional wisdom is that for large arrays it is inefficient to insert and delete into the middle of the array because so many values need to be moved.  Linked lists on the other hand only require adjusting a few pointers and the rest remains unchanged.

---
#####Algorithm:

Choose your next value for n.  (e.g. n = 1,000 the first time, ... and eventually might be 10,000, which we'll use in the example below.)

**For the array version:**

1. Dynamically allocate an array of 10,000 ints
2. Start timer
3. Do the following 10,000 times:
	1. Generate a random number between 1..10,000
	2. Insert it into the array, where values are stored in ascending order.  You may need to shift a large number of values upwards in the array to make room for it.
4. Now the array is full.  Do the following 10,000 times:
	1. Find a random position between 0 and the current last element of the array.  (This last element is 9,999 the first time, will be 9,998 the second time, and so on.)  
	2. Delete this element, shifting all elements above it down so that there are no empty spots in the array
5. Now the array is empty again.  Take another time stamp and compare to the original, printing out the elapsed time.
6. Release the memory from the dynamically allocated array.

**For the linked list version:**

1. Create an array of Node *.  For our current example, this would be an array of 10,000 Node *.
2. Go through the array and do a new for each one of them.  
3. Start timer
4. Do the following 10,000 times:
	1. Generate a random number between 1..10,000
	2. Insert it into the linked list, where values in the list are stored in ascending order.  
5. The linked list now has 10,000 Nodes.  Do the following 10,000 times:
	1. Generate a random number between 1 and the current number of elements in the list.  (The first time the number of list elements is 10,000, the next time it will be 9,999, and so on.) Call this random number i.
	2. Traverse the list until you get to the i th element.  Delete this element, adjusting the pointers around it accordingly.
6. Now the list is empty again.  Take another time stamp and compare to the original, printing out the elapsed time.
7. Go through the array of Node * and delete each one of them.  Lastly also delete the array of Node *.

**Print new line. Repeat for next set of n.** 

---

##### Assignment Guidelines:
You should combine insertion into an array (similar to insertion sort code) as well as using an ordered linked list, and have the system implement timing these programs, as we did at the beginning of the semester with the sorting algorithm program.  Feel free to use the above-linked sample programs we developed in class as a starting point.

You must have at least 10 different samples for each, with n ranging from 1,000 up to over a million.  Be smart in how many values you choose.  We want to clearly see the results without having to wait a long time for your program to run.  Your values should display on the screen as your program runs, giving the values for linked list and array both on the same line, for 10 or more lines of output in your output table.

Take your results and graph them (e.g. using Excel).  Create an explanation in writing explaining your results.  Include your name at the top of this page.  Your graph should not take up more than half of this page.

To make the comparison fair, pre-fetch all the new nodes you will need before starting the timer for the linked-list version.  Do this by creating an array of all the new nodes you might need.  For instance if you are working on 10,000 elements, then before starting the timer for the linked-list version first create an array of 10,000 Node * elements.  Then each time you need one just grab the next one out of the array so you don't have to call new.

You may need to adjust the given programs so that they accommodate duplicate values.

