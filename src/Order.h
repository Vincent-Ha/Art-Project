/*
 * Vincent Ha
 * CIS 22C, Winter 2017
 */

#ifndef ORDER_H_
#define ORDER_H_

#include "assert.h"
#include "List.h"
#include "Art.h"
#include "BST.h"
using namespace std;

enum Shipping {
	standard, rush, overnight
};

class Order {
private:
	string customerFirst_Name;
	string customerLast_Name;
	string address;
	Shipping priority; // Choices for priority are: O for Overnight Shipping, R for Rush Shipping and S for Standard Shipping.
	string date;			//	Should be written as month/day/year
	List<Art> cart;
	double totalPrice;
	bool hasShipped;

public:
	void setDate();
	void setDate(string d);
	Order();
	Order(string cfn, string cln, string a);
	Order(const Order& o);
	string getcustomerFirst_Name();
	string getcustomerLast_Name();
	string getAddress();
	double getTotalPrice();
	bool getHasShipped();
	void setcustomerFirst_Name(string cfn);
	void setcustomerLast_Name(string cln);
	void setAddress(string a);
	void setPriority(char p);	// Input should be: o, O, r, R, s, S
	void setHasShipped();
	void addToCart(Art a);
	Art removeFromCart(Art a);
	void printCart(ostream& os);
	void setTotalPrice();
	void userInteraction(string type);
	void emptyCart(BST<Art>* inventoryArtist, BST<Art>* inventoryTitle);
	List<Art> getCart();


	friend ostream& operator<<(ostream& os, const Order& o);
	bool operator>(const Order& o);
	bool operator<(const Order& o);
	bool operator==(const Order& o);
	Order& operator=(const Order& o);
};

#endif /* ORDER_H_ */
