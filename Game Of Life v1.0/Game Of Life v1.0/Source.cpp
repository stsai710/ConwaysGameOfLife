#include<iostream>
using namespace std;
struct point 
{
	int x, y;
};
int i = 0;
point p[100];
void input (int a[][5])
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
		a[x][y] = 1;
	}
}
void copier(int a[][5], int b[][5])
{
	int i, j;
	for (i = 0;i < 5;i++)
		for (j = 0;j < 5;j++)
			b[i][j] = a[i][j];
}
void output(int a[][5])
{
	for (int i = 0;i < 5;i++)
	{
		for (int j = 0;j < 5;j++)
			cout << a[i][j] << "\t";
		cout << endl;
	}
}
int neighbour(int a[][5], int x, int y)
{
	int c = 0;
	if (a[x - 1][y - 1] == 1)
		c++;
	if (a[x - 1][y] == 1)
		c++;
	if (a[x - 1][y + 1] == 1)
		c++;
	if (a[x][y - 1] == 1)
		c++;
	if (a[x][y + 1] == 1)
		c++;
	if (a[x + 1][y - 1] == 1)
		c++;
	if (a[x + 1][y] == 1)
		c++;
	if (a[x + 1][y + 1] == 1)
		c++;
	//       cout << a[x][y] << "\t" << x << "\t" << y << "\t" << c << endl;
	return c;
}
void initialize(int a[][5])
{
	int i, j;
	for (i = 0;i < 5;i++)
		for (j = 0;j < 5;j++)
			a[i][j] = 0;
}
void main()
{
	int a[5][5], i, j, b[5][5];
	initialize(a);
	initialize(b);
	input(a);
	copier(a, b);
	for (i = 1;i < 4;i++)
		for (j = 1;j < 4;j++)
		{
			if (a[i][j] == 0)
			{
				if (neighbour(a, i, j) == 3)
					b[i][j] = 1;
			}
			else
			{
				if (neighbour(a, i, j) <= 1 || neighbour(a, i, j) >= 4)
					b[i][j] = 0;
			}

		}
	cout << endl;
	output(a);
	cout << endl << endl;
	cout << "Next Generation" << endl;
	output(b);
}