#include<iostream>
#include<vector>
#include<conio.h>
using namespace std;

char board[] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
int magic[] = { 2, 7, 6, 9, 5, 1, 4, 3, 8 };
int rmagic[] = { -1, 5, 0, 7, 6, 4, 2, 1, 8, 3 };
vector<int> playermoves;
vector<int> cpumoves;

void printboard()
{
	cout << "Player (X)  -  CPU (O)" << endl;
	cout << endl;
	cout << "     |     |     " << endl;
	cout << "  " << board[0] << "  |  " << board[1] << "  |  " << board[2] << endl;
	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;
	cout << "  " << board[3] << "  |  " << board[4] << "  |  " << board[5] << endl;
	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;
	cout << "  " << board[6] << "  |  " << board[7] << "  |  " << board[8] << endl;
	cout << "     |     |     " << endl << endl;
}

void mark(int n, char p)
{
	board[n] = p;
	cout << p << " played position " << n + 1 << endl;
	if (p == 'X')
		playermoves.push_back(n);
	else
		cpumoves.push_back(n);
	printboard();
}

bool checkwin() {
	int temp[] = { 0, 3, 6 };
	for (int i = 0; i < 3; i++)
	{
		//check columnwise
		if (board[i] == board[i + 3] && board[i + 3] == board[i + 6] && board[i] != ' ')
		{
			cout << board[i] << " wins";
			_getch();
			return true;
		}
		//check rowwise
		if (board[temp[i]] == board[temp[i] + 1] && board[temp[i] + 1] == board[temp[i] + 2] && board[temp[i]] != ' ')
		{
			cout << board[temp[i]] << " wins";
			_getch();
			return true;
		}
	}

	//check diagonals
	if (board[0] == board[4] && board[4] == board[8] && board[4] != ' ')
	{
		cout << board[4] << " wins";
		_getch();
		return true;
	}
	if (board[2] == board[4] && board[4] == board[6] && board[4] != ' ')
	{
		cout << board[4] << " wins";
		_getch();
		return true;
	}

	//check draw
	for (int i = 0; i < 9; i++)
		if (board[i] == ' ')
			return false;
	cout << "Draw";
	_getch();
	return true;
}

void playuser()
{
	int move;
	do
	{
		cout << "Move[1-9]: ";
		cin >> move;
		move = move - 1;
	} while (board[move] != ' ');
	mark(move, 'X');
}

void playbest()
{
	int temp[] = { 4,0,2,6,8,1,3,5,7 };
	for (int i = 0; i < sizeof(temp)/4; i++)
	{
		if (board[temp[i]] == ' ')
		{
			return mark(temp[i], 'O');
		}

	}


}
bool exists(int n)
{
	if (find(playermoves.begin(), playermoves.end(), n) != playermoves.end())
		return true;
	return false;
}

void playmagic() {
	int temp;
	//check if possible to win in current try
	for (int i = 0; i < cpumoves.size(); i++)
	{
		for (int j = i; j < cpumoves.size(); j++)
		{
			if (i == j)
				continue;
			temp = abs(15 - magic[cpumoves[i]] - magic[cpumoves[j]]);
			if (temp <= 9 && temp >= 1 && board[rmagic[temp]] != 'O' && board[rmagic[temp]] != 'X')
			{
				return mark(rmagic[temp], 'O');
			}
		}
	}
	if (playermoves.size() == 2)
	{
		if (exists(0) && exists(7))
			return mark(6, 'O');
		if (exists(2) && exists(7))
			return mark(8, 'O');
		if (exists(6) && exists(2))
			return mark(0, 'O');
		if (exists(8) && exists(2))
			return mark(9, 'O');

		if (exists(0) && exists(8))
			return mark(5, 'O');
		if (exists(2) && exists(7))
			return mark(3, 'O');

	}

	for (int i = 0; i < playermoves.size(); i++)
	{
		for (int j = i; j < playermoves.size(); j++)
		{
			if (i == j)
				continue;
			temp = abs(15 - magic[playermoves[i]] - magic[playermoves[j]]);
			if (temp <= 9 && temp >= 1 && board[rmagic[temp]] != 'O' && board[rmagic[temp]] != 'X')
			{
				return mark(rmagic[temp], 'O');
			}
		}
	}
	playbest();
}

int main()
{
	char ch;
	cout << "[P]layer or [C]omputer first?";
	cin >> ch;
	cout << "Player is X, Computer is O" << endl;
	if (ch == 'P' || ch == 'p')
	{
		playuser();
	}
	else
	{
		playbest();
		playuser();
	}
	playbest();
	while (true)
	{
		if (checkwin())
			return 0;
		playuser();
		if (checkwin())
			return 0;
		playmagic();
	}
}