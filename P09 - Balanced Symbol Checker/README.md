###Project 9 - Balanced Symbol Checker 

---
Write a C program that will determine whether input is given with properly balanced symbols. We will often use symbols together to specify the beginning and ending of an item, such as the use of parentheses in a mathematic expression or the use of curly braces in a C, C++ or Java program. For this program, we will be checking the following symbol pairs:

- parentheses: ( )
- braces: { }
- square brackets: [ ] 
- angle brackets: < > 

This program will require the use of a stack implemented in a dynamic array. This dynamic array is to grow to a larger size when a push operation would be done to a full array causing an array overflow. For this program, your dynamic array is to start with 2 positions in the array. When the array needs to grow, it size is to grow by 2 additional positions each time (note the array to grow in size from 2 to 4 to 6 to 8 to 10 to ...). 

The **push** operation is defined as follows: 
	
	if (the stack array if full)
		grow the array
	add the value to the stack array
	increment the top-of-stack value

The **grow** operation is defined as follows:
	
	Allocate a new dynamic array of the larger size
	Copy the existing values from the current stack array to the new dynamic array 
	Deallocate the current stack array
	Have the stack array variable refer/point to the new dynamic array
	Update the maximum stack size variable
___
#####Input:
The input for this program will come from standard input. Each line of input will be a single expression that is to be checked for balanced symbols. You may assume that each line of input is less than 300 characters long.

Since we have limited the length of the input and are trying to process one line of input at a time, the best way to read the input is the fgets() function in the <stdio.h> library. Since we are reading from standard input, you are to use the value of stdin for the third parameter of fgets(). This causes fgets() to read input from the standard input. You MUST use fgets() for this programming project to read in the input.

If the input on the line contains only the letter q or Q, quit the program.

___

#####Stack Use Algorithm:
To check for balance symbols in an expression, the expression is inspected from left to right after the entire line is read in. 

When an opening symbol is encountered, this symbol is pushed onto the stack. The opening symbols are: ( { [ and <. 

When a closing symbol is encountered, check the symbol at the top of the stack

- If the symbol on the top of the stack is the corresponding opening symbol, pop the stack and continue. - 
- If the symbol on the top of the stack is NOT the corresponding opening symbol, the expression is NOT balanced and the wrong closing symbol was encountered. 
- If the stack is empty, the expression is NOT balanced and there is a missing opening symbol. 
- When the end of the expression is encountered (i.e. the end of the input line), check to see if the stack is empty
- If the stack is empty, then the expression was balanced.  
- If the stack is NOT empty, the expression was not balanced and there is a missing closing symbol.

Since the only input we really care about are the 8 characters that form the 4 symbol pairs, any other input on the line can be ignored. 
___
#####Output:
For each line of input, your program should display the input and specify whether the expression:

- is balanced 
- is unbalanced because it is expecting a different closing symbol (the wrong closing symbol is on the top of the stack) 
- is unbalanced because it is missing an opening symbol (stack is empty when a closing symbol is encountered) 
- is unbalanced because it is missing a closing symbol (line ends while the stack is not empty) 

For the unbalanced expression, print the “up arrow” character at the place where the unbalanced error occurred. The following are some examples output showing the 4 possible outcomes: 
	
		( ( a a ) < > [ [ [ { [ x ] } ] ] ] < > ) Expression is balanced 

		( ( a a ) < > [ [ [ { [ x ] ] ] ] < > )
                                    ^ expecting }

		( ( a a ) ) < > > [ [ [ { [ x ] } ] ] ] < > ) 
	                    ^ missing < 

		( ( a a ) < > [ [ [ { [ x ] } ] ] ]
	                                       ^ missing ) 
___
#####Guidelines:
Use of C struct and C functions 
When writing your code, you MUST place all of the data items needed for the stack in a C struct called “stack”. These data items must include the following (and may include others if needed). 

- the pointer to the dynamic array that actually holds the stack
- the integer variable specifying the current size of the dynamic array 
- the integer variable specifying the top of the stack  

The instance of this struct MUST be declared in main(). It may NOT be global. 

You MUST write functions for:

- initializing the stack, 
- checking if the stack is empty, 
- pushing an element onto the stack, 
- popping an element off of the stack, 
- accessing the top element on the stack, and 
- resetting the stack so that it is empty and ready to be used again.

All of these functions MUST take as their first parameter a pointer to the struct that contains the instance of the stack that is being used. 