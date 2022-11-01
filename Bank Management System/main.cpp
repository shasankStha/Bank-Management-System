#include <iostream>
#include "SavingAccount.h"
#include "CheckingAccount.h"
#include "BankAccount.h"
#include<fstream>
#include<string>

using namespace std;

/*Intro function it displays group members name  and college name*/
void intro()
{
	cout<<"\n\n\n\t\tBANK MANAGEMENT SYSTEM";
	cout<<"\n\n\n\n\t\t    MADE BY\n\t\tShasank Shrestha";
	cout<<"\n\n\n\n\tThe British College, Trade Tower\n\t\tThapathali";
	cout<<"\n\n";
	system("PAUSE");
}


/*write function is called to create account. It asks the choice of account to be created
whether it is  Saving or Checking. Then it calls create function after making object of the
specified account class and saves the data on the files of particual account*/
void write()
{
	char ch;
	cout<<"\n\n\t01. Saving Account";
	cout<<"\n\n\t02. Checking Account";
	cout<<"\n\n\tSelect Your Option (1-2) : ";
	cin>>ch;
	system("CLS");
	if(ch=='1')
	{
		fstream file;
		fstream file1;
		bool flag=true;
		file1.open("saving_account.dat",ios::binary|ios::in);
		file.open("saving_account.dat",ios::app|ios::binary);
		SavingAccount s,s1;
		s.create();
		while(!file1.eof())
		{
			file1.read((char*)&s1,sizeof(SavingAccount));
			if(s1.get_id()==s.get_id())
			{
				cout<<"\n\nError! Id already taken choose another id.";
				flag=false;
				cout<<"\n\n";
				system("PAUSE");
				break;
			}
		}
		if(flag==true)
		{
			file.write((char*)&s,sizeof(s));
		}
		file.close();
	}
	else if(ch=='2')
	{
		fstream file;
		fstream file1;
		bool flag=true;
		file1.open("checking_account.dat",ios::binary|ios::in);
		file.open("checking_account.dat",ios::app|ios::binary);
		CheckingAccount c,c1;
		c.create();
		while(!file1.eof())
		{
			file1.read((char*)&c1,sizeof(CheckingAccount));
			if(c1.get_id()==c.get_id())
			{
				cout<<"\n\nError! Id already taken choose another id.";
				flag=false;
				cout<<"\n\n";
				system("PAUSE");
				break;
			}
		}
		if(flag==true)
		{
			file.write((char*)&c,sizeof(c));
		}
		file.close();
	}
}


/*display function is called to show the account information. it asks the choice of account that the user wants
to be shown and asks for id then it searches for the id in the specific account files if found it dislays the 
details else Id didn't match is displays*/
void display()
{
	char option;
	int id;
	cout<<"\n\n\t01. Saving Account";
	cout<<"\n\n\t02. Checking Account";
	cout<<"\n\n\tSelect Your Option (1-2) : ";
	cin>>option;
	system("CLS");
	cout<<"Enter the account No. : ";
	ifstream file;
	bool flag=false;
	cin>>id;
	switch(option)
		{
				
		case '1':
			{
				SavingAccount s;
				
				file.open("saving_account.dat",ios::binary|ios::in);
				if(!file)
				{
					cout<<"Error opening file";
					exit(0);
				}
				cout<<"\n\n\tAccount Details:";
				
				while(file.read((char *)&s,sizeof(SavingAccount)))
				{
					if(s.get_id()==id)
					{
						s.show();
						
						flag=true;
					}
				}
				if(flag==false)
				{
					cout<<"\n\nId didn't match";
				}
				file.close();
				cout<<"\n\n";
				system("PAUSE");
				break;
			}
		case '2':
			{
				CheckingAccount c;
				file.open("checking_account.dat",ios::binary|ios::in);
				if(!file)
				{
					cout<<"Error opening file";
					exit(0);
				}
				cout<<"\n\n\tAccount Details:";
				while(file.read((char *)&c,sizeof(CheckingAccount)))
				{
					if(c.get_id()==id)
					{
						c.show();
						flag=true;
					}
				}
				if(flag==false)
				{
					cout<<"\n\nId didn't match";
				}
				file.close();
				cout<<"\n\n";
				system("PAUSE");
				break;
			}
	}
}
	

