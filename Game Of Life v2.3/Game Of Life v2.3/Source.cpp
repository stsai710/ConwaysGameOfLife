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
string select(string s)
{
	string s1;
	s1 = "->" + s + "<-";
	return s1;
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
	char a[m][n];
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
			clearbuffer();
			return;
		}
		if (c == TAB)
		{
			int y, yc, yd;
			system("cls");
			string s[] = { "New File","Existing File" };
			y = 0;
			system("cls");
			for (int i = 0; i < 2; i++)
			{
				if (i != y)
					cout << s[i] << endl;
				else
					cout << select(s[y]) << endl;
			}
		C:
			yc = _getch();
			if (yc == ENTER)
			{
				if (y == 0)
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
				if (y == 1)
				{
					int r;
					cout << "Enter Roll" << endl;
					cin >> r;
					na = readn(r);
					write(r, l, na);
					goto Pause;
				}
			}
			yd = _getch();
			if (yd == UP)
			{
				if (y != 0)
				{
					y--;
					y = y % 2;
				}
				else
				{
					y = 1;
				}
				system("cls");
				for (int i = 0; i < 2; i++)
				{
					if (i != y)
						cout << s[i] << endl;
					else
						cout << select(s[y]) << endl;

				}
			}
			if (yd == DOWN)
			{
				y++;
				y = y % 2;
				system("cls");
				for (int i = 0; i < 2; i++)
				{
					if (i != y)
						cout << s[i] << endl;
					else
						cout << select(s[y]) << endl;

				}
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
			{
				clearbuffer();
				return;
			}
		}
		clearbuffer();
		goto Pause;
	}
}
int main()
{
	//int U_Sno = 0;
	//set_Universal_Sno(U_Sno);
	int ch, p, c, d;
	cout << U_Sno << endl;
	string ar[] = { "New Matrix","Load Matrix","Content Manager","Help","Exit" };
Menu:
	p = 0;
	system("cls");
	for (int i = 0; i < 5; i++)
	{
		if (i != p)
			cout << ar[i] << endl;
		else
			cout << select(ar[p]) << endl;
	}
X:
	c = _getch();
	if (c == ENTER)
	{
		system("cls");
		if (p == 0)
		{
			system("cls");
			life ln;
			board(ln);
		}
		if (p == 1)
		{
			life ll;
			name na;
			string s[20];
			int rc, rd;
			for (int i = 1; i <= U_Sno; i++)
			{
				na = readn(i);
				s[i - 1] = na.getname();
			}
			if (U_Sno == 0)
			{
				cout << "No saved files" << endl;
				_getch();
				goto Menu;
			}
		Load:
			int r = 0;
			cout << "Name" << endl;
			for (int i = 0; i < U_Sno; i++)
			{
				na = readn(i + 1);
				if (i != r)
					cout << s[i] << endl;
				else
					cout << "->" << s[r] << "<-" << endl;
			}
		Load_X:
			rc = _getch();
			if (rc == ENTER)
			{
				ll = readg(r + 1);
				board(ll);
				goto Menu;
			}
			rd = _getch();
			if (rd == UP)
			{
				if (r != 0)
				{
					r--;
					r = r % U_Sno;
				}
				else
				{
					r = U_Sno - 1;
				}
				system("cls");
				cout << "Name" << endl;
				for (int i = 0; i < U_Sno; i++)
				{
					if (i != r)
						cout << s[i] << endl;
					else
						cout << select(s[r]) << endl;

				}
			}
			if (rd == DOWN)
			{
				r++;
				r = r % U_Sno;
				system("cls");
				cout << "Name" << endl;
				for (int i = 0; i < U_Sno; i++)
				{
					if (i != r)
						cout << s[i] << endl;
					else
						cout << select(s[r]) << endl;

				}
			}
			goto Load_X;
		}
		if (p == 2)
		{
			string s[5] = { "Saved Games","Border","Color","Default Speed","Previous Menu" };
			int kc, kd;
		CM:
			system("cls");
			int k = 0;
			for (int i = 0; i < 5; i++)
			{
				if (i != k)
					cout << s[i] << endl;
				else
					cout << select(s[k]) << endl;
			}
		CM_X:
			kc = _getch();
			if (kc == ENTER)
			{
				if (k == 0)
				{
					life l;
					name na;
					int r;
					char b[nam];
					int z, zc, zd;
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
							system("cls");
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
							_getch();
							clearbuffer();
							string s[3] = { "Delete","Rename","Previous Menu" };
						K:
							z = 0;
							system("cls");
							for (int i = 0; i < 3; i++)
							{
								if (i != z)
									cout << s[i] << endl;
								else
									cout << select(s[z]) << endl;
							}
							
						K_X:
							zc = _getch();
							if (zc == ENTER)
							{
								if (z == 0)
								{
									system("cls");
									remove(r);
									if (U_Sno > 0)
										U_Sno--;
									set_Universal_Sno(U_Sno);
									cout << "Deleted" << endl;
									_getch();
									goto CM;
								}
								if (z == 1)
								{
									system("cls");
									cin.ignore();
									cout << "Enter New Name" << endl;
									cin.getline(b, nam);
									na.setname(b);
									write(r, l, na);
									goto CM;
								}
								if (z == 2)
								{
									goto CM;
								}
								goto K;
							}
							zd = _getch();
							if (zd == UP)
							{
								if (z != 0)
								{
									z--;
									z = z % 3;
								}
								else
								{
									z = 2;
								}
								system("cls");
								for (int i = 0; i < 3; i++)
								{
									if (i != z)
										cout << s[i] << endl;
									else
										cout << select(s[z]) << endl;
								}
							}
							if (zd == DOWN)
							{
								z++;
								z = z % 3;
								system("cls");
								for (int i = 0; i < 3; i++)
								{
									if (i != z)
										cout << s[i] << endl;
									else
										cout << select(s[z]) << endl;

								}
							}
							goto K_X;
						}
					}
					else
					{
						system("cls");
						cout << "No Saved Games" << endl;
						_getch();
						goto CM;
					}
				}
				if (k == 4)
				{
					goto Menu;
				}
				goto CM;
			}
			kd = _getch();
			if (kd == UP)
			{
				if (k != 0)
				{
					k--;
					k = k % 5;
				}
				else
				{
					k = 4;
				}
				system("cls");
				for (int i = 0; i < 5; i++)
				{
					if (i != k)
						cout << s[i] << endl;
					else
						cout << select(s[k]) << endl;

				}
			}
			if (kd == DOWN)
			{
				k++;
				k = k % 5;
				system("cls");
				for (int i = 0; i < 5; i++)
				{
					if (i != k)
						cout << s[i] << endl;
					else
						cout << select(s[k]) << endl;

				}
			}
			goto CM_X;
		}
		if (p == 3)
		{

		}
		if (p == 4)
		{
			goto E;
		}
		goto Menu;
	}
	d = _getch();
	if (d == UP)
	{
		if (p != 0)
		{
			p--;
			p = p % 5;
		}
		else
		{
			p = 4;
		}
		system("cls");
		for (int i = 0; i < 5; i++)
		{
			if (i != p)
				cout << ar[i] << endl;
			else
				cout << select(ar[p]) << endl;

		}
	}
	if (d == DOWN)
	{
		p++;
		p = p % 5;
		system("cls");
		for (int i = 0; i < 5; i++)
		{
			if (i != p)
				cout << ar[i] << endl;
			else
				cout << select(ar[p]) << endl;

		}
	}
	goto X;
E:
	return 0;
}
