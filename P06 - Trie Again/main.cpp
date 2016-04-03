//
//  Project 6 - Trie Harder
//      Implements a trie that stores dictionary words and allows
//      the user to manipulate the dictionary in various ways, including
//      search, print, add, and deleting words. This is a variation of
//      program 5, which used arrays to store the letters. Instead,
//      program 6 uses linked list nodes to store a single letter per node.
//
//  Created by Revanth Reddy on 12/2/14.
//  Language: C, C++
//  Envir:  Mac OSX Yosemite, Xcode 6.1
//  Tested on RHEL Server 5.11
//
//  Copyright (c) 2014 Revanth Reddy. All rights reserved.
//


#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cctype>
using namespace std;

// Nodes for dictionary
struct Node {
    char letter;                    // letter stored in node
    bool completeWord;              // does current letter create a complete word?
    Node* pChild;
    Node* pSibling;
};

// Nodes for rhyming words
struct NodeWord {
    char* word;
    NodeWord *pNext;
};

//---------------------------------------------------------------------------------------------------------//
// Display program information
void programInfo() {
    puts ("");
    puts ("**********************************");
    puts ("Author: Revanth Reddy");
    puts ("Project 6: Trie Harder");
    puts ("**********************************\n");
}


//---------------------------------------------------------------------------------------------------------//
// Displays program operations for user
void displayMenu() {
    cout << "Commands: " << endl << endl;
    cout << "f <str>   Find suffix"  << endl;
    cout << "p <n>     Print next n" << endl;
    cout << "a <str>   Add word" << endl;
    cout << "d <str>   Delete word" << endl;
    cout << "?         Help" << endl;
    cout << "x         Exit" << endl;
    cout << endl;
}


//---------------------------------------------------------------------------------------------------------//
// More detailed desciptions for user commands
void commandH() {
    cout << "Commands: " << endl;
    cout << "f <str>   Find suffix:  Searches the tree to see if the string is present and then " << endl;
    cout << "          will set an iterator pointing to the deepest letter of the string." << endl;
    cout << "p <n>     Print next n:  Uses the iterator position set by command f or a " << endl;
    cout << "          previous command p call to find n number of rhyming words or" << endl;
    cout << "          until there are no more to print for given suffix." << endl;
    cout << "a <str>   Add word:  Takes the string and adds the nodes to the tree as a valid word." << endl;
    cout << "d <str>   Delete word:  Searches the tree for the string, if found, it will mark it " << endl;
    cout << "          as an incomplete word and remove any unneeded nodes from the tree." <<  endl;
    cout << "?         Help:  Provides a more detailed description of what each command does." << endl;
    cout << "x         Exit:  Quits the program." << endl << endl;
    cout << "str is a string of alphabetical characters. Any nonalphabetic symbols or " << endl;
    cout << "    numbers cause input error." << endl;
    cout << "n is a positive integer that must be greater than zero, other will cause input error" << endl;
    cout << endl;
}



//--------------------------------------------------------------------------------//
// Clear input until next End of Line Character - \n
void clearToEoln() {
    int ch;
    
    do {
        ch = getc(stdin);
    } while ((ch != '\n') && (ch != EOF));
}


//--------------------------------------------------------------------------------//
// Read in until the first Non-White-Space character is Read
// The white space characters are:
//      space, tab \t, newline \n, vertical tab \v,
//      form feed \f, and carriage return \r
int getNextNWSChar () {
    int ch;
    
    ch = getc(stdin);
    if (ch == EOF)
        return ch;
    while (isspace (ch)) {
        ch = getc(stdin);
        if (ch == EOF)
            return ch;
    }
    return ch;
}


