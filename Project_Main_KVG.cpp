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
#include"Account_KVG.h"
#include"BAnkAccount_KVG.h"
#include"StockAccount_KVG.h"
using namespace std;

int main()
{
	//Variable declaration
	int option,stockopt,bankopt,nstock;
	double withdraw,deposit,amt,bal;
	double a = 0;
	string symbol,line;
	StockAccount_KVG s1;
	BAnkAccount_KVG b1;
	
	ifstream filestr;
	filestr.open("CashBalance.txt", ios::binary); // open your file
	filestr.seekg(0, ios::end); // put the "cursor" at the end of the file
	streampos length = filestr.tellg(); // find the position of the cursor
	filestr.close(); // close your file
	//Creating a cashbalance file and checking if its empty
	if (!length)
	{
		double putbalance = 10000.00;
		ofstream outputfile;
		outputfile.open("CashBalance.txt");
		outputfile << putbalance;
		outputfile.close();
	}
	else
	{
		ifstream readbalance("CashBalance.txt");
		while (getline(readbalance, line))
		{
			stringstream iss(line);
			while (!iss.eof()) 
			{
				iss >> a;
				//setting the balance with the current value in text file
				s1.setBalance(a);	
				b1.setBalance(a);
			}
		}
	}
	//Loading the maps with the stock symbols and values
	s1.loadMaps();
	s1.getAccHistory();
	
	//The following is done until the user wishes to leave the program
	do{
		cout <<endl<<endl<< "Welcome to the Account Management System." << endl;
		cout << "Please select an account to access :" << endl;
		cout << "1. Stock Portfolio Account" << endl;
		cout << "2. Bank Account" << endl;
		cout << "3. Exit" << endl;
		cin >> option;
		cout << "You have chosen Option :" << option << endl << endl;

		switch (option)
		{

		case (1) :
			//The following will run as long as user wishes to stay in stock account
			do{
				bal = s1.readBalance();
				s1.setBalance(bal);
				cout <<endl<<endl<< "Stock Portfolio Account" << endl;
				cout << "Please select an option :" << endl;
				cout << "1. Display the price for a stock symbol" << endl;
				cout << "2. Display the current portfolio" << endl;
				cout << "3. Buy shares" << endl;
				cout << "4. Sell shares" << endl;
				cout << "5. View a graph for the portfolio value" << endl;
				cout << "6. View transaction history" << endl;
				cout << "7. Sort the stocks" << endl;
				cout << "8. Return to previous menu" << endl;
				cin >> stockopt;
				cout << "You hav chosen option : " << stockopt << endl;

				switch (stockopt)
				{
				case (1) :
					cout << "Please enter the stock symbol whose price u want to view : ";
					cin >> symbol;
					s1.displayStockPrice(symbol);		//Function call to display the stock price of user symbol
					break;

				case (2) :
					s1.displayCurrentPortfolio();		//Function call to display the current portfolio
					break;

				case (3) :
					cout << "\n Please enter the symbol for the Stock that you wish to purchase: ";
					cin >> symbol;
					cout << "Please enter the number of Stocks that you wish to purchase: ";
					cin >> nstock;
					cout << "Please enter the maximum amount for the Stock that you wish to purchase: ";
					cin >> amt;
					s1.buyShares(symbol,nstock,amt);		//Function call to buy shares
					s1.writeBalance();
					break;

				case (4) :
					cout << "Please enter the symbol for the Stock that you wish to sell: ";
					cin >> symbol;
					cout << "Please enter the number of Stocks that you wish to sell: ";
					cin >> nstock;
					cout << "Please enter the minimum amount for the Stock you wish to sell: ";
					cin >> amt;
					s1.sellShares(symbol, nstock, amt);		//Function call to sell the shares
					s1.writeBalance();
					break;

				case (5) :
					cout << "Displaying the portfolio graph" << endl;
					s1.viewPortGraph();		//Function call to load the matlab graph
					break;

				case (6) :
					s1.displayStockTransactions();		//function call to display the stock transactions
					break;

				case (7) :
					s1.sortStockList();					//functino call to sort the stock list
					break;

				case (8) :
					s1.writeBalance();	
					break;

				default:
					cout << "Enter Valid Option" << endl;
					break;

				}

			} while (stockopt != 8);
			break;


		case (2) :
			//The following will run as long as the user wishes to make changes in bank account
			do{
				bal = b1.readBalance();
				b1.setBalance(bal);
				cout <<endl<< "Bank Account" << endl;
				cout << "Please select an option :" << endl;
				cout << "1. View account balance" << endl;
				cout << "2. Deposit money" << endl;
				cout << "3. Withdraw money" << endl;
				cout << "4. Print out history" << endl;
				cout << "5. Return to previous menu" << endl;
				cin >> bankopt;
				cout << "You have chosen option : " << bankopt << endl;

				switch (bankopt)
				{
				case (1) :
					b1.accBalance();		//Function call to display the current balance
					break;

				case (2) :
					cout << "Please enter the amount to be deposited : ";
					cin >> deposit;
					b1.depositMoney(deposit);		//Function call to deposit money into the account
					b1.writeBalance();
					break;

				case (3) :
					cout << "Enter the amount you wish to withdraw : ";
					cin >> withdraw;
					b1.withdrawMoney(withdraw);		//Function call to withdraw money from he account
					b1.writeBalance();
					break;

				case (4) :
					b1.accHistory();		//Function call to display the transactions
					break;

				case (5) :
					b1.writeBalance();
					break;

				default:
					cout << "Enter Valid Option" << endl;
					break;
				}
			} while (bankopt != 5);
			break;


		case (3) :
			s1.writeStockHistory();		//Function call to write the stocks and no of stocks before exiting the program
			s1.writePortfolioHistory();		//Function call to write the entire portfolio history before exiting the program
			cout << "~~~Have a nice day~~~" << endl<<endl;
			break;

		default:
			cout << "Enter a valid choice" << endl;
			break;

		}
	} while (option != 3);

 	return 0;
}