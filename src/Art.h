/*
 * Vincent Ha
 * CIS 22C, Winter 2017
 */

#ifndef ART_H_
#define ART_H_

#include <string>
using namespace std;

class Art {
private:
	string title;
	string artist;
	string type;
	string medium;
	double price;
	unsigned int year;

	bool equalsNoCase(string str1, string str2);
public:
	bool sortByTitle;
	Art();
	Art(string t, string a, string g, string m, double p, unsigned int y);

	// Accessors and Manipulators
	void setTitle(string t);
	void setArtist(string a);
	void setType(string g);
	void setMedium(string m);
	void setPrice(double p);
	void setYear(unsigned int y);

	string getTitle();
	string getArtist();
	string getType();
	string getMedium();
	double getPrice();
	unsigned int getYear();

	//Operator Overloads
	friend ostream& operator<<(ostream& os, const Art& art);
	bool operator==(const Art& art);
	bool operator<(const Art& art);
	bool operator>(const Art& art);
};

#endif /* ART_H_ */
