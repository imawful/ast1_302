// Name: Kevin Barrios
// NSHE ID: 2001697903
// Assignment 1 stack of cards
//  use linked lists and stack class to play accordian patience
#include "LL.h"

template <class type>
typename LL<type>::iterator LL<type>::iterator::operator++(int)
{
	iterator current(position);
	position = position->next;

	return current;
}

template <class type>
typename LL<type>::iterator LL<type>::iterator::operator++()
{
	position = position->next;

	return *this;
}

template <class type>
typename LL<type>::iterator LL<type>::iterator::operator--(int)
{
	iterator current(position);
	position = position->prev;

	return current;
}

template <class type>
typename LL<type>::iterator LL<type>::iterator::operator--()
{
	position = position->prev;

	return *this;
}

//default constructor to allocate dummy and create empty LL
template <class type>
LL<type>::LL()
{
	dummy = new node;
	dummy->next = dummy;
	dummy->prev = dummy;
}

//copy constructor
template <class type>
LL<type>::LL(const LL<type>& copy)
{
	dummy = new node;
	dummy->next = dummy;
	dummy->prev = dummy;
	copyList(copy);
}

//assignment operator copies rhs to current list
template <class type>
const LL<type>& LL<type>::operator=(const LL<type>& rhs)
{
	if (this != &rhs)
	{
		clearList();
		copyList(rhs);
	}

	return *this;
}

//destructor * will call clear list *
template <class type>
LL<type>::~LL()
{
	clearList();
	delete dummy;
}


//head insert for linked list
template <class type>
void LL<type>::headInsert(const type& item)
{
	//first allocate a new node and copy our item into it
	node *newhead = new node;
	newhead->item = item;
	//if list is empty we simply have a LL with one node so
	//we can quickly set this up
	//if list is not empty then we must take the old head
	// move it over one spot and put the new head in front
	// this is done by updating the lists pointers
	if (isEmpty())
	{
		newhead->next = dummy;
		newhead->prev = dummy;
		dummy->prev = newhead;
		dummy->next = newhead;
	}
	else
	{
		newhead->next = dummy->next;
		dummy->next->prev = newhead;
		newhead->prev = dummy;
		dummy->next = newhead;
	}
}

//tail insert for linked list
template <class type>
void LL<type>::tailInsert(const type& item)
{
	//allocate new node with item
	node *newtail = new node;
	newtail->item = item;
	//if empty list quickly insert node
	//if list is not empty update the current list
	//to have our new node inserted at the tail
	if(isEmpty())
	{
		newtail->next = dummy;
		newtail->prev = dummy;
		dummy->next = newtail;
		dummy->prev = newtail;

	}
	else
	{
		newtail->next = dummy;
		newtail->prev = dummy->prev;
		dummy->prev->next = newtail;
		dummy->prev = newtail;
	}
}

//head remove we are going to get rid of the first node in our LL
template <class type>
void LL<type>::headRemove()
{
	if(isEmpty())
		return;

	//condition to check if the LL contains only one node
	//MAKE SURE TO DEALLOCATE NODES HERE USING DELETE
	// I LOST SO MANY HOURS OF SLEEP TRYING TO FIGURE OUT WHERE TO DEALLOCATE
	if(dummy->next->next == dummy)
	{
		delete dummy->next;
		dummy->next = dummy;
		dummy->prev = dummy;
	}
	//if more then one node then we update the list so that
	//our new head is the node that was after our previous head
	else
	{
		dummy->next = dummy->next->next;
		//REPEAT DELETE OLD NODES
		delete dummy->next->prev;
		dummy->next->prev = dummy;
	}


}

//tail remove we are going to get rid of the last node in our LL
template <class type>
void LL<type>::tailRemove()
{
	if(isEmpty())
		return;

	//condition to check if the LL contains only one node
	if(dummy->prev->prev == dummy)
	{
		//delete node we will nolonger use
		delete dummy->prev;
		dummy->next = dummy;
		dummy->prev = dummy;
	}
	//if more then one node then we update the list so that
	//our new tail is the node that was before our previous tail
	else
	{
		dummy->prev = dummy->prev->prev;
		//delete node that we will no longer use
		delete dummy->prev->next;
		dummy->prev->next = dummy;
	}
}

// using our iterator we are going to take the node before it and point it
// to the node after it so that our LL removes the node at position IT
template <class type>
void LL<type>::removeAtPosition(LL<type>::iterator & it)
{
	if(it.position == dummy->next)
	{
		headRemove();
		it.position = dummy->next;
	}
	else if(it.position == dummy->prev)
	{
		tailRemove();
		it.position = dummy->prev;
	}
	else
	{
		it++;
		it.position->prev = it.position->prev->prev;
		delete it.position->prev->next;
		it.position->prev->next = it.position;
	}

}

//use head remove to make our list empty
template <class type>
void LL<type>::clearList()
{
	while(!isEmpty())
		headRemove();

	return;
}

//deep copies list using tail insert
template <class type>
void LL<type>::copyList(const LL<type>& copyThisList)
{
	iterator follow = copyThisList.begin();
	for(follow; follow != copyThisList.end(); follow++)
		tailInsert(*follow);
}
