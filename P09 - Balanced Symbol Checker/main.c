//
//  main.c
//  Project 9 - Balanced Symbol Checker
//      This program takes string input from the user and checks
//      for opening/closing symbol balancing while skipping over
//      all other characters in the string. If balanced, it will display
//      a feedback message saying so. If unbalanced, it will display
//      feedback message for exactly which symbol is missing or expected
//      so that the user can know where to make their correction.
//
//  Created by Revanth Reddy on 10/22/14.
//  Language: C
//  Envir:  Mac OSX Yosemite, Xcode 6.1
//  Tested on RHEL Server 5.11
//
//  Copyright (c) 2014 Revanth Reddy. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Stack_ {
    char *symbols;
    int size;
    int top;
} Stack;

//--------------------------------------------------------------------------------//
// Display program information
void programInfo() {
    puts ("");
    puts ("**********************************");
    puts ("Author: Revanth Reddy");
    puts ("Project 9: Balanced Symbol Checker ");
    puts ("**********************************\n");
}


//--------------------------------------------------------------------------------//
// Creates a struct to hold the symbols, size of stack, and current top of stack
// @return {Stack*} temp - holds address pointing to the struct
Stack *createStack() {
    Stack *temp = malloc(sizeof(Stack)); // allocate a stack struct
    
    temp->symbols = malloc(sizeof(char) * 2); // allocate cstring for holding symbols
    int i;                          // iterator
    for (i = 0; i < 2; i++) {       // for each index
        temp->symbols[i] = '\0';    // initialize with null char
    }
    temp->size = 2;         // initial size of 2
    temp->top = -1;         // when the first symbol added, top will be index 0
    
    return temp;
}


//--------------------------------------------------------------------------------//
// Checks if the stack current has no symbols stored in it
// @param {Stack*} s - pointer to the stack struct
// @return - serves as a boolean, 1 if true, 0 if false
int isStackEmpty(Stack *s) {
    if (s->top == -1)              // if stack is empty
        return 1;                  // return true
    else                           // if stack is not empty
        return 0;                  // return false
}


//--------------------------------------------------------------------------------//
// Retrieves the top of the stack
// @param {Stack*} s - pointer to the stack struct
char getTop(Stack *s) {
    if (isStackEmpty(s))           // if stack is empty
        return '$';                // $ is used as special symbol as dummy char
    else                           // if stack is not empty
        return s->symbols[s->top]; // return the current symbol at the top of stack
}


//--------------------------------------------------------------------------------//
// Increases the stack size by two. Creates a new array, copies existing values to
// new array, and deletes old array
// @param {Stack*} s - pointer to the stack struct
void grow(Stack *s) {
    int i;                                   // iterator
    int size = s->size;                      // get current size of symbols cstring
    char *new = malloc(sizeof(char)*size+2); // allocate new string that is 2 char longer
    
    for (i = 0; i < size; i++) { // each index in stack
        new[i] = s->symbols[i];  // copy all current symbols to new string
    }
    new[i++] = '\0';             // initialize null char for two additional indicies
    new[i] = '\0';
    
    free(s->symbols);            // deallocate old string
    s->symbols = new;            // point symbols to new cstring
    s->size += 2;                // increment size by 2
}


//--------------------------------------------------------------------------------//
// Add new opening symbols to the stack
// @param {Stack*} s - pointer to the stack struct
// @param {char} symbol - opening symbol to be added to top of stack
void push(Stack *s, char symbol) {
    if (s->size == s->top+1) {   // if stack is full
        grow(s);                 // grow the stack
    }
    s->top += 1;                 // increment the top position
    s->symbols[s->top] = symbol; // add symbol to top of stack

}


//--------------------------------------------------------------------------------//
// Remove old opening symbol from stack when closing symbol found
// @param {Stack*} s - pointer to the stack struct
void pop(Stack *s) {
    s->symbols[s->top] = '\0'; // overwrite the top with a null char
    (s->top)--;                // decrement the top position
}


//--------------------------------------------------------------------------------//
// Displays the current contents of the struct. Useful for debugging.
// @param {Stack*} s - pointer to the stack struct
void displayStack(Stack *s){
    if (isStackEmpty(s)) {          // if stack is empty
        puts ("Stack is empty.");   // display feedback
    }
    else {                              // if stack is not empty
        printf("Symbols = ");
        int i;                          // loop iterator
        char sym;                       // current symbol
        for (i = 0; (sym = s->symbols[i]) != '\0'; i++) { // display all current symbols in stack
            printf("%c ", sym);
        }
        printf("\n");
    }
    printf("Stack size = %d\n", s->size);   // display stack size
    printf("Stack top = %d\n\n", s->top);     // display position of top of stack
}


//--------------------------------------------------------------------------------//
// Resets the stack to the initial values. Overwrites out the stack array with null
// chars and resets the position of top. Size of array remains the same even if it grew.
// @param {Stack*} s - pointer to the stack struct
void resetStack(Stack *s) {
    if (isStackEmpty(s))             // if stack already empty
        return;                      // do nothing
    
    s->top = -1;                     // reset top
    
    int i;                           // iterator
    int size = s->size;              // get current size of stack
    for (i = 0; i < size; i++) { // overwrite any remaining symbols in stack
        s->symbols[i] = '\0';
    }
}


//--------------------------------------------------------------------------------//
// Displays feedback message for when input is missing an opening symbol.
// @param {char*} input - pointer to the cstring containing the user input
// @param {char} sym - the last symbol that was checked for balance
// @param {int} i - current index position where sym is located
void missingOpeningSymbol(char *input, char sym, int i) {
    int k;                              // iterator
    
    printf ("\n%s", input);             // display input on a line
    for (k = 0; k < i; k++)             // print spacing below input
        printf(" ");                    // to properly position feedback message
    
    switch (sym) {
        case ')':                           // display feedback message
            printf ("^ Missing (\n");
            break;
        case '}':
            printf ("^ Missing {\n");
            break;
        case ']':
            printf ("^ Missing [\n");
            break;
        case '>':
            printf ("^ Missing <\n");
            break;
    }
}


