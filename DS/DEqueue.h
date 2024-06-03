#pragma once
#include"QueueADT.h"
#include"doublyNode.h"

template<class T>
class DEqueue :public QueueADT<T>
{
	doublyNode<T>* frontPtr, * backPtr;
public:
	DEqueue();
	virtual bool isEmpty() const;
	virtual bool enqueue(const T& newEntry); //enqueuing from rear..Normal
	bool enqueueFront(const T& newEntry);
	virtual bool peek(T& frontEnrty) const; //peek the front..normal
	virtual bool peekBack(T& backEntry);
	virtual bool dequeue(T& FrontEntry); //dequeuing from front..Normal
	virtual bool dequeueBack(T& backEntry);
	void print();
	~DEqueue();
};

template<typename T>
DEqueue<T>::DEqueue()
{
	frontPtr = backPtr = nullptr;
}
template <typename T>
bool DEqueue<T>::isEmpty() const
{
	return (frontPtr == nullptr && backPtr==nullptr);
}

template <typename T>
bool DEqueue<T>::enqueue(const T& newEntry) //inserting normally at the back
{
	doublyNode<T>* newNodePtr= new doublyNode<T>(newEntry);
	if (isEmpty())
	{
		frontPtr = backPtr = newNodePtr;
	}
	else
	{
		backPtr->setNext(newNodePtr);
		newNodePtr->setPrev(backPtr);
		backPtr = newNodePtr;
	}
	return true;
}

template<typename T>
bool DEqueue<T>::enqueueFront(const T& newEntry)
{
	doublyNode<T>* newNodePtr = new doublyNode<T>(newEntry);
	if (isEmpty())
	{
		backPtr = newNodePtr;
		frontPtr = newNodePtr;
	}
	else
	{
		newNodePtr->setNext(frontPtr);
		frontPtr->setPrev(newNodePtr);
		frontPtr = newNodePtr;
	}
	return true;
}

template <typename T>
bool DEqueue<T>::peek(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;
}

template<typename T>
bool DEqueue<T>::peekBack(T& backEntry)
{
	if (isEmpty())
		return false;

	backEntry = backPtr->getItem();
	return true;
}

template <typename T>
bool DEqueue<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	doublyNode<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();

	if (backPtr == nodeToDeletePtr)				//Only one Node
	{
		frontPtr = backPtr = NULL;
	}
	else
	{
		frontPtr = frontPtr->getNext();
		frontPtr->setPrev(nullptr);
	}

	delete nodeToDeletePtr;
	return true;
}

template<typename T>
bool DEqueue<T>::dequeueBack(T& backEntry)
{
	if (isEmpty())
		return false;

	doublyNode<T>* nodeToDeletePtr = backPtr;
	backEntry = backPtr->getItem();

	
	if (frontPtr == nodeToDeletePtr)		//Only one Node
	{
		frontPtr = backPtr = nullptr;
	}
	else
	{
		backPtr = backPtr->getPrev();
		backPtr->setNext(nullptr);
	}

	delete nodeToDeletePtr;
	return true;
}

template<class T>
inline void DEqueue<T>::print()
{
	if (isEmpty())
		return;
	doublyNode<T>* temp = frontPtr;
	while (temp->getNext())
	{
		cout << temp->getItem() << ", ";
		temp = temp->getNext();
	}

	cout << temp->getItem();
}

template<class T>
DEqueue<T>::~DEqueue()
{
	T temp;
	while (dequeue(temp));
}
