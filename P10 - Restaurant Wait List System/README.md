###Project 10 - Restaurant Wait List System

---
Write a C program that will implement a customer waiting list that might be used by a restaurant. The program must use a linked list to implement the queue-like data structure.

___
#####User Commands

Command............  | Description
-----------------------|--------------------------
**w \<name>**			| Mark the call ahead group using the given name as waiting in the restaurant. If the name does not exist is the wait list or is not a call ahead group, give an error message.
**r \<table-size>**		| Retrieve and remove the first group on the wait list that is waiting in the restaurant and is less than or equal to the table size. Note that “first” is the group that has been in the wait list the longest.
**l \<name>**			| List total number of groups that are in the wait list in front of the group specified by the given name. Also list the size of each group that are in the wait list ahead of the group specified by the given name. If the name does not exist, give an error message.
**d**					| Display the total number of groups in the wait list. Also display the names, group size and in-restaurant status of all groups in the wait list in order from first to last.

Note that \<size> and <table-size> are to be integer values and <name> is a list of characters.
___
#####Use of C struct and C functions

