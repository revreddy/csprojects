// 
// Form1.cs
// Project 18 - Asian Options Pricing
//      Create a GUI in C# to allow user to input
//      desired values, run the simulation, and 
//      display output.
//
// Created by Revanth Reddy on 3/11/15.
// Language: C#
// Environ: Windows 10, Visual Studio 2013 Update 4
//
// Copyright (c) 2015 Revanth Reddy. All rights reserved.
//

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;
using System.Diagnostics;

namespace AsianOptionsPricing
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        public void textboxNumSimulations_TextChanged(object sender, EventArgs e)
        {

        }

        private void textboxInitialPrice_TextChanged(object sender, EventArgs e)
        {

        }

        private void textboxExercisePrice_TextChanged(object sender, EventArgs e)
        {

        }

        private void textboxUpperBound_TextChanged(object sender, EventArgs e)
        {

        }

        private void textboxLowerBound_TextChanged(object sender, EventArgs e)
        {

        }

        private void textboxInterestRate_TextChanged(object sender, EventArgs e)
        {

        }

        private void textboxTimeToMaturity_TextChanged(object sender, EventArgs e)
        {

        }

        private void textboxOutput_TextChanged(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void buttonRun_Click(object sender, EventArgs e)
        {
            // Parse values from textbox
            double initial = Convert.ToDouble(textboxInitialPrice.Text);
            double exercise = Convert.ToDouble(textboxExercisePrice.Text);
            double up = Convert.ToDouble(textboxUpperBound.Text);
            double down = Convert.ToDouble(textboxLowerBound.Text);
            double interest = Convert.ToDouble(textboxInterestRate.Text);
            long periods = Convert.ToInt64(textboxTimeToMaturity.Text);
            long sims = Convert.ToInt64(textboxNumSimulations.Text);

            // Start clock
            int start = System.Environment.TickCount;

            // Simulate option pricing
            double pricing = AsianOptionsPricing.Simulation(initial, exercise, up, down, interest, periods, sims);

            // Stop clock and calculate time elapsed
            int stop = System.Environment.TickCount;
            double elapsedTimeInSecs = (stop - start) / 1000.0;

            // Output pricing and time elapsed
            String pricingStr = Convert.ToString(Math.Round(pricing, 2));
            String timerStr = Convert.ToString(Math.Round(elapsedTimeInSecs, 2));
            textboxOutput.Text += "$" + pricingStr + " [" + timerStr + " secs]" + Environment.NewLine;
        }

        private void Form1_Load_1(object sender, EventArgs e)
        {

        }
    }
}

