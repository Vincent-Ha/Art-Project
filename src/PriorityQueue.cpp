/*
 * Vincent Ha
 * CIS 22C, Winter 2017
 */

#include "PriorityQueue.h"

void PriorityQueue::swap(int index1, int index2){

	Order temp = shippingList[index1];
	Order temp2 = shippingList[index2];
	shippingList[index1] = temp2;
	shippingList[index2] = temp;
}

void PriorityQueue::insertHelper(int index){
	if(index > 1 && shippingList[index/2] < shippingList[index]){
		swap(index/2, index);
		insertHelper(index/2);
	}
}

PriorityQueue::PriorityQueue(){
	size = 0;
	shippingList.push_back(Order());
}

void PriorityQueue::addToList(Order& o){
	shippingList.push_back(o);
	size++;
	insertHelper(size);
}

Order PriorityQueue::shipOrder(){
	if(size == 0){
		cout << "There is nothing to remove" << endl;
		return Order();
	}
	Order copy(shippingList[1]);
	shippingList[1].setHasShipped();
	shippingList[1] = shippingList[size];
	shippingList.erase(shippingList.begin() + size);
	size--;
	buildMaxHeap();
	return copy;
}

void PriorityQueue::buildMaxHeap(){
	for(int b = size/2; b >= 1; b--){
		maxHeapify(b);
	}
}

void PriorityQueue::maxHeapify(int index){
	int maxIndex = index;
	int left = 2 * index;
	int right = (2 * index) + 1;
	if(left <= size && shippingList[left] > shippingList[index])
		maxIndex = left;
	if(right <= size && shippingList[right] > shippingList[left])
		maxIndex = right;
	if(index != maxIndex){
		Order copy = shippingList[index];
		shippingList[index] = shippingList[maxIndex];
		shippingList[maxIndex] = copy;
		maxHeapify(maxIndex);
	}
}

void PriorityQueue::printShippingList(ostream& os){
	os << "Orders to be Shipped:" << endl;
	os << "---------------------" << endl;
	os << endl;
	for(int a = 1; a <= size; a++){
		os << shippingList[a];
	}
}

int PriorityQueue::getSize(){
	return size;
}
