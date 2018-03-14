#include <iomanip>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "ControlModule.h"
using namespace std;

int main()
{

	BST<Art> *inventoryTitle = new BST<Art>;
	BST<Art> *inventoryArtist = new BST<Art>;
	HashTable customers;
	Art artTitle;
	Art artArtist;
	ifstream infile;
	infile.open("input.txt");
	string inName, outName, temp, title, artist, genre, medium, prompt;
	int count;
	int info = 0;
	int year = 0;
	double price = 0;

	artTitle.sortByTitle = true;

	cout << "Welcome to Project!" << endl << endl;
	cout << "CIS 22C\nFinal Project\nTeam #6\nMembers:" << endl;
	cout << "\tYun Cao, Vincent Ha, Jimmy Nguyen, Kota Iwamoto, Vien Van\n";

	// coping art object to artArtist

	do
	{

		getline(infile,title);
		if(title.empty())
		{
			break;
		}
		artTitle.setTitle(title);
		artArtist.setTitle(title);

		getline(infile,artist);
		artTitle.setArtist(artist);
		artArtist.setArtist(artist);

		getline(infile,medium);
		artTitle.setMedium(medium);
		artArtist.setMedium(medium);


		getline(infile,genre);
		artTitle.setType(genre);
		artArtist.setType(genre);


		infile >> year;
		artTitle.setYear(year);
		artArtist.setYear(year);


		infile >> price;
		artTitle.setPrice(price);
		artArtist.setPrice(price);


		infile >> ws;
		inventoryTitle->insert(artTitle);
		inventoryArtist->insert(artArtist);


	}while(!infile.eof());

	infile.close();

	/*infile.open("output.txt");
	string name, first_name, last_name, address, address2, city, state, zip, junk, date, priority, shipped;
	while(!infile.eof()){
		getline(infile,name);
		if(name.empty())
			break;
		first_name = string(name, 0, name.find(" "));
		last_name = string(name, name.find(" ") + 1);

		getline(infile,address);
		getline(infile,address2);
		city = string(address2, 0 ,address2.find(","));
		state = string(address2, address2.find(", ") + 2, address2.find(" ") - 3);
		zip = string(address2, address2.find(" ") + 4);
		Customer temp_copy(first_name, last_name, address, city, state, atoi(zip.c_str()));
		getline(infile, junk);
		getline(infile, junk);
		getline(infile, junk);

		priority = "N/A";
		while(!priority.empty()){
			getline(infile, junk);
			getline(infile, date);
			getline(infile, priority);
			if(priority.empty())
				break;
			cout << priority << endl;
			getline(infile, shipped);
			getline(infile, junk);
			getline(infile, junk);
			Order order_copy(first_name, last_name, address + address2);
			order_copy.setDate(date);
			order_copy.setPriority(priority[0]);
			while(title != "---"){
				getline(infile, title);
				if(title == "---")
					break;
				getline(infile, artist);
				getline(infile, medium);
				getline(infile, genre);
				infile >> year;
				infile >> price;
				infile >> ws;
				Art art_copy(title, artist, genre, medium, price, year);
				order_copy.addToCart(art_copy);
			}
			temp_copy.addOrder(order_copy);
		}
		customers.insert(temp_copy);
	}
	infile.close();*/

//	customers.printTable(cout);
	ControlModule runner(inventoryTitle, inventoryArtist);
	runner.userInteraction();

	delete inventoryArtist;
	delete inventoryTitle;

	cout << "Thank you! Goodbye!" << endl;
	return 0;
}
