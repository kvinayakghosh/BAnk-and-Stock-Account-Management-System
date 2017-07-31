// Name : Kisholoy Vinayak Ghosh
// Date : 12/13/2015
// Course : 16:332:503 , PM for Financial Applications and Numerical Computing.
// Example : Account Management System (Project)


#pragma comment( lib, "libmx.lib" )
#pragma comment( lib, "libmex.lib" )   
#pragma comment( lib, "libeng.lib" )

#include<iostream>
#include<fstream>
#include<string.h>
#include<time.h>
#include<ctime>
#include<iomanip>
#include<stdlib.h>
#include<sstream>
#include<istream>
#include<ostream>
#include<map>

#include <yvals.h>
#if (_MSC_VER >= 1600)
#define __STDC_UTF_16__
#endif
#include "mex.h"
// end
#include<engine.h>

#include "Node.h"
#include "Account_KVG.h"

using namespace std;
using std::setw;
#ifndef STOCKACCOUNT_KVG_H
#define STOCKACCOUNT_KVG_H
//Creating a stock account class which derives from Account class
class StockAccount_KVG :
	public Account_KVG
{
private:
	//Pointers to point to the head and tail of the list
	Node *myHead;
	Node *myTail;
	int mySize;	//Variable to store the size of the list
	map<string, double>stocklist1;
	map<string, double>stocklist2;
	
public:
	//Public member functions
	StockAccount_KVG();
	~StockAccount_KVG();
	void loadMaps();
	void getAccHistory();
	double readBalance();
	double genStockVal(string&);
	void displayStockPrice(string&);
	void displayCurrentPortfolio();
	void buyShares(string&,int,double);
	void sellShares(string&,int,double);
	void writeStockHistory();
	void writeBalance();
	void displayStockTransactions();
	void sortStockList();
	void removeNode(string&);
	void viewPortGraph();
	void writePortfolioHistory();
	void setBalance(double);
	double getBalance() const;
}; 
#endif;

