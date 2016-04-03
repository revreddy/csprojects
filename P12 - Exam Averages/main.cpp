//
//  main.cpp
//  Project 12 - Exam Averages
//      Computes student exam averages from file input that contains
//      userID and three exam scores
//
//  Created by Revanth Reddy on 1/21/15
//  Language: C++
//  Envir: Windows 10, Visual Studios Community 2013 Update 4
//
//  Copyright (c) 2015 Revanth Reddy. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
using std::cout;
using std::endl;
using std::string;
using std::vector;


// Function prototypes
string parse_netid(const string &s, const string &delimiter, size_t &stop);
int parse_score(const string &s, const string &delimiter, size_t &stop);


// Class for student object
class Student {
public:
    // ------------------- Members ------------------------------------ //
    string netid;
    int exam1, exam2, exam3;
    
    // ------------------- Constructors ------------------------------- //
    // Default constructor with no arguments, initialize the members to default values
    Student() {
        netid = "null";
        exam1 = exam2 = exam3 = 0;
    }
    
    // Constructor that accepts a string
    // @param {string} s - represents one line of the input file containing the netid and 3 exam scores for one student
    Student(string s){
        size_t stop = 0;            // used to determine the last position of the substring
        string delimiter = ",";     // delimiter that separates the substrings
        
        // Initialize the members by parsing the string
        netid = parse_netid(s, delimiter, stop);
        exam1 = parse_score(s, delimiter, stop);
        exam2 = parse_score(s, delimiter, stop);
        exam3 = parse_score(s, delimiter, stop);
    }
    
    
    // ------------------------ Methods ------------------------------- //
    // Calculates the average score using the three exam scores for the student
    // @return {double} - computed average score
    double avg() {
        return (exam1 + exam2 + exam3)/3.0;
    }
    
    // Prints out student members
    void displayOutput() {
        cout << netid << ": avg = " << std::setprecision(5) << avg() << " based on exams "
        << exam1 << ", " << exam2 << ", " << exam3 << endl;
    }
};


//---------------------------------------------------------------------------------------------------------//
// Display program information
void programInfo() {
    cout << endl;
    cout << "******************************" << endl;
    cout << "Author: Revanth Reddy" << endl;
    cout << "Project 12: Exam Averages" << endl;
    cout << "******************************\n" << endl;
}


//---------------------------------------------------------------------------------------------------------//
// Parses the netid from a string
// @param {const string&} s - one line of the input file containing the netid and 3 exam scores for one student
// @param {const string&} delimiter - the value that separates the substrings
// @param {size_t&} stop - stores the index position where the delimiter is found
// @return {string} - the substring with the netid
string parse_netid(const string &s, const string &delimiter, size_t &stop){
    stop = s.find(delimiter);           // finds the index position of the first delimiter and save value to stop
    return s.substr(0, stop);           // parse the substring from the index 0 to stop and return the substring
}


//---------------------------------------------------------------------------------------------------------//
// Parses the exam scores from a string
// @param {const string&} s - one line of the input file containing the netid and 3 exam scores for one student
// @param {const string&} delimiter - the value that separates the substrings
// @param {size_t&} stop - stores the index position where the delimiter is found
// @return {int} - integer value of the exam score
int parse_score(const string &s, const string &delimiter, size_t &stop) {
    size_t start = stop + 1;              // increments the start position to after the previous delimiter
    stop = s.find(delimiter, start);      // updates the index position of the next delimiter and save value to stop
    string token = s.substr(start, stop); // parse the substring from index start to stop and stores the substring
    return atoi(token.c_str());           // converts string to c-string, then c-string to int, returns int
}


//---------------------------------------------------------------------------------------------------------//
int main(int argc, const char * argv[]) {
    programInfo();
    
    // Open file
    std::ifstream file("students.txt");
    std::istream_iterator<string> f_start(file), f_end;
    
    // Read file into vector
    vector<string> fileinput(f_start, f_end);
    
    // Construct student exam scores
    vector<Student> studentList;
    for (auto s : fileinput) {      // for each string of parsed file input
        studentList.push_back(s);   // construct a new student object and add to studentList vector
    }
    
    // Sort students by avg score
    sort(studentList.begin(), studentList.end(), [](Student &s1, Student &s2) {
        if (s1.avg() < s2.avg())
            return false;
        else if (s1.avg() > s2.avg())
            return true;
        else // if same average scores, then sort order by netid:
            return s1.netid < s2.netid;
    });
    
    // Print sorted student list with computed averages scores
    cout << "Exam averages (sorted by descending order, then by netid): \n" << endl;
    for (auto s : studentList) {
        s.displayOutput();
    }
    cout << endl;
    
    system("pause"); // for Windows
    return 0;
}
