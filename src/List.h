/*
 * Author: Vien Van
 * Name: List.h
 * Description: Creating accessors, mutators, copy constructors, and iterators for doubly linked list.
 * Date: 02/06/2017
 */

#ifndef LIST_H_
#define LIST_H_

#include <fstream>
#include <cstddef> //for NULL

template <class listdata> //list stores generic listdata, not any specific C++ type

class List
{
    private:
		struct Node
		{
		listdata data;
		Node* next;
		Node* previous;
		Node(listdata data): data(data), next(NULL), previous(NULL){}
		};

		typedef struct Node* Nodeptr;

		Nodeptr first;
		Nodeptr last;
		Nodeptr iterator;
		int size;

		void reverse(Nodeptr node);
		bool isSorted(Nodeptr node);
		int binarySearch(int low, int high, listdata data);
		//Recursively searchs the list by dividing the search space in half
		//Returns the index of the element, if it is found in the List
		//Returns -1 if the element is not in the List

    public:

        /**Constructors and Destructors*/

        List();
        //Default constructor; initializes and empty list
        //Postcondition: There should be an empty list.

        List(const List &list);
        //Copy Constructor
        //Postcondition: There should be a deep copy of the original list

        ~List();
        //Destructor. Frees memory allocated to the list
        //Postcondition: The list is cleared


        /********************************************************
         *                      Accessors                       *
         ********************************************************/


        listdata getFirst();
        //Returns the first element in the list
        //Precondition: There should be at least one element in the list


        listdata getLast();
        //Returns the last element in the list
        //Precondition: There should be at least one element in the list


        bool isEmpty();
        //Determines whether a list is empty.

        int getSize();
        //Returns the size of the list

        void printList(std::ostream& os);
        //Prints to the console the value of each element in the list sequentially
		//and separated by a blank space
		//Prints nothing if the list is empty

        void printListReverse();

        listdata getIterator();
		//Return element at itertor's node
		//Precondition: size!=0 && iterator!=null

        bool isSorted();

        int getIndex();
        //Indicates the index of the Node where the iterator is currently pointing
        //Nodes are numbered from 1 to size of the list
        //Pre: size != 0
        //Pre: !off_end()

        /*************************************************************
         *                       Manipulators                        *
         *************************************************************/

        void removeLast();
        //Removes the value of the last element in the list
        //Precondition: There should be one element in the list
        //Postcondition: There should be one less element in the list. The last element should be different than before.

        void removeFirst();
        //Removes the value of the first element in the list
        //Precondition: There should be at least one element in the list
        //Postcondition: There should be one less element in the list. The first element should be different than before.

        void insertLast(listdata data);
        //Inserts a new element at the end of the list
        //If the list is empty, the new element becomes both first and last
        //Postcondition: There should be one more element in the list. The last element should be different than before.

        void insertFirst(listdata data);
        //Inserts a new element at the start of the list
        //If the list is empty, the new element becomes both first and last
        //Postcondition: There should be one more element in the list. The first element should be different than before.

        void removeIterator();
		//Remove element at the iterator
		//Precondition: size!=0 && iterator!= null

        void insertIterator(listdata data);
		//Insert node at the element after the iterator is pointing to
		//Precondition: !offEnd

        void advanceToIndex(int index);
        //Moves the iterator to the node whose index number is specified in the parameter
        //Pre: size != 0
        //Pre: index <= size

        int linearSearch(listdata data);
        //Searchs the list, element by element, from the start of the List to the end of the List
        //Returns the index of the element, if it is found in the List
        //Calls the above indexing functions in its implementation
        //Returns -1 if the element is not in the List
        //Pre: size != 0

        int binarySearch(listdata data);
        //Returns the index where data is located in the List
        //Calls the private helper function binarySearch to perform the search
        //Pre: size != 0
        //Pre: List is sorted (must test on a sorted list)

        /**************************************************************
         *             Additional List Operations                     *
         **************************************************************/

        void startIterator();
        //Make iterator point to the first node of the list
        //Precondition: size!=0

        void advanceIterator();
        //Move iteraror to the next node
        //Precondition: size!=0 && iterator!=null

