// 
// Program.fs
// Project 17 - Rainfall Analysis
//      Uses rainfall data collected at Chicago Midway Airport
//      and computes the average rainfall for each month and year
//      as well as the lowest and highest
//      record rainfall.
//
// Created by Revanth Reddy on 2/16/15.
// Language: F#
// Environ: Windows 10, Visual Studio 2013 Update 4
//
// Copyright (c) 2015 Revanth Reddy. All rights reserved.
//

#light

//
// ReadFile: reads a file line by line, returning a list
// of strings, one per line.
//
let ReadFile filename = 
  [ for line in System.IO.File.ReadLines(filename) -> line ]


//
// ParseLine: given a line from the rainfall file, parses this
// string into a tuple (year, values) where values is a list of
// the 12 rainfall data values for year.
//
let ParseLine (line:string) = 
  let strings = line.Split('\t')
  let strlist = Array.toList(strings)
  let year    = System.Int32.Parse(strlist.Head)
  let values  = List.map System.Double.Parse strlist.Tail
  (year, values)

//
// Given a tuple (year, values), prints these to the console
//
let PrintYearData (year:int, values:double list) = 
  printfn ""
  printfn "%A: %A" year values


// Compute and print yearly average rainfall 
let ComputeYearAvgs rainfall = 
  // Create and print a list of 2-tuples (year, averageRainfallPerYear)
  let averages = List.map (fun (year:int, value:double list) -> year, List.average value) rainfall
  List.iter(fun (year:int, avg:double) -> printfn "%A: %A" year avg) averages

// Compute and print montly average rainfall
let ComputeMonthAvgsHelper rainfall monthNum = 
  let perMonth = List.map (fun (year, values:double list) -> values.Item(monthNum)) rainfall
  List.average perMonth

let ComputeMonthAvgs rainfall =
  let MonthNames = ["Jan"; "Feb"; "Mar"; "Apr"; "May"; "Jun"; "Jul"; "Aug"; "Sep"; "Oct"; "Nov"; "Dec" ]
  let MonthIndex = [0 .. 11]
  let MonthAvgs = List.map (fun monthNum -> ComputeMonthAvgsHelper rainfall monthNum) MonthIndex
  List.iter2 (fun month avg -> printfn "%s: %A" month avg) MonthNames MonthAvgs

// Helper function for GetMax to determine month of max
let FindIndexMax value =
  let yrMax = List.max value                      // get min from value list
  List.findIndex (fun elem -> yrMax = elem) value // return index of min

// Helper function for GetMax to determine month of min
let FindIndexMin value =
  let yrMin = List.min value                      // get min from value list
  List.findIndex (fun elem -> yrMin = elem) value // return index of min

// Uses rainfall data to find and print the max of the entire data set
let GetMax rainfall = 
  // Create a list of 3-tuples (rainfall, month, year)
  let YearMax = List.map (fun (year:int, value:double list) ->  List.max value, (FindIndexMax value)+1, year) rainfall
  // Find 3-tuple with the max rainfall value
  let FullSetMax  = List.maxBy (fun (value, month, year) -> value) YearMax
  // Print max 3-tuple
  printfn "Max rainfall:  %A, %A/%A" <||| FullSetMax

// Uses rainfall data to find and print the min of the entire data set
let GetMin rainfall =
  // Create a list of 3-tuples (rainfall, month, year)
  let YearMin = List.map (fun (year:int, value:double list) ->  List.min value, (FindIndexMin value)+1, year) rainfall
  // Find 3-tuple with the min rainfall value
  let FullSetMin  = List.minBy (fun (value, month, year) -> value) YearMin
  // Print min 3-tuple
  printfn "Min rainfall:  %A, %A/%A" <||| FullSetMin

//
// Main:
//
[<EntryPoint>]
let main argv = 
  // read entire file as list of strings and parse into a list
  let file = ReadFile "rainfall-midway.txt"
  let rainfall = List.map ParseLine file

  // Program greeting
  printfn "** Rainfall Analysis Program ** "
  printfn ""

  // Compute and display yearly averages
  ComputeYearAvgs rainfall
  printfn ""

  // Compute and display monthly averages
  ComputeMonthAvgs rainfall
  printfn ""

  // Fetch max and min rainfall
  GetMax rainfall
  GetMin rainfall

  // done:
  printfn ""
  printfn "** Done **"
  printfn ""
  0 // return 0 => success