/*deposit function is called to deposit amount in saving account. It creates object class of SavingAccount class and
asks for id then it search in file if found the account details is loaded then it asks for amount to  be deposit and untill 
the -1 is entered it keeps asking for deposit amount then makeDeposit function is called.
After the deposit is made the files are updated with new balance and other new information*/
void deposit()
{
	int id;
	bool flag=false;
	cout<<"\n\n\tSaving Account Deposit";
	cout<<"\n\nEnter The account No. : ";
	cin>>id;
	fstream file,file1;
	SavingAccount s;
	file.open("saving_account.dat",ios::binary|ios::in);
	file1.open("saving_account1.dat",ios::app|ios::binary);
	if(!file)
	{
		cout<<"Error opening file";
		exit(0);	
	}
	cout<<"\nSaving Account Deposit";
	while(!file.eof())
	{
		file.read((char*)&s,sizeof(SavingAccount));
		if(file.eof())
		{
			break;
		}
		if(s.get_id()==id & flag==false)
		{
			double dep;
			while(1)
			{
				cout<<"\n\nEnter the amount you want to deposit: ";
				cin>>dep;
				if(dep==-1)
				{
					break;
				}
				s.makeDeposit(dep);
				s.show();
				cout<<"\n\nEnter '-1' to exit";
			}
			flag=true;
			cout<<"\n\n\tAccount Details";
			s.show();
			cout<<"\n\n";
			system("PAUSE");
	 		}
			file1.write((char *)&s,sizeof(SavingAccount));
		}
	
		
	if(flag==false)
	{	
		cout<<"\n\nId didn't match";
	}
	file.close();
	file1.close();
	remove("saving_account.dat");
	rename("saving_account1.dat","saving_account.dat");
}


/*withdraw function is called to withdraw amount. It asks the type of account then creates object of specific class type and
asks for id then it search in file if found the account details is loaded thenit asks for amount to be withdrawn and untill
the -1 is entered if keeps asking for withdraw amount then makeWithdrawal function is called.
After the withdrawal is made the files are updated with new balance and other new information*/
void withdraw()
{
	char ch;
	cout<<"\n\n\t01. Saving Account";
	cout<<"\n\n\t02. Checking Account";
	cout<<"\n\n\tSelect Your Option (1-2) : ";
	cin>>ch;
	system("CLS");
	if(ch=='1')
	{
		int id;
		bool flag=false;
		cout<<"\n\n\tSaving Account Withdrawal";
		cout<<"\n\nEnter The account No. : ";
		cin>>id;
		fstream file,file1;
		SavingAccount s;
		file.open("saving_account.dat",ios::binary|ios::in);
		file1.open("saving_account1.dat",ios::app|ios::binary);
		if(!file)
		{
			cout<<"Error opening file";
			exit(0);	
		}
		cout<<"\nSaving Account Withdrawal";
		while(!file.eof())
		{
			file.read((char*)&s,sizeof(SavingAccount));
			if(file.eof())
			{
				break;
			}
			if(s.get_id()==id & flag==false)
			{
				double wit;
				while(1)
				{
					cout<<"\n\nEnter the amount you want to withdraw: ";
					cin>>wit;
					if(wit==-1)
					{
						break;
					}
					s.makeWithdrawal(wit);
					s.show();
					cout<<"\n\nEnter '-1' to exit";
				}
				flag=true;
				cout<<"\n\n\tAccount Details";
				s.show();
				cout<<"\n\n";
				system("PAUSE");
			}
			file1.write((char *)&s,sizeof(SavingAccount));
		}
		
			
		if(flag==false)
		{	
			cout<<"\n\nId didn't match";
		}
		file.close();
		file1.close();
		remove("saving_account.dat");
		rename("saving_account1.dat","saving_account.dat");
	}
	
	else if(ch=='2')
	{
		int id;
		bool flag=false;
		cout<<"\n\n\tChecking Account Withdrawal";
		cout<<"\n\nEnter The account No. : ";
		cin>>id;
		fstream file,file1;
		CheckingAccount c;
		file.open("checking_account.dat",ios::binary|ios::in);
		file1.open("checking_account1.dat",ios::app|ios::binary);
		if(!file)
		{
			cout<<"Error opening file";
			exit(0);	
		}
		cout<<"\nChecking Account Withdrawal";
		while(!file.eof())
		{
			file.read((char*)&c,sizeof(CheckingAccount));
			if(file.eof())
			{
				break;
			}
			if(c.get_id()==id & flag==false)
			{
				double wit;
				while(1)
				{
					cout<<"\n\nEnter the amount you want to withdraw: ";
					cin>>wit;
					if(wit==-1)
					{
						break;
					}
					c.makeWithdrawal(wit);
					c.show();
					cout<<"\n\nEnter '-1' to exit";
				}
				flag=true;
				cout<<"\n\n\tAccount Details";
				c.show();
				cout<<"\n\n";
				system("PAUSE");
			}
			
			file1.write((char *)&c,sizeof(CheckingAccount));
		}
		
			
		if(flag==false)
		{	
			cout<<"\n\nId didn't match";
		}
		file.close();
		file1.close();
		remove("checking_account.dat");
		rename("checking_account1.dat","checking_account.dat");
	}
}


