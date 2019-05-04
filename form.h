#pragma once
	#include <iostream>
#include<conio.h>
#include<sstream>
#include <ctime>
#include <fstream>
#include<sstream>

#include <msclr\marshal_cppstd.h>
namespace Project2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for form
	/// </summary>

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
}AllUsers[100], currentUser,TransArr[10];

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


string  BalanceOfUser(){
	int y=currentUser.Balance;
string x= to_string ( y);
	return x ;
}



void  Withdraw(string WithdrawAmount)
{    
	currentUser.Tran[currentUser.NumberOfTrans].TypeOfTrans="Withdraw";
currentUser.Tran[currentUser.NumberOfTrans].Amount=stoi(WithdrawAmount);
currentUser.Balance-=currentUser.Tran[currentUser.NumberOfTrans].Amount;
currentUser.Tran[currentUser.NumberOfTrans].D1 = Time();
currentUser.NumberOfTrans+=1;
Date D = Time();
		ofstream updating;
				updating.open("transactions.txt",std::ios_base::app);
				updating <<currentUser.Id << " " << "withdraw" << " " << WithdrawAmount << " " << D.Day << " " << D.Month << " " << D.Year << endl;
				updating.close();
}


void Deposit(string DepositAmount)
{   
	currentUser.Tran[currentUser.NumberOfTrans].TypeOfTrans="Deposit";
	currentUser.Tran[currentUser.NumberOfTrans].Amount=stoi(DepositAmount);
	currentUser.Balance+=currentUser.Tran[currentUser.NumberOfTrans].Amount;
	currentUser.Tran[currentUser.NumberOfTrans].D1 = Time();
	currentUser.NumberOfTrans+=1;
	Date D=Time();
	ofstream updating;
				updating.open("transactions.txt",std::ios_base::app);
				updating <<currentUser.Id<< " " << "Deposit" << " " << DepositAmount  << " " << D.Day << " " << D.Month << " " << D.Year<<endl;
				updating.close();
}

void LastTrans ( int &LastTrans)
{   
if  (currentUser.NumberOfTrans<LastTrans){LastTrans=currentUser.NumberOfTrans;}
for (int i =currentUser.NumberOfTrans-1,j=0; j <LastTrans ; j++,i--)
{
	TransArr[j].Tran[j].TypeOfTrans=currentUser.Tran[i].TypeOfTrans;
	TransArr[j].Tran[j].Amount=currentUser.Tran[i].Amount;
	TransArr[j].Tran[j].D1.Day=currentUser.Tran[i].D1.Day;
	TransArr[j].Tran[j].D1.Month=currentUser.Tran[i].D1.Month;
	TransArr[j].Tran[j].D1.Year=currentUser.Tran[i].D1.Year;

}
}


void DailyTrans( Users  DailyTrans[], int &size){  
	Date D2=Time();
	for (int i=0 ; i<10 ;i++ ){
		for (int j=0 ; j<AllUsers[i].NumberOfTrans;j++){
			if (D2.Day==AllUsers[i].Tran[j].D1.Day 
				&& D2.Month==AllUsers[i].Tran[j].D1.Month 
				&& D2.Year==AllUsers[i].Tran[j].D1.Year)  {

					DailyTrans[j].UserName=AllUsers[i].UserName;
					DailyTrans[j].Tran[j].TypeOfTrans=AllUsers[ i].Tran[j].TypeOfTrans;
					DailyTrans[j].Tran[j].Amount=AllUsers[ i].Tran[j].Amount;
						size=j;
			}
		}
	size+=1;}
}

void TranForOneUser (int &size, string name,Users Trans[] ){

	for (int i=0 ; i<10 ; i++){
		if (AllUsers[i].UserName==name){
			size=AllUsers[i].NumberOfTrans;
			for (int j=0 ;j <size ;j++   ){
				Trans[j].Tran[j].TypeOfTrans=AllUsers[i].Tran[j].TypeOfTrans;
				Trans[j].Tran[j].Amount=AllUsers[i].Tran[j].Amount;
				Trans[j].Tran[j].D1.Day=AllUsers[i].Tran[j].D1.Day;
				Trans[j].Tran[j].D1.Month=AllUsers[i].Tran[j].D1.Month;
				Trans[j].Tran[j].D1.Year=AllUsers[i].Tran[j].D1.Year;}
			}
	}
}

