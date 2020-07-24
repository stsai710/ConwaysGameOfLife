#include<iostream>
#include<Windows.h>
#include<stdlib.h>
using namespace std;
struct point
{
	int x, y;
};
int i = 0;
point p[100];
void input(char a[][50])
{
	int n, k, x, y;
	cout << "No. of elements" << endl;
	cin >> n;
	for (k = 0;k < n;k++)
	{
		cout << "Enter point " << k + 1 << endl;
		cin >> x >> y;
		p[i].x = x;
		p[i++].y = y;
		a[x][y] = '*';
	}
}
void copier(char a[][50], char b[][50])
{
	int i, j;
	for (i = 0;i < 39;i++)
		for (j = 0;j < 50;j++)
			b[i][j] = a[i][j];
}
void output(char a[][50])
{
	for (int i = 0;i < 39;i++)
	{
		for (int j = 0;j < 50;j++)
			cout << a[i][j] << " ";
		cout << endl;
	}
}
int neighbour(char a[][50], int x, int y)
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
	//      cout << a[x][y] << "\t" << x << "\t" << y << "\t" << c << endl;
	return c;
}
void initialize (char a[][50])
{
	int i, j;
	for (i = 0;i < 39;i++)
		for (j = 0;j < 50;j++)
			a[i][j] = ' ';
}
void predefined(char a[][50])
{
	int n;
	cout << "1. Glider" << endl;
	cout << "2. Small Exploder" << endl;
	cout << "3. Exploder" << endl;
	cout << "4. 10 Cell Row" << endl;
	cout << "5. Lightweight Spaceship" << endl;
	cout << "6. Tumbler" << endl;
	cout << "7. Gosper Glider Gun" << endl;
	cin >> n;
	if (n == 1)
	{
		a[4][1] = '*';
		a[4][2] = '*';
		a[4][3] = '*';
		a[3][3] = '*';
		a[2][2] = '*';
	}
	if (n == 2)
	{
		a[18][12] = '*';
		a[19][11] = '*';
		a[19][12] = '*';
		a[19][13] = '*';
		a[20][11] = '*';
		a[20][13] = '*';
		a[21][12] = '*';
	}
	if (n == 3)
	{
		a[17][12] = '*';
		a[17][10] = '*';
		a[17][14] = '*';
		a[18][10] = '*';
		a[18][14] = '*';
		a[19][10] = '*';
		a[19][14] = '*';
		a[20][10] = '*';
		a[20][14] = '*';
		a[21][12] = '*';
		a[21][10] = '*';
		a[21][14] = '*';
	}
	if (n == 4)
	{
		a[19][8] = '*';
		a[19][9] = '*';
		a[19][10] = '*';
		a[19][11] = '*';
		a[19][12] = '*';
		a[19][13] = '*';
		a[19][14] = '*';
		a[19][15] = '*';
		a[19][16] = '*';
		a[19][17] = '*';
	}
	if (n == 5)
	{
		a[17][3] = '*';
		a[17][4] = '*';
		a[17][5] = '*';
		a[17][6] = '*';
		a[18][6] = '*';
		a[18][2] = '*';
		a[19][6] = '*';
		a[20][2] = '*';
		a[20][5] = '*';
	}
	if (n == 6)
	{
		a[16][10] = '*';
		a[16][11] = '*';
		a[16][13] = '*';
		a[16][14] = '*';
		a[17][10] = '*';
		a[17][11] = '*';
		a[17][13] = '*';
		a[17][14] = '*';
		a[18][11] = '*';
		a[18][13] = '*';
		a[19][11] = '*';
		a[19][13] = '*';
		a[19][15] = '*';
		a[19][9] = '*';
		a[20][11] = '*';
		a[20][13] = '*';
		a[20][15] = '*';
		a[20][9] = '*';
		a[21][9] = '*';
		a[21][10] = '*';
		a[21][14] = '*';
		a[21][15] = '*';
	}
	if (n == 7)
	{
		a[8][2] = '*';
		a[8][3] = '*';
		a[9][2] = '*';
		a[9][3] = '*';
		a[8][11] = '*';
		a[8][12] = '*';
		a[9][10] = '*';
		a[9][12] = '*';
		a[10][10] = '*';
		a[10][11] = '*';
		a[10][18] = '*';
		a[10][19] = '*';
		a[11][18] = '*';
		a[11][20] = '*';
		a[12][18] = '*';
		a[8][24] = '*';
		a[8][25] = '*';
		a[7][24] = '*';
		a[7][26] = '*';
		a[6][25] = '*';
		a[6][26] = '*';
		a[7][36] = '*';
		a[7][37] = '*';
		a[6][36] = '*';
		a[6][37] = '*';
		a[7][36] = '*';
		a[13][37] = '*';
		a[14][37] = '*';
		a[15][37] = '*';
		a[13][38] = '*';
		a[14][39] = '*';
		a[18][26] = '*';
		a[18][27] = '*';
		a[18][28] = '*';
		a[19][26] = '*';
		a[20][27] = '*';
	}
}
void main()
{
	char a[39][50], b[39][50];
	int i, j, n, speed, no;
	initialize(a);
	initialize(b);
	cout << "WELCOME TO THE GAME OF LIFE" << endl;
	cout << "1. Custom\n2. Predefined" << endl;
	cin >> n;
	if (n == 1)
	{
		input(a);
	}
	if (n == 2)
	{
		predefined(a);
	}
	cout << "No. of generation" << endl;
	cin >> n;
	copier(a, b);
	cout << "Speed" << endl;
	cin >> speed;
	cout << "First Generation" << endl;
	output(a);
	system("Pause");
	for (int v = 0;v < n;v++)
	{
		for (i = 1;i < 38;i++)
			for (j = 1;j < 49;j++)
			{
				if (a[i][j] == ' ')
				{
					if (neighbour(a, i, j) == 3)
						b[i][j] = '*';
				}
				else
				{
					if (neighbour(a, i, j) <= 1 || neighbour(a, i, j) >= 4)
						b[i][j] = ' ';
				}

			}
		system("cls");
		output(b);
		Sleep(speed);
		copier(b, a);
	}
}