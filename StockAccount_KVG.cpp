// Name : Kisholoy Vinayak Ghosh
// Date : 12/13/2015
// Course : 16:332:503 , PM for Financial Applications and Numerical Computing.
// Example : Account Management System (Project)

#include "StockAccount_KVG.h"

//----------------Constructor to create a stock account object----------------
StockAccount_KVG::StockAccount_KVG()
{
	//Initialising the members to 0
	myHead = 0;
	myTail = 0;
	mySize = 0;

}
//-------Constructor ends here--------------------------------------------

void StockAccount_KVG::setBalance(double bal)
{
	balance = bal;
}
double StockAccount_KVG::getBalance() const
{
	return balance;
}


//-------Function to load the stock symbols and values into the map------------
void StockAccount_KVG::loadMaps()
{
	string a, c, d, f, line;
	double b, e;
	ifstream results1("Results_1.txt");		
	ifstream results2("Results_2.txt");
	if (results1.is_open())				//Checking if Results_1.txt is open
	{
		//Following loop will run as long as Results_1.txt has data on each line
		while (getline(results1, line))
		{
			stringstream iss(line);		//Creating a stringstream object to segregate the words by tabs
			//Following code will run as long as the stringstream obkect doesn't reach the end of the file
			while (!iss.eof()) {

				iss >> a >> b >> c;		//Taking input separated by delimiters into the various variables
				stocklist1.insert(pair<string, double>(a, b));	//Loading the stock symbol and no. of stocks into the map stocklist1
			}
		}
		results1.close();			//Close Results_1.txt after all conditions are met
	}
	else
	{
		cout << "File is not open" << endl;		//If Results_1.txt can't be opened return error
	}

	//Checking if Result_2.txt is open
	if (results2.is_open())
	{
		//Following loop will run as long Results_2.txt has lines to read
		while (getline(results2, line))
		{
			stringstream iss(line);		//Creating stringstream object to read the words
			//Following code will run until stringstream object has reached the end of the file
			while (!iss.eof()) {

				iss >> d >> e >> f;			//Taking the input from the file separated by delimiters
				stocklist2.insert(pair<string, double>(d, e));		//Inserting the data into the map stocklist2
			}
		}
		results2.close();			//Close Results_2.txt after all conditions are met
	}
	else
	{
		cout << "File is not open" << endl;		//Send an error if Results_2.txt cannot be opened
	}

}
//-------------------loadMaps ends here-------------------------------------

//--------Function to get stock account history from the text files--------------------
void StockAccount_KVG::getAccHistory()
{
	string a, line, symb;
	int b;

	ifstream history("stockhistory.txt");		
	//Taking stock account history from the text file
	if (history.is_open())
	{
		//Following loop will run as long as the text file has data on a line
		while (getline(history, line))
		{
			stringstream iss(line);		//creating a stringstream object to read the data
			//Following loop will run until the stringstream object reaches the end of the text file
			while (!iss.eof()) 
			{
				iss >> a >> b;
				Node *temp = new Node(a, b, 0.0);	//Creating a new node with the data read from the file
				if (mySize == 0)
				{ // checking to see if head was passed in or is null
					myHead = myTail = temp;
					temp->prev = NULL;
				}
				else
				{
					//Set the end of the list to the newly added node
					myTail->next = temp;
					temp->prev = myTail;
					temp->next = NULL;
					myTail = temp;
				}
				mySize++;

			}//end of file is reached or not
			Node *current = myHead;
			while (current != NULL)		//Loop to reach the end of the list
			{
				current = current->next;		//Point to next node

			}

		}
	}

}
//----------------------getAccHistory ends here---------------------------

//Reading the cash balance from the text file
double StockAccount_KVG::readBalance()
{
	string line;
	double bal;
	ifstream cashbal("CashBalance.txt");		//create ifstream object to read cash balance from the text file
	if (cashbal.is_open())
	{
		while (getline(cashbal, line))
		{
			stringstream iss(line);
			while (!iss.eof()) 
			{
				iss >> bal;
			}
		}
	}
	return bal;
}
//----------------------readBalance ends here--------------------

