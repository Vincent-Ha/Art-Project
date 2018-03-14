#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <string>
#include "List.h"
#include "Customer.h"
using namespace std;

class HashTable {
public:
    /**Constructors*/

    HashTable();
    //constructor

    ~HashTable();
    //destructor


    HashTable(const HashTable& ht);
    //copy constructor

    /**Access Functions*/

    int hash(string key);
    //returns the hash value for the given key
    //the hash value is the sum of
    //of the ASCII values of each char in the key
    //% the size the of the table
    //Key for this table: title + author

    int countBucket(int index);
    //counts the number of Books at this index
    //returns the count
    //pre: 0<= index < SIZE

    int search(Customer b);
    //Searches for b in the table
    //returns the index at which b is located
    //returns -1 if b is not in the table

    /**Manipulation Procedures*/

    void insert(Customer b);
    //inserts a new book into the table
    //calls the hash function on the key to determine
    //the correct bucket

    void remove(Customer b);
    //removes b from the table
    //calls the hash function on the key to determine
    //the correct bucket

    /**Additional Functions*/

    void printBucket(int index, ostream& os);
    //Prints all the books at index
    //pre: 0<= index < SIZE
    //Should print according to the following formula:
    //"Printing index <index#>
    //skips two lines
    //Next, prints each book at that index in the format:
    //<title> by <author>
    //$<X.XX>
    //ISBN: <isbn>
    //followed by a blank line

    void printTable(ostream& os);
    //Prints the first book at each index
    //along with a count of the total books
    //at each index by calling count_bucket
    //as a helper function
    //Prints in the format:

    void userInteraction();

    Customer getItem(Customer& c);

private:
    static const int SIZE = 10;
    List<Customer> Table[SIZE];
};

#endif /* HASHTABLE_H_ */
