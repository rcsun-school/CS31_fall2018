
#include <iostream>
#include <string>
using namespace std;

int main()
{
	int side;

	cout << "Enter a number: ";
	cin >> side;

	if (side > 0) {
		int i = 0;
		do {
			int j = i;
			string hash = "#";
			while (j >= 0) {
				cout << hash;
				j--;
			}
			cout << "\n";
			i++;
		} while (i < side);
	}
}
