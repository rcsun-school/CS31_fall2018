#include <iostream>
#include <string>
using namespace std;

int main()
{
	int side;

	cout << "Enter a number: ";
	cin >> side;

	for (int i = 0; i < side; i++)
	{
		string hash = "#";
		int j = i;
		while (j >= 0) {
			cout << hash;
			j--;
		}
		cout << "\n";
	}
}
