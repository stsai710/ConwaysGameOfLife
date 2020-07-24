#include<iostream>
using namespace std;
struct point
{
	int x, y;
};
int i = 0;
point p[100];
void input(char a[][5])
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
void copier(char a[][5], char b[][5])
{
	int i, j;
	for (i = 0;i < 5;i++)
		for (j = 0;j < 5;j++)
			b[i][j] = a[i][j];
}
void output(char a[][5])
{
	for (int i = 0;i < 5;i++)
	{
		for (int j = 0;j < 5;j++)
			cout << a[i][j] << "\t";
		cout << endl;
	}
}
int neighbour(char a[5][5], int x, int y)
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
void initialize(char a[5][5])
{
	int i, j;
	for (i = 0;i < 5;i++)
		for (j = 0;j < 5;j++)
			a[i][j] = ' ';
}
void main()
{
	char a[5][5], b[5][5];
	int i, j;
	initialize(a);
	initialize(b);
	input(a);
	copier(a, b);
	for (i = 1;i < 4;i++)
		for (j = 1;j < 4;j++)
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
	cout << endl;
	cout << "output a" << endl;
	output(a);
	cout << endl << endl;
	cout << "Next Generation" << endl;
	output(b);
}