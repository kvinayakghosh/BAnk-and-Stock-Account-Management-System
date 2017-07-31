// Name : Kisholoy Vinayak Ghosh
// Date : 12/13/2015
// Course : 16:332:503 , PM for Financial Applications and Numerical Computing.
// Example : Account Management System (Project)

#include <iostream>
#include <string>
#include<iomanip>
using namespace std;
using std::setw;

#ifndef NODE_H
#define NODE_H
//Creating a class node which will hold the node members i.e Stock symbil, no of stocks and total value of each stock.
class Node
{
	friend class StockAccount_KVG;
private:
	string stockSym;
	int countStock;
	double value;
	Node *next;		//pointer to the next node
	Node *prev;		//pointer to the prev node
public:
	//Constructor
	Node(string&, int, double);
};
#endif;