//-------Function to generate random stock values for stock symbols------------
double StockAccount_KVG::genStockVal(string& symbol)
{
	string usersymbol = symbol;
	double stockvalue;
	int filenum = rand() % 2 + 1;		//Creating a random number between 1 & 2
	//Following loop reads stock value from the map stocklist1
	if (filenum == 1)
	{
		map<string, double>::iterator itt = stocklist1.find(usersymbol);		//Iterator to be set at the location of the usersymbol key 
		if (itt != stocklist1.end())
		{
			//element found;
			stockvalue = itt->second;		//stock value is the value of the iterator
			return stockvalue;
		}
		else
		{
			//Symbol not present
			return -100;
		}
	}
	else if (filenum == 2)
	{
		map<string, double>::iterator itt = stocklist2.find(usersymbol);
		if (itt != stocklist2.end())
		{
			//element found;
			stockvalue = itt->second;
			return stockvalue;
		}
		else
		{
			//Symbol not found
			return -100;
		}
	}
	else
		cout << "Invalid entry" << endl;

}
//---------------------genStockVal ends here-----------------

//-------Function to display the stock value for user defined stock symbol------------
void StockAccount_KVG::displayStockPrice(string& symbol)
{
	string usersymbol = symbol;
	double stockvalue;
	stockvalue = genStockVal(usersymbol);   //Generate random stock value for users stock symbol
	if (stockvalue > 0)
	{
		cout << "Company-Symbol " << " Price per share " << endl;
		cout << setw(8) << usersymbol << setw(17) << stockvalue <<" $"<< endl;
	}
	else if (stockvalue == -100)
		cout << "This stock symbol does not exist" << endl;
	}
//---------------------displayStockPrice ends here--------------

//-------Function to display the stock transaction history------------
void StockAccount_KVG::displayStockTransactions()
{
	string a, line, b, f;
	//int c;
	double c,d, e;
	ifstream stockTransact("stock_transaction_history.txt");		//creating an ifstream object to read from the text file
	cout <<endl<< "Event" << setw(12) << "CompSymbol" << setw(10) << "Number" << setw(18) << "PricePerShare" << setw(15) << "TotalValue" << setw(12) << "Time" << endl;
	if (stockTransact.is_open())
	{
		while (getline(stockTransact, line))
		{
			stringstream iss(line);
			//Taking input from the text file until the end of the file
			while (!iss.eof()) {

				iss >> a >> b >> c >> d >> e >> f;
				//Displaying the result
				cout << setw(4) << a << setw(10) << b << setw(10) << c << setw(17) << d << setw(15) << (d*c) <<" $" << setw(14) << f << endl;
			}
		}
	}stockTransact.close();
}
//---------------------displayStockTransactions ends here------------

//-------Function to display the current stock portfolio--------------
void StockAccount_KVG::displayCurrentPortfolio()
{
	double counting = 0.0;
	Node *tempo = myHead;
	double stockvalue;
	if (mySize == 0)//Checking if the list is empty
	{
		cout <<endl<< "There are no values to show currently\n\n";
		return;
	}
	cout << "CompanySymbol " << " Number " << " PricePerShare " << " TotalValue" << endl;
	//going throught the list to display all the purchased stocks
	while (tempo != NULL)
	{

		stockvalue = genStockVal(tempo->stockSym);
		if (stockvalue > 0)
		{
			//display the current stocks in the list
			cout << setw(4) << tempo->stockSym << setw(14) << tempo->countStock << setw(15) << stockvalue << setw(15) << (tempo->countStock * stockvalue) << endl;
			counting += tempo->countStock * stockvalue;
			tempo = tempo->next;
		}
		else if (stockvalue == 0)
			cout << "Stock symbol does not exist" << endl;
	}
	cout << "Cash Balance : $ " << balance << endl;
	cout << "The total portfolio is worth : $ " << (balance + counting)<<endl;
}
//-------displayCurrentPortfolio ends here------------

