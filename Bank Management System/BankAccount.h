#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H
#include<iostream>
#include<cstring>
using namespace std;

//BankAccount class declaration
class BankAccount{
	//data members
	protected:
		int id;
		char name[50];
		double balance;
		int no_of_deposit;
		int no_of_withdrawal;
		double annual_interest;
		double monthly_charge;
		
	public:
		BankAccount()
		{
		}

		//create function declare that asks users information and creates new account
		void create()
		{
			double deposit, rate;
			cout<<"\n\tEnter The account No. :";
			cin>>id;
			if(id<=0)
			{
				cout<< "Id cannot be negative";
				exit(0);
			}
			cin.ignore();
			cout<<"\n\n\tEnter The First Name of The account Holder :";
			cin.getline(name,30);
			int len;
			len=strlen(name);
			for(int i=0;i<len;i++)
			{
				int ch;
				ch=name[i];
				if(65<=ch & ch<=90 | 92<=ch  & ch<=122)
				{
					continue;
				}
				else
				{
					cout<<"Invalid namme input"<<endl;
					system("PAUSE");
					return;
				}
			}
			cout<<"\n\n\tEnter the Beginning Balance : ";
			cin>>balance;
			if(balance<=0)
			{
				cout<<"Beginnning Balance cannot be zero or less than zero";
				exit(0);
			}
			annual_interest=15;
			no_of_deposit=0;
			no_of_withdrawal=0;
			monthly_charge=0;
		}
	
		//show function declare that gives output of account details
		void show()
		{
			cout<<"\n\nAccount No. : "<<id;
			cout<<"\nAccount Holder Name : ";
			cout<<name;
			cout<<"\nBalance amount : $"<<balance;
			cout<<"\nAnnual interest rate: "<<annual_interest<<"%";
			cout<<"\nNo of Deposit: "<<no_of_deposit;
			cout<<"\nNo of Withdraw: "<<no_of_withdrawal;
			cout<<"\nService Charge: "<<monthly_charge;
		}
		//mutator functions
		void set_balance(double bal)
		{
			balance=bal;
		}
		
		void set_rate(double rate)
		{
			annual_interest=rate;
		}
		
		void set_monthly_charge(double m_charge)
		{
			monthly_charge=m_charge;
		}
		//accessor functions
		int get_id()
		{
			return id;
		}
		
		double get_balance()
		{
			return balance;
		}
		
		double get_annual_interest()
		{
			return annual_interest;
		}
		
		int get_no_of_deposit()
		{
			return no_of_deposit;
		}
		
		int get_no_of_withdrawal()
		{
			return no_of_withdrawal;
		}
		
		double get_monthly_charge()
		{
			return monthly_charge;
		}
		
		//function prototype
		virtual void makeDeposit(double);
		virtual void makeWithdrawal(double);
		virtual void calcInt();
		virtual void monthlyProc();
};

/*makeDeposit a virtual function, it accepts mount as parameter and
adds the amount to balance. It also increase number of deposit*/
void BankAccount::makeDeposit(double amount)
{
	balance += amount;
	no_of_deposit++;
}

/*makeWithdrawal a virtual function, it accepts amount as parameter and
subtracts the amount with balance. It also increases number of withdrawal*/
void BankAccount::makeWithdrawal(double amount)
{
	balance-=amount;
	no_of_withdrawal++;
}

/*calcInt a virtual function, whenever called it adds monthly interest to the balance
(monthly interest= annual interest/12) and as annual interest has % it is lso divided
by 100*/
void BankAccount::calcInt()
{
	balance+=(annual_interest/1200)*balance;
}

/*monthlyProc a virtual function, it subtracts monthly charge from balance and calls calcInt
function and sets number of deposit, number of withdrawal and monthly charge to 0*/
void BankAccount::monthlyProc()
{
	balance-=monthly_charge;
	calcInt();
	no_of_withdrawal=0;
	no_of_deposit=0;
	monthly_charge=0;
}

#endif