void Transfer(int size,string name,string  amount) 
{    
	for (int i = 0; i<size; i++){
		if (AllUsers[i].UserName == name){
			AllUsers[i].Tran[AllUsers[i].NumberOfTrans].Amount =stoi( amount);

			break;
		}
	}
	currentUser.Balance -= stoi( amount);
	currentUser.Tran[currentUser.NumberOfTrans].Amount = stoi( amount);
	currentUser.Tran[currentUser.NumberOfTrans].TypeOfTrans = "Transfer";
	currentUser.Tran[currentUser.NumberOfTrans].D1 = Time();
	currentUser.NumberOfTrans += 1;
	Date D=Time();
	ofstream updating;
				updating.open("transactions.txt",std::ios_base::app);
				updating << currentUser.Id << " " << "Transfer" << " " << amount  << " " << D.Day << " " << D.Month << " " << D.Year<<endl;
				updating.close();
				updating.open("users.txt",std::ios_base::app);
				updating <<currentUser.UserName << " " << currentUser.UserPasword << " " << currentUser.Id << " " << currentUser.Balance << endl;
				updating.close();

}
	public ref class form : public System::Windows::Forms::Form
	{
	public:
		form(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//  msclr::interop::marshal_context context;

		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~form()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected: 
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Label^  label4;

	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::Button^  button7;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::ListBox^  listBox1;
	private: System::Windows::Forms::Button^  button10;
	private: System::Windows::Forms::Button^  button11;
	private: System::Windows::Forms::TextBox^  textBox5;
	private: System::Windows::Forms::Button^  button8;
	private: System::Windows::Forms::Button^  button9;
	private: System::Windows::Forms::ListBox^  listBox2;
	private: System::Windows::Forms::Panel^  panel2;
	private: System::Windows::Forms::Panel^  panel3;
	private: System::Windows::Forms::Panel^  panel5;
	private: System::Windows::Forms::Panel^  panel4;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::Button^  button13;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::ListBox^  listBox3;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::ListBox^  listBox4;

	private: System::Windows::Forms::Button^  button15;
	private: System::Windows::Forms::Button^  button16;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::TextBox^  textBoxX;
	private: System::Windows::Forms::TextBox^  textBox6;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Button^  button12;
	private: System::Windows::Forms::Button^  button17;
	private: System::Windows::Forms::TextBox^  textBox7;
	private: System::Windows::Forms::TextBox^  textBox8;
	private: System::Windows::Forms::Button^  button18;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Button^  button14;
	private: System::Windows::Forms::Button^  button19;

	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->button13 = (gcnew System::Windows::Forms::Button());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->listBox3 = (gcnew System::Windows::Forms::ListBox());
			this->panel5 = (gcnew System::Windows::Forms::Panel());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->listBox4 = (gcnew System::Windows::Forms::ListBox());
			this->button15 = (gcnew System::Windows::Forms::Button());
			this->button16 = (gcnew System::Windows::Forms::Button());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->textBoxX = (gcnew System::Windows::Forms::TextBox());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->button12 = (gcnew System::Windows::Forms::Button());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->button11 = (gcnew System::Windows::Forms::Button());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->listBox2 = (gcnew System::Windows::Forms::ListBox());
			this->button17 = (gcnew System::Windows::Forms::Button());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->textBox8 = (gcnew System::Windows::Forms::TextBox());
			this->button18 = (gcnew System::Windows::Forms::Button());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->button14 = (gcnew System::Windows::Forms::Button());
			this->button19 = (gcnew System::Windows::Forms::Button());
			this->panel1->SuspendLayout();
			this->panel2->SuspendLayout();
			this->panel3->SuspendLayout();
			this->panel4->SuspendLayout();
			this->panel5->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(377, 18);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(413, 51);
			this->label1->TabIndex = 3;
			this->label1->Text = L"WELCOM TO ATM";
			this->label1->Click += gcnew System::EventHandler(this, &form::label1_Click);
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Tahoma", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button1->Location = System::Drawing::Point(201, 168);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(241, 86);
			this->button1->TabIndex = 4;
			this->button1->Text = L"USER";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &form::button1_Click);
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Tahoma", 22, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button2->Location = System::Drawing::Point(776, 168);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(241, 86);
			this->button2->TabIndex = 5;
			this->button2->Text = L"EMPLOYEE";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &form::button2_Click);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(304, 467);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(270, 22);
			this->textBox2->TabIndex = 10;
			this->textBox2->Visible = false;
			this->textBox2->TextChanged += gcnew System::EventHandler(this, &form::textBox2_TextChanged);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(304, 351);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(270, 22);
			this->textBox1->TabIndex = 9;
			this->textBox1->Visible = false;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &form::textBox1_TextChanged_1);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Tahoma", 28, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(27, 436);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(222, 57);
			this->label2->TabIndex = 8;
			this->label2->Text = L"Password";
			this->label2->Visible = false;
			this->label2->Click += gcnew System::EventHandler(this, &form::label2_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Tahoma", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(28, 336);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(202, 48);
			this->label3->TabIndex = 7;
			this->label3->Text = L"UserName";
			this->label3->Visible = false;
			this->label3->Click += gcnew System::EventHandler(this, &form::label3_Click);
			// 
			// button3
			// 
			this->button3->Font = (gcnew System::Drawing::Font(L"Tahoma", 22, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button3->Location = System::Drawing::Point(416, 525);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(157, 86);
			this->button3->TabIndex = 6;
			this->button3->Text = L"Login";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Visible = false;
			this->button3->Click += gcnew System::EventHandler(this, &form::button3_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Times New Roman", 36, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(269, 41);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(608, 68);
			this->label4->TabIndex = 11;
			this->label4->Text = L"welcom to your account";
			this->label4->Visible = false;
			this->label4->Click += gcnew System::EventHandler(this, &form::label4_Click);
			// 
			// textBox4
			// 
			this->textBox4->Font = (gcnew System::Drawing::Font(L"Tahoma", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->textBox4->Location = System::Drawing::Point(1052, 260);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(235, 28);
			this->textBox4->TabIndex = 17;
			this->textBox4->Visible = false;
			// 
			// button4
			// 
			this->button4->Font = (gcnew System::Drawing::Font(L"Tahoma", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button4->Location = System::Drawing::Point(1059, 350);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(235, 70);
			this->button4->TabIndex = 16;
			this->button4->Text = L"last 5 \r\ntransactions";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Visible = false;
			this->button4->Click += gcnew System::EventHandler(this, &form::button4_Click);
			// 
			// button5
			// 
			this->button5->Font = (gcnew System::Drawing::Font(L"Tahoma", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button5->Location = System::Drawing::Point(743, 347);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(225, 70);
			this->button5->TabIndex = 15;
			this->button5->Text = L"Withdraw";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Visible = false;
			this->button5->Click += gcnew System::EventHandler(this, &form::button5_Click);
			// 
			// button6
			// 
			this->button6->Font = (gcnew System::Drawing::Font(L"Tahoma", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button6->Location = System::Drawing::Point(729, 155);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(225, 79);
			this->button6->TabIndex = 13;
			this->button6->Text = L"Balance";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Visible = false;
			this->button6->Click += gcnew System::EventHandler(this, &form::button6_Click);
			// 
			// button7
			// 
			this->button7->Font = (gcnew System::Drawing::Font(L"Tahoma", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button7->Location = System::Drawing::Point(1060, 155);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(235, 70);
			this->button7->TabIndex = 12;
			this->button7->Text = L"Deposit";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Visible = false;
			this->button7->Click += gcnew System::EventHandler(this, &form::button7_Click);
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->label5);
			this->panel1->Controls->Add(this->listBox1);
			this->panel1->Location = System::Drawing::Point(11, 156);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(664, 409);
			this->panel1->TabIndex = 18;
			this->panel1->Visible = false;
			this->panel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &form::panel1_Paint);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Tahoma", 22, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(16, 20);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(407, 45);
			this->label5->TabIndex = 1;
			this->label5->Text = L"Your Last 5 Transitions ";
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->ItemHeight = 16;
			this->listBox1->Location = System::Drawing::Point(13, 76);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(643, 308);
			this->listBox1->TabIndex = 0;
			this->listBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &form::listBox1_SelectedIndexChanged);
			// 
			// panel2
			// 
			this->panel2->Controls->Add(this->panel3);
			this->panel2->Controls->Add(this->textBoxX);
			this->panel2->Controls->Add(this->textBox6);
			this->panel2->Controls->Add(this->label6);
			this->panel2->Controls->Add(this->label7);
			this->panel2->Controls->Add(this->button12);
			this->panel2->Location = System::Drawing::Point(11, 10);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(1322, 694);
			this->panel2->TabIndex = 27;
			this->panel2->Visible = false;
			// 
			// panel3
			// 
			this->panel3->Controls->Add(this->panel4);
			this->panel3->Controls->Add(this->panel5);
			this->panel3->Controls->Add(this->button15);
			this->panel3->Controls->Add(this->button16);
			this->panel3->Controls->Add(this->label11);
			this->panel3->Location = System::Drawing::Point(11, 3);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(1328, 685);
			this->panel3->TabIndex = 15;
			this->panel3->Visible = false;
			this->panel3->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &form::panel3_Paint_1);
			// 
			// panel4
			// 
			this->panel4->Controls->Add(this->textBox3);
			this->panel4->Controls->Add(this->button13);
			this->panel4->Controls->Add(this->label8);
			this->panel4->Controls->Add(this->listBox3);
			this->panel4->Location = System::Drawing::Point(7, 314);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(709, 427);
			this->panel4->TabIndex = 12;
			this->panel4->Visible = false;
			this->panel4->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &form::panel4_Paint);
			// 
			// textBox3
			// 
			this->textBox3->Font = (gcnew System::Drawing::Font(L"Tahoma", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->textBox3->Location = System::Drawing::Point(36, 76);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(168, 28);
			this->textBox3->TabIndex = 7;
			this->textBox3->Text = L"enter the username";
			this->textBox3->TextChanged += gcnew System::EventHandler(this, &form::textBox3_TextChanged_1);
			// 
			// button13
			// 
			this->button13->Font = (gcnew System::Drawing::Font(L"Tahoma", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button13->Location = System::Drawing::Point(301, 67);
			this->button13->Name = L"button13";
			this->button13->Size = System::Drawing::Size(145, 40);
			this->button13->TabIndex = 6;
			this->button13->Text = L"search";
			this->button13->UseVisualStyleBackColor = true;
			this->button13->Click += gcnew System::EventHandler(this, &form::button13_Click);
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Times New Roman", 16, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label8->Location = System::Drawing::Point(35, 24);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(589, 31);
			this->label8->TabIndex = 5;
			this->label8->Text = L"Search for all transactions for a specific user account";
			// 
			// listBox3
			// 
			this->listBox3->FormattingEnabled = true;
			this->listBox3->ItemHeight = 16;
			this->listBox3->Location = System::Drawing::Point(46, 120);
			this->listBox3->Name = L"listBox3";
			this->listBox3->Size = System::Drawing::Size(592, 276);
			this->listBox3->TabIndex = 4;
			// 
			// panel5
			// 
			this->panel5->Controls->Add(this->label9);
			this->panel5->Controls->Add(this->label10);
			this->panel5->Controls->Add(this->listBox4);
			this->panel5->Location = System::Drawing::Point(722, 314);
			this->panel5->Name = L"panel5";
			this->panel5->Size = System::Drawing::Size(661, 392);
			this->panel5->TabIndex = 11;
			this->panel5->Visible = false;
			this->panel5->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &form::panel5_Paint);
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Tahoma", 16, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label9->Location = System::Drawing::Point(68, 19);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(481, 33);
			this->label9->TabIndex = 5;
			this->label9->Text = L"Generate report about daily transaction";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Tahoma", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label10->Location = System::Drawing::Point(189, -2);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(0, 41);
			this->label10->TabIndex = 4;
			this->label10->Visible = false;
			// 
			// listBox4
			// 
			this->listBox4->FormattingEnabled = true;
			this->listBox4->ItemHeight = 16;
			this->listBox4->Location = System::Drawing::Point(44, 78);
			this->listBox4->Name = L"listBox4";
			this->listBox4->Size = System::Drawing::Size(612, 308);
			this->listBox4->TabIndex = 3;
			this->listBox4->SelectedIndexChanged += gcnew System::EventHandler(this, &form::listBox4_SelectedIndexChanged);
			// 
			// button15
			// 
			this->button15->Font = (gcnew System::Drawing::Font(L"Times New Roman", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button15->Location = System::Drawing::Point(254, 246);
			this->button15->Name = L"button15";
			this->button15->Size = System::Drawing::Size(834, 63);
			this->button15->TabIndex = 9;
			this->button15->Text = L"2- Search for all transactions for a specific user account";
			this->button15->UseVisualStyleBackColor = true;
			this->button15->Click += gcnew System::EventHandler(this, &form::button15_Click);
			// 
			// button16
			// 
			this->button16->Font = (gcnew System::Drawing::Font(L"Tahoma", 17, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button16->Location = System::Drawing::Point(254, 136);
			this->button16->Name = L"button16";
			this->button16->Size = System::Drawing::Size(644, 63);
			this->button16->TabIndex = 8;
			this->button16->Text = L"1- Generate report about daily transaction";
			this->button16->UseVisualStyleBackColor = true;
			this->button16->Click += gcnew System::EventHandler(this, &form::button16_Click);
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Times New Roman", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label11->Location = System::Drawing::Point(245, 19);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(635, 45);
			this->label11->TabIndex = 7;
			this->label11->Text = L"Welcom To The Employees Account ";
			// 
			// textBoxX
			// 
			this->textBoxX->Location = System::Drawing::Point(447, 235);
			this->textBoxX->Name = L"textBoxX";
			this->textBoxX->Size = System::Drawing::Size(242, 22);
			this->textBoxX->TabIndex = 14;
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(447, 143);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(242, 22);
			this->textBox6->TabIndex = 13;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Tahoma", 22, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(93, 214);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(173, 45);
			this->label6->TabIndex = 12;
			this->label6->Text = L"Password";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Tahoma", 22, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label7->Location = System::Drawing::Point(74, 130);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(270, 45);
			this->label7->TabIndex = 11;
			this->label7->Text = L"EmployeeName";
			// 
			// button12
			// 
			this->button12->Font = (gcnew System::Drawing::Font(L"Tahoma", 22, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button12->Location = System::Drawing::Point(538, 317);
			this->button12->Name = L"button12";
			this->button12->Size = System::Drawing::Size(168, 89);
			this->button12->TabIndex = 10;
			this->button12->Text = L"Login";
			this->button12->UseVisualStyleBackColor = true;
			this->button12->Click += gcnew System::EventHandler(this, &form::button12_Click_1);
			// 
			// button10
			// 
			this->button10->Location = System::Drawing::Point(1143, 302);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(67, 33);
			this->button10->TabIndex = 20;
			this->button10->Text = L"ok";
			this->button10->UseVisualStyleBackColor = true;
			this->button10->Visible = false;
			this->button10->Click += gcnew System::EventHandler(this, &form::button10_Click);
			// 
			// button11
			// 
			this->button11->Location = System::Drawing::Point(817, 500);
			this->button11->Name = L"button11";
			this->button11->Size = System::Drawing::Size(67, 29);
			this->button11->TabIndex = 21;
			this->button11->Text = L"ok";
			this->button11->UseVisualStyleBackColor = true;
			this->button11->Visible = false;
			this->button11->Click += gcnew System::EventHandler(this, &form::button11_Click);
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(729, 451);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(229, 22);
			this->textBox5->TabIndex = 22;
			this->textBox5->Visible = false;
			// 
			// button8
			// 
			this->button8->Location = System::Drawing::Point(799, 302);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(67, 33);
			this->button8->TabIndex = 23;
			this->button8->Text = L"ok";
			this->button8->UseVisualStyleBackColor = true;
			this->button8->Visible = false;
			this->button8->Click += gcnew System::EventHandler(this, &form::button8_Click_1);
			// 
			// button9
			// 
			this->button9->Font = (gcnew System::Drawing::Font(L"Tahoma", 11, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button9->Location = System::Drawing::Point(600, 572);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(67, 61);
			this->button9->TabIndex = 24;
			this->button9->Text = L"ok";
			this->button9->UseMnemonic = false;
			this->button9->UseVisualStyleBackColor = true;
			this->button9->Visible = false;
			this->button9->Click += gcnew System::EventHandler(this, &form::button9_Click);
			// 
			// listBox2
			// 
			this->listBox2->FormattingEnabled = true;
			this->listBox2->ItemHeight = 16;
			this->listBox2->Location = System::Drawing::Point(722, 260);
			this->listBox2->Name = L"listBox2";
			this->listBox2->Size = System::Drawing::Size(225, 36);
			this->listBox2->TabIndex = 25;
			this->listBox2->Visible = false;
			this->listBox2->SelectedIndexChanged += gcnew System::EventHandler(this, &form::listBox2_SelectedIndexChanged);
			// 
			// button17
			// 
			this->button17->Font = (gcnew System::Drawing::Font(L"Tahoma", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button17->Location = System::Drawing::Point(964, 488);
			this->button17->Name = L"button17";
			this->button17->Size = System::Drawing::Size(235, 73);
			this->button17->TabIndex = 16;
			this->button17->Text = L"Transfer";
			this->button17->UseVisualStyleBackColor = true;
			this->button17->Visible = false;
			this->button17->Click += gcnew System::EventHandler(this, &form::button17_Click);
			// 
			// textBox7
			// 
			this->textBox7->Location = System::Drawing::Point(1042, 655);
			this->textBox7->Name = L"textBox7";
			this->textBox7->Size = System::Drawing::Size(229, 22);
			this->textBox7->TabIndex = 28;
			this->textBox7->Visible = false;
			// 
			// textBox8
			// 
			this->textBox8->Location = System::Drawing::Point(725, 655);
			this->textBox8->Name = L"textBox8";
			this->textBox8->Size = System::Drawing::Size(229, 22);
			this->textBox8->TabIndex = 29;
			this->textBox8->Visible = false;
			// 
			// button18
			// 
			this->button18->Location = System::Drawing::Point(1276, 669);
			this->button18->Name = L"button18";
			this->button18->Size = System::Drawing::Size(67, 29);
			this->button18->TabIndex = 30;
			this->button18->Text = L"ok";
			this->button18->UseVisualStyleBackColor = true;
			this->button18->Visible = false;
			this->button18->Click += gcnew System::EventHandler(this, &form::button18_Click);
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label12->Location = System::Drawing::Point(716, 609);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(605, 26);
			this->label12->TabIndex = 31;
			this->label12->Text = L"Enter 1) the name of user account 2) amout to transfer too";
			this->label12->Visible = false;
			this->label12->Click += gcnew System::EventHandler(this, &form::label12_Click);
			// 
			// button14
			// 
			this->button14->Font = (gcnew System::Drawing::Font(L"Tahoma", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button14->Location = System::Drawing::Point(650, 712);
			this->button14->Name = L"button14";
			this->button14->Size = System::Drawing::Size(85, 40);
			this->button14->TabIndex = 32;
			this->button14->Text = L"ok";
			this->button14->UseVisualStyleBackColor = true;
			this->button14->Visible = false;
			this->button14->Click += gcnew System::EventHandler(this, &form::button14_Click);
			// 
			// button19
			// 
			this->button19->Font = (gcnew System::Drawing::Font(L"Tahoma", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button19->Location = System::Drawing::Point(1276, 712);
			this->button19->Name = L"button19";
			this->button19->Size = System::Drawing::Size(85, 40);
			this->button19->TabIndex = 33;
			this->button19->Text = L"ok";
			this->button19->UseVisualStyleBackColor = true;
			this->button19->Visible = false;
			this->button19->Click += gcnew System::EventHandler(this, &form::button19_Click);
			// 
			// form
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1368, 743);
			this->Controls->Add(this->button19);
			this->Controls->Add(this->button14);
			this->Controls->Add(this->label12);
			this->Controls->Add(this->button18);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->textBox8);
			this->Controls->Add(this->textBox7);
			this->Controls->Add(this->button8);
			this->Controls->Add(this->listBox2);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->button17);
			this->Controls->Add(this->button9);
			this->Controls->Add(this->textBox5);
			this->Controls->Add(this->button11);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button10);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->button7);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label1);
			this->Name = L"form";
			this->Text = L"form";
			this->Load += gcnew System::EventHandler(this, &form::form_Load);
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			this->panel3->ResumeLayout(false);
			this->panel3->PerformLayout();
			this->panel4->ResumeLayout(false);
			this->panel4->PerformLayout();
			this->panel5->ResumeLayout(false);
			this->panel5->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				int indexofusers=0; 
				  button2->Visible=false;
				  button3->Visible=true;
				  textBox2->Visible=true;
					  textBox1->Visible=true;
					  label3->Visible=true;
					  label2->Visible=true; 
					  LoadUser(AllUsers,indexofusers);
			 }

private: System::Void label2_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void textBox1_TextChanged_1(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
			 
			msclr::interop::marshal_context context;

		   std::string name2 = context.marshal_as<std::string>(textBox1->Text);
		   std::string pass = context.marshal_as<std::string>(textBox2->Text);
		   

			bool AccountExist = checkUsers(10,name2,pass);
			if(AccountExist==true)
			{  label4->Visible=true;
			button6->Visible=true;
			button7->Visible=true;
			button5->Visible=true;
			button4->Visible=true;
			button17->Visible=true;

			  button2->Visible=false;
				  button3->Visible=false;
				  textBox2->Visible=false;
					  textBox1->Visible=false;
					  label3->Visible=false;
					  label2->Visible=false;
					  button1->Visible=false;
					  label1->Visible=false;
			}
			else
			{    MessageBox::Show("Wrong Password Or UserName Please Try Again");
				// failed
				textBox1->Clear();
				textBox2->Clear();
			}
		 }
private: System::Void label4_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {
			listBox2->Items->Clear();
			 button8->Visible=true;
			 listBox2->Visible=true;
			 string balance=BalanceOfUser();
			 String^g=gcnew String(balance.c_str());
			 listBox2->Items->Add(g);
		
		 }
private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e) {
		 textBox4->Clear();
			 textBox4->Visible=true;
		button10->Visible=true;
		
		 }
private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
             textBox5->Clear();
			 textBox5->Visible=true;
		button11->Visible=true;
			
		 }
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
			 listBox1->Items->Clear();
			 panel1->Visible=true;
			 button9->Visible=true;
int NumbTrans=5;
			 LastTrans(NumbTrans);
			for (int i=0 ;i <NumbTrans; i++){
			 String^A=gcnew String(TransArr[i].Tran[i].TypeOfTrans.c_str())+"   "+TransArr[i].Tran[i].Amount+" $";	 

		    String^C=gcnew String (to_string(TransArr[i].Tran[i].D1.Day).c_str())+"  "+TransArr[i].Tran[i].D1.Month+"  "+TransArr[i].Tran[i].D1.Year;
              
				 listBox1->Items->Add(A);
				
				 listBox1->Items->Add(C);
			 }

		 }

private: System::Void label3_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void textBox2_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }

private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {

			 panel2->Visible=true;
				 LoadEmployees(AllEmployees,5);
				 LoadUser(AllUsers,10);

		 }
private: System::Void form_Load(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void textBox3_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void button10_Click(System::Object^  sender, System::EventArgs^  e) {
			 	textBox4->Visible=false;
		button10->Visible=false;
			
            msclr::interop::marshal_context context;

	 std::string Amount = context.marshal_as<std::string>(textBox4->Text);
		Deposit(Amount);
			
		 }
private: System::Void panel1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		 }
private: System::Void listBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			
			 }
private: System::Void button9_Click(System::Object^  sender, System::EventArgs^  e) {
			  panel1->Visible=false;
			   button9->Visible=false;
			 
		 }
private: System::Void button8_Click_1(System::Object^  sender, System::EventArgs^  e) {
			listBox2->Visible=false;
		
			 button8->Visible=false;
			
		 }
private: System::Void button11_Click(System::Object^  sender, System::EventArgs^  e) {
			 textBox5->Visible=false;
		button11->Visible=false;
		msclr::interop::marshal_context context;
	 std::string Amount = context.marshal_as<std::string>(textBox5->Text);
	  string balance=BalanceOfUser();
			 String^g=gcnew String(balance.c_str());
	
	if (Amount>balance){MessageBox::Show("it's more than your Balance Please Try Again");textBox5->Clear(); }
	else{ Withdraw(Amount);}

			
		 }
private: System::Void listBox2_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void panel2_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		 }

private: System::Void textBoxX_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void panel3_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		 }
private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void button17_Click(System::Object^  sender, System::EventArgs^  e) {
		 textBox8->Clear();
                textBox7->Clear();	
				textBox8->Visible=true;
				 textBox7->Visible=true;
				 label12->Visible=true;
				 button18->Visible=true;
				
		 }

private: System::Void label12_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void button18_Click(System::Object^  sender, System::EventArgs^  e) {
			  textBox8->Visible=false;
				 textBox7->Visible=false;
				 label12->Visible=false;
				 button18->Visible=false;
				  msclr::interop::marshal_context context;

		   std::string name = context.marshal_as<std::string>(textBox8->Text);
		   std::string amount = context.marshal_as<std::string>(textBox7->Text);
				 Transfer(10,name,amount);
		 }
private: System::Void panel4_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		 }
private: System::Void button12_Click_1(System::Object^  sender, System::EventArgs^  e) {

			  msclr::interop::marshal_context context;

		   std::string name2 = context.marshal_as<std::string>(textBox6->Text);
		   std::string pass = context.marshal_as<std::string>(textBoxX->Text);
		 

		bool AccountExist=checkEmploye(5,name2,pass);
		if(AccountExist==true)
		{panel3->Visible=true;
		
			
		}
			 else
			{    MessageBox::Show("Wrong Password Or UserName Please Try Again");
				// failed
				textBox6->Clear();
                textBoxX->Clear();
		}
		 
		 }	
private: System::Void panel3_Paint_1(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		 }
private: System::Void button15_Click(System::Object^  sender, System::EventArgs^  e) {
			 panel4->Visible=true;
			 textBox3->Clear();
			 button14->Visible=true;
			 listBox3->Items->Clear();

		 }
private: System::Void button16_Click(System::Object^  sender, System::EventArgs^  e) {
			  panel5->Visible=true;
			  listBox4->Items->Clear();
			  int size=20;
			  Users *daliyTrans =new Users [size];
			  DailyTrans(daliyTrans,size);

			  for (int i=0 ;i <size; i++){
			 String^k=gcnew String(daliyTrans[i].Tran[i].TypeOfTrans.c_str())+"   "+daliyTrans[i].Tran[i].Amount+" $";	 

			 String^x=gcnew String (daliyTrans[i].UserName.c_str());
              
				 listBox4->Items->Add(x);
				
				 listBox4->Items->Add(k);
			 }

		 }
private: System::Void panel5_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		 }
private: System::Void button13_Click(System::Object^  sender, System::EventArgs^  e) {
			 int size=10;  listBox3->Items->Clear();
			   
Users *Trans = new Users [size];
 msclr::interop::marshal_context context;
 std::string name = context.marshal_as<std::string>(textBox3->Text);
			 TranForOneUser(size,name,Trans);
			 
			for (int i=0 ;i <size; i++){
			 String^b=gcnew String(Trans[i].Tran[i].TypeOfTrans.c_str())+"   "+Trans[i].Tran[i].Amount+" $";	 

		    String^f=gcnew String (to_string(Trans[i].Tran[i].D1.Day).c_str())+"  "+Trans[i].Tran[i].D1.Month+"  "+Trans[i].Tran[i].D1.Year;
              
				 listBox3->Items->Add(b);
				
				 listBox3->Items->Add(f);
			 }
		 }
private: System::Void textBox3_TextChanged_1(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void button14_Click(System::Object^  sender, System::EventArgs^  e) {
			button14 ->Visible=false;
			 panel4->Visible=false;
		 }
private: System::Void listBox4_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {

		 }
private: System::Void button19_Click(System::Object^  sender, System::EventArgs^  e) {
			   panel5->Visible=false;
			   button19->Visible=false;
		 }
};
}
