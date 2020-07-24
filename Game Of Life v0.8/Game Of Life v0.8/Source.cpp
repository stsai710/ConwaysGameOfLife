#include<iostream>
using namespace std;
void main()
{
	int a[5][5], i, j, b[5][5];
	for (i = 0;i < 5;i++)
		for (j = 0;j < 5;j++)
			a[i][j] = b[i][j] = 0;
	a[1][2] = a[1][3] = a[2][3] = 1;
	b[1][2] = b[1][3] = b[2][3] = 1;
	for (i = 0;i < 5;i++)
	{
		for (j = 0;j < 5;j++)
			cout << a[i][j] << "\t";
		cout << endl;
	}
	cout << endl << endl << endl;
	int c = 0;
	for (i = 0;i < 5;i++)
		for (j = 0;j < 5;j++)
		{
			c = 0;
			if (i - 1 >= 0 && i + 1 <= 4 && j - 1 >= 0 && j + 1 <= 4)
				if (a[i][j] != 1)
				{
					if (a[i - 1][j - 1] == 1)
						c++;
					if (a[i - 1][j] == 1)
						c++;
					if (a[i - 1][j + 1] == 1)
						c++;
					if (a[i][j - 1] == 1)
						c++;
					if (a[i][j + 1] == 1)
						c++;
					if (a[i + 1][j - 1] == 1)
						c++;
					if (a[i + 1][j] == 1)
						c++;
					if (a[i + 1][j + 1] == 1)
						c++;
					if (c == 3)
						b[i][j] = 1;
				}
				else
				{
					if (a[i - 1][j - 1] == 1)
						c++;
					if (a[i - 1][j] == 1)
						c++;
					if (a[i - 1][j + 1] == 1)
						c++;
					if (a[i][j - 1] == 1)
						c++;
					if (a[i][j + 1] == 1)
						c++;
					if (a[i + 1][j - 1] == 1)
						c++;
					if (a[i + 1][j] == 1)
						c++;
					if (a[i + 1][j + 1] == 1)
						c++;
					if (c <= 1 || c >= 4)
						b[i][j] = 0;
				}

		}

	for (i = 0;i < 5;i++)
	{
		for (j = 0;j < 5;j++)
			cout << b[i][j] << "\t";
		cout << endl;
	}
}