#pragma once

#ifndef _LinkedList_
#define _LinkedList_

#include <assert.h>
#include <iostream>

template <typename eltType> class LinkedList;
template <typename eltType> class ListIterator;

// NODE
template <typename eltType> class Node
{
public:
	eltType m_Data;
	Node* m_Next;

private:

	Node(eltType info = 0, Node* link = nullptr) :
		m_Data(info), m_Next(link) {};

	friend class LinkedList<eltType>;
	friend class ListIterator<eltType>;
};


// LINKED LIST
template <typename eltType> class LinkedList
{
private:
	//get a (deep) copy of a node
	Node<eltType>* copy(Node<eltType>* node);
	//free nodes of a linked list
	void destroy(Node<eltType>* node);

public:
	// linked list pointer
	Node<eltType>* m_Tail;

	//default constructor
	LinkedList();

	//construct a deep copy of another linked list
	LinkedList(LinkedList& list);

	~LinkedList();

	//assign another linked list to this linked list (deep copy)
	LinkedList& operator=(const LinkedList& list);

	//is the linked list empty
	bool empty();

	bool find(eltType data);

	//ordered insert/remove
	void orderedInsert(eltType data);
	void insert(eltType data);
	void remove(eltType data);

	// Needed to use a list Iterator
	friend class ListIterator<eltType>;
};

template <typename eltType> std::ostream& operator<<(std::ostream& os, const LinkedList<eltType>& list);

//set up an iterator
//an object that provides a pointer to a linked list (in this case)
// LIST ITERATOR
template <typename eltType> class ListIterator
{
private:
	const LinkedList<eltType>& m_Iter;
	Node<eltType>* m_Curr;

public:
	//construct a list iterator
	ListIterator(const LinkedList<eltType>& list);

	//set m_Curr to point at the first node of iter
	void begin();
	//is m_Curr null
	bool more();
	//go to m_Curr->next
	void next();
	//get the value out of m_Curr's node
	eltType value();

	bool isEmpty();
	bool isFirstNode();
	bool isLastNode();

	void  insertInOrder(eltType data);
	void insertAtEnd(eltType data);

	eltType operator*(); //returns the data of the node currently pointed at
	void operator++(); //pre-increment
	void operator++(int); //post-increment

};


//construct an empty linked list
template <typename eltType> LinkedList<eltType>::LinkedList() : m_Tail(nullptr) {}

//copy constructor, copy() does the deep copy
template <typename eltType> LinkedList<eltType>::LinkedList(LinkedList<eltType>& list)
{
	m_Tail = copy(list.m_Tail);
}

//free all nodes
template <typename eltType >LinkedList<eltType>::~LinkedList()
{
	destroy(m_Tail);
}

//assignment operator: copy() does the deep copy
template <typename eltType> LinkedList<eltType>& LinkedList<eltType>::operator =(const LinkedList<eltType>& list)
{
	if (this != &list)
	{
		destroy(m_Tail);
		m_Tail = copy(list.m_Tail);
	}
	return *this;
}

// Place x into the list in order
template <typename eltType> void LinkedList<eltType>::orderedInsert(eltType data)
{
	if (empty())
	{
		Node<eltType>* newNode = new Node<eltType>(data);
		newNode->m_Next = newNode;
		m_Tail = newNode;
		return;
	}


	if (data > m_Tail->m_Data)
	{
		Node<eltType>* newNode = new Node<eltType>(data, m_Tail->m_Next);
		m_Tail->m_Next = newNode;
		m_Tail = newNode;

	}
	else
	{
		Node<eltType>* curr = m_Tail->m_Next;
		Node<eltType>* prev = m_Tail;

		while (curr != m_Tail && data > curr->m_Data)
		{
			prev = curr;
			curr = curr->m_Next;
		}

		assert((prev->m_Next = new Node<eltType>(data, curr)) != nullptr);
	}

}

template <typename eltType> void LinkedList<eltType>::insert(eltType data)
{
	if (empty())
	{
		Node<eltType>* newNode = new Node<eltType>(data);
		newNode->m_Next = newNode;
		m_Tail = newNode;
		return;
	}

	Node<eltType>* newNode = new Node<eltType>(data, m_Tail->m_Next);
	m_Tail->m_Next = newNode;
	m_Tail = newNode;
}

// Is this element in the linked list?
template <typename eltType> bool LinkedList<eltType>::find(eltType data)
{
	Node<eltType>* curr = m_Tail->m_Next;
	while (curr != m_Tail && curr->m_Data != data)
		curr = curr->m_Next;

	return curr->m_Data == data;
}

