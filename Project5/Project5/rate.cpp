#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cctype>
#include <cstring>
#include <array>
#include <cassert>
using namespace std;

const int MAX_WORD_LENGTH = 20;

//removes patterns by placing it at the last known index in cstring
//shifts all patterns formerly to the right of the removed pattern one to the left.
//decreases nPatterns to place element out of known bounds
void removeElement(char word1[][MAX_WORD_LENGTH + 1], char word2[][MAX_WORD_LENGTH + 1], int separation[], int& nPatterns, int pos) {
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
	nPatterns--;
}

//parses the set of patterns for repeating words
//if a repeating word is detected, the pattern with the lowest separation is removed.
void checkRepeat(char word1[][MAX_WORD_LENGTH + 1], char word2[][MAX_WORD_LENGTH + 1], int separation[], int& nPatterns) {
	for (int i = 0; i < nPatterns; i++)
	{
		char temp1[MAX_WORD_LENGTH + 1];
		char temp2[MAX_WORD_LENGTH + 1];
		strcpy(temp1, word1[i]);
		strcpy(temp2, word2[i]);
		for (int j = i + 1; j < nPatterns; j++)
		{
			if ((strcmp(temp1, word1[j]) == 0 && strcmp(temp2, word2[j]) == 0) 
				|| (strcmp(temp2,word1[j]) == 0 && strcmp(temp1,word2[j]) == 0))
			{
				//in case separation value is the same, the first matching element is removed.
				if (separation[i] <= separation[j]) 
				{
					removeElement(word1, word2, separation, nPatterns, i);
				}
				else 
				{
					removeElement(word1, word2, separation, nPatterns, j);
				}
				i--;
				continue;
			}
		}

	}
}  

//modifies cstring into proper form to be rated.
//returns 0 if nPatterns is zero or less
//otherwise returns the number of proper patterns in the string.
int makeProper(char word1[][MAX_WORD_LENGTH + 1], char word2[][MAX_WORD_LENGTH + 1], int separation[], int nPatterns)
{
	if (nPatterns <= 0)
		return 0;
	
	for (int i = 0; i < nPatterns; i++) {
		bool end1 = false;
		bool end2 = false;
		bool removed = false;
		for (int j = 0; (!end1 || !end2) && i>= 0 && !removed; j++) {

			if (word1[i][j] == '\0') {
				end1 = true;
			}
			if (word2[i][j] == '\0') {
				end2 = true;
			}
			if (i >= 0 && separation[i] < 0) {
				removeElement(word1, word2, separation, nPatterns, i);
				i--;
				removed = true;
				continue;
			}
			if (!end1 && !isalpha(word1[i][j])) 
			{
				removeElement(word1, word2, separation, nPatterns, i);
					removed = true;
					i--;
					continue;
			}
			if (!end2 && !isalpha(word2[i][j])) {
				removeElement(word1, word2, separation, nPatterns, i);
					removed = true;
					i--;
					continue;
			}
			if (!end1 && isupper(word1[i][j])) {
				word1[i][j] = tolower(word1[i][j]);
			}
			if (!end2 && isupper(word2[i][j])) {
				word2[i][j] = tolower(word2[i][j]);
			}
		}
	}
	checkRepeat(word1, word2, separation, nPatterns);
	return nPatterns;
}



//removes all non alphabetical characters from the duplicate document
//makes all letters in document lowercase
void cleanText(char editDocument []) {
	char * split = strtok(editDocument, "-!?.,#$%@^&*()1234567890/;:'`+=\"\\|");
	char cleanDocument [250]  = { '\0' };
	while (split != NULL) {
		strcat(cleanDocument, split);
		split = strtok(NULL, "-!?.,#$%@^&*()1234567890/;:'`+=\"\\|"); //splits string at non alphabetical characters
	}
	int n = 0;
	do {
		cleanDocument[n] = tolower(cleanDocument[n]);
		
			n++;
	} while (cleanDocument[n] != '\0');
	strcpy(editDocument, cleanDocument); //assigns new values to array that was passed in
		
}