//-------Function to perform buying of shares--------------
void StockAccount_KVG::buyShares(string &symbol,int nstock,double amt)
{
	string usersymbol = symbol;
	int nofstock = nstock;
	double amount = amt;
	double stockvalue = genStockVal(usersymbol);		//Generating a random stock value for user defined stock symbol
	if (stockvalue > 0)
	{
		//Condition to check if the entered amount is less than the stock value
		if (stockvalue > amount)
		{
			cout << "The current value of the " << usersymbol << " is $ " << stockvalue << endl;
			cout << "The maximum amount you wish to spend on this stock is: $ " << amount << endl;
			cout << "Hence the purchase could not be processed" << endl;
		}
		//Condition to check if the no of shares at the current stock value result in negative balance
		else if ((amount >= stockvalue) && (nofstock*stockvalue) > balance)
			cout << "Transaction failed due to insufficient balance" << endl;
		//Condition for successful transaction
		else if ((amount >= stockvalue) && (nofstock*stockvalue) < balance)
		{
			balance -= nofstock*stockvalue;
			cout << "You have bought " << nofstock << " shares of " << usersymbol << " at $ " << stockvalue << " per share." << endl;

			//Writing the transaction details and time stamping it
			time_t currentTime;
			struct tm *localTime;

			time(&currentTime);                   // Get the current time
			localTime = localtime(&currentTime);  // Convert the current time to the local time
			int Hour = localTime->tm_hour;
			int Min = localTime->tm_min;
			int Sec = localTime->tm_sec;
			int Day = localTime->tm_mday;
			int Month = localTime->tm_mon + 1;
			int Year = localTime->tm_year + 1900;
			//Write the transaction details into the stock transaction file
			ofstream transact("stock_transaction_history.txt", ios::app);
			if (transact.is_open())
			{
				transact << "Buy" << "\t" << usersymbol << "\t" << nofstock << "\t" << stockvalue << "\t" << (nofstock*stockvalue) << "\t" << Hour << ":" << Min << ":" << Sec << endl;
			}
			transact.close();
			//Write the transaction details into the banks transaction file as well
			ofstream banktransact3("bank_transaction_history.txt", ios::app);
			if (banktransact3.is_open())
			{
				banktransact3 << "Withdrawal" << "\t" << "Stock"<<"\t"<<(nofstock*stockvalue) << "\t" << Day << "/" << Month << "/" << Year << "\t" << balance << endl;
			}
			banktransact3.close();

			//Adding the purchased shares to the doubly linked list
			Node *temp = new Node(usersymbol, nofstock,0.0);
			if (mySize == 0){ // checking to see if head was passed in or is null
				myHead = myTail = temp;
				temp->prev = NULL;

			}
			else
			{
				Node *current = myHead;
				while (current != 0)
				{
					//Checking to see if the stocksymbol already exists in the current portfolio
					if (current->stockSym == usersymbol)
					{
						current->countStock += nofstock;
						return;
					}
					else
					{
						current = current->next;
					}
				}
				if (current == NULL)
				{	//Set the end of the list to the newly added node	
					myTail->next = temp;
					temp->prev = myTail;
					temp->next = NULL;
					myTail = temp;

				}
			}

			mySize++;
		}
	}
	else if (stockvalue == -100)
		cout << "Stock symbol does not exist" << endl;

}
//-------buyShares ends here--------------

