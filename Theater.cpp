// Theather Project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>
#include <ctime>
#include <windows.h> 
using namespace std;

void showrow(char auditorium[][30]);
void soldmoney(char auditorium[][30], ifstream& in);
void soldticks(char auditorium[][30]);
void buy(char auditorium[][30], ifstream& in);
void random(char auditorium[][30]);
void displayentire(char auditorium[][30]);
void a(char auditorium[][30]);
void color(char a);
int _tmain(int argc, _TCHAR* argv[])
{
	char auditorium[15][30] = { {} };
	ifstream in;
	in.open("seats.txt"); // read price of tickets
	int choose = 0;
	random(auditorium); //randomizes seats available 
	do 
	{
		cout << "Choose one of the following to do." << endl; // 6 options
		cout << "(1) Purchase tickets (2) Display the total dollar value of all tickets sold (3) Display the total number of tickets sold" << endl;
		cout << "(4) Display the number of seats available in each row  (5) Display the number of seats available in the entire auditorium" << endl;
		cout << "(6) Display the current seating chart  (7) Exit the system" << endl;
		cin >> choose;
		if (choose == 1)
		{
			in.close();
			buy(auditorium, in);
			system("CLS");
			in.open("seats.txt");
		}
		if (choose == 2)
		{
			in.close();
			soldmoney(auditorium, in);
			system("CLS");
			in.open("seats.txt");
		}
		if (choose == 3)
		{
			soldticks(auditorium);
			system("CLS");
		}
		if (choose == 4)
		{
			showrow(auditorium);
			system("CLS");
		}
		if (choose == 5)
		{
			a(auditorium);
			system("CLS");
		}
		if (choose == 6)
		{
			displayentire(auditorium);
			system("CLS");
		}
	} while (choose != 7);
	in.close();
	return 0;
}

void displayentire(char auditorium[][30]) //display the auditorium
{
	int w = 1;
	cout.setf(ios::left);
	cout << setw(29) << " ";
	cout.unsetf(ios::left);
	cout.setf(ios::right);
	for (int i = 1; i <= 30; i++)
	{
			cout << setw(3) << i;
	}
	cout.unsetf(ios::right);
	cout << endl;
	for (int i = 0; i < 15; i++)
	{
		cout.setf(ios::left);
		cout << setw(30) << " ";
		cout.unsetf(ios::left);
		cout.setf(ios::right);
		cout << "------------------------------------------------------------------------------------------" << endl;
		for (int j = 0; j < 30; j++)
		{
			if (w == 1)
			{
				cout.unsetf(ios::right);
				cout.setf(ios::left);
				if (i > 8)
				{
					if (i == 9)
					{
						cout << "Row " << i + 1 << setw(25);
					}
					else
					{
						cout << "Row " << i + 1 << setw(25);
					}
				}
				else
				{
					cout << "Row " << i + 1 << setw(26);
				}
				w = 0;
				cout.unsetf(ios::left);
				cout.setf(ios::right);
			}
			cout << "|";
			char a = auditorium[i][j];
			color(a);
			cout << "|";
		}
		cout << endl;
		w = 1;
	}
	cout.setf(ios::left);
	cout << setw(30) << " ";
	cout.unsetf(ios::left);
	cout.setf(ios::right);
	cout << "------------------------------------------------------------------------------------------" << endl;
	cout.unsetf(ios::right);
	system("pause");
}

void random(char auditorium[][30])
{
	srand(time(NULL));
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			char available[2] = { '*', '#' };
			int random = rand() % 2;
			auditorium[i][j] = available[random];

		}
	}
}

void buy(char auditorium[][30], ifstream& in)
{
	int i = 0, j = 0, m = 0, l = 0, p = 0;
	char more = 'y';
	do{
		in.open("seats.txt");
		i = 0, j = 0, m = 0, l = 0, p = 0;
		cout << "Choose a row (1 - 15)" << endl;
		cin >> i;
		cout << "Choose a column (1 -30)" << endl;
		cin >> j;
		if (auditorium[i - 1][j - 1] == '*')
		{
			do
			{
				cout << "Seat is already taken" << endl;
				cout << "Choose a row (1 - 15)" << endl;
				cin >> i;
				cout << "Choose a column (1 -30)" << endl;
				cin >> j;
			} while (auditorium[i - 1][j - 1] == '*');
		}
		auditorium[i - 1][j - 1] = '*';
		while (in >> m)
		{
			p = m;
			if (l == i)
			{
				break;
			}
			l++;
		}
		cout << "Your total is $" << p << endl;
		cout << "Purchase more?" << endl;
		cin >> more;
		in.close();
	} while (more == 'y');

}

void soldticks(char auditorium[][30])
{
	int s = 0;
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			if (auditorium[i][j] == '*')
			{
				s++;
			}
		}
	}
	cout << "There are " << s << " tickets sold." << endl;
	system("pause");
}

void soldmoney(char auditorium[][30], ifstream& in)
{
	in.open("seats.txt");
	int m = 0, ticks = 0;
	double total = 0;
	for (int i = 0; i < 15; i++)
	{
		in >> m;
		for (int j = 0; j < 30; j++)
		{
			if (auditorium[i][j] == '*')
			{
				ticks++;
			}
		}
		total = total + (m * ticks);
		ticks = 0;
	}
	cout.precision(2);
	cout.setf(ios::fixed);
	cout << "You have sold $" << total << endl;
	in.close();
	system("pause");
}

void showrow(char auditorium[][30])
{
	int row = 0, seats = 0;
	cout << "What row do want to see (1 - 15)" << endl;
	cin >> row;
	row = row - 1;
	for (int j = 0; j < 30; j++)
	{
		if (auditorium[row][j] == '#')
		{
			seats++;
		}
	}
	cout << "There are " << seats << " available at row " << row << endl;
	system("pause");
}

void a(char auditorium[][30])
{
	int total = 0;
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			if (auditorium[i][j] == '#')
			{
				total++;
			}
		}
	}
	cout << "The total seats available: " << total << endl;
	system("pause");
}

void color(char a) //Used to display auditorium w/ color
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (a == '*')
	{
		SetConsoleTextAttribute(hConsole, 12); //Red
		cout << "*";
	}
	if (a == '#')
	{
		SetConsoleTextAttribute(hConsole, 10); //Green
		cout << "#";
	}
	SetConsoleTextAttribute(hConsole, 7);

}
