#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string>
#include<Windows.h>                               //Target was NOT to use <graphics.h>
#include<time.h>

#define HEIGHT 41
#define WIDTH 157
#define M HEIGHT
#define N 2 * ( WIDTH / 3 )
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

#define BLUE 0x01
#define GREEN 0x02
#define AQUA 0x03
#define RED 0x04
#define PURPLE 0x05
#define YELLOW 0x06
#define WHITE 0x07
#define GRAY 0x08
#define LIGHT_BLUE 0x09
#define LIGHT_GREEN 0x0A
#define LIGHT_AQUA 0x0B
#define LIGHT_RED 0x0C
#define LIGHT_PURPLE 0x0D
#define LIGHT_YELLOW 0x0E
#define LIGHT_WHITE 0x0F

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
	char a[M][N];
	int SNo;
public:
	life()
	{
		for (int i = 0;i < M;i++)
			for (int j = 0;j < N;j++)
				a[i][j] = ' ';
		SNo = 0;
	}
	void assign(int i, int j, char c)
	{
		a[i][j] = c;
	}
	void output(char b[M][N])
	{
		for (int i = 0;i < M;i++)
			for (int j = 0;j < N;j++)
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

//  Data File Handling Starts Here

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


int get_Universal_color()
{
	int a;
	fstream fin("universalcolor.dat", ios::in | ios::binary);
	fin.read((char*)&a, sizeof(a));
	fin.close();
	return a;
}
void set_Universal_color(int a)
{
	fstream fout("universalcolor.dat", ios::out | ios::binary | ios::trunc);
	fout.write((char*)&a, sizeof(a));
	fout.close();
}


int get_Universal_speed()
{
	int a;
	fstream fin("universalspeed.dat", ios::in | ios::binary);
	fin.read((char*)&a, sizeof(a));
	fin.close();
	return a;
}
void set_Universal_speed(int a)
{
	fstream fout("universalspeed.dat", ios::out | ios::binary | ios::trunc);
	fout.write((char*)&a, sizeof(a));
	fout.close();
}


bool get_Universal_random()
{
	bool a;
	fstream fin("universalrandom.dat", ios::in | ios::binary);
	fin.read((char*)&a, sizeof(a));
	fin.close();
	return a;
}
void set_Universal_random(bool a)
{
	fstream fout("universalrandom.dat", ios::out | ios::binary | ios::trunc);
	fout.write((char*)&a, sizeof(a));
	fout.close();
}


bool random = get_Universal_random();
int U_Sno = get_Universal_Sno();
int color = get_Universal_color();
int speed = get_Universal_speed();

string colorset(int x)
{
	if (x == BLUE)
		return "Blue";
	if (x == GREEN)
		return "Green";
	if (x == AQUA)
		return "Aqua";
	if (x == RED)
		return "Red";
	if (x == PURPLE)
		return "Purple";
	if (x == YELLOW)
		return "Yellow";
	if (x == WHITE)
		return "White";
	if (x == GRAY)
		return "Grey";
	if (x == LIGHT_BLUE)
		return "Light Blue";
	if (x == LIGHT_GREEN)
		return "Light Green";
	if (x == LIGHT_AQUA)
		return "Light Aqua";
	if (x == LIGHT_RED)
		return "Light Red";
	if (x == LIGHT_PURPLE)
		return "Light Purple";
	if (x == LIGHT_YELLOW)
		return "Light Yellow";
	if (x == LIGHT_WHITE)
		return "Light White";
}

string color_str = colorset(color);


void gotoxy(int y, int x)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void textcolor(int k)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), k);
}

void clearbuffer()
{
	while (_kbhit())
		_getch();
}

void main_border()
{
	gotoxy(0, 0);
	for (int i = 0; i < WIDTH; i++)
	{
		if (i % 6 == 0)
			textcolor(LIGHT_AQUA);
		else if (i % 6 == 1)
			textcolor(LIGHT_AQUA);
		else if (i % 6 == 2)
			textcolor(LIGHT_GREEN);
		else if (i % 6 == 3)
			textcolor(LIGHT_GREEN);
		else if (i % 6 == 4)
			textcolor(LIGHT_YELLOW);
		else
			textcolor(LIGHT_YELLOW);
		cout << "*";
	}
	for (int i = 1; i < HEIGHT - 1; i++)
	{
		if (i % 2)
			textcolor(LIGHT_RED);
		else
			textcolor(LIGHT_PURPLE);
		gotoxy(i, 0);
		cout << "*";
		gotoxy(i, WIDTH - 1);
		cout << "*";
	}
	textcolor(WHITE);
	gotoxy(HEIGHT - 1, 0);
	for (int i = 0; i < WIDTH; i++)
	{
		if (i % 6 == 0)
			textcolor(LIGHT_AQUA);
		else if (i % 6 == 1)
			textcolor(LIGHT_AQUA);
		else if (i % 6 == 2)
			textcolor(LIGHT_GREEN);
		else if (i % 6 == 3)
			textcolor(LIGHT_GREEN);
		else if (i % 6 == 4)
			textcolor(LIGHT_YELLOW);
		else
			textcolor(LIGHT_YELLOW);
		cout << "*";
	}
}

void clear_area(int x1, int y1, int x2, int y2)
{
	for (int i = x1; i <= x2; i++)
		for (int j = y1; j <= y2; j++)
		{
			gotoxy(i, j);
			cout << " ";
		}
}

string select(string s)
{
	string s1;
	s1 = "->" + s + "<-";
	return s1;
}

int neighbour(char a[M][N], int x, int y)
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
	char a[M][N];
	int i = 1, j = 1, c, d, g = 0;
	name na;
Board:
	clearbuffer();
	system("cls");
	textcolor(WHITE);
	main_border();
	for (int i = 1;i < HEIGHT - 1;i++)
	{
		if (i % 2)
			textcolor(LIGHT_AQUA);
		else
			textcolor(BLUE);
		gotoxy(i, 2 * (WIDTH / 3));
		cout << "#";
	}
