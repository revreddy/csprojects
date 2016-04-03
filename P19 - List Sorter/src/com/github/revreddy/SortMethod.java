package com.github.revreddy;

//
// Project 19 - List sorter
//      A simple command line interface to allow user to
//      choose options to create and sort a list of integers.
//      This program implements the Strategy Pattern approach
//      involving one main client class and three sort classes
//      implementing an interface.
//
// Created by Revanth Reddy 3/12/2015
// Language: Java
// Environ: Mac OSX 10.10, IntelliJ IDEA 14.0.3, Java 8
//
// Copyright (c) 2015 Revanth Reddy. All rights reserved.
//

import java.util.ArrayList;

public interface SortMethod {

    public ArrayList<Integer> sort(ArrayList<Integer> values);

}