//parameter: 2D array containing original document, array containing other word in pattern, separation array, 
//position in pattern of match, position in document of original match, number of words.
//return true if the other word in pattern exists in document array within separation bounds
//return false otherwise
bool findMatch (const char text [][MAX_WORD_LENGTH+1], const char nextWord[], const int separation [], int patternPos, int textPos, int numWords) {
		for (int i = textPos + 1; i <= textPos + separation[patternPos] + 1 && i < numWords; i++) {
			if (strcmp(text[i], nextWord) == 0) {
				return true;
			}
		}
	
	return false;
}

//return number of distinct matching patterns found within document
int rate(const char document[], const char word1[][MAX_WORD_LENGTH + 1], const char word2[][MAX_WORD_LENGTH + 1], const int separation[], int nPatterns) {
	if (nPatterns <= 0) {
		return 0;
	}
	const int MAX_DOCUMENT_LENGTH = 250;
	const int MAX_NO_OF_WORDS = MAX_DOCUMENT_LENGTH / 2;
	int nMatches = 0;
	int numWords = 1;

	//extract information from document and convert into a usable form
	char tempDocument[MAX_DOCUMENT_LENGTH + 1];
	strcpy(tempDocument, document);
	cleanText(tempDocument);
	//transfer contents of document into a 2D array
	char docFile[MAX_NO_OF_WORDS][MAX_WORD_LENGTH + 1]; 
	char * word = strtok(tempDocument, " ");
	for (int i = 0; word != NULL; i++) {
		strcpy(docFile[i], word);
		word = strtok(NULL, " ");
		numWords++;
	}

	
	//determine the number of matches
	for (int k = 0; k < nPatterns; k++) { 
		bool hasMatch = false;
		for (int n = 0; n < numWords && !hasMatch; n++) {
			if (strcmp(docFile[n], word1[k]) == 0) {
				if (findMatch(docFile, word2[k], separation, k, n, numWords)) {
					nMatches++;
					hasMatch = true;
				}
			}
			if (strcmp(docFile[n], word2[k]) == 0) {
			    if (findMatch(docFile, word1[k], separation, k, n, numWords)) {
					 nMatches++;
					 hasMatch = true;
				} 
			}
		}
	}
	return nMatches;
} 

