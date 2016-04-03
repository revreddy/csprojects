//
//  main.cpp
//  Project 5 - Rhymes With
//      Create a dictionary and output words that rhyme with a user specified
//      word ending by finding all words that have the same word ending.
//
//  Created by Revanth Reddy on 11/20/14.
//  Language: C, C++
//  Envir: Mac OSX 10.10.1, Xcode 6.1
//  Tested on RHEL Server 5.11
//
//  Copyright (c) 2014 Revanth Reddy. All rights reserved.
//
//  Dictionary size has no limits, nor does retrieving the rhyming words.
//  Entering a single letter suffix will yield the largest number of potential matches.
//  The longest word stored in most reputable dictionaries ranges from 20-40 letters.
//  To provide additional flexibility, this program accepts words and suffixes up to 75 char.

#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cctype>
using namespace std;

// Constants
#define ALPHABET_SIZE 26            // 26 letters in the alphabet

// Nodes for dictionary
struct Node {
    char letter;                    // letter stored in node
    bool completeWord;              // does current letter create a complete word?
    Node *children[ALPHABET_SIZE];  // represents letters a to z for next letter in word
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
    puts ("Project 5: Rhymes With");
    puts ("**********************************\n");
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
    for (int i = 0; i < ALPHABET_SIZE; i++)     // set all pointers to null by default
        temp->children[i] = NULL;
    
    return temp;                                // return address to node
}


//---------------------------------------------------------------------------------------------------------//
// Allocate memory for a node, store letter, and set remaining struct members to defaults
// @param {char*} str - the letter to be saved in the node
// @return {Node*} temp - returns address to the new node
NodeWord *createNodeWord (char *str) {
    NodeWord *temp = (NodeWord*) malloc (sizeof(NodeWord)); // allocate memory for new node
    
    temp->word = str;                      // store letter char
    temp->pNext = NULL;                  // set pointer to default value of null
    
    return temp;
}

//---------------------------------------------------------------------------------------------------------//
// Adds the first letter of reversed word (last letter of ordered word), helper function for createDictionary()
// @param {Node**} dictionary - double pointer to the dictionary array of Node* for each letter of alphabet
// @param {char} letter - the first letter of reversed word to be added to dictionary
// @return {Node*} dictionary[index] - returns address to the node of the first letter being added
Node *addFirstLetter (Node **dictionary, char letter) {
    int index = letter - 'a';                   // find index that corresponds to letter
    
    if (dictionary[index] == NULL) {            // if no previous words entered for letter
        Node *newNode = createNode(letter);     // create new node for letter
        dictionary[index] = newNode;            // make dictionary point to new node
        return newNode;                         // return address to this new node
    }
    else                                        // if node for this letter already exists, simply...
        return dictionary[index];               // return address to this letter node
}


//---------------------------------------------------------------------------------------------------------//
// Adds remaining letters of reversed word, helper function for createDictionary()
// @param {Node*} current - pointer to the previous letter added in previous function call
// @param {char*} inputString - c-string containing the entire parsed word to be stored in dictionary
// @param {int} i - keeps track of index of the letter to add in this function call
void addRemainingLetters (Node *current, char *inputString, int i, int wordSize) {
    char letter = inputString[i];               // store next letter to be added
    int index = letter - 'a';                   // find index that corresponds to letter
    
    if (current->children[index] == NULL) {     // if no node for letter exists
        Node *newNode = createNode(letter);     // create new node for letter
        current->children[index] = newNode;     // make current node point to new node
        current = newNode;                      // update traversal pointer 'current' to this new node
    }
    else {                                      // if node for this letter already exists, simply...
        current = current->children[index];     // update traversal pointer 'current' to this new node
    }
    
    if (i < wordSize) {                         // more middle letters to add...
        addRemainingLetters(current, inputString, i+1, wordSize); // make another recursive call
    }
    else { // i == wordSize, last letter added
        current->completeWord = true;  // set boolean to true to signify complete word
    }
}


