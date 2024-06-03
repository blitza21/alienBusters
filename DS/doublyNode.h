#pragma once
template<typename T>
class doublyNode
{
	doublyNode<T>* next, * prev;
	T item;
public:
	doublyNode();
	doublyNode(const T& r_Item);
	void setItem(const T& r_Item);
	void setNext(doublyNode<T>* nextNodePtr);
	void setPrev(doublyNode<T>* prevNodePtr);
	T getItem() const;
	doublyNode<T>* getNext() const;
	doublyNode<T>* getPrev() const;
};
template<typename T>
doublyNode<T>::doublyNode()
{
	next = prev = nullptr;
}

template<typename T>
doublyNode<T>::doublyNode(const T& item)
{
	this->item = item;
	next = prev = nullptr;
}

template < typename T>
void doublyNode<T>::setItem(const T& r_Item)
{
	item = r_Item;
}

template < typename T>
void doublyNode<T>::setNext(doublyNode<T>* nextNodePtr)
{
	next = nextNodePtr;
}

template<typename T>
void doublyNode<T>::setPrev(doublyNode<T>* prevNodePtr)
{
	prev = prevNodePtr;
}

template < typename T>
T doublyNode<T>::getItem() const
{
	return item;
}

template < typename T>
doublyNode<T>* doublyNode<T>::getNext() const
{
	return next;
}

template < typename T>
doublyNode<T>* doublyNode<T>::getPrev() const
{
	return prev;
}