//-------Function to perform selling of shares--------------
void StockAccount_KVG::sellShares(string &symbol, int nstock, double amt)
{
	string usersymbol = symbol;
	int nofstock = nstock;
	double amount = amt;
	double stockvalue;
	stockvalue = genStockVal(usersymbol);
	if (stockvalue > 0)
	{
		if (amount >= stockvalue)
		{
			cout << "The current value of " << usersymbol << " is " << stockvalue << endl;
			cout << "You are willing to sell for a minimum of " << amount << " $ " << endl;
			cout << "Hence Transaction has failed" << endl;
		}

		Node *temp = myHead;
		Node *next = temp->next;
		while (temp != NULL)
		{
			if (temp->stockSym == usersymbol && temp->countStock > nofstock && amount < stockvalue)
			{
				balance += stockvalue*nofstock;
				temp->countStock -= nofstock;
				cout << "You have sold " << nofstock << " shares of " << usersymbol << " at $ " << stockvalue << " per share." << endl;
				time_t currentTime;
				struct tm *localTime;

				time(&currentTime);                   // Get the current time
				localTime = localtime(&currentTime);  // Convert the current time to the local time
				int Hour = localTime->tm_hour;
				int Min = localTime->tm_min;
				int Sec = localTime->tm_sec;
				int Day = localTime->tm_mday;
				int Month = localTime->tm_mon + 1;
				int Year = localTime->tm_year + 1900;

				ofstream transact("stock_transaction_history.txt", ios::app);
				if (transact.is_open())
				{
					transact << "Sell" << "\t" << usersymbol << "\t" << nofstock << "\t" << stockvalue << "\t" << (nofstock*stockvalue) << "\t" << Hour << ":" << Min << ":" << Sec << "\n";
				}
				transact.close();
				ofstream banktransact4("bank_transaction_history.txt", ios::app);
				if (banktransact4.is_open())
				{
					banktransact4 << "Deposit" << "\t" << "Stock" << "\t" << (nofstock*stockvalue) << "\t" << Day << "/" << Month << "/" << Year << "\t" << balance << endl;
				}
				banktransact4.close();
			}
			else if (temp->countStock == nofstock && temp->stockSym == usersymbol && amount < stockvalue)
			{
				balance += stockvalue*nofstock;
				temp->countStock -= nofstock;
				cout << "You have sold " << nofstock << " shares of " << usersymbol << " at $ " << stockvalue << " per share." << endl;
				removeNode(usersymbol);
				time_t currentTime;
				struct tm *localTime;

				time(&currentTime);                   // Get the current time
				localTime = localtime(&currentTime);  // Convert the current time to the local time
				int Hour = localTime->tm_hour;
				int Min = localTime->tm_min;
				int Sec = localTime->tm_sec;
				int Day = localTime->tm_mday;
				int Month = localTime->tm_mon + 1;
				int Year = localTime->tm_year + 1900;

				ofstream transact("stock_transaction_history.txt", ios::app);
				if (transact.is_open())
				{
					transact << "Sell" << "\t" << usersymbol << "\t" << nofstock << "\t" << stockvalue << "\t" << (nofstock*stockvalue) << "\t" << Hour << ":" << Min << ":" << Sec << "\n";
				}
				transact.close();
				ofstream banktransact4("bank_transaction_history.txt", ios::app);
				if (banktransact4.is_open())
				{
					banktransact4 << "Deposit" << "\t" << "Stock" << "\t" << (nofstock*stockvalue) << "\t" << Day << "/" << Month << "/" << Year << "\t" << balance << endl;
				}
				banktransact4.close();
				return;
			}

			else if (temp->stockSym == usersymbol && temp->countStock < nofstock)
			{
				cout << "Your portfolio doesn't contain " << nofstock << " shares of " << usersymbol << " company." << "/n" << "Hence transcation failed" << endl;
			}
			temp = temp->next;
		}
	}
	Node *cur = myHead;
	if (cur->countStock == 0)
	{
		//if current node is head
		if (cur == myHead)
		{
			Node *temp = cur->next;
			myHead = cur->next;
			temp->prev = NULL;
			delete cur; // delete the node.
			mySize--;     // reduce the size.
			return;
		}
		//if current node is tail
		else if (cur == myTail)
		{
			Node *temp2 = cur->prev;
			myTail = cur->prev;
			temp2->next = NULL;
			delete cur;    // delete the node
			mySize--;        // reduce the size.
			return;
		}
		//else is the current node is middle node
		else
		{
			Node *temp3 = cur->prev;
			Node *temp4 = cur->next;
			temp3->next = cur->next;  // prev node's next pointer should be current node's next pointer.
			temp4->prev = cur->prev;  // current node's next node prev pointer should be current node's prev. pointer
			delete cur;                     // delete current node.
			mySize--;                         // reduce the size.
			return;
		}
	}
	else if (stockvalue == -100)
		cout << "Stock symbol does not exist" << endl;

}
//-------sellShares ends here--------------

