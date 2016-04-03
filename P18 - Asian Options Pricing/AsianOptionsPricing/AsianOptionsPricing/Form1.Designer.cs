// 
// Form1.Designer.cs
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


namespace AsianOptionsPricing
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.labelNumSimulations = new System.Windows.Forms.Label();
            this.labelInitialPrice = new System.Windows.Forms.Label();
            this.labelExercisePrice = new System.Windows.Forms.Label();
            this.labelUpperBound = new System.Windows.Forms.Label();
            this.labelLowerBound = new System.Windows.Forms.Label();
            this.labelInterestRate = new System.Windows.Forms.Label();
            this.labelTimeToMaturity = new System.Windows.Forms.Label();
            this.buttonRun = new System.Windows.Forms.Button();
            this.textboxNumSimulations = new System.Windows.Forms.TextBox();
            this.textboxInitialPrice = new System.Windows.Forms.TextBox();
            this.textboxExercisePrice = new System.Windows.Forms.TextBox();
            this.textboxUpperBound = new System.Windows.Forms.TextBox();
            this.textboxLowerBound = new System.Windows.Forms.TextBox();
            this.textboxInterestRate = new System.Windows.Forms.TextBox();
            this.textboxTimeToMaturity = new System.Windows.Forms.TextBox();
            this.textboxOutput = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // labelNumSimulations
            // 
            this.labelNumSimulations.AutoSize = true;
            this.labelNumSimulations.Location = new System.Drawing.Point(37, 320);
            this.labelNumSimulations.Name = "labelNumSimulations";
            this.labelNumSimulations.Size = new System.Drawing.Size(228, 25);
            this.labelNumSimulations.TabIndex = 0;
            this.labelNumSimulations.Text = "Number of Simulations";
            // 
            // labelInitialPrice
            // 
            this.labelInitialPrice.AutoSize = true;
            this.labelInitialPrice.Location = new System.Drawing.Point(37, 37);
            this.labelInitialPrice.Name = "labelInitialPrice";
            this.labelInitialPrice.Size = new System.Drawing.Size(117, 25);
            this.labelInitialPrice.TabIndex = 1;
            this.labelInitialPrice.Text = "Initial Price";
            // 
            // labelExercisePrice
            // 
            this.labelExercisePrice.AutoSize = true;
            this.labelExercisePrice.Location = new System.Drawing.Point(37, 83);
            this.labelExercisePrice.Name = "labelExercisePrice";
            this.labelExercisePrice.Size = new System.Drawing.Size(150, 25);
            this.labelExercisePrice.TabIndex = 2;
            this.labelExercisePrice.Text = "Exercise Price";
            // 
            // labelUpperBound
            // 
            this.labelUpperBound.AutoSize = true;
            this.labelUpperBound.Location = new System.Drawing.Point(37, 127);
            this.labelUpperBound.Name = "labelUpperBound";
            this.labelUpperBound.Size = new System.Drawing.Size(138, 25);
            this.labelUpperBound.TabIndex = 3;
            this.labelUpperBound.Text = "Upper Bound";
            // 
            // labelLowerBound
            // 
            this.labelLowerBound.AutoSize = true;
            this.labelLowerBound.Location = new System.Drawing.Point(37, 175);
            this.labelLowerBound.Name = "labelLowerBound";
            this.labelLowerBound.Size = new System.Drawing.Size(138, 25);
            this.labelLowerBound.TabIndex = 4;
            this.labelLowerBound.Text = "Lower Bound";
            // 
            // labelInterestRate
            // 
            this.labelInterestRate.AutoSize = true;
            this.labelInterestRate.Location = new System.Drawing.Point(37, 223);
            this.labelInterestRate.Name = "labelInterestRate";
            this.labelInterestRate.Size = new System.Drawing.Size(134, 25);
            this.labelInterestRate.TabIndex = 5;
            this.labelInterestRate.Text = "Interest Rate";
            // 
            // labelTimeToMaturity
            // 
            this.labelTimeToMaturity.AutoSize = true;
            this.labelTimeToMaturity.Location = new System.Drawing.Point(37, 271);
            this.labelTimeToMaturity.Name = "labelTimeToMaturity";
            this.labelTimeToMaturity.Size = new System.Drawing.Size(166, 25);
            this.labelTimeToMaturity.TabIndex = 6;
            this.labelTimeToMaturity.Text = "Time to Maturity";
            // 
            // buttonRun
            // 
            this.buttonRun.BackColor = System.Drawing.SystemColors.Control;
            this.buttonRun.ForeColor = System.Drawing.Color.Black;
            this.buttonRun.Location = new System.Drawing.Point(299, 367);
            this.buttonRun.Name = "buttonRun";
            this.buttonRun.Size = new System.Drawing.Size(146, 41);
            this.buttonRun.TabIndex = 7;
            this.buttonRun.Text = "Run";
            this.buttonRun.UseVisualStyleBackColor = false;
            this.buttonRun.Click += new System.EventHandler(this.buttonRun_Click);
            // 
            // textboxNumSimulations
            // 
            this.textboxNumSimulations.Location = new System.Drawing.Point(299, 317);
            this.textboxNumSimulations.Name = "textboxNumSimulations";
            this.textboxNumSimulations.Size = new System.Drawing.Size(146, 31);
            this.textboxNumSimulations.TabIndex = 8;
            this.textboxNumSimulations.Text = "5000000";
            this.textboxNumSimulations.TextChanged += new System.EventHandler(this.textboxNumSimulations_TextChanged);
            // 
            // textboxInitialPrice
            // 
            this.textboxInitialPrice.Location = new System.Drawing.Point(299, 31);
            this.textboxInitialPrice.Name = "textboxInitialPrice";
            this.textboxInitialPrice.Size = new System.Drawing.Size(146, 31);
            this.textboxInitialPrice.TabIndex = 9;
            this.textboxInitialPrice.Text = "30.0";
            this.textboxInitialPrice.TextChanged += new System.EventHandler(this.textboxInitialPrice_TextChanged);
            // 
            // textboxExercisePrice
            // 
            this.textboxExercisePrice.Location = new System.Drawing.Point(299, 80);
            this.textboxExercisePrice.Name = "textboxExercisePrice";
            this.textboxExercisePrice.Size = new System.Drawing.Size(146, 31);
            this.textboxExercisePrice.TabIndex = 10;
            this.textboxExercisePrice.Text = "30.0";
            this.textboxExercisePrice.TextChanged += new System.EventHandler(this.textboxExercisePrice_TextChanged);
            // 
            // textboxUpperBound
            // 
            this.textboxUpperBound.Location = new System.Drawing.Point(299, 124);
            this.textboxUpperBound.Name = "textboxUpperBound";
            this.textboxUpperBound.Size = new System.Drawing.Size(146, 31);
            this.textboxUpperBound.TabIndex = 11;
            this.textboxUpperBound.Text = "1.4";
            this.textboxUpperBound.TextChanged += new System.EventHandler(this.textboxUpperBound_TextChanged);
            // 
            // textboxLowerBound
            // 
            this.textboxLowerBound.Location = new System.Drawing.Point(299, 172);
            this.textboxLowerBound.Name = "textboxLowerBound";
            this.textboxLowerBound.Size = new System.Drawing.Size(146, 31);
            this.textboxLowerBound.TabIndex = 12;
            this.textboxLowerBound.Text = "0.8";
            this.textboxLowerBound.TextChanged += new System.EventHandler(this.textboxLowerBound_TextChanged);
            // 
            // textboxInterestRate
            // 
            this.textboxInterestRate.Location = new System.Drawing.Point(299, 220);
            this.textboxInterestRate.Name = "textboxInterestRate";
            this.textboxInterestRate.Size = new System.Drawing.Size(146, 31);
            this.textboxInterestRate.TabIndex = 13;
            this.textboxInterestRate.Text = "1.08";
            this.textboxInterestRate.TextChanged += new System.EventHandler(this.textboxInterestRate_TextChanged);
            // 
            // textboxTimeToMaturity
            // 
            this.textboxTimeToMaturity.Location = new System.Drawing.Point(299, 268);
            this.textboxTimeToMaturity.Name = "textboxTimeToMaturity";
            this.textboxTimeToMaturity.Size = new System.Drawing.Size(146, 31);
            this.textboxTimeToMaturity.TabIndex = 14;
            this.textboxTimeToMaturity.Text = "30";
            this.textboxTimeToMaturity.TextChanged += new System.EventHandler(this.textboxTimeToMaturity_TextChanged);
            // 
            // textboxOutput
            // 
            this.textboxOutput.Location = new System.Drawing.Point(21, 425);
            this.textboxOutput.Multiline = true;
            this.textboxOutput.Name = "textboxOutput";
            this.textboxOutput.ReadOnly = true;
            this.textboxOutput.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textboxOutput.Size = new System.Drawing.Size(470, 209);
            this.textboxOutput.TabIndex = 15;
            this.textboxOutput.TextChanged += new System.EventHandler(this.textboxOutput_TextChanged);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(12F, 25F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.LightBlue;
            this.ClientSize = new System.Drawing.Size(514, 686);
            this.Controls.Add(this.textboxOutput);
            this.Controls.Add(this.textboxTimeToMaturity);
            this.Controls.Add(this.textboxInterestRate);
            this.Controls.Add(this.textboxLowerBound);
            this.Controls.Add(this.textboxUpperBound);
            this.Controls.Add(this.textboxExercisePrice);
            this.Controls.Add(this.textboxInitialPrice);
            this.Controls.Add(this.textboxNumSimulations);
            this.Controls.Add(this.buttonRun);
            this.Controls.Add(this.labelTimeToMaturity);
            this.Controls.Add(this.labelInterestRate);
            this.Controls.Add(this.labelLowerBound);
            this.Controls.Add(this.labelUpperBound);
            this.Controls.Add(this.labelExercisePrice);
            this.Controls.Add(this.labelInitialPrice);
            this.Controls.Add(this.labelNumSimulations);
            this.Name = "Form1";
            this.Text = "Asian Option Stock Pricing";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label labelNumSimulations;
        private System.Windows.Forms.Label labelInitialPrice;
        private System.Windows.Forms.Label labelExercisePrice;
        private System.Windows.Forms.Label labelUpperBound;
        private System.Windows.Forms.Label labelLowerBound;
        private System.Windows.Forms.Label labelInterestRate;
        private System.Windows.Forms.Label labelTimeToMaturity;
        private System.Windows.Forms.Button buttonRun;
        private System.Windows.Forms.TextBox textboxNumSimulations;
        private System.Windows.Forms.TextBox textboxInitialPrice;
        private System.Windows.Forms.TextBox textboxExercisePrice;
        private System.Windows.Forms.TextBox textboxUpperBound;
        private System.Windows.Forms.TextBox textboxLowerBound;
        private System.Windows.Forms.TextBox textboxInterestRate;
        private System.Windows.Forms.TextBox textboxTimeToMaturity;
        private System.Windows.Forms.TextBox textboxOutput;
    }
}