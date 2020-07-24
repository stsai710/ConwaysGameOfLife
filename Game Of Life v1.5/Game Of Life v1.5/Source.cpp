#include<iostream>
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
	for (i = 0;i < 50;i++)
		for (j = 0;j < 50;j++)
			b[i][j] = a[i][j];
}
void output(char a[][50])
{
	for (int i = 0;i < 50;i++)
	{
		for (int j = 0;j < 50;j++)
			cout << a[i][j] << " ";
		cout << endl;
	}
}
int neighbour(char a[50][50], int x, int y)
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
void initialize(char a[50][50])
{
	int i, j;
	for (i = 0;i < 50;i++)
		for (j = 0;j < 50;j++)
			a[i][j] = ' ';
}
void main()
{
	char a[50][50], b[50][50];
	int i, j, n;
	cout << "No. of generation" << endl;
	cin >> n;
	initialize(a);
	initialize(b);
	input(a);
	copier(a, b);
	cout << "First Generation" << endl;
	output(a);
	for (int v = 0;v < n;v++)
	{
		for (i = 1;i < 49;i++)
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
		cout << endl;
		cout << endl << endl;
		cout << "Generation " << v + 2 << endl;
		output(b);
		copier(b, a);
	}
}