//-------Function to sort the stock list by stock value--------------
void StockAccount_KVG::sortStockList()
{
	double stockvalue;
	Node *cur=myHead;
	//loading a random value for the node's current total value
	while (cur != NULL)
	{
		stockvalue = genStockVal(cur->stockSym);
		cur->value = cur->countStock * stockvalue;
		cur = cur->next;
	}


	cur = myHead;
	if (myHead != NULL)
	{
		Node *current = myHead;
		Node* prev = 0;
		Node *tempNode = NULL;
		int swapFlag = 0;
		for (int i = 0; i < mySize; i++)
		{
			while (current->next != 0)
			{
				tempNode = current->next;
				//Checking to see if the current value of total no of stocks for any symbol is less than the next in the list
				//swap them if it is true
				if (current->value < tempNode->value)
				{
					swapFlag = 1;
					current->next = tempNode->next;
					current->prev = tempNode;  //added now
					tempNode->next = current;
					
					if (prev != 0)
						prev->next = tempNode;
					prev = tempNode;
					if (myHead == current)
					{
						myHead = tempNode;
					}
					if (current->next == 0)
						myTail = current;
				}
				else
				{
					prev = current;
					current = current->next;
				}
			}
			//Condition when swapping is not needed
			if (swapFlag == 0)
				break;
			else
			{
				prev = 0;
				current = myHead;
				swapFlag = 0;
			}
		}
	}
	cout << "\nStock portfolio is sorted!\n";
}
//-------sortStockList ends here--------------

//-------Function to write the stocks and no of stocks in a text file--------------
void StockAccount_KVG::writeStockHistory()
{
	ofstream outputfile1;
	outputfile1.open("stockhistory.txt");
	Node *temp = myHead;
	while (temp != NULL)
	{
		//update the stocklist and no of shares in the text file
		outputfile1 << temp->stockSym << "\t" << temp->countStock << endl;
		temp = temp->next;
	}
	outputfile1.close();

}
//-------writeStockHistory ends here--------------

//-------Function to write the cash balance into its text file--------------
void StockAccount_KVG::writeBalance()
{
	ofstream writebal;
	balance = getBalance();
	writebal.open("CashBalance.txt");
	writebal << balance << endl;		//update the balance in the text file
	writebal.close();
}
//-------writeBalance ends here--------------

//-------Function to write portfolio transactions into a text file--------------
void StockAccount_KVG::writePortfolioHistory()
{
	ofstream outputfile1;
	time_t currentTime;
	struct tm *localTime;
	double totalval = 0;
	time(&currentTime);                   // Get the current time
	localTime = localtime(&currentTime);  // Convert the current time to the local time
	int Hour = localTime->tm_hour;
	int Min = localTime->tm_min;
	int Sec = localTime->tm_sec;
	int Day = localTime->tm_mday;
	int Month = localTime->tm_mon + 1;
	int Year = localTime->tm_year + 1900;
	outputfile1.open("Total_Portfolio.txt",ios::app);
	Node *temp = myHead;
	//condition to go throught the entire list and keep the total value, dat and time in the text file
	while (temp != NULL)
	{
		double stockvalue = genStockVal(temp->stockSym);
		totalval += stockvalue*temp->countStock;
		temp = temp->next;
	}
	outputfile1 << (totalval + balance) << "\t" << Day << "/" << Month << "/" << Year << "\t" << Hour << ":" << Min << ":" << Sec << endl;
	outputfile1.close();
}
//-------writePortfolioHistory ends here--------------

