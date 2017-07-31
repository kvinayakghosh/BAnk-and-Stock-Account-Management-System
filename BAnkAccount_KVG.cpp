// Name : Kisholoy Vinayak Ghosh
// Date : 12/13/2015
// Course : 16:332:503 , PM for Financial Applications and Numerical Computing.
// Example : Account Management System (Project)


#include "BAnkAccount_KVG.h"

//-------Constructor--------------
BAnkAccount_KVG::BAnkAccount_KVG()
{
}

//-------Function to set balance--------------

void BAnkAccount_KVG::setBalance(double bal)
{
	balance = bal;
}

//-------Function to get the balance--------------
double BAnkAccount_KVG::getBalance() const
{
	return balance;
}

//-------Function to display the current cash balance in the account--------------
void BAnkAccount_KVG::accBalance()
{
	cout << endl << "The current Balance in the accout is : $ " << readBalance() << endl;
}
//-------AccBalance ends here--------------

//-------Function to perform depositing of money--------------
void BAnkAccount_KVG::depositMoney(double put)
{
	double deposit = put;	
	//Checking if the user nput amount is non-negative
	if (deposit > 0)
	{
		//updating the balance
		balance += deposit;
		time_t currentTime;
		struct tm *localTime;

		time(&currentTime);                   // Get the current time
		localTime = localtime(&currentTime);  // Convert the current time to the local time
		int Day = localTime->tm_mday;
		int Month = localTime->tm_mon + 1;
		int Year = localTime->tm_year + 1900;
		//Writing the transaction details in the text file
		ofstream banktransact;
		banktransact.open("bank_transaction_history.txt", ios::app);
		banktransact << "Deposit" << "\t" << "Bank" << "\t" << deposit << "\t" << Day << "/" << Month << "/" << Year << "\t" << balance << endl;
		banktransact.close();
	}

	else
		cout << "Enter a valid amount to be deposited" << endl;
}
//-------depositMoney ends here--------------

//-------Function to perform withdrawal of money--------------
void BAnkAccount_KVG::withdrawMoney(double takeout)
{
	double withdraw = takeout;
	//Checking if the user entered amount is non negative and balance is more than desired withrawal amount
	if (withdraw > 0 && (balance - withdraw) >= 0)
	{
		//updating balance
		balance -= withdraw;
		time_t currentTime;
		struct tm *localTime;

		time(&currentTime);                   // Get the current time
		localTime = localtime(&currentTime);  // Convert the current time to the local time
		int Day = localTime->tm_mday;
		int Month = localTime->tm_mon + 1;
		int Year = localTime->tm_year + 1900;
		//Writing the transaction details into the text file
		ofstream banktransact2;
		banktransact2.open("bank_transaction_history.txt", ios::app);
		banktransact2 << "Withdrawal" << "\t" << "Bank" << "\t"<<  withdraw << "\t" << Day << "/" << Month << "/" << Year << "\t" << balance << endl;
		banktransact2.close();
	}
	//condition when balance is less than withdrawal amount 
	else if (withdraw > 0 && (balance - withdraw) < 0)
		cout << "Insufficient balance. Hence, cannot withdraw" << endl;
	//condition where withdrawal amount is negaitive
	else if (withdraw < 0)
			cout << "Enter a valid amount to withdraw" << endl;

}
//-------withdrawMoney ends here--------------

//-------Function to display the transactions of both bank and stock a/c--------------
void BAnkAccount_KVG::accHistory()
{
	string a, line, b, d;
	double c, e;
	//Reading the transactions from the text file and displaying it
	ifstream bankTransact("bank_transaction_history.txt");
	cout << endl <<setw(9)<< "Event" << setw(16) << "AccountType" << setw(12) << "Amount" << setw(10) << "Date" << setw(15) << "Balance" << endl;
	if (bankTransact.is_open())
	{
		while (getline(bankTransact, line))
		{
			stringstream iss(line);
			while (!iss.eof()) 
			{

				iss >> a >> b >> c >> d >> e;
				cout << setw(10) << a << setw(10) << b << " A/c" << setw(12) << c << setw(14) << d << setw(12) << e << " $" << endl;
			}
		}
		bankTransact.close();
	}
}
//-------accHistory ends here--------------

//-------Function to read the balance from the text file-------------
double BAnkAccount_KVG::readBalance()
{
	string line;
	double bal;
	ifstream cashbal("CashBalance.txt");
	if (cashbal.is_open())
	{
		while (getline(cashbal, line))
		{
			stringstream iss(line);
			while (!iss.eof()) {
				//reading the balance from the text file
				iss >> bal;
			}
		}
	}
	return bal;
}
//-------readBalance ends here--------------

//-------Function to write the cash balance into the text file--------------
void BAnkAccount_KVG::writeBalance()
{
	//writing the balance into the text file
	ofstream writebal;
	writebal.open("CashBalance.txt");
	writebal << balance << endl;
	writebal.close();
}
//-------writeBalance ends here--------------


BAnkAccount_KVG::~BAnkAccount_KVG()
{
}
