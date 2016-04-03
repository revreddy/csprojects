//
//  main.cpp
//  Project 11 - Vector Basics
//      Create vectors and output sizeof(v), v.size(), v.capacity()
//      to observe its behavior
//
//  Created by Revanth Reddy on 1/12/15.
//  Language: C++
//  Envir: Windows 10, Visual Studios Community 2013 Update 4
//
//  Copyright (c) 2015 Revanth Reddy. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::endl;


//--------------------------------------------------------------------------------//
// Display program information
void programInfo() {
    cout << endl;
    cout << "******************************" << endl;
    cout << "Author: Revanth Reddy" << endl;
    cout << "Project 11: Vector Basics" << endl;
    cout << "******************************\n" << endl;
}

//--------------------------------------------------------------------------------//
int main(int argc, const char * argv[]) {
    programInfo();
    
    std::vector<std::string> V1;
    std::vector<int> V2;
    
    cout << "_____Iteration 0_____" << endl << endl;
    cout << "V1 details: " << endl;
    cout << "\tSize = " << sizeof(V1) << endl;
    cout << "\tNum of elements = " << V1.size() << endl;
    cout << "\tCapacity = " << V1.capacity() << endl << endl;
    
    cout << "V2 details: " << endl;
    cout << "\tSize = " << sizeof(V2) << endl;
    cout << "\tNum of elements = " << V2.size() << endl;
    cout << "\tCapacity = " << V2.capacity() << endl << endl;
    
    std::string s = "cs341";
    int n = 341;
    
    for (int i = 0; i < 2; ++i ) {
        for (int j = 0; j < 5; ++j) {
            V1.push_back(s);
            V2.push_back(n);
        }
        
        cout << "_____Iteration " << i+1 << "_____" << endl << endl;
        cout << "V1 details: " << endl;
        cout << "\tSize = " << sizeof(V1) << endl;
        cout << "\tNum of elements = " << V1.size() << endl;
        cout << "\tCapacity = " << V1.capacity() << endl<< endl;
        
        cout << "V2 details: " << endl;
        cout << "\tSize = " << sizeof(V2) << endl;
        cout << "\tNum of elements = " << V2.size() << endl;
        cout << "\tCapacity = " << V2.capacity() << endl;
        cout << endl;
    }
    
    return 0;
}