Pause:
	{
		textcolor(LIGHT_AQUA);
		gotoxy(HEIGHT / 2 - 6, 2 * (WIDTH / 3) + 1);
		cout << " Use arrow keys to move the pointer               ";
		textcolor(LIGHT_GREEN);
		gotoxy(HEIGHT / 2 - 4, 2 * (WIDTH / 3) + 1);
		cout << " S            Start the game                      ";
		textcolor(LIGHT_YELLOW);
		gotoxy(HEIGHT / 2 - 2, 2 * (WIDTH / 3) + 1);
		cout << " Tab          Save the board                      ";
		textcolor(LIGHT_RED);
		gotoxy(HEIGHT / 2, 2 * (WIDTH / 3) + 1);
		cout << " Enter        Mark the box as alive               ";
		textcolor(LIGHT_PURPLE);
		gotoxy(HEIGHT / 2 + 2, 2 * (WIDTH / 3) + 1);
		cout << " BackSpace    Mark the box as dead                ";
		textcolor(LIGHT_BLUE);
		gotoxy(HEIGHT / 2 + 4, 2 * (WIDTH / 3) + 1);
		cout << " +/-          Increase and decrease the time delay";
		textcolor(GRAY);
		gotoxy(HEIGHT / 2 + 6, 2 * (WIDTH / 3) + 1);
		cout << " Esc          Exit the game                       ";
	Change:
		l.output(a);
		srand(time(0));
		textcolor(color);
		for (int i = 1; i < M - 1; i++)
		{
			for (int j = 1; j < N - 1; j++)
			{
				if (random)
					textcolor(rand() % 15 + 1);
				gotoxy(i, j);
				cout << a[i][j];
			}
			cout << endl;
		}
		textcolor(RED);
		gotoxy(HEIGHT / 2 + 14, 2 * (WIDTH / 3) + 1);
		cout << " Time Delay            : ";
		textcolor(AQUA);
		cout << speed << " ms    " << endl;
		gotoxy(i, j);
	Assign:
		c = _getch();
		if (c == ENTER || c == BACKSPACE || c == ESC || c == TAB || c == START || c == S_INC || c == S_DEC || c == 224)
		{
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
				system("cls");
				return;
			}
			if (c == TAB)
			{
				int y, yc, yd;
				string s[] = { "New File","Existing File" };
				y = 0;
				system("cls");
				textcolor(color);
				srand(time(0));
				for (int i = 1;i < M;i++)
				{
					for (int j = 1;j < N;j++)
					{
						if (random)
							textcolor(rand() % 15 + 1);
						gotoxy(i, j);
						cout << a[i][j];
					}
				}
				main_border();
				for (int i = 1;i < HEIGHT - 1;i++)
				{
					if (i % 2)
						textcolor(LIGHT_AQUA);
					else
						textcolor(BLUE);
					gotoxy(i, 2 * (WIDTH / 3));
					cout << "#";
				}
				textcolor(LIGHT_PURPLE);
				gotoxy(2, 5 * (WIDTH / 6) - 5);
				cout << "Save As...";
				gotoxy(4, 2 * (WIDTH / 3) + 1);
				for (int i = 0;i < WIDTH / 3 - 1;i++)
				{
					if (i % 4 == 0)
						textcolor(LIGHT_YELLOW);
					else if (i % 4 == 1)
						textcolor(LIGHT_YELLOW);
					else if (i % 4 == 2)
						textcolor(LIGHT_RED);
					else
						textcolor(LIGHT_RED);
					cout << "=";
				}
				for (int i = 0; i < 2; i++)
				{
					if (i != y)
					{
						gotoxy(6 + i, 5 * (WIDTH / 6) - s[i].size() / 2);
						textcolor(WHITE);
						cout << s[i] << endl;
					}
					else
					{
						gotoxy(6 + i, 5 * (WIDTH / 6) - select(s[i]).size() / 2);
						textcolor(color);
						cout << select(s[y]) << endl;
					}
				}
			C:
				gotoxy(HEIGHT - 1, WIDTH - 1);
				yc = _getch();
				if (yc == ENTER || yc == 224 || yc == ESC)
				{
					if (yc == ENTER)
					{
						if (y == 0)
						{
							char b[nam];
							clearbuffer();
							clear_area(6, 5 * (WIDTH / 6) - 17 / 2, 7, 5 * (WIDTH / 6) + 17 / 2);
							gotoxy(6, 2 * (WIDTH / 3) + 5);
							textcolor(LIGHT_AQUA);
							cout << "Enter Name";
							gotoxy(8, 2 * (WIDTH / 3) + 5);
							textcolor(WHITE);
							cin.getline(b, nam);
							if (cin.fail())
							{
								clearbuffer();
								cin.clear();
								cin.ignore(INT_MAX, '\n');
								goto Board;
							}
							na.setname(b);
							U_Sno++;
							l.setsno(U_Sno);
							na.setsno(U_Sno);
							write(U_Sno, l, na);
							set_Universal_Sno(U_Sno);
							goto Board;
						}
						if (y == 1)
						{
							string s[40];
							int sp = 0, spc, spd;
							for (int i = 1; i <= U_Sno; i++)
							{
								na = readn(i);
								s[i - 1] = na.getname();
							}
							if (U_Sno == 0)
							{
								textcolor(WHITE);
								gotoxy(6, 2 * (WIDTH / 3) + 5);
								cout << "No Saved Files                ";
								gotoxy(7, 2 * (WIDTH / 3) + 5);
								cout << "                              ";
								gotoxy(8, 2 * (WIDTH / 3) + 5);
								_getch();
								goto Board;
							}
							textcolor(LIGHT_AQUA);
							clear_area(6, 5 * (WIDTH / 6) - 17 / 2, 7, 5 * (WIDTH / 6) + 17 / 2);
							gotoxy(6, 2 * (WIDTH / 3) + 5);
							cout << "Name" << endl;
							for (int i = 0; i < U_Sno; i++)
							{
								if (i != sp)
								{
									gotoxy(8 + i, 2 * (WIDTH / 3) + 5);
									textcolor(WHITE);
									cout << s[i] << endl;
								}
								else
								{
									gotoxy(8 + i, 2 * (WIDTH / 3) + 3);
									textcolor(color);
									cout << select(s[i]) << endl;
								}
							}
						Save:
							gotoxy(HEIGHT - 1, WIDTH - 1);
							spc = _getch();
							if (spc == ENTER || spc == 224 || spc == ESC)
							{
								if (spc == ENTER)
								{
									na = readn(sp + 1);
									l.setsno(na.getsno());
									write(sp + 1, l, na);
									goto Board;
								}
								if (spc == ESC)
								{
									goto Board;
								}
								spd = _getch();
								if (spd == UP)
								{
									clear_area(8 + sp, 2 * (WIDTH / 3) + 1, 8 + sp, WIDTH - 2);
									if (sp != 0)
									{
										sp--;
									}
									else
									{
										sp = U_Sno - 1;
									}
									for (int i = 0; i < U_Sno; i++)
									{
										if (i != sp)
										{
											gotoxy(8 + i, 2 * (WIDTH / 3) + 5);
											textcolor(WHITE);
											cout << s[i] << endl;
										}
										else
										{
											gotoxy(8 + i, 2 * (WIDTH / 3) + 3);
											textcolor(color);
											cout << select(s[i]) << endl;
										}
									}
								}
								if (spd == DOWN)
								{
									clear_area(8 + sp, 2 * (WIDTH / 3) + 1, 8 + sp, WIDTH - 2);
									sp++;
									sp = sp % U_Sno;
									for (int i = 0; i < U_Sno; i++)
									{
										if (i != sp)
										{
											gotoxy(8 + i, 2 * (WIDTH / 3) + 5);
											textcolor(WHITE);
											cout << s[i] << endl;
										}
										else
										{
											gotoxy(8 + i, 2 * (WIDTH / 3) + 3);
											textcolor(color);
											cout << select(s[i]) << endl;
										}
									}
								}
							}
							goto Save;
						}
					}
					if (yc == ESC)
					{
						goto Board;
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
						clear_area(6, 5 * (WIDTH / 6) - 17 / 2, 7, 5 * (WIDTH / 6) + 17 / 2);
						for (int i = 0; i < 2; i++)
						{
							if (i != y)
							{
								gotoxy(6 + i, 5 * (WIDTH / 6) - s[i].size() / 2);
								textcolor(WHITE);
								cout << s[i] << endl;
							}
							else
							{
								gotoxy(6 + i, 5 * (WIDTH / 6) - select(s[i]).size() / 2);
								textcolor(color);
								cout << select(s[y]) << endl;
							}
						}

					}
					if (yd == DOWN)
					{
						y++;
						y = y % 2;
						clear_area(6, 5 * (WIDTH / 6) - 17 / 2, 7, 5 * (WIDTH / 6) + 17 / 2);
						for (int i = 0; i < 2; i++)
						{
							if (i != y)
							{
								gotoxy(6 + i, 5 * (WIDTH / 6) - s[i].size() / 2);
								textcolor(WHITE);
								cout << s[i] << endl;
							}
							else
							{
								gotoxy(6 + i, 5 * (WIDTH / 6) - select(s[i]).size() / 2);
								textcolor(color);
								cout << select(s[y]) << endl;
							}
						}
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
				if (speed > 0)
					speed--;
				goto Change;
			}
			d = _getch();
			if (d == UP && i > 1)
			{
				i--;
				gotoxy(i, j);
			}
			if (d == DOWN && i < M - 2)
			{
				i++;
				gotoxy(i, j);
			}
			if (d == RIGHT && j < N - 2)
			{
				j++;
				gotoxy(i, j);
			}
			if (d == LEFT && j > 1)
			{
				j--;
				gotoxy(i, j);
			}
		}
		goto Assign;
	}
Start:
	{
		gotoxy(HEIGHT / 2 - 6, 2 * (WIDTH / 3) + 1);
		cout << "                                                  ";
		gotoxy(HEIGHT / 2 - 4, 2 * (WIDTH / 3) + 1);
		cout << "                                                  ";
		textcolor(LIGHT_AQUA);
		gotoxy(HEIGHT / 2 - 2, 2 * (WIDTH / 3) + 1);
		cout << " P            Pause the game                      ";
		textcolor(LIGHT_GREEN);
		gotoxy(HEIGHT / 2, 2 * (WIDTH / 3) + 1);
		cout << " +/-          Increase and decrease the time delay";
		textcolor(LIGHT_YELLOW);
		gotoxy(HEIGHT / 2 + 2, 2 * (WIDTH / 3) + 1);
		cout << " Esc          Exit the game                       ";
		gotoxy(HEIGHT / 2 + 4, 2 * (WIDTH / 3) + 1);
		cout << "                                                  ";
		gotoxy(HEIGHT / 2 + 6, 2 * (WIDTH / 3) + 1);
		cout << "                                                  ";
		textcolor(PURPLE);
		gotoxy(HEIGHT / 2 + 10, 2 * (WIDTH / 3) + 1);
		cout << " No. of generations    : " << g;
		srand(time(0));
		while (!GetAsyncKeyState(PAUSE))              //There is a bug here
		{
			textcolor(color);
			for (int i = 1; i < M - 1; i++)
			{
				for (int j = 1; j < N - 1; j++)
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
					if (random)
						textcolor(rand() % 15 + 1);
					gotoxy(i, j);
					cout << a[i][j];
				}
			}
			textcolor(RED);
			gotoxy(HEIGHT / 2 + 14, 2 * (WIDTH / 3) + 1);
			cout << " Time Delay            : ";
			textcolor(AQUA);
			cout << speed << " ms    " << endl;
			gotoxy(HEIGHT / 2 + 10, 2 * (WIDTH / 3) + 26);
			cout << g++;
			l.output(a);
			Sleep(speed);
			if (GetAsyncKeyState(VK_ADD))
				speed++;
			if (GetAsyncKeyState(VK_SUBTRACT))
			{
				if (speed > 0)
					speed--;
			}
			if (_kbhit() ? (int(_getch()) == ESC ? 1 : 0) : 0)
			{
				clearbuffer();
				return;
			}
		}
		clearbuffer();
		goto Pause;
	}
}

