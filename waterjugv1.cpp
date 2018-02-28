#include<iostream>
#include<vector>
#include<queue>
#include<string>
#include<iomanip>
#include<conio.h>
using namespace std;

struct jugs
{
	int jug1 = 0;
	int jug2 = 0;
	vector<int> path;
	int lastaction = -1;
};

vector<jugs> seen;
int capj1;
int capj2;
int gj1;
int gj2;

void doAction(jugs &j, int id)
{
	int temp;
	j.path.push_back(id);
	j.lastaction = id;
	switch (id)
	{
	case 1:
		j.jug1 = capj1;
		break;
	case 2:
		j.jug2 = capj2;
		break;
	case 3:
		j.jug1 = 0;
		break;
	case 4:
		j.jug2 = 0;
		break;
	case 5:
		temp = j.jug1 - (capj2 - j.jug2);
		j.jug2 = (j.jug2 + j.jug1) > capj2 ? capj2 : j.jug2 + j.jug1;
		j.jug1 = (temp > 0) ? temp : 0;
		break;
	case 6:
		temp = j.jug2 - (capj1 - j.jug1);
		j.jug1 = (j.jug1 + j.jug2) > capj1 ? capj1 : j.jug1 + j.jug2;
		j.jug2 = (temp > 0) ? temp : 0;
		break;
	}
}

void listAction(int num = -1)
{
	string s1[6];
	s1[0] = "Fill jug 1";
	s1[1] = "Fill jug 2";
	s1[2] = "Empty jug 1";
	s1[3] = "Empty jug 2";
	s1[4] = "Transfer jug 1 into jug 2";
	s1[5] = "Transfer jug 2 into jug 1";
	if (num == -1)
		for (int i = 0; i < 6; i++)
			cout << "[" << i + 1 << "] " << s1[i] << endl;
	else
		cout << left << setw(45) << s1[num - 1];
}

bool checkSeen(jugs j)
{
	for (int i = 0; i < seen.size(); i++)
	{
		if (j.jug1 == seen[i].jug1 && j.jug2 == seen[i].jug2)
			return true;
	}
	return false;
}

void prettyPrint(jugs j)
{
	jugs temp;
	system("cls");
	cout << left << setw(48) << "Action" << "Jug 1(" << capj1 << "L)\tJug 2(" << capj2 << "L)\n";
	for (int i = 0; i < j.path.size(); i++)
	{
		cout << "[" << right<<setfill('0')<<setw(2)<< i+1 << "] "<<setfill(' ');
		listAction(j.path[i]);
		doAction(temp, j.path[i]);
		cout << temp.jug1 << "\t\t  " << temp.jug2 << endl;
	}
}

void userPlay(jugs &j)
{
	int ac;
	while (j.jug1 != gj1 || j.jug2 != gj2)
	{
		system("cls");
		cout << "Jug 1: " << j.jug1 << endl;
		cout << "Jug 2: " << j.jug2 << endl;
		listAction();
		cout << "Enter next action: ";
		cin >> ac;
		doAction(j, ac);
	}
}

jugs aiPlay(jugs j)
{
	jugs temp;
	queue<jugs> q;
	q.push(j);
	while (!q.empty())
	{
		for (int i = 1; i <= 6; i++)
		{
			temp = q.front();
			if (temp.lastaction != i)
			{
				doAction(temp, i);
				if (temp.jug1 == gj1 && temp.jug2 == gj2)
					return temp;
				if (!checkSeen(temp))
				{
					q.push(temp);
					seen.push_back(temp);
				}
			}
		}
		q.pop();
	}
	return temp;
}

int main()
{
	jugs j;
	char ch;
	cout << "Capacity:\nJug 1: ";
	cin >> capj1;
	cout << "Jug 2: ";
	cin >> capj2;
	do {
		cout << "\nGoal:\nJug 1: ";
		cin >> gj1;
		cout << "Jug 2: ";
		cin >> gj2;
	} while (gj1 > capj1 || gj2 > capj2);
	cout << "\nUse AI ?[y/n] ";
	cin >> ch;
	cout << endl;
	if(ch=='y' || ch=='Y')
		j = aiPlay(j);
	else
		userPlay(j);
	cout << "\nPath Found!\n[Enter] for solution";
	_getch();
	prettyPrint(j);
	_getch();
	return 0;
}