//-------Function to delete nodes from the stock linked list--------------
void StockAccount_KVG::removeNode(string& symbol)
{
	string usersymbol = symbol;
	if (mySize == 0)		//Checking if the list is empty
	{
		cout << "The list is empty!\n" << endl;
		return;
	}

	if (myHead->stockSym == usersymbol) // Check if the item name is the first one
	{
		myHead = myHead->next;
		myHead->next->prev = NULL;
		return;
	}

	if (myTail->stockSym == usersymbol) // Check if the item name is the last one
	{
			Node *temp2 = myTail->prev;
			myTail = myTail->prev;
			temp2->next = NULL;
			delete myTail->next;    // delete the node
			mySize--;        // reduce the size.
			return;

	}

	//Condition if the item is present somewhere in the list
	Node *curr = myHead;
	Node *next = myHead->next;
	//Loop up until the last node
	while (next->stockSym != usersymbol && next != myTail)
	{
		curr = next;
		next = next->next;
	}
	//If the tail is reached, the item is not present in the list
	if (next == myTail)
	{
		cout << "The item is not in the list.\n" << endl;
	}
	else
	{
		curr->next = next->next;
		next->next->prev = curr->prev;
		delete next;
		mySize--;

	}
	return;
}
//-------removeNode ends here--------------

//-------Function to display stock trends on MATLAB--------------
void StockAccount_KVG::viewPortGraph()
{

	// creating a pointer to the engine
	Engine *ep;
	ep = engOpen(NULL);

	if (ep == NULL)
	{
		cout << "Error: Not Found." << endl;
		exit(1);
	}
	// end
	int count = 0;
	double totvalmat[100];
	string timemat[100];
	string line,date,time;
	double bal;
	//read the text file to load the total portfolio value and time of transaction
	ifstream totport("Total_Portfolio.txt");
	if (totport.is_open())
	{
	while (getline(totport, line))
	{
	stringstream iss(line);
	//Read the lines of the file and load the total value and the time in respective arrays
	while (!iss.eof()) {
	
	iss >> bal>>date>>time;
	totvalmat[count] = bal;
	timemat[count] = time;
	count++;
	}
	}
	}
	totport.close();
	//Load the total portfolio value into matlab array
	mxArray *A;
	A = mxCreateDoubleMatrix(1, count, mxREAL);
	memcpy((void *)mxGetPr(A), (void *)totvalmat, count*sizeof(double));
	engPutVariable(ep, "xx", A);

/*	mxArray *B;
	mxArray *mxCreateCharMatrixFromStrings(mwSize count, const char **str);
	B = mxCreateDoubleMatrix(1, count, mxREAL);
	memcpy((void *)mxGetPr(B), (void *)timemat, count*sizeof(double));
	engPutVariable(ep, "yy", B); */

	engEvalString(ep, "X=xx");
	engEvalString(ep, "plot(X);");	//call plot function
	engEvalString(ep, "title('Portfolio Value Variation graph');");

	mxDestroyArray(A);
	//mxDestroyArray(B);
}
//-------viewPortGraph ends here--------------

//-------Destructor--------------
StockAccount_KVG::~StockAccount_KVG()

{
	// Checking if list is not empty
	if (mySize != 0)
	{

		Node *currPtr = myHead;	//pointing to the head of the list
		Node *temp;				//Creating a temporary pointer

		while (currPtr != 0) // loop to run through the list
		{
			temp = currPtr;

			currPtr = currPtr->next;

			delete temp;		//Delete the memory allocated to the nodes

		}
	}

}
