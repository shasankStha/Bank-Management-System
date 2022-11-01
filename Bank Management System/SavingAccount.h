#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H
#include <iostream>
#include "BankAccount.h"
using namespace std;

//Child class SavingAccount created from BankAccount
class SavingAccount:public BankAccount{
	
		
	
	public:
		char flag;//flag member is declared to identify whether the account is active or inactive
		SavingAccount()
		{
		}
		void status();
		void makeWithdrawal(double);
		void makeDeposit(double);
		void monthlyProc();
};

/*status function, whenever called checks whether the balance is below 25 or not
and if it is below 25, it makes accoount inactive*/
void SavingAccount::status()
{
	
	if(balance<25)
	{
		flag='i';
	}
	else
	{
		flag='a';
	}
}

/*makeWithdrawal function first checks the status of account
if it is inactive withdrawal is not allowed
if the account is active then withdrawal is made then again the status
is check whether the withdrawal made account inactive or not*/
void SavingAccount::makeWithdrawal(double amount)
{
	SavingAccount::status();
	if(balance<amount)
	{
		cout<<"Insufficient balance";
		return;
	}
	if(amount<=0)
	{
		cout<<"Invalid amount";
		return;
	}
	if(flag=='a')
	{
		BankAccount::makeWithdrawal(amount);
		status();
	}
	else
	{
		cout<<"Your Saving Account is Inactive"<<endl;
		BankAccount::show();
		return;
	}
	
}

/*makeDeposit function checks if the balance becomes more than 25,
if it does the deposit is made and the status of account becomes active
else the deposit will not be made and account inactive message will be shown*/
void SavingAccount::makeDeposit(double amount)
{
	double bal,total;
	bal=BankAccount::get_balance();
	if(amount<=0)
	{
		cout<<"Invalid amount";
		return;
	}
	total=bal+amount;
	if(total>=25.0)
	{
		BankAccount::makeDeposit(amount);
		status();
	}
	else
	{
		cout<<"Your Saving Account is Inactive"<<endl;
		cout<<"Your current balance is $"<<bal<<endl;
		return;
	}
}

/*monthlyProc function, before calling base class function it is called  and
if nnumber of withdrawal is more than 4 a  charge of 1$ for each withdrawal above 4
is added to monthly charge,
it also checks the status to identify whether the account becomes inactive after
the interest charged.*/
void SavingAccount::monthlyProc()
{
	double charge;
	if(no_of_withdrawal>4)
	{
		charge += 1.0*(no_of_withdrawal-4);
	}
	BankAccount::set_monthly_charge(charge);
	BankAccount::monthlyProc();
	status();
}

#endif