//--------------------------------------------------------------------------------//
// read in the next Positive Integer or error:
// This is based on the Mathematical definition of a Postive Integer
//    zero is not counted as a positive number
int getPosInt () {
    int value = 0;
    
    // clear white space characters
    int ch;
    ch = getc(stdin);
    while (!isdigit(ch)) {
        if ('\n' == ch)     // if \n encounter, no integer given
            return 0;       // return as error
        if (!isspace(ch)) { // if non white space encountered, integer not given next
            clearToEoln();  // clear buffer, return as error
            return 0;
        }
        ch = getc(stdin);   // get next char
    }
    
    //convert digit chars to int
    value = ch - '0';
    ch = getc(stdin);
    while (isdigit(ch)) {
        value = value * 10 + ch - '0';
        ch = getc(stdin);
    }
    
    ungetc (ch, stdin);  // put the last read character back in input stream
    
    if (0 == value)      // Integer value of 0 is an error in this program
        clearToEoln();   // clear buffer
    
    return value;        // return pos int
}


//---------------------------------------------------------------------------------------------------------//
// Converts any uppercase to lowercase
// @param {char*} word - pointer to a c-string
void convertToLowercase(char *word, int wordSize) {
    for (int i = 0; i < wordSize; i++) {        // for every char in word
        word[i] = tolower(word[i]);             // convert word to lowercase
    }
}


//---------------------------------------------------------------------------------------------------------//
// Reverses the string using bitwise XORs to modify the original c-string using in place swapping
// @param {char*} str - c-string holding the word to be reversed
void strReverse(char *str) {
    char *p1, *p2;
    for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2) {
        *p1 ^= *p2;
        *p2 ^= *p1;
        *p1 ^= *p2;
    }
}


//---------------------------------------------------------------------------------------------------------//
// Allocate memory for a node, store letter, and set remaining struct members to defaults
// @param {char} letter - the letter to be saved in the node
// @return {Node*} temp - returns address to the new node
Node *createNode (char letter) {
    Node *temp = (Node*) malloc (sizeof(Node)); // allocate memory for new node
    
    temp->letter = letter;                      // store letter char
    temp->completeWord = false;                 // set default values
    temp->pChild = NULL;
    temp->pSibling = NULL;
    
    return temp;                                // return address to node
}


//---------------------------------------------------------------------------------------------------------//
// Adds the first letter of reversed word (last letter of ordered word), helper function for createDictionary()
// @param {Node*} parent - pointer to the letter node of the previous call
// @param {char} letter - next letter to check in tree or added to tree
// @return {Node*} - returns address to the node added or to the node of the next letter if already exists
Node *addLetters(Node *parent, char letter) {
    Node *current = parent->pChild;
    
    if (parent->pChild == NULL) {               // if no previous words entered for letter
        Node *newNode = createNode(letter);     // create new node for letter
        parent->pChild = newNode;               // make root point to new node
        newNode->pSibling = createNode ('*');
        newNode->pSibling->pChild = parent;
        return newNode;                         // return address to this new node
    }
    else if (current->letter == letter) {       // if first node is matching letter
        return current;                         // do nothing, just return node address to update iterator
    }
    else {
        // Traverse through sibling nodes
        while (current->pSibling->letter != '*') {
            if (current->pSibling->letter == letter) { // if letter already exists
                return current->pSibling;              // make another call using it
            }
            current = current->pSibling;               // else goto next sibling
        }
        
        // Insert new sibling node before the end node
        Node *newNode = createNode(letter);     // create new node for letter
        newNode->pSibling = current->pSibling;
        current->pSibling = newNode;
        return newNode;                         // return address to this new node
    }
}


