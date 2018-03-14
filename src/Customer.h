/*
* Vincent Ha
* CIS 22C, Winter 2017
*/

#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include <iostream>
#include "Order.h"
using namespace std;

class Customer {

private:
    string first_name;
    string last_name;
    string address;
    string city;
    string state;
    int zip;
    List<Order> orderHistory;

public:
    Customer();
    Customer(string fn, string ln, string a, string c, string s, int z);
    Customer(const Customer& c);
    void setFirst_Name(string fn);
    void setLast_Name(string ln);
    void setAddress(string a);
    void setCity(string c);
    void setState(string s);
    void setZip(int z);
    void addOrder(Order& o);
    void shippedOrder(Order o);
    void printOrderHistory(ostream& os);
    friend ostream& operator<< (ostream& os, const Customer& c);

    string getFirst_Name();
    string getLast_Name();
    string getAddress();
    string getCity();
    string getState();
    int getZip();
    bool operator==(const Customer& customer);
    Customer& operator=(const Customer& c);
};
#endif /* CUSTOMER_H_ */
