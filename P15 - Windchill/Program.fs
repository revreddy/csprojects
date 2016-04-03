//
// Program.fs
// Project 15 - Windchill
//     Basic program to compute the windchill.
//     Input:  temperature in degrees Fahrenheit
//     Output: wind chill temperatures listed for wind
//             speeds of 1mph to 20mph in 1mph increments.
//
// Created by Revanth Reddy on 2/7/15.
// Language: F#
// Environ: Windows 10, Visual Studio 2013 Update 4
//
// Copyright (c) 2015 Revanth Reddy. All rights reserved.
//


#light

let windchill T W = 
  let WC = 35.7 + 0.6*T - 35.7 * System.Math.Pow(W, 0.16) + 0.43 * T * System.Math.Pow(W, 0.16)
  WC

[<EntryPoint>]
let main argv = 
  printf "Please enter temperature (degrees F): "

  let input = System.Console.ReadLine()
  let T = System.Convert.ToDouble(input)
 
  let WS = [1.0 .. 20.0]
  let windchills = List.map (fun W -> windchill T W) WS
  
  printfn ""
  printfn "Windchills:"
  printfn "%A" windchills
  printfn ""
  0
