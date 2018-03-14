/*
 * Vincent Ha
 * CIS 22C, Winter 2017
 */

#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_

#include <vector>
#include "Order.h"
using namespace std;

class PriorityQueue{
private:
	vector<Order> shippingList;
	int size;
	void swap(int index1, int index2);
	void insertHelper(int index);
public:
	PriorityQueue();
	void addToList(Order& o);
	Order shipOrder();
	void buildMaxHeap();
	void maxHeapify(int index);
	void printShippingList(ostream& os);
	int getSize();
	void setHasShipped();
};



#endif /* PRIORITYQUEUE_H_ */
