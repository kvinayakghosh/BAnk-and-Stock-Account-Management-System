// Name : Kisholoy Vinayak Ghosh
// Date : 12/13/2015
// Course : 16:332:503 , PM for Financial Applications and Numerical Computing.
// Example : Account Management System (Project)

#include<iostream>
#include<iomanip>
#include<string.h>
#include <fstream>
#include <time.h>
#include<ctime>
#include <stdlib.h>
#include "Account_KVG.h"
using namespace std;
using std::setw;

#ifndef BANKACCOUNT_KVG_H
#define BANKACCOUNT_KVG_H
//Creating derived class Bank Account which derives from Account class
class BAnkAccount_KVG :
	public Account_KVG
{
public:
	//Public function definitions
	BAnkAccount_KVG();
	~BAnkAccount_KVG();
	double readBalance();
	void accBalance();
	void setBalance(double);
	double getBalance() const;
	void depositMoney(double);
	void withdrawMoney(double);
	void accHistory();
	void writeBalance();


};
#endif;
