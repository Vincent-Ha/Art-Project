/*
 * Vincent Ha
 * CIS 22C, Winter 2017
 */

#include "Customer.h"

Customer::Customer() :
		first_name("N/A"), last_name("N/A"), address("N/A"), city("N/A"), state(
				"N/A"), zip(0) {
}

Customer::Customer(string fn, string ln, string a, string c, string s, int z) {
	first_name = fn;
	last_name = ln;
	address = a;
	city = c;
	state = s;
	zip = z;
}

Customer::Customer(const Customer& c): first_name(c.first_name), last_name(c.last_name), address(c.address), city(c.city), state(
		c.state), zip(c.zip){
	List<Order> copy(c.orderHistory);
	if(!copy.isEmpty()){
		copy.startIterator();
		while(!copy.offEnd()){
			orderHistory.insertLast(copy.getIterator());
			copy.advanceIterator();
		}
	}
}

void Customer::setFirst_Name(string fn) {
	first_name = fn;
}

void Customer::setLast_Name(string ln) {
	last_name = ln;
}

void Customer::setAddress(string a) {
	address = a;
}

void Customer::setCity(string c) {
	city = c;
}

void Customer::setState(string s) {
	state = s;
}

void Customer::setZip(int z) {
	zip = z;
}

void Customer::addOrder(Order& o) {
	orderHistory.insertLast(o);
}

void Customer::shippedOrder(Order o) {
	if (!orderHistory.isEmpty()) {
		Order temp2;
		orderHistory.startIterator();
		while (!orderHistory.offEnd()) {
			if (orderHistory.getIterator() == o) {
				Order temp(orderHistory.getIterator());
				temp.setHasShipped();
				orderHistory.removeIterator();
				if (orderHistory.isEmpty()) {
					orderHistory.insertFirst(temp);
					break;
				}
				orderHistory.startIterator();
				while (!orderHistory.offEnd()) {
					if (orderHistory.getIterator() == temp2) {
						orderHistory.insertIterator(temp);
					}
				}
				break;
			}
			temp2 = orderHistory.getIterator();
			orderHistory.advanceIterator();
		}
	}
}

void Customer::printOrderHistory(ostream& os) {
	if (orderHistory.isEmpty())
		os << "This customer has not made any orders" << endl;
	else {
		orderHistory.startIterator();
		while (!orderHistory.offEnd()) {
			os << orderHistory.getIterator();
			orderHistory.advanceIterator();
		}
	}
}

ostream& operator<<(ostream& os, const Customer& c) {
	os << c.first_name << " " << c.last_name << endl;
	os << c.address << endl;
	os << c.city << ", " << c.state << " " << c.zip << endl;
	os << endl;

	List<Order> copy(c.orderHistory);
	os << "Order History" << endl;
	os << "-------------" << endl;
	if (copy.isEmpty())
		os << "This customer has not made any orders" << endl;
	else {
		copy.startIterator();
		while (!copy.offEnd()) {
			os << copy.getIterator();
			copy.advanceIterator();
		}
	}
	os << "---" << endl;
	os << endl;
	return os;
}

string Customer::getFirst_Name() {
	return first_name;
}

string Customer::getLast_Name() {
	return last_name;
}

string Customer::getAddress() {
	return address;
}

string Customer::getCity() {
	return city;
}

string Customer::getState() {
	return state;
}

int Customer::getZip() {
	return zip;
}

bool Customer::operator==(const Customer& customer) {
	return first_name == customer.first_name && last_name == customer.last_name;
}

Customer& Customer::operator=(const Customer& c){
	first_name = c.first_name;
	last_name = c.last_name;
	address = c.address;
	city = c.city;
	state = c.state;
	zip = c.zip;
	if(!orderHistory.isEmpty()){
		orderHistory.removeLast();
	}

	List<Order> copy(c.orderHistory);
	if(!copy.isEmpty()){
		copy.startIterator();
		while(!copy.offEnd()){
			orderHistory.insertLast(copy.getIterator());
			copy.advanceIterator();
		}
	}
	return *this;
}
