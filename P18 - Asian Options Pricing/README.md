###Project 18 - Asian Options Pricing
___

#####Decription
Create a GUI-based C# program using the source from the AsianOptionsPricing.cs file. The program as given performs Asian Options Pricing using Monte Carlo simulations (aka coin-flipping) to predict the market. This type of approach is surprisingly accurate if the number of simulation runs is large.
___

#####Requirements
The program must be written in C#, and you must build a GUI-based application that yields the same results as the console-based program. The GUI can be simple or not, but the user interface must having the following:
- allow the user to change the number of simulations to run- allow the user to modify any of the simulation parameters (initial price, exercise price, etc.)- provide reasonable defaults for each of the above values (use defaults from console app) — if you are using textboxes for the user to enter the values, this means the default values must be displayed in the textbox initially- display simulation result — price and elapsed time- allow the user to run as many simulations as he/she wantsAssume the user will provide valid input; input validation is not required.
Display the following defaults in the text input fields:
- Intial price = 30.0
- Exercise price = 30.0
- Upper Bound = 1.4
- Lower Bound = 0.8
- Interest Rate = 1.08
- Time to Maturity = 30
- Number of simulations = 5000000