/*remove function is called to delete account. It asks the type of account to be deleated then creates object of specific class type
and asks forr id then is search in files if found, the account with non matched id will be written in  new file. Atlast, the old file
is deleated and the new  file is reanamed as  the old file*/
void remove()
{
	char ch;
	cout<<"\n\n\t01. Saving Account";
	cout<<"\n\n\t02. Checking Account";
	cout<<"\n\n\tSelect Your Option (1-2) : ";
	cin>>ch;
	system("CLS");
	if(ch=='1')
	{
		int id;
		cout<<"\n\n\tDeleting Saving Account";
		cout<<"\n\nEnter The account No. : ";
		cin>>id;
		fstream file;
		fstream file1;
		file.open("saving_account.dat",ios::binary|ios::in);
		file1.open("saving_account1.dat",ios::app|ios::binary);
		SavingAccount s;
		while(!file.eof())
		{
			file.read((char*)&s,sizeof(SavingAccount));
			if(s.get_id()!=id)
			{
				file1.write((char *)&s,sizeof(s));
			}
		}
		file.close();
		file1.close();
		remove("saving_account.dat");
		rename("saving_account1.dat","saving_account.dat");
		cout<<"\n\n\tAccount deleted successfully!!!";
		cout<<"\n\n";
		system("PAUSE");
	}
	if(ch=='2')
	{
		int id;
		cout<<"\n\n\tDeleting Checking Account";
		cout<<"\n\nEnter The account No. : ";
		cin>>id;
		fstream file;
		fstream file1;
		file.open("checking_account.dat",ios::binary|ios::in);
		file1.open("checking_account1.dat",ios::app|ios::binary);
		CheckingAccount c;
		while(!file.eof())
		{
			file.read((char*)&c,sizeof(CheckingAccount));
			if(c.get_id()!=id)
			{
				file1.write((char *)&c,sizeof(c));
			}
		}
		file.close();
		file1.close();
		remove("checking_account.dat");
		rename("checking_account1.dat","checking_account.dat");
		cout<<"\n\n\tAccount deleted successfully!!!";
		cout<<"\n\n";
		system("PAUSE");
	}
}


/*interest funnction is called in every first day of the month, it creats obj os both account types then load every account from files
then calls monthlyProc function to deduct monthly charge and add interest then the updated data stored in new file after all faccount is
updated and stored old file is deleated and new file is renamed with old file name*/
void interest()
{
	fstream file, file1;
	file.open("saving_account.dat",ios::binary|ios::in);
	file1.open("saving_account1.dat",ios::app|ios::binary);
	SavingAccount s;
	while(!file.eof())
	{
		file.read((char *)&s,sizeof(SavingAccount));
		if(file.eof())
		{
			break;
		}
		s.monthlyProc();
		file1.write((char *)&s,sizeof(s));
	}
	file.close();
	file1.close();
	remove("saving_account.dat");
	rename("saving_account1.dat","saving_account.dat");
	
	file.open("checking_account.dat",ios::binary|ios::in);
	file1.open("checking_account1.dat",ios::app|ios::binary);
	CheckingAccount c;
	while(!file.eof())
	{
		file.read((char *)&c,sizeof(CheckingAccount));
		if(file.eof())
		{
			break;
		}
		c.monthlyProc();
		file1.write((char *)&c,sizeof(c));
	}
	file.close();
	file1.close();
	remove("checking_account.dat");
	rename("checking_account1.dat","checking_account.dat");
}



int main()
{
	char ch;
	int id;
	intro();//intro function is called
	string date;
	date=__DATE__;//Current date  is stored is date string
	if(date[4]==' '&date[5]=='1')//the day is indexed annd compared to find whether it is first day of month
	{
		bool flag=true;
		fstream file;
		file.open("date.dat",ios::in|ios::binary);//Current date is stored in file
		string check;
		while(getline(file,check))
		{
			if(check==date)//date is checked if it matches then the flag becomes false and interest fuction is not called
			{
				flag=false;
			}
		}
		file.close();
		if(flag==true)
		{
			file.open("date.dat",ios::app|ios::binary);//if flag is true the date is stored in file and interest function is called 
			file<<date<<endl;
			interest();
		}
		file.close();
	}
	
	/*Menu driven function it will loop untill '6' is entered then only the program will terminate
	There are 6 option to create, to view, to withdraw, to deposit, to delete and exit.*/
	do
	{
		system("cls");
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. CREATE NEW ACCOUNT";
		cout<<"\n\n\t02. ACCOUNT ENQUIRY";
		cout<<"\n\n\t03. WITHDRAW AMOUNT";
		cout<<"\n\n\t04. DEPOSIT AMOUNT IN SAVING ACCOUNT";
		cout<<"\n\n\t05. DELETE AN ACCOUNT";
		cout<<"\n\n\t06. EXIT";
		cout<<"\n\n\tSelect Your Option (1-6) ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
			write();
			break;
		case '2':
			display();
			break;
		case '3':
			withdraw();
			break;
		case '4':
			deposit();
			break;
		case '5':
			remove();
			break;
		 case '6':
			cout<<"\n\n\tThank You!!!";
			exit(0);
		}
	}while(ch!='6');
	return 0;
}
