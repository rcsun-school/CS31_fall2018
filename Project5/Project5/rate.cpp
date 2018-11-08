#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cctype>
#include <cstring>
#include <array>
#include <cassert>
using namespace std;

const int MAX_WORD_LENGTH = 20;

void removeElement(char word1[][MAX_WORD_LENGTH + 1], char word2[][MAX_WORD_LENGTH + 1], int separation[], int nPatterns, int pos) {
	char temp1[MAX_WORD_LENGTH + 1];
	char temp2[MAX_WORD_LENGTH + 1];
	strcpy(temp1, word1[pos]);
	strcpy(temp2, word2[pos]);
	int temp3 = separation[pos];
	for (int i = pos + 1; i < nPatterns; i++) {
		strcpy(word1[i-1],word1[i]);
		strcpy(word2[i-1],word2[i]);
		separation[i - 1] = separation[i];
	}
	strcpy(word1[nPatterns - 1], temp1);
	strcpy(word2[nPatterns - 1], temp2);
	separation[nPatterns - 1] = temp3; 
}


void checkRepeat(char word1[][MAX_WORD_LENGTH + 1], char word2[][MAX_WORD_LENGTH + 1], int separation[], int& nPatterns) {
	for (int i = 0; i < nPatterns; i++)
	{
		char temp1[MAX_WORD_LENGTH + 1];
		char temp2[MAX_WORD_LENGTH + 1];
		strcpy(temp1, word1[i]);
		strcpy(temp2, word2[i]);
		for (int j = i + 1; j < nPatterns; j++) 
		{
			if (strcmp(temp1, word1[j]) == 0 || strcmp(temp1, word2[j]) == 0
				|| strcmp(temp2, word1[j]) == 0 || strcmp(temp2, word2[j]) == 0)
			{
				if (separation[i] <= separation[j]) 
				{
					removeElement(word1, word2, separation, nPatterns, i);
					nPatterns--;
					i--;
				}
				else 
				{
					removeElement(word1, word2, separation, nPatterns, j);
					nPatterns--;
					i--;
				}
			}
		}

	}
}  

int makeProper(char word1[][MAX_WORD_LENGTH + 1], char word2[][MAX_WORD_LENGTH + 1], int separation[], int nPatterns)
{
	if (nPatterns <= 0)
		return 0;
	for (int i = 0; i < nPatterns; i++) {
		for (int j = 0; word1[i][j] != '\0' && word2[i][j] != '\0'; j++) {
			if (!isalpha(word1[i][j]) || !isalpha(word2[i][j]) || separation[i] <= 0) {
				removeElement(word1, word2, separation, nPatterns, i);
				nPatterns--;
				continue;
			}
			if (isupper(word1[i][j])) {
				word1[i][j] = tolower(word1[i][j]);
			}
			if (isupper(word2[i][j])) {
				word2[i][j] = tolower(word2[i][j]);
			}
		}
	}
	checkRepeat(word1, word2, separation, nPatterns);
	return nPatterns;
}


int rate(const char document[], const char word1[][MAX_WORD_LENGTH + 1], const char word2[][MAX_WORD_LENGTH + 1], const int separation[], int nPatterns) {
	if (nPatterns <= 0) {
		return 0;
	}
	int nMatches = 0;
	int lenDocument= strlen(document);
	char storage[MAX_WORD_LENGTH + 1];
	strcpy(storage, document);
	for (int i = 0; i < nPatterns; i++) {
		int j = 0;
		do {
			if (isalpha(document[j])) { //continue working. Solution seems to involve a pointer
			}
		}
	}
}

int main() {
	char a[7][21] = {"Timmy", "Fruit", "Nine","Gerald","Nino","Lucina","Hawkeye"};
	char b[7][21] = { "Newton","8nut","Timmy","Nino", "Fruit", "timmy", "Jake"};
	int num[7] = { 6,2,3,3,1,8,2};
	cout << makeProper(a, b, num, 3) << endl;
	for (int i = 0; i < 7; i++) {
		cout << a[i] << "    " << b[i] << "    " << num[i] << endl;
	}
}