//---------------------------------------------------------------------------------------------------------//
// Read input file and store the letters/words into the dictionary
// @param {char[]} fileName - input file name with the dictionary words to be read
// @return {Node*} dictionary - pointer to the dictionary Node* to be used as the head.
Node *createDictionary (char fileName[]) {
    ifstream inStream;                              // file stream variable
    size_t inputSize = 75;                          // max word size accepted
    char *inputString = (char*)malloc(sizeof(char) * inputSize + 1);   // allocate c-string to hold word and null char
    bool foundNonAlphaChar = false;                 // boolean for when word has non-alphabet char
    int wordSize;                                   // stores length of input word
    int i;                                          // loop iterator
    Node *current;                                  // stores pointer to first letter of each word added to dictionary
    
    // Allocate a root node and initialize
    Node *dictionary = (Node*) malloc (sizeof(Node));
    dictionary->letter = '$';
    dictionary->completeWord = false;
    dictionary->pChild = NULL;
    dictionary->pSibling = NULL;
    
    inStream.open(fileName);                             // Open file and check if valid
    assert(!inStream.fail());
    
    // Add each word to dictionary
    cout << "Reading dictionary file... ";
    int wordCount = 0;
    while (inStream.getline(inputString, inputSize, '\n')) {    // store word up to newline char
        wordSize = strlen(inputString);                  // store size of word
        if (wordSize == 0) {                             // if wordsize == 0, then empty line encountered in input file
            continue;                                    // skip to next line in input file
        }
        
        for (i = 0; i < wordSize; i++) {                 // for each char in the word
            if (!isalpha(inputString[i])) {              // if isalpha returns 0 when char not in alphabet
                foundNonAlphaChar = true;                // set boolean to true since invalid char is found
                break;                         // stop looping through word since invalid char makes whole word invalid
            }
        }
        if (foundNonAlphaChar) {                         // if non-alpha char is found in current word
            foundNonAlphaChar = false;                   // reset boolean back to false for next word
            continue;                                    // do not add current word to dictionary, skip to next word
        }
        
        convertToLowercase(inputString, wordSize);       // covert any upper case char to lower case
        strReverse(inputString);                         // reverse the string char order
        
        current = dictionary;                                  // reset current to root of dictionary
        for (i = 0; i < wordSize; i++) {                       // reset iterator to index 0, increment until word size
            current = addLetters(current, inputString[i]);     // first letter and save its node location
        }
        current->completeWord = true;                          // set boolean to true to signify complete word
        wordCount++;
    }
    
    cout << wordCount << " words added." << endl << endl; // program feedback output
    inStream.close();               // close input file
    free(inputString);              // free memory for inputString
    return dictionary;              // returns address to dictionary
}


//---------------------------------------------------------------------------------------------------------//
// Prompts user to input suffix to use for finding corresponding rhyming words
// Used by commands F, A, and D.
// @return {char*} suffix - c-string containing the reversed suffix input
char *getSuffix() {
    bool foundNonAlphaChar = false;                     // boolean for when word has non-alphabet char
    int suffixSize = 0;                                 // stores the c-string length
    int i;
    
    char *suffix = (char*) malloc (sizeof(char)*76);    // allocate memory for suffix upto 75 chars
    //cout << "Enter the suffix: ";                     // display prompt statement
    scanf("%s", suffix);                                // get suffix input
    suffixSize = strlen(suffix);                        // get length of suffix
    
    // Check for non-alpha chars
    for (i = 0; i < suffixSize; i++) {  // for each char in the word
        if (!isalpha(suffix[i])) {      // if isalpha returns 0 when char not in alphabet
            foundNonAlphaChar = true;   // set boolean to true since invalid char is found
            break;                      // stop looping, one invalid char makes whole word invalid
        }
    }
    if (foundNonAlphaChar) {           // if non-alpha char is found in suffix, reject input
        return NULL;
    }

    convertToLowercase(suffix, suffixSize);                 // covert any upper case char to lower case
    strReverse(suffix);                                     // reverse the string char order
    
    return suffix;                                          // return valid suffix
}


//---------------------------------------------------------------------------------------------------------//
// Fetches the address to the first letter of the string input. Performs recursively.
// @param {Node*} parent - points to the root of the dictionary intially, then updated to point to found letters
// @param {char*} str - string containing suffix/word to find
// @param {int} i - current index position of letter to be checked
// @param {int} size - number of letters in string
// @return - address to first letter of string if all letters completely found, else NULL as error
Node *findStr(Node *parent, char *str, int i, int size) {
    Node *current = parent->pChild;
    
    if (i == size)          // if entire string is found
        return parent;      // stop making recursive calls, return parent
    
    if (parent->pChild == NULL) {   // if parent does not have a child, then str[i] cannot be found.
        return NULL;
    }
    
    while (current->letter != '*') {                   // Traverse through siblings until end node
        if (current->letter == str[i]) {               // if letter found
            return findStr(current, str, i+1, size);   // make another call to find next letter of str
        }
        current = current->pSibling;                   // else traverse to next sibling
    }
    return 0;  // return statement to supress warning, will never be used,
}