//--------------------------------------------------------------------------------//
// Displays feedback message for when input is missing a closing symbol.
// @param {Stack*} s - pointer to the stack struct
// @param {char*} input - pointer to the cstring containing the user input
void missingClosingSymbol(Stack *s, char *input) {
    int i;                                  // iterator
    int top = getTop(s);                // get symbol at top of stack
    int size = strlen(input) - 1;       // get length of input

    printf ("\n%s", input);             // display input on a line
    for (i = 0; i < size; i++)      // print spacing below the input
        printf(" ");                    // to properly position feedback message
    
    switch  (top) {                     // display feedback message
        case '(':
            printf ("^ Missing )\n");
            break;
        case '{':
            printf ("^ Missing }\n");
            break;
        case '[':
            printf ("^ Missing ]\n");
            break;
        case '<':
            printf ("^ Missing >\n");
            break;
    }
}


//--------------------------------------------------------------------------------//
// Displays feedback message for when input has the wrong closing symbol.
// @param {Stack*} s - pointer to the stack struct
// @param {char*} input - pointer to the cstring containing the user input
// @param {char} sym - the last symbol that was checked for balance
// @param {int} i - current index position where sym is located
void expectingDifferentSymbol(Stack *s, char *input, char sym, int i) {
    int k;                                  // iterator
    int top = getTop(s);                    // get symbol at top of stack
    
    printf("\n%s", input);                  // display input on a line
    for (k = 0; k < i; k++)                 // print spacing below the input
        printf(" ");                        // to properly position feedback message
    
    if (top == '{')                         // if nonmatching opening symbol
        printf ("^ Expecting }\n");         // display expected closing symbol
    else if (top == '[')
        printf ("^ Expecting ]\n");
    else if (top == '<')
        printf ("^ Expecting >\n");
    else // if (top == '(')
        printf ("^ Expecting )\n");
}

//--------------------------------------------------------------------------------//
int main(int argc, const char * argv[]) {
    int sizeInput = 300;                              // max number of char accepted for input
    int i;                                            // iterator
    int mismatch = false;                             // boolean used to break looping when error found
    char *input = malloc(sizeof(char)*sizeInput + 1); // allocate array for 300 char and null char
    Stack *s = createStack();                         // pointer for stack struct
    
    programInfo();
    
    printf("Enter input or 'q' to exit:  ");
    while (fgets(input, sizeInput, stdin)) {
        if (input[0] == '\n') {                     // If no input given
            printf("Enter input or 'q' to exit: "); // Prompt again for new input
            continue;
        }
        // Exit command
        // Input in array will be as follows: [q][\n][\0] or [Q][\n][\0]
        if ((input[0] == 'q' || input[0] == 'Q') && input[2] == '\0') {
            puts ("Exit program.");
            break;
        }
        
        // Scan input for matching symbol pairs
        char sym;
        int top;
        mismatch = false;
        for (i = 0; (sym = input[i]) != '\n'; i++) {
            if (sym  == '(' || sym  == '{' || sym == '[' || sym == '<') { // if opening symbol...
                push(s, sym);                                             // push into stack
            }
            
            else if (sym == ')' || sym == '}' || sym == ']' || sym == '>') { // if closing symbol found in input
                if (isStackEmpty(s)) {                                    // and if stack is empty
                    missingOpeningSymbol(input, sym, i);                  // display missing opening symbol
                    mismatch = true;                                      // set boolean to true to break out for loop
                }
                else {
                    top = getTop(s);           // get symbol at top of stack
                    switch (sym) {             // if stack is not empty
                        case ')':
                            if (top == '(')    // if current sym is a closing symbol for the top symbol, pop from stack
                                pop(s);
                            else if (top == '{' || top == '[' || top == '<') { // if nonmatching opening symbol
                                expectingDifferentSymbol(s, input, sym, i);    // display expected closing symbol
                                mismatch = true;                            // set boolean to true to break out for loop
                            }
                            break;
                        case '}':
                            if (top == '{')
                                pop(s);
                            else if (top == '(' || top == '[' || top == '<') {
                                expectingDifferentSymbol(s, input, sym, i);
                                mismatch = true;
                            }
                            break;
                        case ']':
                            if (top == '[')
                                pop(s);
                            else if (top == '(' || top == '{' || top == '<') {
                                expectingDifferentSymbol(s, input, sym, i);
                                mismatch = true;
                            }
                            break;
                        case '>':
                            if (top == '<')
                                pop(s);
                            else if (top == '(' || top == '{' || top == '[') {
                                expectingDifferentSymbol(s, input, sym, i);
                                mismatch = true;
                            }
                            break;
                    }
                }
                if (mismatch)   // if mismatch found
                    break;      // stop looping through input
            }
            // else: ignore any other characters in input
        }
        
        if (mismatch) { // if mismatch found above
                        // do nothing, skips checking the two conditions below
        }
        else if (isStackEmpty(s)) {             // input done, stack empty
            puts("Balanced");                   // Stack is balanced
        }
        else {                                  // input done, stack not empty
            missingClosingSymbol(s, input);     // Display missing closing symbol
        }
        
        resetStack(s);                          // reset stack for next input
        printf("\nEnter input or 'q' to exit: ");
    }
    
    // Deallocate memory before program exit
    free(s->symbols);
    free(s);
    free(input);
    return 0;
}
