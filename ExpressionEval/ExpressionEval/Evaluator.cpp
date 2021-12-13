#include <iostream> 
#include <string>
#include <fstream>
#include "Evaluator.h"
#include "CharStack.h"
#include "IntStack.h"
#include <windows.h>

using namespace std;

Evaluator::Evaluator() {};

//Handle used for displaying
HANDLE out;

//Fuction to move the cursor in order to display the results
void gotoxy(int x, int y)
{

	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	out = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(out, &csbiInfo);
	csbiInfo.dwCursorPosition.X = x;
	csbiInfo.dwCursorPosition.Y = y;
	SetConsoleCursorPosition(out, csbiInfo.dwCursorPosition);
}

//Prints the 2 number equation animated below the stacks
void printEquation(int num1, int num2, char op, int result)
{
	//clears ares
	gotoxy(46, 19);
	cout << "              ";

	//second number
	gotoxy(46, 19);
	cout << num2;
	Sleep(1000);

	//operator
	cout << " " << op <<" ";
	Sleep(1000);

	//first number
	cout << num1;
	Sleep(1000);

	//Equal sign
	cout << " = ";
	Sleep(1000);

	//Result
	cout << result;
}

//Reads the input file and return the equation to be used
string Evaluator::readFile(string file)
{
	fstream in;
	in.open(file);

	//get entire equation
	string line;
	getline(in, line);

	//return full line of text
	return line;
}

//Function to return precedence of operators 
int prec(char c)
{
	//Multiplication and division come first
	if (c == '*' || c == '/')
		return 2;
	//Addition and subtraction come second
	else if (c == '+' || c == '-')
		return 1;
	//Catch case
	else
		return -1;
}

////Function to evaluate the expression and print result animated
void Evaluator::evaluate(string s)
{
	//The two stacks used
	CharStack StackOps;
	IntStack stackNums;

	//Push initial char into stack
	StackOps.push('N');

	int l = s.length(); //Used for length of string

	string tempNum; //Used to store two digit numbers

	//Numbers used in equations
	int numOne;
	int numTwo;

	//Initialize character stack
	StackOps.printCharStack();

	//Go character by character through string
	for (int i = 0; i < l; i++)
	{

		//If character is a number 
		if (s[i] >= 48 && s[i] <= 57)
		{
			//check for multi digit number

			tempNum = s[i]; //first digit

			//go through string adding digits to string until total number
			while(i < s.length() - 1 && isdigit(s[i + 1]))
			{
				tempNum += s[++i];
			}

			//push the int form of total string and display
			stackNums.push(stoi(tempNum));
			stackNums.printIntStack();
		}

		// If the scanned character is a (, push it to the stack. 
		else if (s[i] == '(')
		{
			StackOps.push('(');
			StackOps.printCharStack(); //display new addition
		}

		// If the scanned character is a ), pop and perform equations from the stack until a ( is encountered. 
		else if (s[i] == ')')
		{
			//Go until a ( is found or empty
			while (StackOps.peek() != 'N' && StackOps.peek() != '(')
			{
				//store operator
				char c = StackOps.peek();

				//pop operator
				StackOps.pop();

				//store two top numbers from stack
				numOne = stackNums.pop();
				numTwo = stackNums.pop();

				//Push the calculated number
				stackNums.push(calculate(numOne, numTwo, c));

				//Display changed stacks after equation
				StackOps.printCharStack();
				stackNums.printIntStack();
			}
			//Once ( is reached, pop it out
			if (StackOps.peek() == '(')
			{
				char c = StackOps.peek();
				StackOps.pop();
			}
		}

		//If an operator is scanned 
		else {
			//Go until empty or operator of higher precidence is found
			while (StackOps.peek() != 'N' && prec(s[i]) <= prec(StackOps.peek()))
			{
				//store operator
				char c = StackOps.peek();

				//pop operator
				StackOps.pop();

				//store two top numbers from stack
				numOne = stackNums.pop();
				numTwo = stackNums.pop();

				//Push the calculated number
				stackNums.push(calculate(numOne, numTwo, c));

				//Display changed stacks after equation
				StackOps.printCharStack();
				stackNums.printIntStack();
			}
			//Push the operator, display and continue
			StackOps.push(s[i]);
			StackOps.printCharStack();
		}

	}

	// Pop all the remaining elements from the stack 
	while (StackOps.peek() != 'N')
	{
		//store operator
		char c = StackOps.peek();

		//pop operator
		StackOps.pop();

		//store two top numbers from stack
		numOne = stackNums.pop();
		numTwo = stackNums.pop();
		
		//Push the calculated number
		stackNums.push(calculate(numOne, numTwo, c));

		//Display changed stacks after equation
		StackOps.printCharStack();
		stackNums.printIntStack();
	}

	//Go to center and display final result
	gotoxy(50, 21);
	cout << stackNums.pop();
}

//Function used for two number equations
int Evaluator::calculate(int num1, int num2, char sign)
{
	int result; //Store result

	//Addition
	if (sign == '+')
	{
		result = (num2 + num1);
	}

	//Subtraction
	if (sign == '-')
	{
		result = (num2 - num1);
	}

	//Multiplication
	if (sign == '*')
	{
		result = (num2 * num1);
	}

	//Division
	if (sign == '/')
	{
		result = (num2 / num1);
	}

	//Animate equation
	printEquation(num1, num2, sign, result);

	return result;
}

