#include<iostream>
using namespace std;
void main()
{
	// first send 224 then the key you want to use
	for (int i = 0;i < 256;i++)
		cout << i << "\t" << char(i) << endl;
}