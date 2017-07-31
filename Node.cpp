// Name : Kisholoy Vinayak Ghosh
// Date : 12/13/2015
// Course : 16:332:503 , PM for Financial Applications and Numerical Computing.
// Example : Account Management System (Project)

#include "Node.h"

//Constructor to initialise the data members of each node
Node::Node(string& symbol, int stockcount, double val)
{
	stockSym = symbol;
	countStock = stockcount;
	value = val;

	next = 0;
	prev = 0;
}