        void retreatIterator();

        bool offEnd();
        //Returns true or false whether the iterator is null (end of the list)

        bool operator==(const List &list);

        void printReverse();
};


#include <iostream>
#include "List.h"
#include <assert.h>
using namespace std;

/***********************************************************
 *             Constructors + Destructors                  *
 ***********************************************************/

template <class listdata>
List<listdata>::List() : first(NULL), last(NULL), iterator(NULL), size(0) {}

template <class listdata>
List<listdata>::~List()
{
    Nodeptr cursor = first;
    Nodeptr temp;
    while(cursor != NULL)
    {
        temp = cursor->next;

        delete cursor;

        cursor = temp;

    }
}

template <class listdata>
List<listdata>::List(const List &list): size(list.size)
{
    if(list.first == NULL) //If the original list is empty, make an empty list for this list
    {
        first = last = iterator = NULL;
    }
    else
    {
        first = new Node(list.first->data); //calling Node constructor
        Nodeptr temp = list.first; //set a temporary node pointer to point at the first of the original list
        iterator = first; //set iterator to point to first node of the new list

        while(temp->next != NULL)
        {

            temp = temp->next; //advance up to the next node in the original list
            iterator->next = new Node(temp->data); //using node constructor to create a new node with copy of data
            iterator = iterator->next; //advance to this new node
        }

        last = iterator; //Why do I need this line of code?
        iterator = NULL;

    }
}


/*************************************************************************
 *                              ACCESSORS                                *
 *************************************************************************/

template <class listdata>
listdata List<listdata>::getFirst() {
	assert(size!=0);
	return first -> data;
}

template <class listdata>
listdata List<listdata>::getLast() {
	assert(size!=0);
	return last -> data;
}

template <class listdata>
bool List<listdata>::isEmpty() { return (size==0);}

template <class listdata>
int List<listdata>::getSize() { return size;}

template <class listdata>
void List<listdata>::printList(std::ostream& os)
{
    Nodeptr temp = first; //create a temporary iterator
    while (temp != NULL)
    {
    	os << temp-> data << " ";
    	temp = temp->next;
    }
    cout << endl; //What does this do?
}

template <class listdata>
void List<listdata>::printListReverse()
{
	Nodeptr temp = last;
	while (temp != NULL)
	{
		cout <<  temp->data << " ";
		temp = temp ->previous;
	}

	cout << endl;
}


template <class listdata>
listdata List<listdata>::getIterator()
{
	assert (size != 0);
	assert (iterator != NULL);
	return iterator -> data;
}

template <class listdata>
bool List<listdata>::isSorted(Nodeptr node)
{
	if(node->next->data > node->data)
	{
		return true;
	}
	else
	{
		isSorted(node->next);
	}
	return false;
}

template <class listdata>
bool List<listdata>::isSorted()
{
	return isSorted(first);
}

template <class listdata>
int List<listdata>::getIndex()
{
	assert(size != 0);
	assert(!offEnd());
	Nodeptr temp = iterator;
	startIterator();
	int count = 1;
	while( iterator!= temp )
	{
		iterator = iterator->next;
		++count;
	}
	return count;

}

template <class listdata>
void List<listdata>::advanceToIndex(int index)
{
	assert(size != 0);
	assert(index <= size);
	iterator = first;
	int current = 1;
	while(current != index)
	{
		iterator = iterator->next;
		current++;
	}
}

template <class listdata>
int List<listdata>::linearSearch(listdata data)
{
	assert( size != 0);
	startIterator();
	int i = 1;
	while(iterator != NULL)
	{
		if (iterator->data == data)
		{
			return i;
		}
		i++;
		advanceIterator();
	}
	return -1;
}

template <class listdata>
int List<listdata>::binarySearch(int low, int high, listdata data)
{
	assert(size != 0);
	assert(isSorted());
	if(high < low) { return -1; }
	int mid = low + (high - low) / 2;
	advanceToIndex(mid);
	if( iterator->data == data)
	{
		return mid;
	}
	else if (data < iterator->data)
	{
		return binarySearch(low, mid-1, data);
	}
	else
	{
		return binarySearch(mid+1, high, data);
	}

}

