#include <iostream>
#include <string>
#pragma once

//Evaluator class that calculates and animates expressions
class Evaluator {

	

public:
	Evaluator(); //Constructor

	void evaluate(std::string s); //Function to evaluate the expression and print result animated

	int calculate(int num1, int num2, char sign); //Used for two number calculations

	std::string readFile(std::string file); //Reads input file
};