//---------------------------------------------------------------------------------------------------------//
// Read input file and store the letters/words into the dictionary
// @param {char[]} fileName - input file name with the dictionary words to be read
// @return {Node**} dictionary - double pointer to the dictionary Node* array containing all the words
Node **createDictionary (char fileName[]) {
    ifstream inStream;                              // file stream variable
    size_t inputSize = 75;                          // max word size accepted
    char *inputString = (char*)malloc(sizeof(char) * inputSize + 1);   // allocate c-string to hold word and null char
    bool foundNonAlphaChar = false;                 // boolean for when word has non-alphabet char
    int wordSize;                                   // stores length of input word
    int i;                                          // loop iterator
    Node *current;                                  // stores pointer to first letter of each word added to dictionary
    
    // Allocate array of pointers to nodes and initialize to null
    Node **dictionary = (Node**) malloc (sizeof(Node*) * ALPHABET_SIZE);
    for (i = 0; i < ALPHABET_SIZE; i++) {
        dictionary[i] = NULL;
    }
    
    inStream.open(fileName);                             // Open file and check if valid
    assert(!inStream.fail());
    
    // Add each word to dictionary
    cout << "Reading dictionary file...";
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
        
        i = 0;                                                          // reset iterator to index 0
        current = addFirstLetter(dictionary, inputString[i]);           // first letter and save its node location
        if (wordSize == 1)                                              // if word is only one letter
            current->completeWord = true;                               // set boolean to true to signify complete word
        if (wordSize > 1)                                    // if word is more than one letter... add remaining letters
            addRemainingLetters(current, inputString, i+1, wordSize-1); // to the node of first letter
    }
    
    cout << "Done" << endl << endl; // program feedback output
    inStream.close();               // close input file
    free(inputString);              // free memory for inputString
    return dictionary;              // returns address to dictionary
}


//---------------------------------------------------------------------------------------------------------//
// Finds all rhyming words that contains the suffix at the end of the word and saves them to a linked list.
//      Based on recursive depth first search algorithm. Helper function for getRhymingWords().
//      Resembles the displayWords() function.
// @param {Node*} current - points to the current letter to scan
// @param {char*} word - stores the letters of the word up the current function call
// @param {int} wordSize - stores the current word size
// @param {NodeWord*} wordListCurrent - points to the last node of the wordList linked list
// @param {int&} wordcount - tracks the current number of words stored in the wordList
void searchForRhymingWords(Node *current, char *word, int wordSize, NodeWord *&wordListCurrent, int &wordCount) {
    int i;                 // loop iterator
    
    if (current == NULL) { // base case to end recursion
        return;
    }
    else {
        for (i = 0; i < ALPHABET_SIZE; i++) {                 // for each letter in alphabet
            Node *child = current->children[i];               // save next potential letter
            if (child != NULL) {                              // if next potential letter has at least one word
                word[wordSize] = child->letter;               // append next letter to existing word
                word[++wordSize] = '\0';                      // add null terminating char
                
                if (child->completeWord == true) {                       // if current letter creates a complete word
                    char *c = (char*)malloc(sizeof(char) * wordSize +1); // allocate c-string to fit word and null char
                    strcpy(c, word);                                     // copy current word to c-string
                    strReverse(c);                                       // reverse the word back to its proper order
                    wordListCurrent->pNext = createNodeWord(c);          // save word to new node and add to wordList
                    wordListCurrent = wordListCurrent->pNext;            // update pointer to newly added node
                    wordCount++;                                         // increment wordCount
                }
                
                // make recursive call to find more words with current substring
                searchForRhymingWords(child, word, wordSize, wordListCurrent, wordCount);
                
                word[--wordSize] = '\0';  // decrement word size and overwrite the last added char with a null char
            }
        }
    }
}