void loading()
{
	cout << "*";
	gotoxy(0, WIDTH - 1);
	cout << "*";
	gotoxy(HEIGHT - 1, 0);
	cout << "*";
	gotoxy(HEIGHT - 1, WIDTH - 1);
	cout << "*";
	gotoxy(HEIGHT / 2, (WIDTH - 25) / 2 + 1);
	cout << "Is the screen callibrated";
	gotoxy(HEIGHT / 2 + 1, WIDTH / 2 + 1);
	char enter;
	enter = _getch();
	if (enter == 'n')
		exit(0);
	system("cls");
	for (int i = 0; i < 5; i++)
	{
		gotoxy(HEIGHT / 2, (WIDTH - 11) / 2 + 1);
		cout << "Loading   " << "-";
		Sleep(50);
		gotoxy(HEIGHT / 2, (WIDTH - 11) / 2 + 1);
		cout << "Loading   " << "\\";
		Sleep(50);
		gotoxy(HEIGHT / 2, (WIDTH - 11) / 2 + 1);
		cout << "Loading   " << "|";
		Sleep(50);
		gotoxy(HEIGHT / 2, (WIDTH - 11) / 2 + 1);
		cout << "Loading   " << "/";
		Sleep(50);
	}
	gotoxy(0, 0);
	for (int i = 0;i < WIDTH;i++)
	{
		if (i % 6 == 0)
			textcolor(LIGHT_AQUA);
		else if (i % 6 == 1)
			textcolor(LIGHT_AQUA);
		else if (i % 6 == 2)
			textcolor(LIGHT_GREEN);
		else if (i % 6 == 3)
			textcolor(LIGHT_GREEN);
		else if (i % 6 == 4)
			textcolor(LIGHT_YELLOW);
		else
			textcolor(LIGHT_YELLOW);
		cout << "*";
		Sleep(10);
	}
	for (int i = 1;i < HEIGHT - 1;i++)
	{
		if (i % 2)
			textcolor(LIGHT_RED);
		else
			textcolor(LIGHT_PURPLE);
		gotoxy(i, WIDTH - 1);
		cout << "*";
		Sleep(10);
	}
	for (int i = WIDTH - 1;i >= 0;i--)
	{
		if (i % 6 == 0)
			textcolor(LIGHT_AQUA);
		else if (i % 6 == 1)
			textcolor(LIGHT_AQUA);
		else if (i % 6 == 2)
			textcolor(LIGHT_GREEN);
		else if (i % 6 == 3)
			textcolor(LIGHT_GREEN);
		else if (i % 6 == 4)
			textcolor(LIGHT_YELLOW);
		else
			textcolor(LIGHT_YELLOW);
		gotoxy(HEIGHT - 1, i);
		cout << "*";
		Sleep(10);
	}
	for (int i = HEIGHT - 2;i >= 1;i--)
	{
		if (i % 2)
			textcolor(LIGHT_RED);
		else
			textcolor(LIGHT_PURPLE);
		gotoxy(i, 0);
		cout << "*";
		Sleep(10);
	}
	textcolor(LIGHT_AQUA);
	clear_area(HEIGHT / 2, (WIDTH - 11) / 2 + 1, HEIGHT / 2, (WIDTH + 11) / 2);
	gotoxy(HEIGHT / 2, (WIDTH - 7) / 2 + 1);
	cout << "Welcome";
	Sleep(2000);
	textcolor(LIGHT_GREEN);
	clear_area(HEIGHT / 2, (WIDTH - 7) / 2 + 1, HEIGHT / 2, (WIDTH + 7) / 2);
	gotoxy(HEIGHT / 2, (WIDTH - 2) / 2 + 1);
	cout << "To";
	Sleep(2000);
	textcolor(LIGHT_YELLOW);
	clear_area(HEIGHT / 2, (WIDTH - 2) / 2 + 1, HEIGHT / 2, (WIDTH + 2) / 2);
	gotoxy(HEIGHT / 2, (WIDTH - 8) / 2 + 1);
	cout << "Conway's";
	Sleep(2000);
	textcolor(LIGHT_RED);
	clear_area(HEIGHT / 2, (WIDTH - 8) / 2 + 1, HEIGHT / 2, (WIDTH + 8) / 2);
	gotoxy(HEIGHT / 2, (WIDTH - 12) / 2 + 1);
	cout << "Game Of Life";
	Sleep(2000);
	clear_area(HEIGHT / 2, (WIDTH - 12) / 2 + 1, HEIGHT / 2, (WIDTH + 12) / 2);
	clearbuffer();
}

