#include <iostream>
#include "IntStack.h"
#include <Windows.h>
#include <iomanip>
using namespace std;

//Handle used in display fucntions
HANDLE intOut;

//Fuction to move the cursor in order to display the stack
void moveIntCurs(int x, int y)
{
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	intOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(intOut, &csbiInfo);
	csbiInfo.dwCursorPosition.X = x;
	csbiInfo.dwCursorPosition.Y = y;
	SetConsoleCursorPosition(intOut, csbiInfo.dwCursorPosition);
}

//Prints the stack graphically
void IntStack::printIntStack()
{
	//Sets bottom bar in blue
	moveIntCurs(44, 16);
	SetConsoleTextAttribute(intOut, 18);
	cout << "    ";

	//Loops through elements of stack
	for (int i = 13; i >= 0 ; i--)
	{
		//Left Boundary of stack
		moveIntCurs(44, 15 - i);
		cout << " ";


		SetConsoleTextAttribute(intOut, 15); //return to white text

		//If element is not a null address
		if (arr[i] > -100 && arr[i] < 100)
		{ 
			//If element is at the top, animate it falling
			if (i == top)
			{
				//Animation, fall from top
				for (int j = 13; j >= i; j--)
				{
					//Left Boundary
					moveIntCurs(44, 15 - j);
					SetConsoleTextAttribute(intOut, 18);
					cout << " ";

					//Print two digit number
					SetConsoleTextAttribute(intOut, 15);
					cout << setw(2) << arr[i];
					Sleep(100);

					//Reset space after it has moved
					moveIntCurs(44, 15 - j);
					SetConsoleTextAttribute(intOut, 18);
					cout << " ";
					SetConsoleTextAttribute(intOut, 15);
					cout << "  ";
					SetConsoleTextAttribute(intOut, 18);
					cout << " ";
					SetConsoleTextAttribute(intOut, 15);
				}
			}
			//Permanently show stack item after it has fallen
			moveIntCurs(45, 15 - i);
			cout << setw(2) << arr[i]; 
			Sleep(100);
		}
		//If it is null, print empty space
		else
		{ 
			cout << "  "; 
		}
		//Righ boundary
		SetConsoleTextAttribute(intOut, 18);
		cout << " ";
	}
	SetConsoleTextAttribute(intOut, 15); //reset text color
}

//Adds an item to the top of the stack
bool IntStack::push(int x)
{
	//Limit of 15 on stack, show error if limit past
	if (top >= (15)) {
		cout << "Stack Overflow";
		return false;
	}
	//otherwise, add item and increment top
	else {
		arr[++top] = x;
		return true;
	}
}

//Removes an item from the top og the stack
int IntStack::pop()
{
	//Bottom case
	if (top < 0) {
		cout << "Stack Underflow";
		return 0;
	}
	//Otherwise remove top item and reset space
	else {
		char x = arr[top];
		arr[top--] = -1000;
		return x;
	}
}

//returns the top item of the stack
int IntStack::peek()
{
	//Bottom case
	if (top < 0) {
		cout << "Stack is Empty";
		return 0;
	}
	//Otherwise return top item
	else {
		char x = arr[top];
		return x;
	}
}

//Returns whether the stack is empty or not
bool IntStack::isEmpty()
{
	return (top < 0);
}
