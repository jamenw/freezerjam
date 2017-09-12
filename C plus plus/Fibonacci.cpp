#include<iostream>
#include <conio.h> 

using namespace std;

int main()  {
	int n, c, first = 0, second = 1, next;

	cout << "Number of Fibonacci numbers: ";
	cin >> n;

	cout << "First " << n << " terms of Fibonacci series are: " << endl;

	for (c = 0; c < n; c++)
	{
		if (c <= 1)
			next = c;
		else
		{
			next = first + second;
			first = second;
			second = next;
		}
		cout << next << " ";
	}
	_getch();
	return 0;
	
}