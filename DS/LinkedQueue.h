
#ifndef LINKED_QUEUE_
#define LINKED_QUEUE_
#include "Node.h"
#include "QueueADT.h"
#include <iostream>
using namespace std;

template <typename T>
class LinkedQueue:public QueueADT<T>
{
protected :
	Node<T>* backPtr;
	Node<T>* frontPtr;
public :
	LinkedQueue();	
	virtual bool isEmpty() const ;
	virtual bool enqueue(const T& newEntry);
	virtual bool dequeue(T& frntEntry);  
	virtual bool peek(T& frntEntry)  const;	
	virtual void print() const;
	~LinkedQueue();
};

template <typename T>
LinkedQueue<T>::LinkedQueue()
{
	backPtr=nullptr;
	frontPtr=nullptr;

}
template <typename T>
bool LinkedQueue<T>::isEmpty() const
{
	return (frontPtr==nullptr);
}

template <typename T>
bool LinkedQueue<T>::enqueue( const T& newEntry)
{
	Node<T>* newNodePtr = new Node<T>(newEntry);
	// Insert the new node
	if (isEmpty())	//special case if this is the first node to insert
		frontPtr = newNodePtr; // The queue is empty
	else
		backPtr->setNext(newNodePtr); // The queue was not empty

	backPtr = newNodePtr; // New node is the last node now
	return true ;
} // end enqueue

template <typename T>
bool LinkedQueue<T>:: dequeue(T& frntEntry)  
{
	if(isEmpty())
		return false;

	Node<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
		backPtr = nullptr ;	
		
	// Free memory reserved for the dequeued node
	delete nodeToDeletePtr;

	return true;
}

template <typename T>
bool LinkedQueue<T>:: peek(T& frntEntry) const 
{
	if(isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}

template <typename T>
LinkedQueue<T>::~LinkedQueue()
{
	T temp;
	while(dequeue(temp));
}


template <typename T>
void LinkedQueue<T>::print() const
{
	if (isEmpty())
		return;
	Node<T>* temp = frontPtr;
	while (temp->getNext())
	{
		cout << temp->getItem()<<", ";
		temp = temp->getNext();
	}

	cout << temp->getItem();
}

#endif