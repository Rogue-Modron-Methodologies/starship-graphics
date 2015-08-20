//  Copyright 2015 Jamie Johnson.
//  This work is for educational purposes only.
//  No commercial use, duplication, or distribution is allowed.
//  All artwork belongs to Mayfair Games Inc.
//  www.mayfairgames.com
//  Used without permission for educational purposes only.
//
//  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

#ifndef Linked_List_H
#define Linked_List_H

#include "ListNode.h"

template <class T>
class LinkedList
{
private:
	// Declare structure for list nodes
	ListNode<T>	data;
	ListNode<T>*	front;					// Pointer to the head sentinel node
	ListNode<T>*	rear;					// Pointer to the rear sentinel node
	ListNode<T>*	curr;					// Pointer to the current node
	int			count;					// Count of total active nodes in the list
	bool			iconOnly;					// Flag for only displaying first node
	bool			smallDisplay;				// Flag to see if list is Large/Small Scale
	sf::Vector2f	scrPos;					// Screen Position for first card
	sf::Vector2f	cScale;					// Current scale of list

public:

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)
// Constructor                                     
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)
LinkedList()
{
	front = new ListNode<T>;		// SENTINEL
	rear = new ListNode<T>;		// SENTINEL

	front->setNext(rear);
	front->setPrev(NULL);

	rear->setNext(NULL);
	rear->setPrev(front);

	count = 0;
	iconOnly = true;	
	smallDisplay = true;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)
// Returns iconOnly flag value.     
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)
int showIconOnly() const{
	return iconOnly;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)
// Sets iconOnly flag value.     
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)
void setIconOnly(bool toggle) {
	iconOnly = toggle;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)
// Checks to see if Icon is Targeted.    
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)
bool isIconTargeted(sf::RenderWindow &gWindow) const{
	if (front->getNext())
		return front->getNext()->getData()->isTargeted(gWindow);
	else
		return false;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)
// Checks to see if any card in the List has been targeted   
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)
bool isZoneTargeted(sf::RenderWindow &gWindow, int &type) const
{
	ListNode<T> *walker;  

	walker = front->getNext();

	// While walker doesn't point to rear, traverse the list.
	while (walker != rear)
	{
		if (walker->getData()->isTargeted(gWindow))
		{
			type = walker->getData()->getType();
			return true;
		}
		walker = walker->getNext();
	}
	return false;
}


// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)
// Returns isSmall flag value.     
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)
int isSmall() const{
	return smallDisplay;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)
// Shows the number of Nodes in the list.    
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)
int getCount() const{
	return count;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)
// Inserts a node into the first available position of the list //////////////// needs to insert in sorted order       
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)
void insertNode(T* Card)
{
	ListNode<T> *newNode;             // A new node
	ListNode<T> *walker;              // To traverse the list

	// Allocate a new node and store the string.
	newNode = new ListNode<T>;
	newNode->setData(Card);
	
	// Position walker at the head of list.
	walker = front;

	// Proceed 
	while(walker->getNext() != rear){
		walker = walker->getNext();
	}
	// Insert node into the list after the walker's position.
	newNode->setNext(walker->getNext());
	newNode->setPrev(walker);
	walker->getNext()->setPrev(newNode);
	walker->setNext(newNode);
	count++;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)
//  Shows the value stored in the front node.                             
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)
void displayHead(sf::RenderWindow &gWindow) 
{
	ListNode<T> *walker;  // To move through the list

	if (count == 0)
		return;

	// Position walker after the front sentinel.
	walker = front->getNext();
	walker->getData()->draw(gWindow);

}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)
//  Shows the value stored in each node of the linked list in 
//  front to rear order.                             
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)
void displayList(sf::RenderWindow &gWindow) const{
	ListNode<T> *walker;  // To move through the list

	if (count == 0)
		return;

	walker = front->getNext();

	// While walker doesn't point to rear, traverse the list.
	while (walker != rear)
	{
		walker->getData()->draw(gWindow);
		walker = walker->getNext();
	}
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)
//  Checks to see if num is in the list                         
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)
bool findColonyResource(int num){
	ListNode<T> *walker;  // To move through the list
	bool flag = false;

	walker = front->getNext();

	while (walker != rear)
	{
		if (walker->getData()->getActNum() == num)
			return true;
		walker = walker->getNext();
	}
	return false;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)
//  Shows the value stored in each node of the linked list in 
//  front to rear order.                             
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)
bool getTradeResources(T* rtdAtry[], int& lineCount)
{
	ListNode<T> *walker;  // To move through the list
	lineCount = 0;
	bool flag = false;

	// Position walker after the front sentinel.
	walker = front->getNext();

	// While walker doesn't point to rear, traverse the list.
	while (walker != rear)
	{
		// Display the value in this node.
		rtdAtry[lineCount] = walker->getData();
		// Move to the next node.
		walker = walker->getNext();
		lineCount++;
		flag = true;
	}
	cout << endl;
	return flag;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)
//  Shows the value stored in each node of the linked list in 
//  front to rear order.                             
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)
void updateList(sf::Vector2f pos, sf::Vector2f scale)
{
	if (count == 0)
		return;

	ListNode<T> *walker;  // To move through the list
	int cardCnt = 0;

	// Position walker after the front sentinel.
	walker = front->getNext();

	// While walker doesn't point to rear, traverse the list.
	while (walker != rear)
	{
		// Update screen position and scale of Node.
		walker->getData()->setScale(scale);
		walker->getData()->setPosition(pos + sf::Vector2f{ 150.0f * cardCnt, 0 });
		// Move to the next node.
		walker = walker->getNext();
		cardCnt++;
	}
	if (scale == CRDZNSCL)
		smallDisplay = false;
	else
		smallDisplay = true;

}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)
// Destructor                                      
// This function deletes every node in the list.   
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)
~LinkedList()
{
	ListNode<T> *walker;   // To traverse the list

	// Position walker after the front sentinel.
	walker = front->getNext();

	// While walker is not at the end of the list...
	while (walker != rear)
	{
		// Save a pointer to the next node.
		walker = walker->getNext();

		// Delete the previous node.
		delete walker->getPrev();
	}
}

};

#endif

