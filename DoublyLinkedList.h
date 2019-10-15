/*
Class: DoublyLinkedList
Author: Dan Luoma
Description: A container for storing a linked list of a template type. Nodes can accessed either forwards or backwards
*/
#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <cstdlib>
#include <iostream>

/*
Structure: Node
Author: Dan Luoma
Description: Used to store the data for each entry, as well as two pointers to the nodes before and after it
*/
template <class T>
struct Node
{
	T First;
	T Second;
	Node *Next;
	Node *Prev;
};

template <class T>
class DoublyLinkedList
{
public:
	//constructor
	DoublyLinkedList();

	//mutators
	void addNode(T first, T second);
	bool deleteNode(T search);
	void deleteRear();

	//accessors
	Node<T> *getRear() const;
	int getSize() const;

	//deconstructor
	~DoublyLinkedList();

private:
	Node<T> *Head;
	Node<T> *Tail;
	int size;
};

/*
Function: DoublyLinkedList()
Author: Dan Luoma
Description: Initializes head node of list. Sets @param *Head and @param *Tail to head node.
*/
template <class T>
DoublyLinkedList<T>::DoublyLinkedList()
{
	this->Head = new Node<T>;
	Head->Next = NULL;
	Head->Prev = NULL;
	size = 0;
	Tail = Head;
}

/*
Function: addNode(T first, T second)
Author: Dan Luoma
Description: Used to add nodes at the end of a DoublyLinkedList.
Inputs: A template object
Outputs: A node containing the objects data
*/
template <class T>
void DoublyLinkedList<T>::addNode(T first, T second)
{
	Node<T> *p = this->Head;

	while (p->Next != NULL)
	{
		p = p->Next;
	}

	Node<T> *n = new Node<T>;
	n->First = first;
	n->Second = second;
	n->Next = NULL;
	n->Prev = p;

	p->Next = n;
	Tail = n;

	size++;
}

/*
Function: deleteNode(T search)
Author: Dan Luoma
Description: Searches for a node containing @param search, then deletes the node while maintaining continutity of DoublyLinkedList
Inputs: A template search object
*/
template <class T>
bool DoublyLinkedList<T>::deleteNode(T search)
{
	if (this->findNode(search) == false)
	{
		return false;
	}
	else
	{
		Node<T> *delPtr = new Node<T>;
		if (this->Tail->Data == search) //Ensures @param *Tail points to a valid node after deletion
		{
			delPtr = this->Tail;
			this->Tail = this->Tail->Prev;
			this->Tail->Next = NULL;
		}
		else
		{
			Node<T> *p = this->Head;
			while (p->Next->Data != search)
			{
				p = p->Next;
			}

			delPtr = p->Next;
			p->Next = p->Next->Next;
			p->Next->Prev = p;
		}

		delete delPtr;
		size--;
		return true;
	}
}

/*
Function: deleteRear()
Author: Dan Luoma
Description: Used by the Maze class to delete the last entry in the DoublyLinkedList
*/
template<class T>
void DoublyLinkedList<T>::deleteRear()
{
	Node<T> *delPtr = new Node<T>;
	delPtr = this->Tail;
	this->Tail = this->Tail->Prev;
	this->Tail->Next = NULL;
	delete delPtr;
	size--;
}

/*
Function: getRear() const
Author: Dan Luoma
Description: Returns a pointer to @param Tail
Outputs: A pointer to a node object
*/
template<class T>
Node<T>* DoublyLinkedList<T>::getRear() const
{
	return this->Tail;
}

/*
Function: getSize() const
Author: Dan Luoma
Description: Returns the size of the DoublyLinkedList
Outputs: An integer containing the size of the DoublyLinkedList
*/
template<class T>
int DoublyLinkedList<T>::getSize() const
{
	return this->size;
}

/*
Function: ~DoublyLinkedList()
Author: Dan Luoma
Description: Standard deconstructor
*/
template<class T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
}

#endif