//---------------------------------------------------------------------------------------------------------//
// Helper function for command F to handle some error checking and user feedback.
// @param {Node*} dictionary - contains the trie to all the stored words
// @param {Node*&} root - stores the last letter of the string suffix, used for commandP
// @param {int&} error - boolean for whether input error has occurred.
void commandF(Node *dictionary, Node *&root, bool &error) {
    char *str;                                          // pointer to input string
    if ((str = getSuffix()) == NULL) {                  // get valid input string
        cout << "Error: String contains non-alpha characters. Retry command." << endl;
        error = true;
        return;
    }
    int size = strlen(str);                             // store size of input string
    Node *current = findStr(dictionary, str, 0, size); // find the string in the dictionary, save last letter
    free(str);                                          // deallocate string, not needed anymore
    
    if (current == NULL) { // if string not found or is not complete word
        cout << "String not found." << endl;
        return;
    }

    root = current;  // suffix was found, set root

    // Display user feedback when string is found.
    // Complete word feedback useful checking if words were properly deleted after using command d
    if (current->completeWord == true)
        cout << "String found. Complete word." << endl;
    else
        cout << "String found. Not complete word." << endl;
}


//---------------------------------------------------------------------------------------------------------//
// Adds the string input as a valid word in the dictionary
// Uses the helper function addLetters() and calls it the same way observed in createDictionary().
// @param {Node*} current - initially points to the dictionary root node, before being used as iterator
// @param {int&} error - boolean for whether input error has occurred.
void commandA(Node *current, bool &error) {
    char *str;
    if ((str = getSuffix()) == NULL) {                     // get valid string input
        cout << "Error: String contains non-alpha characters. Retry command." << endl;
        error = true;
        return;
    }
    
    int size = strlen(str);                                // get size of input string
    
    for (int i = 0; i < size; i++) {                       // reset iterator to index 0, increment until word size
        current = addLetters(current, str[i]);             // first letter and save its node location
    }
    current->completeWord = true;                          // set boolean to true to signify complete word
    cout << "String added." << endl;                       // display user feedback
    free (str);                                            // deallocate string
}


//---------------------------------------------------------------------------------------------------------//
// Traverses back up the tree to print out all the parent letters to form the full word to be completed.
// Helper function for printNWords() to perform the repeated task of printing the words.
// @param {Node*} iterator - points to a letter that forms a complete words
void printWord(Node *iterator){
    while(iterator->letter != '$'){             // until dictionary root is reached
        printf("%c", iterator->letter);         // print letter of current parent
        
        while(iterator->pSibling != NULL)       // traverse through siblings until end node
            iterator = iterator->pSibling;
        
        iterator = iterator->pChild;            // use end node to move up one level to next parent
    }
    cout << endl;
}


//---------------------------------------------------------------------------------------------------------//
// Prints n number of rhyming words based on a previous string suffix. Uses DFS recursively.
// Helper function for commandP(). Calls printWord to handle displaying the full word.
// @param {Node*&} root - points to letter node to start or resume searching for words to print.
// @param {Node*&} current - initally points to first child letter of the root, then used as iterator
// @param {int} n - max number of words to print
void printNWords(Node *&root, Node *current, int n){
    int wordCount = 0;
    
    while ((current!= NULL) && (current != root)) {
        // Current letter has a child and sibling, goto next child
        if (current->pChild != NULL && current->pSibling != NULL) {
            current = current->pChild;
        }
        // Current letter does not have child but has sibling
        else if (current->pChild == NULL && current->pSibling != NULL){
            if (current == root)                // if current node has reached back to root
                return;                         // return, all words have been printed
            
            if (current->completeWord == true) {  // if current letter makes a complete word
                printWord(current);             // print the word
                current = current->pSibling;    // then move to next sibling
                wordCount++;                    // increment word count by one
            }
        }
        
        // Current letter is last sibling
        else {
            current = current->pChild;          // Move back to its parent
            
            // Check if suffix string is a complete word, print if it is
            if ((current == root) && (current->completeWord == true)) {
                printWord(current);
                cout << "No remaining words left to print." << endl;
                return;
            }
            
            // if current letter is a complete word, print
            if (current->completeWord == true) {
                printWord(current);
                wordCount++;
            }
            
            // move to next sibling letter
            current = current->pSibling;
        }
        
        if (wordCount == n)       // if word count has reached the number n requested to be printed
            return;               // return, do not print anymore words
    }
    cout << "No remaining words left to print." << endl;
}