void help()
{
	system("cls");
	main_border();
	gotoxy(2, (WIDTH - 4) / 2);
	textcolor(LIGHT_GREEN);
	cout << "Help";
	int c;
	for (int i = 1;i < WIDTH - 1;i++)
	{
		if (i % 4 == 0)
			textcolor(LIGHT_YELLOW);
		else if (i % 4 == 1)
			textcolor(LIGHT_YELLOW);
		else if (i % 4 == 2)
			textcolor(LIGHT_RED);
		else
			textcolor(LIGHT_RED);
		gotoxy(4, i);
		cout << "=";
	}
	textcolor(LIGHT_AQUA);
	gotoxy(6, 5);
	cout << "Conway's Game Of Life was created by John Horton Conway (mathematician) in 1970.";
	gotoxy(8, 5);
	cout << "The \"game\" is a zero-player game, meaning that its evolution is determined by its initial state, requiring no further input.";
	gotoxy(10, 5);
	cout << "One interacts with the Game of Life by creating an initial configuration and observing how it evolves.";
	gotoxy(12, 5);
	cout << "This game has a Two-Dimensional grid.";
	gotoxy(14, 5);
	cout << "Each block or cell of the grid can be in either alive \" * \" or dead \"   \".";
	gotoxy(16, 5);
	cout << "Cells adjacent to a particular cell are called its neighbours.";
	textcolor(LIGHT_PURPLE);
	gotoxy(18, WIDTH / 3);
	cout << "-------------";
	gotoxy(19, WIDTH / 3);
	cout << "| 1 | 2 | 3 |";
	gotoxy(20, WIDTH / 3);
	cout << "-------------";
	gotoxy(21, WIDTH / 3);
	cout << "| 4 | * | 5 |";
	gotoxy(22, WIDTH / 3);
	cout << "-------------";
	gotoxy(23, WIDTH / 3);
	cout << "| 6 | 7 | 8 |";
	gotoxy(24, WIDTH / 3);
	cout << "-------------";
	textcolor(LIGHT_AQUA);
	gotoxy(21, WIDTH / 3 + 30);
	cout << "Each cell has 8 neighbours.";
	gotoxy(30, (WIDTH - 11) / 2);
	cout << "Rules : - > ";
	gotoxy(31, WIDTH / 2);
	c = _getch();
	if (c == ESC)
		return;
	clearbuffer();


	system("cls");
	main_border();
	gotoxy(2, (WIDTH - 4) / 2);
	for (int i = 1;i < WIDTH - 1;i++)
	{
		if (i % 4 == 0)
			textcolor(LIGHT_YELLOW);
		else if (i % 4 == 1)
			textcolor(LIGHT_YELLOW);
		else if (i % 4 == 2)
			textcolor(LIGHT_RED);
		else
			textcolor(LIGHT_RED);
		gotoxy(4, i);
		cout << "=";
	}
	gotoxy(2, (WIDTH - 11) / 2);
	textcolor(LIGHT_GREEN);
	cout << "-> Rules <-";
	gotoxy(14, (WIDTH - 89) / 2);
	cout << "Any live cell with fewer than two live neighbours dies, as if caused by underpopulation.";
	gotoxy(18, (WIDTH - 48) / 2);
	textcolor(LIGHT_PURPLE);
	cout << "-------------                     -------------";
	gotoxy(19, (WIDTH - 48) / 2);
	cout << "|   |   |   |                     |   |   |   |";
	gotoxy(20, (WIDTH - 48) / 2);
	cout << "-------------                     -------------";
	gotoxy(21, (WIDTH - 48) / 2);
	cout << "|   | * |   |         -->>        |   |   |   |";
	gotoxy(22, (WIDTH - 48) / 2);
	cout << "-------------                     -------------";
	gotoxy(23, (WIDTH - 48) / 2);
	cout << "| * |   |   |                     | * |   |   |";
	gotoxy(24, (WIDTH - 48) / 2);
	cout << "-------------                     -------------";
	gotoxy(28, (WIDTH - 63) / 2);
	textcolor(LIGHT_AQUA);
	cout << "Cell will die in next generation as it has only one neighbour.";
	gotoxy(32, (WIDTH - 11) / 2);
	cout << "Rules : - > ";
	gotoxy(33, WIDTH / 2);
	c = _getch();
	if (c == ESC)
		return;
	clearbuffer();


	system("cls");
	main_border();
	gotoxy(2, (WIDTH - 4) / 2);
	for (int i = 1;i < WIDTH - 1;i++)
	{
		if (i % 4 == 0)
			textcolor(LIGHT_YELLOW);
		else if (i % 4 == 1)
			textcolor(LIGHT_YELLOW);
		else if (i % 4 == 2)
			textcolor(LIGHT_RED);
		else
			textcolor(LIGHT_RED);
		gotoxy(4, i);
		cout << "=";
	}
	gotoxy(2, (WIDTH - 11) / 2);
	textcolor(LIGHT_GREEN);
	cout << "-> Rules <-";
	gotoxy(14, (WIDTH - 81) / 2);
	cout << "Any live cell with two or three live neighbours lives on to the next generation.";
	gotoxy(18, (WIDTH - 48) / 2);
	textcolor(LIGHT_PURPLE);
	cout << "-------------                     -------------";
	gotoxy(19, (WIDTH - 48) / 2);
	cout << "|   |   |   |                     |   |   |   |";
	gotoxy(20, (WIDTH - 48) / 2);
	cout << "-------------                     -------------";
	gotoxy(21, (WIDTH - 48) / 2);
	cout << "|   | * |   |         -->>        |   | * |   |";
	gotoxy(22, (WIDTH - 48) / 2);
	cout << "-------------                     -------------";
	gotoxy(23, (WIDTH - 48) / 2);
	cout << "| * | * |   |                     | * | * |   |";
	gotoxy(24, (WIDTH - 48) / 2);
	cout << "-------------                     -------------";
	gotoxy(28, (WIDTH - 60) / 2);
	textcolor(LIGHT_AQUA);
	cout << "Cell will live in next generation as it has two neighbours.";
	gotoxy(32, (WIDTH - 11) / 2);
	cout << "Rules : - > ";
	gotoxy(33, WIDTH / 2);
	c = _getch();
	if (c == ESC)
		return;
	clearbuffer();


	system("cls");
	main_border();
	gotoxy(2, (WIDTH - 4) / 2);
	for (int i = 1;i < WIDTH - 1;i++)
	{
		if (i % 4 == 0)
			textcolor(LIGHT_YELLOW);
		else if (i % 4 == 1)
			textcolor(LIGHT_YELLOW);
		else if (i % 4 == 2)
			textcolor(LIGHT_RED);
		else
			textcolor(LIGHT_RED);
		gotoxy(4, i);
		cout << "=";
	}
	gotoxy(2, (WIDTH - 11) / 2);
	textcolor(LIGHT_GREEN);
	cout << "-> Rules <-";
	gotoxy(14, (WIDTH - 82) / 2);
	cout << "Any live cell with more than three live neighbours dies, as if by overpopulation.";
	gotoxy(18, (WIDTH - 48) / 2);
	textcolor(LIGHT_PURPLE);
	cout << "-------------                     -------------";
	gotoxy(19, (WIDTH - 48) / 2);
	cout << "| * | * |   |                     | * | * |   |";
	gotoxy(20, (WIDTH - 48) / 2);
	cout << "-------------                     -------------";
	gotoxy(21, (WIDTH - 48) / 2);
	cout << "|   | * | * |         -->>        |   |   | * |";
	gotoxy(22, (WIDTH - 48) / 2);
	cout << "-------------                     -------------";
	gotoxy(23, (WIDTH - 48) / 2);
	cout << "| * | * |   |                     | * | * |   |";
	gotoxy(24, (WIDTH - 48) / 2);
	cout << "-------------                     -------------";
	gotoxy(28, (WIDTH - 60) / 2);
	textcolor(LIGHT_AQUA);
	cout << "Cell will die in next generation as it has five neighbours.";
	gotoxy(32, (WIDTH - 11) / 2);
	cout << "Rules : - > ";
	gotoxy(33, WIDTH / 2);
	c = _getch();
	if (c == ESC)
		return;
	clearbuffer();


	system("cls");
	main_border();
	gotoxy(2, (WIDTH - 4) / 2);
	for (int i = 1;i < WIDTH - 1;i++)
	{
		if (i % 4 == 0)
			textcolor(LIGHT_YELLOW);
		else if (i % 4 == 1)
			textcolor(LIGHT_YELLOW);
		else if (i % 4 == 2)
			textcolor(LIGHT_RED);
		else
			textcolor(LIGHT_RED);
		gotoxy(4, i);
		cout << "=";
	}
	gotoxy(2, (WIDTH - 11) / 2);
	textcolor(LIGHT_GREEN);
	cout << "-> Rules <-";
	gotoxy(14, (WIDTH - 93) / 2);
	cout << "Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.";
	gotoxy(18, (WIDTH - 48) / 2);
	textcolor(LIGHT_PURPLE);
	cout << "-------------                     -------------";
	gotoxy(19, (WIDTH - 48) / 2);
	cout << "|   | * |   |                     |   | * |   |";
	gotoxy(20, (WIDTH - 48) / 2);
	cout << "-------------                     -------------";
	gotoxy(21, (WIDTH - 48) / 2);
	cout << "| * |   |   |         -->>        | * | * |   |";
	gotoxy(22, (WIDTH - 48) / 2);
	cout << "-------------                     -------------";
	gotoxy(23, (WIDTH - 48) / 2);
	cout << "| * |   |   |                     | * |   |   |";
	gotoxy(24, (WIDTH - 48) / 2);
	cout << "-------------                     -------------";
	gotoxy(28, (WIDTH - 77) / 2);
	textcolor(LIGHT_AQUA);
	cout << "Cell will become live in next generation as it has exactly three neighbours.";
	gotoxy(32, (WIDTH - 11) / 2);
	cout << "Rules : - > ";
	gotoxy(33, WIDTH / 2);
	c = _getch();
	if (c == ESC)
		return;
	clearbuffer();
}

