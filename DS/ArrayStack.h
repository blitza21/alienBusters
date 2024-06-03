#ifndef ARRAY_STACK_
#define ARRAY_STACK_

#include "StackADT.h"
#include <iostream>
using namespace std;
template<typename T>
class ArrayStack : public StackADT<T>
{
	enum { MAX_SIZE = 1000 };
private:
	T items[MAX_SIZE];		// Array of stack items
	int top;                   // Index to top of stack
	
public:

	ArrayStack()
	{
		top = -1;
	}  // end default constructor

	bool isEmpty() const
	{
		return top == -1;	
	}  // end isEmpty

	bool push(const T& newEntry)
	{
		if( top == MAX_SIZE-1 ) return false;	//Stack is FULL

		top++;
		items[top] = newEntry;   
		return true;
	}  // end push

	bool pop(T& TopEntry)
	{
		if (isEmpty()) return false;
		
		TopEntry = items[top];		 
		top--;
		return true;
	}  // end pop
	
	bool peek(T& TopEntry) const
	{
		if (isEmpty()) return false;
		
		TopEntry = items[top];		 
		return true;
	}  // end peek


	void print() const
	{
		if (isEmpty())
			return;
		for (int i = top; i > 0; i--)
			cout << items[i]<< ", ";
		cout << items[0];
	}
}; // end ArrayStack

#endif