//---------------------------------------------------------------------------------------------------------//
// Uses suffix to traverse through the dictionary to a starting point, calls searchForRhymingWords() to
//      search and save rhyming words, then prints all rhyming words
// @param {Node**} dictionary - double pointer to the dictionary array of Node* for each letter of alphabet
// @param {char*} suffix - serves as a base word for finding the rhyming words
void getRhymingWords(Node **dictionary, char *suffix) {
    int suffixSize = strlen(suffix);
    
    // traverse to first letter of suffix  (note: suffix is in reversed order)
    int i = 0;                                              // index counter for suffix
    int index = suffix[i] - 'a';                            // get corresponding index of next letter
    Node* current = dictionary[index];                      // save address to each dicationary letter
    if (current == NULL) {                    // if first letter does not have any words stored in dictionary
        cout << "No rhyming words for this suffix" << endl; // print message
        return;                                             // end search
    }
    
    // Traverse to remaining letters of suffix
    for (i = 1; i < suffixSize; i++) {                          // for the remaining letters in suffix
        index = suffix[i] - 'a';                                // get corresponding index of next letter
        current = current->children[index];                     // update current to point to next letter
        if (current == NULL) {                                  // if next letter is not part of any words
            cout << "No rhyming words for this suffix" << endl; // print message
            return;                                             // end search
        }
    }
    
    NodeWord* wordList = createNodeWord(NULL);  // create head pointer for linked list to store rhyming words
                                                // initialize head pointer to a dummy node with no c-string
                                                // this avoids the need for base case if statement during
                                                // recursive calls for searchForRhymingWords(), saves cpu ops
    NodeWord* wordListCurrent = wordList;       // create traversal pointer and initial to same dummy node
    int wordCount = 0;                          // set starting word count to 0
    
    // Check if suffix is a complete word
    if (current->completeWord == true) {                          // if current letter creates a complete word
        char *c = (char*)malloc(sizeof(char) * suffixSize + 1);   // allocate c-string to fit word and null char
        strcpy(c, suffix);                                        // copy current word to c-string
        strReverse(c);                                            // reverse the word back to its proper order
        wordListCurrent->pNext = createNodeWord(c);               // save word to new node and add to wordList
        wordListCurrent = wordListCurrent->pNext;                 // update pointer to newly added node
        wordCount++;                                              // increment wordCount
    }
    
    // Find all words ending with the suffix
    searchForRhymingWords(current, suffix, i, wordListCurrent, wordCount);
    
    // Print rhyming words and free memory
    cout << "Found " << wordCount << " rhyming words:  " << endl;   // display number of words found
    
    wordListCurrent = wordList-> pNext;                     // skip dummy NodeWord
    free(wordList);                                         // deallocate dummy NodeWord
    while (wordListCurrent->pNext != NULL) {                // for every NodeWord until the last
        NodeWord *toDelete = wordListCurrent;               // update temp pointer to current node
        wordListCurrent = wordListCurrent->pNext;           // udpate persistent pointer to next node
        cout << toDelete->word << " ";                      // print rhyme word stored in current node
        free(toDelete->word);                               // deallocate c-string word
        free(toDelete);                                     // deallocate NodeWord
    }
    
    // Print and free last node
    cout << wordListCurrent->word << " ";                   // print rhyme word stored in last node
    free(wordListCurrent->word);                            // deallocate rhyme word c-string
    free(wordListCurrent);                                  // deallocate NodeWord
    free(suffix);                                           // deallocate suffix c-string
    cout << endl << endl;
}


//---------------------------------------------------------------------------------------------------------//
// Prompts user to input suffix to use for finding corresponding rhyming words
// @return {char*} suffix - c-string containing the reversed suffix input
char *getSuffix() {
    bool foundNonAlphaChar = false;                     // boolean for when word has non-alphabet char
    int suffixSize = 0;                                 // stores the c-string length
    int i;
    
    char *suffix = (char*) malloc (sizeof(char)*76);    // allocate memory for suffix upto 75 chars
    cout << "Enter the suffix to find rhyming words: "; // display prompt statement
    while (scanf("%s", suffix)) {                       // get suffix input
        suffixSize = strlen(suffix);                    // get length of suffix
        
        // Check for non-alpha chars
        for (i = 0; i < suffixSize; i++) {  // for each char in the word
            if (!isalpha(suffix[i])) {      // if isalpha returns 0 when char not in alphabet
                foundNonAlphaChar = true;   // set boolean to true since invalid char is found
                break;                      // stop looping, one invalid char makes whole word invalid
            }
        }
        if (!foundNonAlphaChar) {           // if non-alpha char is not found in suffix, accept input
            break;
        }
        
        // prompt again for invalid inputs
        foundNonAlphaChar = false;                          // else reset boolean back to false...
        cout << "Enter the suffix to find rhyming words: "; // and prompt again
    }
    convertToLowercase(suffix, suffixSize);                 // covert any upper case char to lower case
    strReverse(suffix);                                     // reverse the string char order
    
    return suffix;                                          // return valid suffix
}