//---------------------------------------------------------------------------------------------------------//
// Prints n number of rhyming words based on previous string suffix. Handles some error checking
// and user feedback. Calls printNWords() to perform DFS traversal to find rhymings words.
// @param {Node*&} root - stores the last position traversed after printNWords() so it can be
//    reused to fetch next n words
// @param {int&} error - boolean for whether input error has occurred.
void commandP (Node *&root, bool &error) {
    if (root == NULL) {                             // check if current is valid
        cout << "Error: Must use command f before using command p." << endl;
        error = true;
        return;
    }
    int n;
    if ((n = getPosInt()) <= 0) {                   // get number of words to print
        cout << "Error: Value of n must be greater than zero." << endl;
        error = true;
        return;
    }
    
    printNWords(root, root->pChild, n);             // search for complete words to print
}


//---------------------------------------------------------------------------------------------------------//
// Removes nodes that are part of a word. Traverses back up the tree using parent letters.
// Continues removing letters until it reaches root or reaches a point where a remaining letters are part of
//  a larger word. Helper function for commandD().
// @param {Node*} current - intially points to first (deepest) letter of word, before being used as an iterator
void deleteWord (Node *current) {
    if (current->pChild != NULL || current->completeWord == true) {    // if string is part of other words
        return;                            // return, deleting any other nodes will delete other words too
    }
    if (current->letter == '$') {          // if current node is the root of the dictionary
        return;                            // return, no more nodes to delete
    }
    
    Node *parent = current;                // pointer to save parent node, initially not parent itself
    while (parent->letter != '*') {        // traverse through siblings until end node reached
        parent = parent->pSibling;
    }
    parent = parent->pChild;               // use end node to move up one level to point to parent
    
    // Letter to be removed is directly connected to parent and has no siblings
    if (parent->pChild == current && current->pSibling->letter == '*') {
        free(parent->pChild->pSibling);    // deallocate the end pointer for the letter level
        free(parent->pChild);              // deallocate letter node itself
        parent->pChild = NULL;             // reset the child pointer
        deleteWord(parent);                // make next call using parent
    }
    
    // Letter to be removed is directly connected to parent and has siblings
    else if (parent->pChild->letter == current->letter) {
        parent->pChild = current->pSibling;                 // update pointer to bypass letter
        free(current);                                      // deallocate the letter
        deleteWord(parent);                                 // make next call using parent
    }
    
    // Letter to be removed is not directly connected to parent and in middle of siblings
    else {
        Node *temp = parent->pChild;                        // use temp to traverse siblings
        while (temp->pSibling->letter != current->letter)   // until the node before the letter
            temp = temp->pSibling;
        temp->pSibling = current->pSibling;                 // detach letter from siblings
        free(current);                                      // deallocate letter
        deleteWord(parent);                                 // make next call using parent
    }
}


