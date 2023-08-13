// Name: Kevin Barrios
// NSHE ID: 2001697903
// Assignment 1 stack of cards
//  use linked lists and stack class to play accordian patience 
#include <cstdlib>
#include "myStack.h"

//default constructor
template <class type>
myStack<type>::myStack()
{
	size = 0;
	capacity = 5;
	stackElements = new type[capacity];
}

//copy constructor *uses our deep copy function*
template <class type>
myStack<type>::myStack(const myStack<type>& copy)
{
	copyStack(copy);
}

//assignemt operator copies rhs into current list
template <class type>
const myStack<type>& myStack<type>::operator=(const myStack<type>& rhs)
{
	if (this != & rhs)
	{
		clearStack();
		copyStack(rhs);
	}
	return *this;
}

//destructor
template <class type>
myStack<type>::~myStack()
{
	clearStack();
}

//our push function takes in an item and places it at the top of our stack
template <class type>
void myStack<type>::push(const type& item)
{
	//if we reach max capacity then we double our capactiy
	if(size == capacity)
	{
		//if doubling capacity is needed
		//we must update the stackElements array
		capacity = capacity*2;
		type temp[capacity];
		for(int i = 0; i < capacity/2; i++)
		{
			temp[i] = stackElements[i];
		}
		delete [] stackElements;
		stackElements = new type[capacity];
		for(int i = 0; i < capacity/2; i++)
		{
			stackElements[i] = temp[i];
		}
	}
	//place item on top of stack and increase our size
	stackElements[size] = item;
	size++;
}

//peek function just shows us the top of the stack
template <class type>
type myStack<type>::peek() const
{
	if(size == 0)
		throw std::out_of_range("out of range exception PEEK\n");
	else
	return stackElements[size-1];
}

//gives us size of stack
template <class type>
std::size_t myStack<type>::getSize() const
{
	return size;
}

//pop will return the top most element of stack then remove it from stack
template <class type>
type myStack<type>::pop()
{
	type temp = stackElements[size-1];
	size--;
	return temp;
}

//returns true if our stack is empty
template <class type>
bool myStack<type>::isEmpty() const
{
	if(size == 0)
		return true;
	else
		return false;
}

//emptys out the entire stack
template <class type>
void myStack<type>::clearStack()
{
	delete [] stackElements;
	size = 0;
	capacity = 0;
}

//deep copies our stack
template <class type>
void myStack<type>::copyStack(const myStack<type>& copyThisStack)
{
	size = copyThisStack.size;
	capacity = copyThisStack.capacity;
	stackElements = new type[capacity];
	for(int i = 0; i < size; i++)
		stackElements[i] = copyThisStack.stackElements[i];
}