int main()
{
	loading();
	int p, c, d;
	char page[HEIGHT][WIDTH];
	char ch;
	int i = 0;
	fstream f("frontpage.txt", ios::in);
	f.seekg(0);
	f.get(ch);
	while (!f.eof())
	{
		if (ch != '\n')
		{
			page[i / WIDTH][i % WIDTH] = ch;         // My favourite line 
			if (i < HEIGHT * WIDTH)                 //Initialization of 2D array using single variable "i"
				i++;
		}
		f.get(ch);
	}
	f.close();
	string ar[] = { "New Matrix","Content Manager","Load Matrix","Help","Exit" };
Menu:
	clearbuffer();
	system("cls");
	textcolor(color);
	srand(time(0));
	for (int i = 0;i < HEIGHT;i++)
		for (int j = 0;j < WIDTH;j++)
		{
			if(random)
				textcolor(rand() % 15 + 1);
			gotoxy(i, j);
			cout << page[i][j];
		}
	textcolor(WHITE);
	main_border();
	p = 0;
	textcolor(LIGHT_PURPLE);
	gotoxy(HEIGHT / 2 - 5, (WIDTH - 26) / 2);
	cout << "Conway's Game Of Life v2.5";
	for (int i = 0; i < 5; i++)
	{
		if (i != p)
		{
			gotoxy(HEIGHT / 2 + i - 1, (WIDTH - ar[i].size()) / 2);
			textcolor(WHITE);
			cout << ar[i];
			Sleep(200);
		}
		else
		{
			gotoxy(HEIGHT / 2 + i - 1, (WIDTH - select(ar[i]).size()) / 2);
			textcolor(color);
			cout << select(ar[p]);
			Sleep(200);
		}
	}
X:
	gotoxy(HEIGHT - 1, WIDTH - 1);
	c = _getch();
	if (c == ENTER || c == 224)
	{
		if (c == ENTER)
		{
			system("cls");
			if (p == 0)
			{
				help();
				system("cls");
				life ln;
				board(ln);
			}
			if (p == 1)
			{
				string s[4] = { "Saved Matrix","Color","Delay by (ms)","Randomize" };
				int kc, kd;
			CM:
				system("cls");
				main_border();
				textcolor(LIGHT_PURPLE);
				gotoxy(2, (WIDTH - 15) / 2);
				cout << "Content Manager";
				for (int i = 1;i < WIDTH - 1;i++)
				{
					if (i % 4 == 0)
						textcolor(LIGHT_YELLOW);
					else if (i % 4 == 1)
						textcolor(LIGHT_YELLOW);
					else if (i % 4 == 2)
						textcolor(LIGHT_RED);
					else
						textcolor(LIGHT_RED);
					gotoxy(4, i);
					cout << "=";
				}
				int k = 0;
				for (int i = 0; i < 4; i++)
				{
					if (i != k)
					{
						textcolor(WHITE);
						gotoxy(HEIGHT / 2 + 2 * i - 2, (WIDTH - s[i].size()) / 2);
						cout << s[i];
						if (i == 1)
							cout << "         -> " << color_str << " <-              ";
						if (i == 2)
							cout << "     -> " << speed << " <-     ";
						if (i == 3 && random)
							cout << "       -> On <-          ";
						if (i == 3 && !random)
							cout << "       -> Off <-         ";
					}
					else
					{
						textcolor(color);
						gotoxy(HEIGHT / 2 + 2 * i - 2, (WIDTH - s[i].size()) / 2);
						cout << s[i];
						if (i == 1)
							cout << "         -> " << color_str << " <-              ";
						if (i == 2)
							cout << "     -> " << speed << " <-     ";
						if (i == 3 && random)
							cout << "       -> On <-          ";
						if (i == 3 && !random)
							cout << "       -> Off <-         ";
					}
				}
				gotoxy(HEIGHT - 1, WIDTH - 1);
			CM_X:
				kc = _getch();
				if (kc == ENTER || kc == ESC || kc == 224 || isdigit(kc))    //	There is a bug here
				{
					if (k == 0 && kc == ENTER)
					{
						life l;
						name na;
						int c;
						char b[nam];
						int z, zc, zd;
						if (U_Sno == 0)
						{
							system("cls");
							main_border();
							gotoxy(HEIGHT / 2, (WIDTH - 14) / 2);
							cout << "No Saved Games" << endl;
							gotoxy(HEIGHT / 2 + 1, WIDTH / 2);
							_getch();
							goto CM;
						}
						system("cls");
						textcolor(WHITE);
						main_border();
						for (int i = 1;i < HEIGHT - 1;i++)
						{
							if (i % 2)
								textcolor(LIGHT_AQUA);
							else
								textcolor(BLUE);
							gotoxy(i, WIDTH / 3);
							cout << "#";
						}
						gotoxy(2, 5);
						textcolor(LIGHT_PURPLE);
						cout << "SNo     Name" << endl;
						for (int i = 1;i < WIDTH / 3 - 1;i++)
						{
							if (i % 4 == 0)
								textcolor(LIGHT_YELLOW);
							else if (i % 4 == 1)
								textcolor(LIGHT_YELLOW);
							else if (i % 4 == 2)
								textcolor(LIGHT_RED);
							else
								textcolor(LIGHT_RED);
							gotoxy(4, i);
							cout << "=";
						}
						textcolor(WHITE);
						for (int i = 1; i <= U_Sno; i++)
						{
							na = readn(i);
							gotoxy(5 + i, 5);
							cout << na.getsno();
							gotoxy(5 + i, 13);
							cout << na.getname();
						}
						textcolor(color);
						gotoxy(HEIGHT / 2, 2 * (WIDTH / 3) - 14 / 2);
						cout << "Enter the SNo.";
						gotoxy(HEIGHT / 2 + 1, 2 * (WIDTH / 3));
						cin >> c;
						if (cin.fail())
						{
							clearbuffer();
							cin.clear();
							cin.ignore(INT_MAX, '\n');
							goto CM;
						}
						if (c <= U_Sno && c >= 1)
						{
							l = readg(c);
							na = readn(c);
							system("cls");
							main_border();
							for (int i = 1;i < HEIGHT - 1;i++)
							{
								if (i % 2)
									textcolor(LIGHT_AQUA);
								else
									textcolor(BLUE);
								gotoxy(i, WIDTH / 3);
								cout << "#";
							}
							gotoxy(2, 5);
							textcolor(LIGHT_PURPLE);
							cout << "Content Manager";
							for (int i = 1;i < WIDTH / 3 - 1;i++)
							{
								if (i % 4 == 0)
									textcolor(LIGHT_YELLOW);
								else if (i % 4 == 1)
									textcolor(LIGHT_YELLOW);
								else if (i % 4 == 2)
									textcolor(LIGHT_RED);
								else
									textcolor(LIGHT_RED);
								gotoxy(4, i);
								cout << "=";
							}
							textcolor(LIGHT_AQUA);
							gotoxy(6, 5);
							cout << "Name : ";
							gotoxy(7, 5);
							cout << na.getname();
							textcolor(LIGHT_GREEN);
							gotoxy(9, 5);
							cout << "NA_Sno : ";
							gotoxy(10, 5);
							cout << na.getsno();
							textcolor(LIGHT_YELLOW);
							gotoxy(12, 5);
							cout << "L_Sno : ";
							gotoxy(13, 5);
							cout << l.getsno();
							srand(time(0));
							textcolor(color);
							for (int i = 1; i < M - 1; i++)
							{
								for (int j = 1; j < N - 1; j++)
								{
									if (random)
										textcolor(rand() % 15 + 1);
									gotoxy(i, WIDTH / 3 + j);
									cout << l.getchar(i, j);
								}
							}
							clearbuffer();
							string s[2] = { "Delete","Rename" };
						K:
							z = 0;
							for (int i = 0; i < 2; i++)
							{
								if (i != z)
								{
									textcolor(WHITE);
									gotoxy(20 + i, 3);
									cout << "  " << s[i] << "       ";
								}
								else
								{
									textcolor(color);
									gotoxy(20 + i, 3);
									cout << select(s[z]) << "       ";
								}
							}
						K_X:
							gotoxy(HEIGHT - 1, WIDTH - 1);
							zc = _getch();
							if (zc == ENTER || zc == ESC || zc == 224)
							{
								if (zc == ENTER)
								{
									if (z == 0)
									{
										system("cls");
										remove(c);
										if (U_Sno > 0)
											U_Sno--;
										set_Universal_Sno(U_Sno);
										main_border();
										gotoxy(HEIGHT / 2, (WIDTH - 7) / 2);
										cout << "Deleted";
										gotoxy(HEIGHT / 2 + 1, WIDTH / 2);
										_getch();
										goto CM;
									}
									if (z == 1)
									{
										system("cls");
										main_border();
										for (int i = 1;i < HEIGHT - 1;i++)
										{
											if (i % 2)
												textcolor(LIGHT_AQUA);
											else
												textcolor(BLUE);
											gotoxy(i, WIDTH / 3);
											cout << "#";
										}
										gotoxy(2, 5);
										textcolor(LIGHT_PURPLE);
										cout << "Content Manager";
										for (int i = 1;i < WIDTH / 3 - 1;i++)
										{
											if (i % 4 == 0)
												textcolor(LIGHT_YELLOW);
											else if (i % 4 == 1)
												textcolor(LIGHT_YELLOW);
											else if (i % 4 == 2)
												textcolor(LIGHT_RED);
											else
												textcolor(LIGHT_RED);
											gotoxy(4, i);
											cout << "=";
										}
										srand(time(0));
										textcolor(color);
										for (int i = 1; i < M - 1; i++)
										{
											for (int j = 1; j < N - 1; j++)
											{
												if (random)
													textcolor(rand() % 15 + 1);
												gotoxy(i, WIDTH / 3 + j);
												cout << l.getchar(i, j);
											}
										}
										textcolor(LIGHT_AQUA);
										clearbuffer();
										cin.ignore();
										gotoxy(6, 5);
										cout << "Enter New Name";
										gotoxy(8, 5);
										textcolor(WHITE);
										cin.getline(b, nam);
										if (cin.fail())
										{
											clearbuffer();
											cin.clear();
											cin.ignore(INT_MAX, '\n');
											goto CM;
										}
										na.setname(b);
										write(c, l, na);
										goto CM;
									}
									goto K;
								}
								if (zc == ESC)
								{
									goto CM;
								}
								zd = _getch();
								if (zd == UP)
								{
									if (z != 0)
									{
										z--;
										z = z % 2;
									}
									else
									{
										z = 1;
									}
									for (int i = 0; i < 2; i++)
									{
										if (i != z)
										{
											textcolor(WHITE);
											gotoxy(20 + i, 3);
											cout << "  " << s[i] << "       ";
										}
										else
										{
											textcolor(color);
											gotoxy(20 + i, 3);
											cout << select(s[z]) << "       ";
										}
									}
								}
								if (zd == DOWN)
								{
									z++;
									z = z % 2;
									for (int i = 0; i < 2; i++)
									{
										if (i != z)
										{
											textcolor(WHITE);
											gotoxy(20 + i, 3);
											cout << "  " << s[i] << "       ";
										}
										else
										{
											textcolor(color);
											gotoxy(20 + i, 3);
											cout << select(s[z]) << "       ";
										}
									}
								}
							}
							goto K_X;
						}
						clearbuffer();
						goto CM;
					}
					if (k == 2 && isdigit(kc))
					{
						int sp = 0, temp;
						sp = sp * 10 + (kc - 48);
					Speed:
						textcolor(WHITE);
						gotoxy(HEIGHT / 2 + 2, (WIDTH - 40) / 2);
						cout << "                                                 ";
						gotoxy(HEIGHT / 2 + 2, (WIDTH - 13) / 2);
						cout << s[2] << "     ";
						textcolor(color);
						cout << "-> " << sp << " <-";
						temp = _getch();
						if (temp == ENTER)
						{
							set_Universal_speed(sp);
							speed = get_Universal_speed();
							textcolor(WHITE);
							cout << "Done";
							goto CM_X;
						}
						if (temp == 224)
						{
							kd = _getch();
							goto CM_UP_DOWN;
						}
						if (isdigit(temp))
						{
							sp = sp * 10 + (temp - 48);
							goto Speed;
						}
						goto CM_X;
					}
					if (kc == ESC)
					{
						goto Menu;
					}
					kd = _getch();
					if (k == 1 && (kd == LEFT || kd == RIGHT))
					{
						int temp = color;
					Color:
						if (kd == RIGHT)
							if (temp == 15)
								temp = 1;
							else
								temp++;
						if (kd == LEFT)
							if (temp == 1)
								temp = 15;
							else
								temp--;
						textcolor(WHITE);
						gotoxy(HEIGHT / 2, (WIDTH - 20) / 2);
						cout << "                    ";
						gotoxy(HEIGHT / 2, (WIDTH - 5) / 2);
						cout << s[1] << "         ";
						textcolor(temp);
						color_str = colorset(temp);
						cout << "-> " << color_str << " <-        ";
						kc = _getch();
						if (kc == ENTER)
						{
							color = temp;
							set_Universal_color(temp);
							textcolor(WHITE);
							cout << "Done";
						}
						if (kc == ESC)
						{
							color_str = colorset(color);
							goto Menu;
						}
						if (kc == 224)
						{
							kd = _getch();
							if (kd == UP || kd == DOWN)
							{
								color_str = colorset(color);
								goto CM_UP_DOWN;
							}
							if (kd == LEFT || kd == RIGHT)
								goto Color;
						}
						goto CM_X;
					}
					if (k == 3 && (kd == LEFT || kd == RIGHT))
					{
					Random:
						random = !random;
						set_Universal_random(random);
						if (random)
						{
							gotoxy(HEIGHT / 2 + 4, (WIDTH - s[3].size()) / 2);
							cout << s[3] << "       -> On <-          ";
						}
						else
						{
							gotoxy(HEIGHT / 2 + 4, (WIDTH - s[3].size()) / 2);
							cout << s[3] << "       -> Off <-         ";
						}
						kc = _getch();
						if (kc == ESC)
							goto Menu;
						if (kc == 224)
						{
							kd = _getch();
							if (kd == UP || kd == DOWN)
								goto CM_UP_DOWN;
							if (kd == LEFT || kd == RIGHT)
								goto Random;
						}
						goto CM_X;
					}
				CM_UP_DOWN:
					if (kd == UP)
					{
						gotoxy(HEIGHT / 2 + 2 * k - 2, (WIDTH - 30) / 2);
						cout << "                                                     ";
						if (k != 0)
						{
							k--;
						}
						else
						{
							k = 3;
						}
						for (int i = 0; i < 4; i++)
						{
							if (i != k)
							{
								textcolor(WHITE);
								gotoxy(HEIGHT / 2 + 2 * i - 2, (WIDTH - s[i].size()) / 2);
								cout << s[i];
								if (i == 1)
									cout << "         -> " << color_str << " <-              ";
								if (i == 2)
									cout << "     -> " << speed << " <-     ";
								if (i == 3 && random)
									cout << "       -> On <-          ";
								if (i == 3 && !random)
									cout << "       -> Off <-         ";
							}
							else
							{
								textcolor(color);
								gotoxy(HEIGHT / 2 + 2 * i - 2, (WIDTH - s[i].size()) / 2);
								cout << s[i];
								if (i == 1)
									cout << "         -> " << color_str << " <-              ";
								if (i == 2)
									cout << "     -> " << speed << " <-     ";
								if (i == 3 && random)
									cout << "       -> On <-          ";
								if (i == 3 && !random)
									cout << "       -> Off <-         ";
							}
						}
						gotoxy(HEIGHT - 1, WIDTH - 1);
					}
					if (kd == DOWN)
					{
						gotoxy(HEIGHT / 2 + 2 * k - 2, (WIDTH - 30) / 2);
						cout << "                                                     ";
						k++;
						k = k % 4;
						for (int i = 0; i < 4; i++)
						{
							if (i != k)
							{
								textcolor(WHITE);
								gotoxy(HEIGHT / 2 + 2 * i - 2, (WIDTH - s[i].size()) / 2);
								cout << s[i];
								if (i == 1)
									cout << "         -> " << color_str << " <-              ";
								if (i == 2)
									cout << "     -> " << speed << " <-     ";
								if (i == 3 && random)
									cout << "       -> On <-          ";
								if (i == 3 && !random)
									cout << "       -> Off <-         ";
							}
							else
							{
								textcolor(color);
								gotoxy(HEIGHT / 2 + 2 * i - 2, (WIDTH - s[i].size()) / 2);
								cout << s[i];
								if (i == 1)
									cout << "         -> " << color_str << " <-              ";
								if (i == 2)
									cout << "     -> " << speed << " <-     ";
								if (i == 3 && random)
									cout << "       -> On <-          ";
								if (i == 3 && !random)
									cout << "       -> Off <-         ";
							}
						}
						gotoxy(HEIGHT - 1, WIDTH - 1);
					}
				}
				goto CM_X;
			}
			if (p == 2)
			{
				life ll;
				name na;
				string s[40];
				int rc, rd;
				if (U_Sno == 0)
				{
					system("cls");
					main_border();
					gotoxy(HEIGHT / 2, (WIDTH - 14) / 2 + 1);
					cout << "No Saved Files" << endl;
					gotoxy(HEIGHT / 2 + 1, WIDTH / 2);
					_getch();
					goto Menu;
				}
				int r = 0;
				system("cls");
				textcolor(WHITE);
				main_border();
				for (int i = 1;i < HEIGHT - 1;i++)
				{
					if (i % 2)
						textcolor(LIGHT_AQUA);
					else
						textcolor(BLUE);
					gotoxy(i, WIDTH / 3);
					cout << "#";
				}
				textcolor(LIGHT_GREEN);
				gotoxy(2, (WIDTH / 3 - 12) / 2);
				cout << "Saved Matrix";
				for (int i = 1;i < WIDTH / 3 - 1;i++)
				{
					if (i % 4 == 0)
						textcolor(LIGHT_YELLOW);
					else if (i % 4 == 1)
						textcolor(LIGHT_YELLOW);
					else if (i % 4 == 2)
						textcolor(LIGHT_RED);
					else
						textcolor(LIGHT_RED);
					gotoxy(4, i);
					if (i % 2)
						cout << "~";
					else
						cout << "-";
				}
				for (int i = 1; i <= U_Sno; i++)
				{
					na = readn(i);
					s[i - 1] = na.getname();
				}
				for (int i = 0; i < U_Sno; i++)
				{
					if (i != r)
					{
						gotoxy(6 + i, 3);
						textcolor(WHITE);
						cout << "  " << s[i] << "  ";
					}
					else
					{
						gotoxy(6 + i, 3);
						textcolor(color);
						cout << select(s[i]);
						ll = readg(r + 1);
						srand(time(0));
						textcolor(color);
						for (int i = 1; i < M - 1; i++)
						{
							for (int j = 1; j < N - 1; j++)
							{
								if (random)
									textcolor(rand() % 15 + 1);
								gotoxy(i, WIDTH / 3 + j);
								cout << ll.getchar(i, j);
							}
						}
					}
				}
			Load:
				gotoxy(HEIGHT - 1, WIDTH - 1);
				rc = _getch();
				if (rc == ENTER || rc == 224 || rc == ESC)
				{
					if (rc == ENTER)
					{
						board(ll);
						goto Menu;
					}
					if (rc == ESC)
					{
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
						for (int i = 0; i < U_Sno; i++)
						{
							if (i != r)
							{
								gotoxy(6 + i, 3);
								textcolor(WHITE);
								cout << "  " << s[i] << "  ";
							}
							else
							{
								gotoxy(6 + i, 3);
								textcolor(color);
								cout << select(s[i]);
								ll = readg(r + 1);
								srand(time(0));
								textcolor(color);
								for (int i = 1; i < M - 1; i++)
								{
									for (int j = 1; j < N - 1; j++)
									{
										if (random)
											textcolor(rand() % 15 + 1);
										gotoxy(i, WIDTH / 3 + j);
										cout << ll.getchar(i, j);
									}
								}
							}
						}
					}
					if (rd == DOWN)
					{
						r++;
						r = r % U_Sno;
						for (int i = 0; i < U_Sno; i++)
						{
							if (i != r)
							{
								gotoxy(6 + i, 3);
								textcolor(WHITE);
								cout << "  " << s[i] << "  ";
							}
							else
							{
								gotoxy(6 + i, 3);
								textcolor(color);
								cout << select(s[i]);
								ll = readg(r + 1);
								srand(time(0));
								textcolor(color);
								for (int i = 1; i < M - 1; i++)
								{
									for (int j = 1; j < N - 1; j++)
									{
										if (random)
											textcolor(rand() % 15 + 1);
										gotoxy(i, WIDTH / 3 + j);
										cout << ll.getchar(i, j);
									}
								}
							}
						}
					}
				}
				goto Load;
			}
			if (p == 3)
			{
				help();
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
			clear_area(HEIGHT / 2 - 1, (WIDTH - 19) / 2, HEIGHT / 2 + 3, (WIDTH + 19) / 2 - 1);
			for (int i = 0; i < 5; i++)
			{
				if (i != p)
				{
					gotoxy(HEIGHT / 2 + i - 1, (WIDTH - ar[i].size()) / 2);
					textcolor(WHITE);
					cout << ar[i] << endl;
				}
				else
				{
					gotoxy(HEIGHT / 2 + i - 1, (WIDTH - select(ar[i]).size()) / 2);
					textcolor(color);
					cout << select(ar[p]) << endl;
				}
			}
		}
		if (d == DOWN)
		{
			p++;
			p = p % 5;
			clear_area(HEIGHT / 2 - 1, (WIDTH - 19) / 2, HEIGHT / 2 + 3, (WIDTH + 19) / 2 - 1);
			for (int i = 0; i < 5; i++)
			{
				if (i != p)
				{
					gotoxy(HEIGHT / 2 + i - 1, (WIDTH - ar[i].size()) / 2);
					textcolor(WHITE);
					cout << ar[i] << endl;
				}
				else
				{
					gotoxy(HEIGHT / 2 + i - 1, (WIDTH - select(ar[i]).size()) / 2);
					textcolor(color);
					cout << select(ar[p]) << endl;
				}
			}
		}
	}
	goto X;
E:
	textcolor(WHITE);
	return 0;
}