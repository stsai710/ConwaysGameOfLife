#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string>
#include<Windows.h>
#include<iomanip>
#define m 10
#define n 10
#define nam 100
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define PAUSE 0x50
#define START 115
#define ENTER 13
#define BACKSPACE 8
#define ESC 27
#define TAB 9
#define S_INC 43
#define S_DEC 45
using namespace std;
class name
{
	char a[nam];
	int SNo;
public:
	name()
	{
		strcpy_s(a, "New Game");
		SNo = 0;
	}
	void setname(char b[])
	{
		strcpy_s(a, b);
	}
	void setsno(int a)
	{
		SNo = a;
	}
	int getsno()
	{
		return SNo;
	}
	char* getname()
	{
		return a;
	}
};
class life
{
	char a[m][n];
	int SNo;
public:
	life()
	{
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				a[i][j] = char(65 + i);
		SNo = 0;
	}
	void assign(int i, int j, char c)
	{
		a[i][j] = c;
	}
	void output(char b[m][n])
	{
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				b[i][j] = a[i][j];
	}
	int getsno()
	{
		return SNo;
	}
	void setsno(int a)
	{
		SNo = a;
	}
	char getchar(int i, int j)
	{
		return a[i][j];
	}
};
void write(int r, life l, name na)
{
	fstream fout("gol.dat", ios::in | ios::out | ios::binary);
	fout.seekp((r - 1) * sizeof(l));
	fout.write((char*)&l, sizeof(l));
	fout.close();
	fstream foutn("golname.dat", ios::in | ios::out | ios::binary);
	foutn.seekp((r - 1) * sizeof(na));
	foutn.write((char*)&na, sizeof(na));
	foutn.close();
}
life readg(int r)
{
	life l;
	fstream fin("gol.dat", ios::in | ios::binary);
	fin.seekg((r - 1) * sizeof(l));
	fin.read((char*)&l, sizeof(l));
	fin.close();
	return l;
}
name readn(int r)
{
	name na;
	fstream fin("golname.dat", ios::in | ios::binary);
	fin.seekg((r - 1) * sizeof(na));
	fin.read((char*)&na, sizeof(na));
	fin.close();
	return na;
}
void remove(int r)
{
	fstream fin("gol.dat", ios::in | ios::binary);
	fstream fout("gol1.dat", ios::out | ios::binary | ios::trunc);
	life l;
	fin.read((char*)&l, sizeof(l));
	while (!fin.eof())
	{
		if (l.getsno() > r)
		{
			l.setsno(l.getsno() - 1);
			fout.write((char*)&l, sizeof(l));
		}
		if (l.getsno() < r)
			fout.write((char*)&l, sizeof(l));
		fin.read((char*)&l, sizeof(l));
	}
	fin.close();
	fout.close();
	remove("gol.dat");
	rename("gol1.dat", "gol.dat");
	fstream fin_name("golname.dat", ios::in | ios::binary);
	fstream fout_name("gol1name.dat", ios::out | ios::binary | ios::trunc);
	name na;
	fin_name.read((char*)&na, sizeof(na));
	while (!fin_name.eof())
	{
		if (na.getsno() > r)
		{
			na.setsno(na.getsno() - 1);
			fout_name.write((char*)&na, sizeof(na));
		}
		if (na.getsno() < r)
			fout_name.write((char*)&na, sizeof(na));
		fin_name.read((char*)&na, sizeof(na));
	}
	fin_name.close();
	fout_name.close();
	remove("golname.dat");
	rename("gol1name.dat", "golname.dat");
}
int get_Universal_Sno()
{
	int a;
	fstream fin("universalsno.dat", ios::in | ios::binary);
	fin.read((char*)&a, sizeof(a));
	fin.close();
	return a;

}
void set_Universal_Sno(int a)
{
	fstream fout("universalsno.dat", ios::out | ios::binary | ios::trunc);
	fout.write((char*)&a, sizeof(a));
	fout.close();
}
int U_Sno = get_Universal_Sno();
void output_matrix(char a[m][n], int speed)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			cout << a[i][j];
		cout << endl;
	}
	cout << endl;
	cout << "Speed" << speed << endl;
}
void gotoxy(int y, int x)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void clearbuffer()
{
	while (_kbhit())
		_getch();
}
int neighbour(char a[m][n], int x, int y)
{
	int c = 0;
	if (a[x - 1][y - 1] == '*')
		c++;
	if (a[x - 1][y] == '*')
		c++;
	if (a[x - 1][y + 1] == '*')
		c++;
	if (a[x][y - 1] == '*')
		c++;
	if (a[x][y + 1] == '*')
		c++;
	if (a[x + 1][y - 1] == '*')
		c++;
	if (a[x + 1][y] == '*')
		c++;
	if (a[x + 1][y + 1] == '*')
		c++;
	return c;
}
void board(life &l)
{
	system("cls");
	char a[m][n], ch;
	int speed = 100, i = 1, j = 1, c, d;
	name na;
Pause:
	{
	Change:
		system("cls");
		l.output(a);
		output_matrix(a, speed);
		gotoxy(i, j);
	Assign:
		c = _getch();
		if (c == ENTER)
		{
			l.assign(i, j, '*');
			goto Change;
		}
		if (c == BACKSPACE)
		{
			l.assign(i, j, ' ');
			goto Change;
		}
		if (c == ESC)
		{
			return;
		}
		if (c == TAB)
		{
		C:
			system("cls");
			cout << "1. New File\n2. Existing File" << endl;
			cin >> ch;
			if (ch == '1')
			{
				char b[nam];
				cin.ignore();
				cout << "Enter Name" << endl;
				cin.getline(b, nam);
				na.setname(b);
				U_Sno++;
				l.setsno(U_Sno);
				na.setsno(U_Sno);
				write(U_Sno, l, na);
				set_Universal_Sno(U_Sno);
				goto Pause;
			}
			if (ch == '2')
			{
				int r;
				cout << "Enter Roll" << endl;
				cin >> r;
				na = readn(r);
				write(r, l, na);
				goto Pause;
			}
			goto C;
		}
		if (c == START)
		{
			goto Start;
		}
		if (c == S_INC)
		{
			speed++;
			goto Change;
		}
		if (c == S_DEC)
		{
			speed--;
			goto Change;
		}
		d = _getch();
		if (d == UP)
		{
			i--;
			gotoxy(i, j);
		}
		if (d == DOWN)
		{
			i++;
			gotoxy(i, j);
		}
		if (d == RIGHT)
		{
			j++;
			gotoxy(i, j);
		}
		if (d == LEFT)
		{
			j--;
			gotoxy(i, j);
		}
		goto Assign; 
	}
Start:
	{
		while (!GetAsyncKeyState(PAUSE))
		{
			for (int i = 1; i < m - 1; i++)
			{
				for (int j = 1; j < n - 1; j++)
				{
					if (l.getchar(i, j) == ' ')
					{
						if (neighbour(a, i, j) == 3)
							l.assign(i, j, '*');
					}
					else
					{
						if (neighbour(a, i, j) <= 1 || neighbour(a, i, j) >= 4)
							l.assign(i, j, ' ');
					}
				}
			}
			system("cls");
			output_matrix(a, speed);
			l.output(a);
			Sleep(speed);
			if (GetAsyncKeyState(VK_ADD))
				speed++;
			if (GetAsyncKeyState(VK_SUBTRACT))
				speed--;
			if (GetAsyncKeyState(VK_ESCAPE))
				return;
		}
		clearbuffer();
		goto Pause;
	}
}
int main()
{
	//int U_Sno = 0;
	//set_Universal_Sno(U_Sno);
	char ch;
X:
	system("cls");
	cout << U_Sno << endl;
	cout << "1. New Matrix\n2. Load Matrix\n3. Content Manager\n4. Help\n5. Exit" << endl;
	cin >> ch;
	if (ch == '1')
	{
		system("cls");
		life ln;
		board(ln);
	}
	if (ch == '2')
	{
		system("cls");
		life ll;
		name na;
		int r;
		cout << "SNo\tName" << endl;
		for (int i = 1; i <= U_Sno; i++)
		{
			na = readn(i);
			cout << na.getsno() << '\t' << na.getname() << endl;
		}
		cout << "Roll" << endl;
		cin >> r;
		ll = readg(r);
		board(ll);
	}
	if (ch == '3')
	{
	CM:
		char k;
		cout << "1. Saved Games\n2. Border\n3. Color\n4. Default Speed\n5. Previous Menu" << endl;
		cin>>k;
		if (k == '1')
		{
			life l;
			name na;
			int r;
			char ck, b[nam];
			if (U_Sno > 0)
			{
				cout << "SNo\tName" << endl;
				for (int i = 1; i <= U_Sno; i++)
				{
					na = readn(i);
					cout << na.getsno() << '\t' << na.getname() << endl;
				}
				cout << "Roll" << endl;
				cin >> r;
				if (r <= U_Sno)
				{
					l = readg(r);
					na = readn(r);
					cout << "Name : " << na.getname() << endl
						<< "NA_Sno : " << na.getsno() << endl
						<< "L_Sno : " << l.getsno() << endl
						<< "OUtput : " << endl;
					for (int i = 0; i < m; i++)
					{
						for (int j = 0; j < n; j++)
							cout << l.getchar(i, j);
						cout << endl;
					}
				K:
					cout << "1. Delete\n2. Rename\n3. Previous Menu" << endl;
					cin >> ck;
					if (ck == '1')
					{
						remove(r);
						if (U_Sno > 0)
							U_Sno--;
						set_Universal_Sno(U_Sno);
						cout << "Deleted" << endl;
						goto CM;
					}
					if (ck == '2')
					{
						cin.ignore();
						cout << "Enter New Name" << endl;
						cin.getline(b, nam);
						na.setname(b);
						write(r, l, na);
						goto CM;
					}
					if (ck == '3')
					{
						goto CM;
					}
					goto K;
				}
			}
			else
				cout << "No Saved Games" << endl;
		}
		if (k == '5')
		{
			goto X;
		}
		goto CM;
	}
	if (ch == '4')
	{
		
	}
	if (ch == '5')
	{
		goto E;
	}
	goto X;
E:
	return 0;
}