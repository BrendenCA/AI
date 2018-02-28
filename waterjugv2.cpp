#include<iostream>
#include<conio.h>
#include<iomanip>
using namespace std;

int jug1 = 0;
int jug2 = 0;
int capj1;
int capj2;

int gcd(int num1, int num2)
{
	while (num2 != 0)
	{
		int temp = num1 % num2;
		num1 = num2;
		num2 = temp;
	}
	return num1;
}
void printLine(const char* str, int& i)
{
	cout << "[" << right << setfill('0') << setw(2) << i  << "] " << setfill(' ');
	cout << left << setw(45) << str;
	cout << jug1 << "\t\t  " << jug2 << endl;
	i++;
}

void getPath(int goal)
{
	int i = 1;
	cout << left << setw(48) << "Action" << "Jug 1(" << capj1 << "L)\tJug 2(" << capj2 << "L)\n";
	printLine("Initial State", i);
	while (jug1 != goal)
	{
		if (jug1 != capj1 && jug2 == 0)
		{
			jug2 = capj2;
			printLine("Fill jug 2", i);			
		}
		if (jug1 == capj1)
		{
			jug1 = 0;
			printLine("Empty jug 1", i);
		}
		int temp = jug2 - (capj1 - jug1);
		jug1 = (jug1 + jug2) > capj1 ? capj1 : jug1 + jug2;
		jug2 = (temp > 0) ? temp : 0;
		printLine("Pour from jug 2 to jug 1", i);
	}
}

int main()
{
	int goal;
	cout << "Capacity:\nJug 1: ";
	cin >> capj1;
	cout << "Jug 2: ";
	cin >> capj2;
	do {
		cout << "\nGoal:\nJug 1: ";
		cin >> goal;
	} while (goal > capj1 || goal % gcd(capj1, capj2) != 0);
	cout << endl;
	getPath(goal);
	_getch();
	return 0;
}