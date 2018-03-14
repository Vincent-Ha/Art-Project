/*
 * Vincent Ha
 * CIS 22C, Winter 2017
 */

#include <locale>
#include <iostream>
#include <ctime>
#include "Order.h"

List<Art> Order::getCart()
{
	return cart;
}

void Order::setDate() {
	date = "03/28/2017";
}

void Order::setDate(string d){
	date = d;
}

Order::Order() :
		customerFirst_Name("N/A"), customerLast_Name("N/A"), address("N/A"), priority(
				standard), date(""), totalPrice(0), hasShipped(false) {
}

Order::Order(string cfn, string cln, string a) :
		customerFirst_Name(cfn), customerLast_Name(cln), address(a), priority(
				standard), date(""), totalPrice(0), hasShipped(false) {
}

Order::Order(const Order& o) :
		customerFirst_Name(o.customerFirst_Name), customerLast_Name(
				o.customerLast_Name), priority(o.priority), date(o.date), totalPrice(
				o.totalPrice), hasShipped(o.hasShipped) {
	List<Art> copy(o.cart);
	if (!copy.isEmpty()) {
		copy.startIterator();
		while (!copy.offEnd()) {
			cart.insertLast(copy.getIterator());
			copy.advanceIterator();
		}
	}
}

string Order::getcustomerFirst_Name() {
	return customerFirst_Name;
}

string Order::getcustomerLast_Name() {
	return customerLast_Name;
}

string Order::getAddress() {
	return address;
}

double Order::getTotalPrice() {
	if (!cart.isEmpty()) {
		cart.startIterator();
		while (!cart.offEnd()) {
			totalPrice += cart.getIterator().getPrice();
			cart.advanceIterator();
		}
	}
	return totalPrice;
}

void Order::setcustomerFirst_Name(string cfn) {
	customerFirst_Name = cfn;
}

void Order::setcustomerLast_Name(string cln) {
	customerLast_Name = cln;
}

void Order::setAddress(string a) {
	address = a;
}

void Order::setPriority(char p) {
	if (toupper(p) == 'O')
		priority = overnight;
	if (toupper(p) == 'R')
		priority = rush;
	if (toupper(p) == 'S')
		priority = standard;
}

void Order::setHasShipped() {
	hasShipped = true;
}

void Order::addToCart(Art a) {
	cart.insertLast(a);
}

Art Order::removeFromCart(Art a) {
	if (!cart.isEmpty()) {
		cart.startIterator();
		while (!cart.offEnd()) {
			if (a == cart.getIterator()) {
				Art temp_copy = cart.getIterator();
				cart.removeIterator();
				cout << "Item was successfully removed from the cart" << endl;
				return temp_copy;
			}
			cart.advanceIterator();
		}
	} else
		cout << "The item was not found in the cart." << endl;
		return Art();
}

void Order::printCart(ostream& os) {
	if (!cart.isEmpty()) {
		os << "Items Currently in the Cart:" << endl;
		os << endl;
		cart.startIterator();
		while (!cart.offEnd()) {
			os << cart.getIterator() << endl;
			cart.advanceIterator();
		}
	} else
		os << "The cart is currently empty." << endl;
}

ostream& operator<<(ostream& os, const Order& o) {
	os << o.customerFirst_Name << " " << o.customerLast_Name
			<< endl;
	os << o.date << endl;
	switch (o.priority) {
	case standard:
		os << "Standard" << endl;
		break;
	case rush:
		os << "Rush" << endl;
		break;
	default:
		os << "Overnight" << endl;
	}

	if (o.hasShipped == true)
		os << "Shipped" << endl;
	else
		os << "Has Not Shipped" << endl;
	os << "Items Ordered:" << endl;
	os << "--------------" << endl;

	List<Art> copy(o.cart);
	if (!copy.isEmpty()) {
		os << endl;
		copy.startIterator();
		while (!copy.offEnd()) {
			os << copy.getIterator();
			copy.advanceIterator();
		}
	} else
		os << "Nothing" << endl;
	os << "---" << endl;
	os << endl;
	return os;
}

bool Order::operator>(const Order& o) {
	if (priority != o.priority) {
		return priority > o.priority;
	} else
		return date < o.date;
}

bool Order::operator<(const Order& o) {
	if (priority != o.priority) {
		return priority < o.priority;
	} else
		return date > o.date;
}

bool Order::operator==(const Order& o) {
	if (priority == o.priority && date == o.date) {
		List<Art> copy(o.cart);
		if (cart.isEmpty() && copy.isEmpty())
			return true;
		if (!cart.isEmpty() && !copy.isEmpty()) {
			cart.startIterator();
			copy.startIterator();
			while (!cart.offEnd()) {
				if (cart.getIterator() == copy.getIterator()) {
					cart.advanceIterator();
					copy.advanceIterator();
				} else
					return false;
			}
			return true;
		}
	}
	return false;
}

Order& Order::operator=(const Order& o) {
	if (this == &o) {
		return *this;
	} else {
		customerFirst_Name = o.customerFirst_Name;
		customerLast_Name = o.customerLast_Name;
		priority = o.priority;
		date = o.date;
		while (!cart.isEmpty()) {
			cart.removeLast();
		}

		List<Art> copy(o.cart);
		if (!copy.isEmpty()) {
			copy.startIterator();
			while (!copy.offEnd()) {
				cart.insertLast(copy.getIterator());
				copy.advanceIterator();
			}
		}
		return *this;
	}
}

void Order::setTotalPrice() {
	if (!cart.isEmpty()) {
		cart.startIterator();
		while (!cart.offEnd()) {
			totalPrice += cart.getIterator().getPrice();
			cart.advanceIterator();
		}
	}
}

void Order::userInteraction(string type) {
	string choice;
	if (type == "employee") {
		cout << "\tMona Lisa Art Dealer" << endl
			 << "\t Orders " << endl
			 << "1. View Orders by Priority" << endl
			 << "2. Ship an Order"<< endl
			 << "3. Exit " << endl;
	} else
	{
		string choice;
		cout << "\tMona Lisa Art Dealer" << endl << "\tPlace an order" << endl
				<< endl << "First Name: ";
		// get customer info
		string firstName;
		string lastName;
		getline(cin, firstName);
		setcustomerFirst_Name(firstName);
		cout << "\nLast Name: ";
		getline(cin, lastName);
		setcustomerLast_Name(lastName);
		setDate();
		// get total price of cart
		while (cart.getSize() != 0) {
			cart.startIterator();
			Art art = cart.getIterator();
			totalPrice += art.getPrice();
			cart.advanceIterator();
		}
		cout << "Would you like to purchase this item? (y or n)" << endl;
		getline(cin, choice);
		if (choice == "y" || choice == "Y")
		{
			cout
					<< "Your order has been placed. Thank you for shopping with us."
					<< endl;
		}
	}

}

void Order::emptyCart(BST<Art>* inventoryArtist, BST<Art>* inventoryTitle){
	if(!cart.isEmpty()){
		cart.startIterator();
		Art temp_art;
		while(!cart.isEmpty()){
			temp_art = cart.getFirst();
			temp_art.sortByTitle = true;
			inventoryTitle->insert(temp_art);
			temp_art.sortByTitle = false;
			inventoryArtist->insert(temp_art);
			cart.removeFirst();
		}
	} else{
		cout << "The Order Is Already Empty" << endl;
	}
}
