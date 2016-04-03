### Project 12 - Exam Averages

---
##### Description
Assume the existence of a text file named “students.txt” that contains info about N > 0 students, one student per line. Here’s an example file:

	drugni3,60,60,60
	jhummel2,0,0,34	ddas6,60,60,60
	sdeitz2,100,94,81Each line contains 4 values: a netid and 3 exam scores. The values are separated by commas, and there are no spaces in the line. Your assignment is to read this file, sort the data by exam average, and output each student’s netid, exam average, and exam scores.
Note that the output is in descending order by exam average. If two students have the same exam average — as in the case of “ddas6” and “drugni3” — note that the netids are output in ascending order. [In sorting terminology, exam average is called the primary sort and netid the secondary sort.]---
##### GuidelinesThe assignment is meant to be straightforward. However, the challenge is in *how* you solve it; you are required to solve it in a particular way. We don’t want just any solution, but a particular type of solution that emphasizes the modern aspects of C++. In particular, you must satisfy *all* of the following requirements:
1. No index-based loops. You may use range-for loops, or iterator-based loops, that’s it.2. Do not open/close the file yourself. Instead, use ifstream approach shown in class.3. You must sort the data using the built-in sort algorithm, using a lambda expression.4. You must define a class student to the data about an individual student.5. You must use a vector of student objects, i.e. vector<student>, to store the data about all the students.6. The must sort and output based on this vector of student objects.