// Inline: Look into this.
template <typename eltType> inline bool LinkedList<eltType>::empty()
{
	return (m_Tail == nullptr);
}

//remove a node in an ordered list
//pre: node will be found
template <typename eltType> void LinkedList<eltType>::remove(eltType data)
{
	assert(!empty());

	Node<eltType>* curr = m_Tail->m_Next;
	Node<eltType>* prev = m_Tail;

	while (curr != m_Tail && curr->m_Data != data)
	{
		prev = curr;
		curr = curr->m_Next;
	}
	assert(!(curr == m_Tail && curr->m_Data != data)); // x is not in the LinkedList

	if (curr == m_Tail)
		m_Tail = m_Tail->m_Next;	// x is first in the LinkedList
	else
		prev->m_Next = curr->m_Next;	// x is farther down in the LinkedList
	delete curr;
}

// Remove all nodes in the linked list, starting at node
template <typename eltType> void LinkedList<eltType>::destroy(Node<eltType>* node)
{
	if (!node)
		return;

	Node<eltType>* curr = node->m_Next;

	while (curr != node)
	{
		Node<eltType>* doomed = curr;
		curr = curr->m_Next;
		delete doomed;
	}
	delete node;
}

// The deep copy. Copy the source list l, one node at a time
template <typename eltType> Node<eltType>* LinkedList<eltType>::copy(Node<eltType>* node)
{
	Node<eltType>* tail = nullptr;	// ptr to beginning of copied LinkedList
	Node<eltType>* curr = nullptr;	// ptr to last item insert in the copy
	if (node != nullptr)
	{
		assert((tail = curr = new Node<eltType>(node->m_Data, nullptr)) != nullptr);

		for (Node<eltType>* source = node->m_Next; source != node; source = source->m_Next, curr = curr->m_Next)
		{
			curr->m_Next = new Node<eltType>(source->m_Data, nullptr);
			assert(curr->m_Next);
		}
		curr->m_Next = tail;
	}
	return tail;
}

// Output a linked list, using a list iterator
template <typename eltType> std::ostream& operator<<(std::ostream& os, const LinkedList<eltType>& list)
{
	ListIterator<eltType> lt(list);

	for (lt.begin(); lt.more(); lt.next())
		os << lt.value() << " ";

	os << lt.value();
	return os;
}


/* ****************************************************************
   ************** List Iterator Implementations *******************
   ****************************************************************/

   // Construct a list iterator. It consists of:
   //	 a reference to a linked list object
   //	 a pointer to the actual list, initially pointing to its head
template <typename eltType> ListIterator<eltType>::ListIterator(const LinkedList<eltType>& list) : m_Iter(list), m_Curr(list.m_Tail ? list.m_Tail->m_Next : nullptr) {}

// Set m_Curr to point at iter's head
template <typename eltType> void ListIterator<eltType>::begin(void)
{
	m_Curr = m_Iter.m_Tail->m_Next;
}

// Is m_Curr at the end of the list?
template <typename eltType> bool ListIterator<eltType>::more(void)
{
	return m_Curr != m_Iter.m_Tail;
}

// Move m_Curr to next node
template <typename eltType> void ListIterator<eltType>::next(void)
{
	assert(m_Curr != nullptr);
	m_Curr = m_Curr->m_Next;
}

// Return data in m_Curr's node. Regardless of assert(), this 
//	function shouldn't be called until making sure more() returns true
template <typename eltType> eltType ListIterator<eltType>::value(void)
{
	assert(m_Curr != nullptr);
	return m_Curr->m_Data;
}

template <typename eltType> bool ListIterator<eltType>::isEmpty()
{
	return m_Iter.empty();
}

template <typename eltType> bool ListIterator<eltType>::isFirstNode()
{
	return m_Curr == m_Iter.m_Tail->m_Next;
}

template <typename eltType>
bool ListIterator<eltType>::isLastNode()
{
	return m_Curr == m_Iter.m_Tail;
}

template <typename eltType> eltType ListIterator<eltType>::operator*()
{
	return m_Curr->m_Data;
}

template <typename eltType> void ListIterator<eltType>::operator++()
{
	if (!m_Iter.empty())
		m_Curr = m_Curr->m_Next;
}

template <typename eltType> void ListIterator<eltType>::operator++(int)
{
	if (!m_Iter.empty())
		m_Curr = m_Curr->m_Next;
}

template <typename eltType> void ListIterator<eltType>::insertAtEnd(eltType data)
{
	m_Iter.insert(data);
}

template <typename eltType> void ListIterator<eltType>::insertInOrder(eltType data)
{
	m_Iter.orderedInsert(data);
}



#endif // !_Linkedlist_