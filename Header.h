#include <iostream>
#include<conio.h>
#include<sstream>
#include <ctime>
#include <fstream>
using namespace std;


struct Date
{
	int Day,Month,Year;
};
struct Transictions
{
	string TypeOfTrans;
	int Amount;
	Date D1;
};
struct Users
{
	string UserName,UserPasword;
	int Balance;
	string Id;
	Transictions Tran[100];
	int NumberOfTrans;
}AllUsers[100], currentUser;

struct Employee
{
	string EmployeeName,EmployeePassword;
}AllEmployees[100];

void LoadUser(Users AllUsers[],int IndexArrayOfUsers) {
	ifstream inFile2;
	string UserName,TypeOfTrans;
	string UserPass;
	string UserId;
	Date DateOfTrans;
	double Balance,AmountOfTrans;
	IndexArrayOfUsers=0;
	inFile2.open("users.txt");

	while (!inFile2.eof())
	{
		Users u;
		inFile2>>u.UserName;
		inFile2>>u.UserPasword;
		inFile2>>u.Id ;
		inFile2>>u.Balance;
		u.NumberOfTrans=0;
		AllUsers[IndexArrayOfUsers]=u;
		IndexArrayOfUsers++;
	}
	inFile2.close();
	inFile2.open("transactions.txt");
	while (!inFile2.eof())
	{
		string text;
		inFile2>>text;
		for (int IndexTrans=0; IndexTrans<IndexArrayOfUsers; IndexTrans++)
		{
			if (text==AllUsers[IndexTrans].Id)
			{

				Transictions T;
				inFile2 >> T.TypeOfTrans;
				inFile2 >> T.Amount;
				inFile2 >> T.D1.Day;
				inFile2 >> T.D1.Month;
				inFile2 >> T.D1.Year;
				AllUsers[IndexTrans].Tran[AllUsers[IndexTrans].NumberOfTrans] = T;
				AllUsers[IndexTrans].NumberOfTrans++;
				break;
			}


		}

	} 
	inFile2.close();
}
void LoadEmployees(Employee AllEmployees[], int IndexArrayOfEmployes) {
	fstream inFile1;
	IndexArrayOfEmployes=0;
	inFile1.open("employees.txt");
	while (!inFile1.eof())
	{
		Employee e;
		inFile1>>e.EmployeeName;
		inFile1>>e.EmployeePassword;
		AllEmployees[IndexArrayOfEmployes]=e;
		IndexArrayOfEmployes++;
	}
	inFile1.close();
}
bool checkUsers (int size, string Name, string Pass )
{


	for (int i =0 ; i< size ; i++)
	{
		if(AllUsers[i].UserName == Name  && AllUsers[i].UserPasword == Pass)
		{              
			currentUser =  AllUsers[i];
			return true;
		}
	}  

	return false ;
}

bool checkEmploye(int size,string Name,string Pass)
{

	for(int i =0 ; i<size ; i++)
	{
		if(AllEmployees[i].EmployeeName == Name  && AllEmployees[i].EmployeePassword == Pass)
		{
			return true;
		}

	}
	return false;
}
Date Time  (   ){
	Date D;
	time_t now;
	struct tm  nowlocal;
	now=time(NULL);
	nowlocal=*localtime(&now);
	D.Day = nowlocal.tm_mday;
	D.Month = nowlocal.tm_mon+1;
	D.Year = nowlocal.tm_year+1900;

	return D;
}


int  BalanceOfUser()
{
	return currentUser.Balance;
}



void  Withdraw(string amount)
{    
	currentUser.Tran[currentUser.NumberOfTrans].TypeOfTrans="Withdraw";
currentUser.Tran[currentUser.NumberOfTrans].Amount=stoi(amount);
currentUser.Balance-=currentUser.Tran[currentUser.NumberOfTrans].Amount;
currentUser.Tran[currentUser.NumberOfTrans].D1 = Time();
currentUser.NumberOfTrans+=1;
}

void Deposit(string amount)
{   
	currentUser.Tran[currentUser.NumberOfTrans].TypeOfTrans="Deposit";
	currentUser.Tran[currentUser.NumberOfTrans].Amount=stoi(amount);
	currentUser.Balance+=currentUser.Tran[currentUser.NumberOfTrans].Amount;
	currentUser.Tran[currentUser.NumberOfTrans].D1 = Time();
	currentUser.NumberOfTrans+=1;
}

void ArrayOfLastTrans (int &size)
{     int LastTrans=5;
if  (currentUser.NumberOfTrans<LastTrans){LastTrans=currentUser.NumberOfTrans;}
for (int i =currentUser.NumberOfTrans,j=0; j <LastTrans ; j++,i--)
{
	cout<<currentUser.Tran[i].TypeOfTrans<<" ";
	cout<<currentUser.Tran[i].Amount<<"  ";
	cout<<currentUser.Tran[i].D1.Day<<" "
		<<currentUser.Tran[i].D1.Month<<" "
		<<currentUser.Tran[i].D1.Year<<endl;

}
}


void DailyTrans( int size ){  
	Date D2=Time();
	for (int i=0 ; i<size ;i++ ){
		for (int j=0 ; j<AllUsers[i].NumberOfTrans;j++){
			if (D2.Day==AllUsers[i].Tran[j].D1.Day 
				&& D2.Month==AllUsers[i].Tran[j].D1.Month 
				&& D2.Year==AllUsers[i].Tran[j].D1.Year)  {

					cout<<AllUsers[i].UserName<<" "<<AllUsers[ i].Tran[j].TypeOfTrans<<" ";
					cout<<AllUsers[ i].Tran[j].Amount<<endl;  
			}
		}
	}
}

void TranForOneUser (int size, string name ){

	for (int i=0 ; i<size ; i++){
		if (AllUsers[i].UserName==name){
			for (int j=0 ;j <AllUsers[i].NumberOfTrans;j++   ){
				cout<<AllUsers[i].Tran[j].TypeOfTrans<<" "<<
					AllUsers[i].Tran[j].Amount<<"    "<<
					AllUsers[i].Tran[j].D1.Day<<" "<<
					AllUsers[i].Tran[j].D1.Month<<" "<<
					AllUsers[i].Tran[j].D1.Year<<endl;}
			break;}
	}
}