//---------------------------------------------------------------------------------------------------------//
// Displays each word, helper function for displayDictionary()
// @param {Node*} current - points to the current letter to scan
// @param {string} word - saves the letters of the word up the current function call
void displayWords(Node *current, string word) {
    int i;                                               // loop counter
    
    if (current == NULL) {                               // base case to end recursion
        return;
    }
    else {
        for (i = 0; i < ALPHABET_SIZE; i++) {            // for each letter in alphabet
            Node *child = current->children[i];
            if (child != NULL) {                         // if current letter has at least one word
                word += child->letter;                   // append new letter to existing word
                
                if (child->completeWord == true) {                          // if current letter creates a complete word
                    char *c = (char*)malloc(sizeof(char) * word.size()+1);  // allocate c-string to fit word and null char
                    strcpy(c, word.c_str());                                // copy current word to c-string
                    strReverse(c);                                          // reverse the word back to its proper order
                    printf ("%s\n", c);                                     // print c-string for output ***
                    free(c);                                                // free c-string memory
                }
                displayWords(child, word);               // make recursive call to find more words with current substring
                word = word.substr(0, word.size()-1);    // undo last appended letter before going to next letter
            }
        }
    }
}


//---------------------------------------------------------------------------------------------------------//
// Displays all the words in the dictionary
// @param {Node**} dictionary - double pointer to the dictionary array of Node* for each letter of alphabet
void displayDictionary(Node **dictionary) {
    string word;
    for (int i = 0; i < ALPHABET_SIZE; i++) {       // for each letter in alphabet
        if (dictionary[i] != NULL) {                // if current letter has at least one word
            word = dictionary[i]->letter;           // save current letter to a string
            displayWords(dictionary[i], word);      // find and display all words for this letter
        }
    }
}


//---------------------------------------------------------------------------------------------------------//
// Deallocate memory used for the nodes storing the letters
// helper function for deleteDictionary(), resembles the displayWord() function
// @param {Node*} current - points to the current letter to scan
void deleteLetters(Node *current) {
    
    int i;                 // loop iterator
    if (current == NULL) { // base case to end recursion
        return;
    }
    else {
        for (i = 0; i < ALPHABET_SIZE; i++) {     // for each letter in alphabet
            Node *child = current->children[i];
            if (child != NULL) {                  // if current letter has at least one word
                deleteLetters(child);             // make recursive call to find more words with current substring
                free(child);                      // deallocate node
            }
        }
    }
}


//---------------------------------------------------------------------------------------------------------//
// Deallocate memory used by the dictionary, resembles the displayDictionary() function
// @param {Node**} dictionary - double pointer to the dictionary array of Node* for each letter of alphabet
void deleteDictionary(Node **dictionary) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {       // for each letter in alphabet
        if (dictionary[i] != NULL) {                // if current letter has at least one word
            deleteLetters(dictionary[i]);           // find and display all words for this letter
            free(dictionary[i]);                    // deallocate node
        }
    }
    free(dictionary);                               // deallocate array of node pointers
}



//---------------------------------------------------------------------------------------------------------//
int main(int argc, const char *argv[]) {
    programInfo();
    
    // Create rhyming dictionary
    char fileName[] = "dictionary.txt";              // *** USE THIS LINE TO CHANGE INPUT FILE ***
    Node **dictionary = createDictionary(fileName);
    //displayDictionary(dictionary);                 // use to print dictionary contents after making tree
    
    // Prompt user for suffix
    char* suffix = getSuffix();
    
    // Find and output words with matching suffix
    getRhymingWords(dictionary, suffix);
    
    // Free memory
    deleteDictionary(dictionary);
    
    cout << "Done" << endl;
    return 0;
}
