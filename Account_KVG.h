// Name : Kisholoy Vinayak Ghosh
// Date : 12/13/2015
// Course : 16:332:503 , PM for Financial Applications and Numerical Computing.
// Example : Account Management System (Project)

#include<iostream>
#include<fstream>
#include<string.h>
#include<time.h>
#include<iomanip>
#include<stdlib.h>
#include<sstream>
using namespace std;
using std::setw;

#ifndef ACCOUNT_KVG_H
#define ACCOUNT_KVG_H
//Creating an abstract base class Account_KVG
class Account_KVG
{
protected:
	//data member
	double balance = 10000.00;
public:
	//Creating virtual functions to declare in derived classes
	virtual double readBalance() = 0;
	virtual void writeBalance() = 0;
};
#endif;
