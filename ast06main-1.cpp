// assignment is to implement a banking account matching system using hash maps 

#include "hashMap.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string> 

using namespace std; 

struct bankType
{
	struct transactionType
	{
		transactionType(bool t, double a)
		{
			type = t;
			amount = a;
		}

		bool type;
		double amount;
	};

	bankType(std::string first, std::string last, std::string acctNo,
		double balance,unsigned int pin)
	{
		name = last + ", " + first;
		this->balance = balance;
		this->pin = pin;
		this->acctNo = acctNo;
		locked = false;
	}

	bankType()
	{
		name = "";
		balance = 0;
		pin = 0;
		locked = false;
	}

	std::string name;
	std::string acctNo;
	double balance;
	unsigned int pin;
	bool locked;

	std::vector<transactionType> transactions;
};


string convertToLower(string a){
	for(int i = 0; i < a.length(); i++){
		a[i] = tolower(a[i]); 
	}
	return a; 
}

int main()
{
	std::cout << std::fixed << std::setprecision(2);
	hashMap< std::string, hashMap< std::string, bankType > > bank;

	hashMap<string, bool> banksMap; // contains a list of all the banks 

	ifstream fin; 
	fin.open("data-1 copy.csv"); 
	string inputLine; 
	std::getline(fin, inputLine); // process first junk line 

	while(!fin.eof()){
		
		std::getline(fin, inputLine); 

		if(inputLine == ""){ // to avoid any blank lines in input file 
			break; 
		}


		string firstName = inputLine.substr( 0, inputLine.find(",") );
		inputLine.erase( 0, inputLine.find(",") + 1 );

		string lastName = inputLine.substr( 0, inputLine.find(",") );
		inputLine.erase( 0, inputLine.find(",") + 1 );

		string location = inputLine.substr( 0, inputLine.find(",") );
		inputLine.erase( 0, inputLine.find(",") + 1 );
		location = convertToLower(location); 
		banksMap[location] = true; 

		string acctNo = inputLine.substr( 0, inputLine.find(",") ); 
		inputLine.erase( 0, inputLine.find(",") + 1 );
		string acct4Digits = acctNo.substr(6, 4); // grab last 4 digits of string for indexing later 

		string balanceStr = inputLine.substr( 0, inputLine.find(",") ); 
		inputLine.erase( 0, inputLine.find(",") + 1 );

		double balanceDbl = stod(balanceStr); // convert string to double 

		string pinStr = inputLine.substr( 0, inputLine.find(",") ); 
		inputLine.erase( 0, inputLine.find(",") + 1 );

		unsigned int pinInt = stoi(pinStr); // convert string to int 

		bank[location ][ acct4Digits] = bankType(firstName , lastName , acct4Digits , balanceDbl , pinInt); 


	}
	fin.close(); 

	string bankInput; // for getting the bank name 
	string last4Input; // for getting last 4 digits of account number 
	string continueVal; 
	string pinVal; 
	string menuChoice; 
	unsigned int pinValInt; 
	int pinAttempts = 0; 

	startPrompt: 
			std::cout << "Please enter a bank branch location: "; 
			 
			std::getline(std::cin, bankInput); 
			std::cin.clear();  
			std::cin.sync(); 
			bankInput = convertToLower(bankInput); 

			if(banksMap[bankInput] == false){
				std::cout << "Bank branch not found" << endl << endl; 
				goto continueLabel; 
			}

			std::cout << "Enter last 4 digits of account: "; 
			 
			std::getline(std::cin, last4Input); 
			std::cin.clear();  
			std::cin.sync();

			if(bank[bankInput][last4Input].acctNo != last4Input){
				std::cout << "Account not found " << endl << endl;
				goto continueLabel; 
			}

			pinAttempts = 0; // reset pin attempts to keep track of lock 
			while(true){
				cout << "Enter a pin: " << endl; 
				std::getline(std::cin, pinVal); 
				std::cin.clear();  
				std::cin.sync();
				pinValInt = stoi(pinVal); 

				if(bank[bankInput][last4Input].pin != pinValInt){
					cout << "Invalid Pin" << endl; 
					pinAttempts++; 
				}
				else{
					break; 
				}
				
				if(pinAttempts >= 3){
					cout << "3 failed login attempts, account is now locked" << endl;
					goto continueLabel; 
				}
			}
		

		mainMenu: 
			cout << "(D)eposit" << endl; 
			cout << "(W)ithdrawal" << endl; 
			cout << "(V)iew Account" << endl; 
			cout << "(E)xit Account" << endl; 

			std::getline(std::cin, menuChoice); 
			std::cin.clear();  
			std::cin.sync();

			menuChoice = convertToLower(menuChoice); 
			
			if(menuChoice == "d"){

			}
			else if(menuChoice == "w"){

			}
			else if(menuChoice == "v"){
				
			}



		continueLabel: 

		std::cout << "Continue? (Y/N): "; 
		std::getline(std::cin, continueVal); 
		std::cin.clear();  
		std::cin.sync();

		if(continueVal == "Y" || continueVal == "y"){
			goto startPrompt; 
		}




	return 0;
}