int main() {
	char one_one[4][MAX_WORD_LENGTH + 1] = { "compare","thee","Thou","shake" };
	char one_two[4][MAX_WORD_LENGTH + 1] = { "Shall","summer's","lovely","Rough" };
	int one_num[4] = { 1,2,2,2 };

	assert(makeProper(one_one, one_two, one_num, 4) == 3 && strcmp(one_one[1], "thou") == 0);
	assert(rate("Shall I compare thee to a summer's day? Thou art more lovely and more temperate: Rough winds do shake the darling buds of May,", one_one, one_two, one_num, 3) == 3);
	cout << "checkpoint A1 passed" << endl;

	char two_one[4][MAX_WORD_LENGTH + 1] = { "lovely","darling","lease","May" };
	char two_two[4][MAX_WORD_LENGTH + 1] = { "temperate:","May","And","darling" };
	int two_num[4] = { 2,3,2,1 };

	assert(makeProper(two_one, two_two, two_num, 4) == 2 && strcmp(two_two[0], "may") == 0);
	assert(rate("Rough winds do shake the darling buds of May, And summer's lease hath all too short a date", two_one, two_two, two_num, 2) == 2);
	cout << "checkpoint A2 passed" << endl;

	char three_one[4][MAX_WORD_LENGTH + 1] = { "eye","often","dimm'd","Sometime" };
	char three_two[4][MAX_WORD_LENGTH + 1] = { "heaVen","complexion","gold","shines" };
	int three_num[4] = { 1, -3, 1, 5 };
	assert(makeProper(three_one, three_two, three_num, 4) == 2 && strcmp(three_one[1], "sometime") == 0);
	assert(rate("Sometime too hot the eye of heaven shines, And often is his gold complexion dimm'd", three_one, three_two, three_num, 2) == 1);
	cout << "checkpoint A3 passed" << endl;


	char four_one[4][MAX_WORD_LENGTH + 1] = { "fair", "declines", "chance", "untrimm'd" };
	char four_two[4][MAX_WORD_LENGTH + 1] = { "fair","from","course","or" };
	int four_num[4] = { 0, 1, 4, 2 };
	assert(makeProper(four_one,four_two,four_num, 4) == 3 && strcmp(four_two[3],"or") == 0);
	assert(rate("And every fair from fair sometime declines, By chance or nature's changing course untrimm'd", four_one, four_two, four_num, 3) == 1);
	cout << "checkpoint A4 passed" << endl;

	// Sonnet 18, Shakespeare



	char two_one_one[6][MAX_WORD_LENGTH + 1] = { "3.", "Christopher","cities","know","prime","prime" };
	char two_one_two[6][MAX_WORD_LENGTH + 1] = { "know","Boone","capitaL","prime","know","7057" };
	int two_one_num[6] = { 8,2,0,12,14,3 };
	assert(makeProper(two_one_one, two_one_two, two_one_num, 6) == 3 && two_one_num[2] == 14);
	assert(rate("3. My name is Christopher John Francis Boone. I know all the countries in the word and their capital cities and every prime number up to 7057. Eight years ago, when I first met Siobhan, she showed me this picture", two_one_one, two_one_two, two_one_num, 3) == 3);
	cout << "Checkpoint B1 passed" << endl;


	char two_two_one[5][MAX_WORD_LENGTH + 1] = { "take", "work", "simple", "formula", "codes" };
	char two_two_two[5][MAX_WORD_LENGTH + 1] = { "multiples", "numbers", "formula", "simple", "America" };
	int two_two_num[5] = { 6, 2, 0, 9, 5 };
	assert(makeProper(two_two_one, two_two_two, two_two_num, 5) == 4 && strcmp(two_two_two[3], "america") == 0);
	assert(rate("This is how you work out what prime numbers are. First you write down all the positive whole numbers in the world. Then you take away all the numbers that are multiples of 2. Then you take away all the numbers that are multiples of 3.",two_two_one, two_two_two, two_two_num, 4) == 1);
	cout << "Checkpoint B2 passed" << endl;

	char two_three_one[4][MAX_WORD_LENGTH + 1] = { "that", "M16", "$10,000", "digits" };
	char two_three_two[4][MAX_WORD_LENGTH + 1] = { "left", "computer", "they", "cIa" };
	int two_three_num[4] = { 3, 5, 5, 7 };
	assert(makeProper(two_three_one, two_three_two, two_three_num, 4) == 2);
	assert(rate("but no one has ever worked out a simple formula for telling you whether a very big number is a prime number or what the next one will be. If a number is really, really big, it can take a computer years to work out whether it is a prime number.", two_three_one, two_three_two, two_three_num, 2) == 0);
	cout << "Checkpoint B3 passed" << endl;

	char two_four_one[4][MAX_WORD_LENGTH + 1] = { "down", "all", "multiples", "You" };
	char two_four_two[4][MAX_WORD_LENGTH + 1] = { "First", "pos", "delta", "This" };
	int two_four_num[4] = { 2, 4, 5, 6 };
	makeProper(two_four_one, two_four_two, two_four_num, 4);
	assert(rate("This is how you work out what prime numbers are. First you write down all the positive whole numbers in the world. Then you take away all the numbers that are multiples of 2. Then you take away all the numbers that are multiples of 3.", two_four_one, two_four_two, two_four_num, 4) == 2);
	cout << "Checkpoint B4 passed" << endl;  


	char three_one_one[5][MAX_WORD_LENGTH + 1] = { "gr8", "Alvin", "acorn", "nIghTMaRe", "wAkAndA" };
	char three_one_two[5][MAX_WORD_LENGTH + 1] = { "cheese", "ChipMunKs", "tL;Dr", "sErEndipiTy", "T'Challa" };
	int three_one_num[5] = { 5, 8, 12, 7, 5 };
	assert(makeProper(three_one_one, three_one_two, three_one_num, 5) == 2 && strcmp(three_one_two[0], "chipmunks") == 0 && strcmp(three_one_one[1], "nightmare") == 0);
	cout << "Checkpoint C1 passed" << endl;

    char three_two_one[9][MAX_WORD_LENGTH + 1] = { "(estuary)", "verdant", "magenta", "KenTUCKY", ":rational", "curmudgeon", "SalaciOus", "StromATOLITE", "FrOST" };
	char three_two_two[9][MAX_WORD_LENGTH + 1] = { "codename", "elk", "venison", "MilkShake", "aloof", "recalcitrant", "SaVoRY", "ENDoPhile", "Jean-Luc" };
	int three_two_num[9] = { 5, 8, 12, 7, 5, 4, 7, -5, 3 };
	assert(makeProper(three_two_one, three_two_two, three_two_num, 9) == 5 && strcmp(three_two_one[4], "salacious") == 0);
	cout << "Checkpoint C2 passed" << endl;

	char three_three_one[5][MAX_WORD_LENGTH + 1] = { "$100", "panda", "*snorts*", "@rye.sun", "elephant"};
	char three_three_two[5][MAX_WORD_LENGTH + 1] = { "meow", "wo!f", "excalibur", "BORK!", "^_^" };
	int three_three_num[5] = { 2, 3, 4, 1, 2 };
	assert(makeProper(three_three_one, three_three_two, three_three_num, 5) == 0);
	assert(rate("Once upon a time and a very good time it was there was a moocow coming down along the road and this moocow that was coming down along the road met a nicens little boy named baby tuckoo.", three_three_one, three_three_two, three_three_num, 0) == 0);
	cout << "Checkpoint C3 passed" << endl;

	char three_four_one[6][MAX_WORD_LENGTH + 1] = { "daisy", "lilac", "lavender", "dahlia", "fern", "poppy" };
	char three_four_two[6][MAX_WORD_LENGTH + 1] = { "dahlia", "poppy", "fern", "daisy", "lavender", "lilac" };
	int three_four_num[6] = { 1, 3, 4, 2, 3, 3 };
	assert(makeProper(three_four_one, three_four_two, three_four_num, 6) == 3);
	assert(three_four_num[0] == 4 && three_four_num[1] == 2 && three_four_num[2] == 3);
	cout << "Checkpoint C4 passed" << endl;

	char four_one_one[6][MAX_WORD_LENGTH + 1] = { "jovial", "duck", "infamy", "fission", "science", "PhD"};
	char four_one_two[6][MAX_WORD_LENGTH + 1] = { "jocular", "hatter", "mincemeat", "duck", "success", "risk" };
	int four_one_three[6] = {1, 10, 7, 3, 12, 2};
	makeProper(four_one_one, four_one_two, four_one_three, 6);
	assert(rate("Repost Duck, PhD., lives on in infamy for his success in fissioning a magnet made of buckminsterfullerenes. The jovial duck made science headlines.", four_one_one, four_one_two, four_one_three, 6) == 1);

	assert(rate("mz0ABjzSe4zjlslzxJh2ycEdZLhVFlAC41BjWf2mw2ofJDh6kkJH4wzcrNp1joSQldL6KJE07ri7veynHDLHL4KQ8nivkFnQwJxuHc1mmBP6vJmGpn8bALzbsIepS4xZlzkvcgDiTXLan41XMVNEwSYORqXkBJidbgXir0wuXLAcmuDGxfP07oO9tA8SijahxK2gsEKRgPWLCurIeYk12mZTLoaCbXcU2EuqtExnDZv2C9VEhNt8zYIblu", four_one_one, four_one_two, four_one_three, 6) == 0);
	cout << "Congrats, you somehow didn't break anything!" << endl;
	cout << "all tests clear"; 


}