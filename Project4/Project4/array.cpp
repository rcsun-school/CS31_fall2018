#include <iostream>
#include <array>
#include <string>
#include <cassert>
using namespace std;

//Concatenates the string parameter value to elements in array
//Returns array size n for all elements modified
//Returns -1 if n is a negative number
int appendToAll(string a[], int n, string value) {
	if (n < 0) {
		return -1;
	}
	for (int i = 0; i < n; i++) {
		a[i] += value;
	}
	return n;
}

//Return pos of target within array
//Return -1 if n is negative or target is not contained in array
int lookup(const string a[], int n, string target) {
	if (n < 0) {
		return -1;
	} 
	for (int i = 0; i < n; i++) {
		if (a[i] == target) {
			return i;
		}
	}
	return -1;
}

//Return pos of highest value string in the array
//Return -1 if no interesting elements found
int positionOfMax(const string a[], int n) {
	if (n <= 0) {
		return -1;
	}
	int posMax = -1;
	string max = "";
	for (int i = 0; i < n; i++) {
		if (a[i] > max) {
			max = a[i];
			posMax = i;
		}
	}
	return posMax;
}

//all elements after pos are shifted left
//return new position of eliminated string
//return -1 if n is negative or pos is greater than n
int rotateLeft(string a[], int n, int pos) {
	if (n <= 0 || pos >= n) {
		return -1;
	}
	string eliminate = a[pos];
	int i = pos + 1;
	while (i < n) {
		a[i - 1] = a[i];
		i++;
	} 
	a[n - 1] = eliminate;
	return pos;
}



//return the number of consecutive sequences of an identical element
int countRuns(const string a[], int n) {
	if (n < 0)
		return 1;
	int nRuns = 0;
	string temp = "";
	for (int i = 0; i < n; i++) {
		if (a[i] != temp) {
			temp = a[i];
			nRuns++;
			}
	}
	return nRuns;
}

//reverses elements in array
//returns n if successful flip
//returns -1 if n size is negative
int flip(string a[], int n) {
	if (n < 0) {
		return -1;
	}
	string temp;
	for (int i = 0; i < n / 2; i++) {
		temp = a[i];
		a[i] = a[(n-1) - i];
		a[(n - 1) - i] = temp;
	}
	return n;
}

//return index where a1 and a2 do not have equal elements.
//return shorter length if a1 and a2 are matched until the end of shorter array
int differ(const string a1[], int n1, const string a2[], int n2) {
	if (n1 < 0 || n2 < 0) {
		return -1;
	}
	int i = 0;
	while (i < n1 && i < n2) {
		if (a1[i] != a2[i]) {
			return i;
		}
		i++;
	}
	return i + 1;
}

//return the lowest starting position in a1 at which a2 is a subsequence of a1
int subsequence(const string a1[], int n1, const string a2[], int n2) {
	if (n1 < 0 || n2 < 0 || n1 < n2) {
		return -1;
	}
	if (n2 == 0)
		return 0;
	int startPos = 0;
	for (int i = 0; i < n1; i++) {
		if (a1[i] == a2[0]) {
			startPos = i;
			int j = 0;
			while (i < n1 && j < n2 && a1[i] == a2[j]) {
				i++;
				j++;
			}
			if (j == n2) 
				return startPos;
			else {
				startPos = 0;
			}
		
		}
		if (i >= n1) { //incrementing i on a second loop is high risk for undefined behavior
			break;
		}
	} 
	return -1;

}

//return the smallest position in a1 of an element equal to any of those in a2
//return -1 otherwise
int lookupAny(const string a1[], int n1, const string a2[], int n2) {
	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < n2; j++) {
			if (a1[i] == a2[j]) {
				return i;
			}
		}
	}
	return -1;
}


//return true if a value less than divider still exists to left of pos
//false if only values greater than or equal to divider remain.
bool hasLesserValue(string a[], int n, string divider, int pos) {
	for (int i = pos; i < n; i++) {
		if (a[i] < divider) {
			return true;
		}
	}
	return false;
} 

//separates all elements with value less than divider left 
//and all elements with value greater than divider right
//return index of element with greater than or equal value than divider
int divide(string a[], int n, string divider) {
	if (n < 0) {
		return -1;
	}
	for (int i = 0; i < n && hasLesserValue(a, n, divider, i); i++) {
		if (a[i] > divider) {
			rotateLeft(a, n, i);
			i--;
		}
	}
	//identifies smallest pos where values aren't < divider
	int i = 0;
	while (i < n) {
		if (a[i] >= divider) {
			return i;
		}
		i++;
	}
	return -1;
}


int main() {

	string h[7] = { "greg", "gavin", "ed", "xavier", "", "eleni", "fiona" };
	assert(lookup(h, 7, "eleni") == 5);
	assert(lookup(h, 7, "ed") == 2);
	assert(lookup(h, 2, "ed") == -1);
	assert(positionOfMax(h, 7) == 3);

	string g[4] = { "greg", "gavin", "fiona", "kevin" };
	assert(differ(h, 4, g, 4) == 2);
	assert(appendToAll(g, 4, "?") == 4 && g[0] == "greg?" && g[3] == "kevin?");
	assert(rotateLeft(g, 4, 1) == 1 && g[1] == "fiona?" && g[3] == "gavin?");

	string e[4] = { "ed", "xavier", "", "eleni" };
	assert(subsequence(h, 7, e, 4) == 2);
	string u[4] = { "xavier", "", "eleni", "fiona" };
	assert(subsequence(h, 7, u, 4) == 3);
	assert(subsequence(h, 7, u, 0) == 0);
	assert(subsequence(h, 0, u, 0) == 0);
	string x[7] = { "greg","lucy","steve","greg","lucy","george" };
	string w[3] = { "greg","lucy","george" };
	assert(subsequence(x, 7, w, 3) == 3);

	string d[5] = { "gavin", "gavin", "gavin", "xavier", "xavier" };
	assert(countRuns(d, 5) == 2);

	string f[3] = { "fiona", "ed", "john" };
	assert(lookupAny(h, 7, f, 3) == 2);
	assert(flip(f, 3) == 3 && f[0] == "john" && f[2] == "fiona");

	assert(divide(h, 7, "fiona") == 3);

	cout << "All tests succeeded" << endl; 

	

}