template <class listdata>
int List<listdata>::binarySearch(listdata data)
{
	return binarySearch(1, size, data);

}
/**************************************************************
 *                   MUTATORS                                 *
 **************************************************************/
template <class listdata>
void List<listdata>::removeLast()
{
    assert (size != 0);
	if ( size == 1)
	{

    	delete first;

    	first = last = NULL;

    	size = 0;

    }
	else
	{
        Nodeptr temp = first;
        while (temp->next != last)
        {
            temp = temp->next; //advance the pointer
        }
        delete last; //free the memory for the original last node

        last = temp;

        last->next = NULL; //so last->next is not pointing at freed memory

        size--;
    }
}

template <class listdata>
void List<listdata>::removeFirst()
{
    assert (size != 0);
	if (size == 1) {

        delete first;

        first = last = NULL;

        size = 0;

    } else {

        Nodeptr temp = first; //store pointer to first so we don't lose access to it

        first = first->next; //advance the pointer

        delete temp; //free the memory for the original first node

        size--;
    }

}


template <class listdata>
void List<listdata>::insertLast(listdata data)
{
    if (size==0) //Why is this necessary?
    {
        first = new Node(data);
        last = first; //notice the order here. Assignment is right to left
        last->previous = NULL;
    }
    else
    {
        Nodeptr N = new Node(data);//create the new node by calling the node constructor
        last->next = N;
        N->previous = last;
        last  = N;
    }

    size++;

}

template <class listdata>
void List<listdata>::insertFirst(listdata data)
{
    if (size==0) //Why is this necessary?
    {
        first = new Node(data);
        last = first; //notice the order here. Assignment is right to left
        first->previous = NULL;

    }
    else
    {
        Nodeptr N = new Node(data);//create the new node by calling the node constructor
        N->next = first;//set the new node's next field to point to the first node
        first->previous = N; //Need to update the previous pointer of first to point back at the new node
        first = N;//point the first pointer to the new node
    }

    size++;

}


template <class listdata>
void List<listdata>::insertIterator(listdata data)
{
	assert(iterator != NULL);

	if(iterator == last)
	{
		insertLast(data);
	}
	else
	{
		Nodeptr N = new Node(data);
		N->next = iterator->next;
		N->previous = iterator;
		iterator->next->previous = N;
		iterator->next = N;
		size++;
	}
}
template <class listdata>
void List<listdata>::removeIterator()
{
	assert(size != 0);
	assert(iterator != NULL);
	if(size == 1)
	{
		delete first;
		first = last = iterator = NULL;
		size = 0;
	}
	else if(iterator == last)
	{
		removeLast();
	}
	else
	{
		iterator->previous->next = iterator->next;
		iterator->next->previous = iterator->previous;
		delete iterator;
		iterator = NULL;
		size--;
	}
}


/********************************************************
 *              ADDITIONAL OPERATIONS                   *
 ********************************************************/

template <class listdata>
void List<listdata>::startIterator()
{
	assert(size != 0);
	iterator = first;
}

template <class listdata>
void List<listdata>::advanceIterator()
{
	assert (size != 0);
	assert (iterator != NULL);
	iterator = iterator -> next;
}


template <class listdata>
void List<listdata>::retreatIterator()
{
	iterator = iterator -> previous;
}

template <class listdata>
bool List<listdata>::offEnd()
{
	return iterator == NULL;
}

template <class listdata>
bool List<listdata>::operator==(const List& list)
{
    if(size != list.size)
        return false;
    Nodeptr temp1 = first;
    Nodeptr temp2 = list.first;
    while(temp1 != NULL)
    {
        if(temp1->data != temp2->data)
            return false;
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    return true;
}

template <class listdata>
void List<listdata>::reverse(Nodeptr node)
{	if(node == NULL )
	{
		cout << " ";
	}
	else
	{
		cout << node->data << " ";
		reverse(node->previous);
	}
}

template <class listdata>
void List<listdata>::printReverse()
{	if(size == 0)
	{
		cout << "\n";
		return;
	}
	else
	{
		reverse(last);
		cout << endl;
	}
}


#endif /* LIST_H_ */
