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
#define K_UP 72
#define K_DOWN 80
#define K_LEFT 75
#define K_RIGHT 77
#define ENTER 13
#define BACKSPACE 8
#define ESC 27
using namespace std;
class name
{
	char a[nam];
	int SNo;
public:
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
void output_matrix(char a[m][n])
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			cout << a[i][j];
		cout << endl;
	}
}
void gotoxy(int y, int x)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void assign(life &l)
{
	char a[m][n];
	int i = 1, j = 1, c, d;
Change:
	l.output(a);
	gotoxy(0, 0);
	output_matrix(a);
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
	d = _getch();
	if (d == K_UP)
	{
		i--;
		gotoxy(i, j);
	}
	if (d == K_DOWN)
	{
		i++;
		gotoxy(i, j);
	}
	if (d == K_RIGHT)
	{
		j++;
		gotoxy(i, j);
	}
	if (d == K_LEFT)
	{
		j--;
		gotoxy(i, j);
	}
	goto Assign;
}
void input(life &l, name &na)
{
	char b[50];
	cin.ignore();
	cout << "Enter name" << endl;
	cin.getline(b, 50);
	na.setname(b);
	assign(l);
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
int main()
{
	int U_Sno = 0;
	//set_Universal_Sno(U_Sno);
	//int U_Sno = get_Universal_Sno();
	char ch, ar[m][n];
	life l;
X:
	system("cls");
	cout << U_Sno << endl;
	cout << "1. Write\n2. Read\n3. Update\n4. Delete\n5. Play\n6. Exit" << endl;
	cin >> ch;
	if (ch == '1')
	{
		life lw;
		name na;
		input(lw, na);
		U_Sno++;
		lw.setsno(U_Sno);
		na.setsno(U_Sno);
		write(U_Sno, lw, na);
		set_Universal_Sno(U_Sno);
	}
	if (ch == '2')
	{
		name na;
		int r;
		cout << "Roll" << endl;
		cin >> r;
		l = readg(r);
		na = readn(r);
		l.output(ar);
		cout << "Name : " << na.getname() << endl
			<< "NA_Sno : " << na.getsno() << endl
			<< "L_Sno : " << l.getsno() << endl
			<< "OUtput : " << endl;
		output_matrix(ar);
		_getch();
	}
	if (ch == '3')
	{
		life lu;
		name na;
		int r;
		cout << "Roll" << endl;
		cin >> r;
		lu = readg(r);
		na = readn(r);
		input(lu, na);
		write(r, lu, na);
	}
	if (ch == '4')
	{
		int r;
		cout << "Roll" << endl;
		cin >> r;
		remove(r);
		if (U_Sno > 0)
			U_Sno--;
		set_Universal_Sno(U_Sno);
	}
	if (ch == '5')
	{
		int gene, time;
		output_matrix(ar);
		_getch();
		cout << "Genration" << endl;
		cin >> gene;
		cout << "Time" << endl;
		cin >> time;
		for (int  k= 0; k < gene; k++)
		{
			for (int i = 1; i < m - 1; i++)
			{
				for (int j = 1; j < n - 1; j++)
				{
					if (l.getchar(i, j) == ' ')
					{
						if (neighbour(ar, i, j) == 3)
							l.assign(i, j, '*');
					}
					else
					{
						if (neighbour(ar, i, j) <= 1 || neighbour(ar, i, j) >= 4)
							l.assign(i, j, ' ');
					}
				}
			}
			output_matrix(ar);
			l.output(ar);
			Sleep(time);
		}
	}
	if (ch == '6')
	{
		goto E;
	}
	goto X;
E:
	//life l;
	//assign(l);
	return 0;
}