#pragma once

//Class for Stack of Chars
class CharStack {
	

public:

	CharStack() { top = -1; }; //Constructor, initializes top to -1

	char arr[100]; // Maximum size of Stack

	int top; //Value of the index of the top

	bool push(char x); //Adds item to top of stack

	char pop(); //Remove top item of stack

	char peek(); //Shows top item of stack

	bool isEmpty(); //Returns true if the stack is empty

	void printCharStack(); //Prints the stack graphically

};