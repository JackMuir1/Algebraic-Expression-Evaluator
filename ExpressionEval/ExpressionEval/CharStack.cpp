#include <iostream>
#include "CharStack.h"
#include <Windows.h>
#include <iomanip>
#include <string>
using namespace std;

//Handle used in display fucntions
HANDLE charOut;

//Fuction to move the cursor in order to display the stack
void moveCharCurs(int x, int y)
{

	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	charOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(charOut, &csbiInfo);
	csbiInfo.dwCursorPosition.X = x;
	csbiInfo.dwCursorPosition.Y = y;
	SetConsoleCursorPosition(charOut, csbiInfo.dwCursorPosition);
}

//Prints the stack graphically
void CharStack::printCharStack()
{
	//Sets bottom bar in red
	moveCharCurs(55, 16);
	SetConsoleTextAttribute(charOut, 199);
	cout << "    ";

	//Loops through elements of stack
	for (int i = 14; i >= 0; i--)
	{

		//Left Boundary of stack
		moveCharCurs(55, 16 - i);
		cout << " ";

		SetConsoleTextAttribute(charOut, 15);//return to white text

		//If element is not a null address, also not printing initial char
		if (arr[i] > 39 && arr[i] < 64 && i != 0)
		{
			//show stack item after it has fallen
			moveCharCurs(56, 16 - i);
			cout << setw(2) << arr[i];
			Sleep(100);
		}
		//If it is initial char, print bottom bar
		else if(i != 0)
		{
			cout << "  ";
		}
		//Righ boundary
		SetConsoleTextAttribute(charOut, 199);
		cout << " ";
	}
	SetConsoleTextAttribute(charOut, 15); //reset text color
}

//Adds an item to the top of the stack
bool CharStack::push(char x)
{
	//Limit of 15 on stack, show error if limit past
	if (top >= (15)) {
		cout << "Stack Overflow";
		return false;
	}
	//otherwise, add item and increment top
	else {
		arr[++top] = x;
		//Animation, fall from top if not inital char
		if (x != 'N')
		{
			for (int j = 14; j >= top; j--)
			{
				//Left Boundary
				moveCharCurs(55, 16 - j);
				SetConsoleTextAttribute(charOut, 199);
				cout << " ";

				//Print two digit number
				SetConsoleTextAttribute(charOut, 15);
				cout << setw(2) << x;
				Sleep(100);

				//Reset space after it has moved
				moveCharCurs(55, 16 - j);
				SetConsoleTextAttribute(charOut, 199);
				cout << " ";
				SetConsoleTextAttribute(charOut, 15);
				cout << "  ";
				SetConsoleTextAttribute(charOut, 199);
				cout << " ";
				SetConsoleTextAttribute(charOut, 15);
			}
		}
		return true;
	}
}

//Removes an item from the top og the stack
char CharStack::pop()
{
	//Bottom case
	if (top < 0) {
		cout << "Stack Underflow";
		return 0;
	}
	//Otherwise remove top item and reset space
	else {
		char x = arr[top];
		arr[top--] = 100;
		//cout << x << " popped";
		return x;
	}
}

//returns the top item of the stack
char CharStack::peek()
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
bool CharStack::isEmpty()
{
	return (top < 0);
}
