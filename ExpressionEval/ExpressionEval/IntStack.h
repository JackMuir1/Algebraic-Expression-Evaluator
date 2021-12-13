#pragma once

//Class for Stack of Ints
class IntStack {


public:

	IntStack() { top = -1; }; //Constructor, initializes top to -1

	int arr[15]; // Maximum size of Stack

	int top; //Value of the index of the top

	bool push(int x); //Adds item to top of stack
	
	int pop(); //Remove top item of stack

	int peek(); //Shows top item of stack

	bool isEmpty(); //Returns true if the stack is empty

	void printIntStack(); //Prints the stack graphically

};
