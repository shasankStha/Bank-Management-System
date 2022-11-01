#ifndef CHECKINGACCOUNT_H
#define CHECKINGACCOUNT_H
#include <iostream>
#include "BankAccount.h"
using namespace std;

//Child class CheckingAccount created from BankAccount
class CheckingAccount: public BankAccount{
	public:
		CheckingAccount()
		{
		}
		void makeWithdrawal(double);
		void monthlyProc();
};

/*makewithdrawal function accepts amount as parameter. Before base class function
is called it checks whether the withdrawal makes balance drop below zero, if it does
this function increases monthly_charge with 15 and the withdrawal will not be made*/
void CheckingAccount::makeWithdrawal(double amount)
{
	if(amount<=0)
	{
		cout<<"Invalid amount";
		return;
	}
	if(amount>balance)
	{
		cout<<"Insufficient balance"<<endl;
		cout<<"You will be charged with 15$ as your balance is less than withrawal amount"<<endl;
		monthly_charge+=15;
	}
	else
	{
		BankAccount::makeWithdrawal(amount);
	}
}

/*monthlyProc function adds the monthly charge of 5 plus 0.10 per no of withdraw made*/
void CheckingAccount::monthlyProc()
{
	monthly_charge += 5+(0.10*no_of_withdrawal);
	BankAccount::monthlyProc();
}

#endif
