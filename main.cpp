// Name: Kevin Barrios
// NSHE ID: 2001697903
// Assignment 1 stack of cards
//  use linked lists and stack class to play accordian patience 
#include "LL.h"
#include "LL.cpp"
#include "myStack.h"
#include "myStack.cpp"
#include <iostream>
#include <string>
using namespace std;

// writing the main game
int main()
{
	LL< myStack<string> > accordian;

	// deal cards one by one in a row from left to right
	string word;
	while(cin >> word)
	{
		myStack<string> oneCard; // temp stack to push cards
		oneCard.push(word);
		accordian.tailInsert(oneCard);
	}


//***DEFINING THE VARIBALES NEEDED FOR RUNNING THE GAME***
	// daisy, daisy 2 are the main iterators
	// daisy2 will remain still while daisy hops around to check for matches
	LL< myStack<string> >::iterator daisy, daisy2;
	// these booleans tell us if a match was found
	bool oneSpot = false;
	bool threeSpot = false;
	// ofRange keeps a flag if we can peek or not
	bool ofRange = false;
	// string temp holds the cards that we are moving around
	string temp;

	//set begginig condition and then start game loop
	daisy = accordian.begin();
	while(daisy2 != accordian.end())
	{
		//set the main place holder iterator equal to the iterator thats moving
		daisy2 = daisy;

		//quickly check if we are valid to check 3 neighbors to the left
		//store the result in ofRange
		LL< myStack<string> >::iterator tempit = daisy;
		for(int k = 0; k < 3-1; k++)
		{
			if(tempit == accordian.begin())
				ofRange = true;
			tempit--;
			if(tempit == accordian.begin())
				ofRange = true;
		}

		//if we are valid to check then go ahead and see if
		//we have a match 3 neighbors down
		if(!ofRange)
		{
			//move our moving iterator to the left 3 times
			for(int k = 0; k < 3; k++)
				daisy--;
			//if a match is found then we flag it
			//if no match then reset our moving iterator to the still iterator
			if((*daisy).peek()[0] == (*daisy2).peek()[0] || (*daisy).peek()[1] == (*daisy2).peek()[1])
				threeSpot = true;
			else
				daisy = daisy2;
		}

		//if we cant move 3 neighbors to left we then check immidiate neighbor
		if(!threeSpot)
		{
			//set up to make sure we only check immidiate if possilbe
			if(daisy != accordian.begin())
			{
				daisy--;
				//if a match is found then we flag
				//if no match then reset our moving iterator to the still one
				if((*daisy).peek()[0] == (*daisy2).peek()[0] || (*daisy).peek()[1] == (*daisy2).peek()[1])
					oneSpot = true;
				else
					daisy = daisy2;
			}
		}

		// if match is found stack the cards
		// then update our still iterator to the moving one
		// 		---- this will make sure we keep moving to left
		//		---- if possible
		// if no match found we "move over" to the next card/pile
		if(oneSpot || threeSpot)
		{
			temp = (*daisy2).pop();
			(*daisy).push(temp);
			if((*daisy2).isEmpty())
				accordian.removeAtPosition(daisy2);
			daisy2 = daisy;
		}
		else
		{
			daisy++;
			daisy2 = daisy;
		}


		// reset the match conditions
		oneSpot = false;
		threeSpot = false;
		ofRange = false;

	}

	//OUTPUT NUMBER OF STACKS
	LL< myStack<string> >::iterator it;
	int numofstacks = 0;
	for(it = accordian.begin(); it != accordian.end(); it++)
		numofstacks++;
	cout << numofstacks << " Stacks: ";
	for(it = accordian.begin(); it != accordian.end(); it++)
		cout << (*it).peek() << ":" << (*it).getSize()  << " ";

	cout << endl;
}
