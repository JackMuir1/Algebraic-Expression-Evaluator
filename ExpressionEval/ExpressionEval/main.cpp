//Jack Muir
//900783742

#include <iostream>
#include <string>
#include "Evaluator.h"
using namespace std;

//Driver program
int main()
{
	//Create evaluator
	Evaluator e;
	string equation;

	//Enter string for equation below
	//Or store equation from input file - input file named "input.txt" - full address "c:\\temp\\input.txt"
	

	equation = "(3*5)+3-10";
	//equation = e.readFile("c:\\temp\\input.txt");

	//print intial equation
	cout << "                                              " << equation;

	//Evaluate the equation and print/animate result
	e.evaluate(equation);

	return 0;
}
