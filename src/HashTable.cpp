/*
 * HashTable.cpp
 *
 *  Created on: Mar 25, 2017
 *      Author: Vincent_Ha
 */

#include <fstream>
#include "HashTable.h"

/*********************************************
 *       Constructors & Destructors          *
 *********************************************/

HashTable::HashTable() {}

HashTable::~HashTable() {}


/*********************************************
 *     			    ACCESSORS                *
 *********************************************/

int HashTable::hash(string key)
{
    int index, sum = 0;
    for(int i = 0; i < key.length(); i++)
        sum += (int) key[i]; //summing the ASCII values for each character in the string
    index = sum % SIZE; //dividing the summed ASCII values by 35 && storing remainder as my index
    return index;
}

int HashTable::countBucket(int index)
{
	if(Table[index].isEmpty())
	{
		return 0;
	}
	return Table[index].getSize();
}

int HashTable::search(Customer c)
{
	// concatenate title and author for key
	string key = c.getFirst_Name() + c.getLast_Name();

	// get index to insert to
	int index = hash(key);
	List<Customer> customer_list = Table[index];

	if(customer_list.isEmpty())
	{
		return -1;
	}
	else
	{
		// search through list of books

		// advance iterator of list to the found book
		if(Table[index].linearSearch(c) == -1)
		{
			return -1;
		}
		else
		{
			return index;
		}

	}
}

/**********************************************
 * 				MANIPULATORS		          *
 **********************************************/

void HashTable::insert(Customer c)
{
	// concatenate title and author for key
	string key = c.getFirst_Name() + c.getLast_Name();

	// get index to insert to
	int index = hash(key);

	// insert book at indexed array
	Table[index].insertLast(c);
}

void HashTable::remove(Customer c)
{
	// concatenate title and author for key
	string key = c.getFirst_Name() + c.getLast_Name();

	// get index to insert to
	int index = hash(key);

	// insert book at indexed array

	List<Customer> customer_list = Table[index];
	if(customer_list.getSize() == 0)
	{
		cout << "This book is not in the hash table." << endl;
		return;
	}
	else
	{
		int list_index = Table[index].linearSearch(c);
		Table[index].advanceToIndex(list_index);
		Table[index].removeIterator();
	}

}

/***********************************************
 * 			 ADDT'L FUNCTIONS                  *
 ***********************************************/

void HashTable::printBucket(int index, ostream& os)
{
	Table[index].printList(os);
}

void HashTable::printTable(ostream& os)
{
	for (int i = 0; i < SIZE; i++)
	{
		// print customers
		printBucket(i, os);
	}
}

void HashTable::userInteraction()
{
	string choice;
	string firstName, lastName;
	Customer customer_copy;
	do
	{
		cout << "Customer's Info" << endl;
		cout << "1. Search for a customer by name" << endl;
		cout << "2. Display unsorted customer information" << endl;
		cout << "3. Exit" << endl;
		cout << "Enter your choice: ";
		getline(cin, choice);
		if(atoi(choice.c_str()) > 3 || atoi(choice.c_str()) < 1)
		{
			cout << "Invalid Input. Please Try Again." << endl;
			cout << endl;
			continue;
		}
		switch (atoi(choice.c_str()))
		{
			case 1:
			{
				cout << "Enter the First Name of the Customer: ";
				getline(cin,firstName);
				cout << "Enter the Last Name of the Customer: ";
				getline(cin, lastName);
				customer_copy.setFirst_Name(firstName);
				customer_copy.setLast_Name(lastName);
				if(search(customer_copy) != -1)
				{
					customer_copy = getItem(customer_copy);
					cout << "Found A Customer" << endl;
					cout << customer_copy << endl;
				}
				else
				{
					cout << "Customer Not Found" << endl;
				}
				cout << endl;
			}
			break;
			case 2:
			{
				printTable(cout);
			}
			break;
			default:
			{
				cout << "hello world"<< endl;
			}
			break;
		}
	} while(atoi(choice.c_str()) != 3);

	ofstream output("Customer.txt");
	printTable(output);
}

Customer HashTable::getItem(Customer& c)
{
	Customer temp_customer;
	if(search(c) != -1)
	{
		int index = search(c);
		Table[index].startIterator();
		while(!Table[index].offEnd())
		{
			if(Table[index].getIterator() == c)
			{
				temp_customer = Table[index].getIterator();
			}
			Table[index].advanceIterator();
		}
	}
	else
	{
		cout << "It is not in the list" << endl;
		temp_customer = Customer();
	}
	return temp_customer;
}