//---------------------------------------------------------------------------------------------------------//
// Removes the word from dictionary if found. Handle error checking and user feedback for command.
// Calls deleteWord() when letter nodes need to be deleted from the trie.
// @param {Node*} dictionary - points to the trie with all the stored words
// @param {Node*&} root - stores the last letter of the string suffix previously fetched by command F
// @param {int&} error - boolean for whether input error has occurred.
void commandD (Node *dictionary, Node *&root, bool &error) {
    char *str;
    if ((str  = getSuffix()) == NULL) { // get valid input string
        cout << "Error: String contains non-alpha characters. Retry command." << endl;
        error = true;
        return;
    }
    
    int size = strlen(str);                             // get size of input string
    Node *current = findStr(dictionary, str, 0, size);  // find the string in the dictionary, save last letter
    free(str);                                          // deallocate string, not needed anymore

    if (current == NULL) {                              // if string not found
        cout << "Word not found." << endl;              // display feedback and do nothing else
        return;
    }
    
    if (current->pChild != NULL && current->completeWord == true) {  // string is part of other words
        current->completeWord = false;                           // simply mark as incomplete word without deleting
        cout << "Word deleted. Part of a larger word(s)." << endl;
    }
    else {
        current->completeWord = false;         // mark as incomplete word anyway to avoid base case in deleteWord()
        deleteWord(current);                   // if string found and not part of larger word, call delete function
        cout << "Word deleted." << endl;       // display feedback
    }
    root = NULL;     // reset root so that command P cannot try to access a deleted node,
                     // this forces user to use command f again before trying to use command p.
}
//---------------------------------------------------------------------------------------------------------//
// Deallocates the entire dictionary trie. Used upon program exit.
// Implements DFS to free the nodes until only the root node remains, and then frees that too.
// @param {Node*} dictionary - points to the trie with all the stored words
void deleteDictionary (Node *dictionary) {
    Node *current = dictionary->pChild;     // used as iterator to traverse and delete nodes
    Node *parent = NULL;                    // used for moving up levels
    
    if (current == NULL) {                  // if no words in dictionary
        free(dictionary);                   // just free root node
        return;
    }
    while (current != dictionary) {         // perform DFS traversal until only root node remains
        if (current->pChild != NULL) {      // if current letter has a child letter
            current = current->pChild;      // then go one more level down to next child
        }
        else if (current->pChild == NULL && current->pSibling->letter == '*') { // If no child or siblings
            parent = current->pSibling->pChild;  // set parent by going up one level using end node
            Node *temp = current->pSibling;      // set a temp pointer to the end node
            free(temp);                          // deallocate the end node
            free(current);                       // deallocate the lone letter node
            parent->pChild = NULL;               // pointer now points to freed node, so set to null
            current = parent;                    // set current to parent since we move iterator back to previous level
        }
        else if (current->pChild == NULL && current->pSibling->letter != '*') { // If no child, but has siblings
            parent = current;                      // set parent to current node
            while (parent->letter != '*') {        // traverse through siblings until end node reached
                parent = parent->pSibling;
            }
            parent = parent->pChild;               // use end node loop up one level to point to parent
            
            parent->pChild = current->pSibling;    // update pointer to bypass letter node to be deleted
            free(current);                         // deallocate the letter node
            current = parent->pChild;              // set current point to the sibling of the deleted letter node
        }
    }
    free(dictionary);                              // deallocate root note that remains
}


//---------------------------------------------------------------------------------------------------------//
int main(int argc, const char * argv[]) {
    programInfo();
    
    // Create rhyming dictionary
    char fileName[] = "dictionary.txt";              // *** USE THIS LINE TO CHANGE INPUT FILE ***
    Node *dictionary = createDictionary(fileName);
    
    char ch;                // stores single character from buffer
    bool error = false;     // if error encountered
    Node *root;             // last letter of suffix
    
    displayMenu();
    cout << "Enter command: ";
    while ((ch = getNextNWSChar() ) != EOF) {
        error = false;          // reset boolean to false

        switch (ch) {
            case 'f': {
                commandF(dictionary, root, error);
                break;
            }
            case 'p': {
                commandP(root, error);
                break;
            }
            case 'a': {
                commandA(dictionary, error);
                break;
            }
            case 'd': {
                commandD(dictionary, root, error);
                break;
            }
            case '?': {
                commandH();
                break;
            }
            case 'x': {
                cout << "Exiting program." << endl;
                deleteDictionary(dictionary);
                return 0;
            }
            default:
                clearToEoln();
                cout << "Error: Invalid command. Use '?' for detailed commands." << endl;
                error = true;
        }
        if (error) {
            clearToEoln();
            cout << "Enter command: ";
            continue;
        }
        
        cout << "\n--------\n" << endl;
        clearToEoln();
        displayMenu();
        cout << "Enter command: ";
    }
    
    return 0;
}
