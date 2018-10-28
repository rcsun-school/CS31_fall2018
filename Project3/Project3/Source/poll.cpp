
//Ryan Sun 305109611 CS31 Smallberg
//Interprets a poll string and calculates the number of congressional seats 
//a political party wins in one or more states.

#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
#include <cmath>
using namespace std; 

// Return true if the argument is a two-uppercase-letter state code, or
// false otherwise.

bool isValidUppercaseStateCode(string stateCode)
{
	const string codes =
		"AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
		"LA.ME.MD.MA.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
		"OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
	return (stateCode.size() == 2 &&
		stateCode.find('.') == string::npos  &&  // no '.' in stateCode
		codes.find(stateCode) != string::npos);  // match found
}

//Returns true if a poll string contains invalid characters, false otherwise
bool hasInvalidCharacters(string s) {
	if (s == "") {
		return false;
	}
	for (int i = 0; i != s.size(); i++)
	{
		if (isalpha(s[i]) || isdigit(s[i]))
		{
			continue;
		}
		else if (s[i] == ',')
		{
			if (i == s.size() - 1) {
				return true;
			}
			else if (i == 0) {
				return true;
			}
			else 
			continue;
		}
		else
		{
			return true;
		}
	}
	return false;
}

bool hasProperPollResult(string pollData) {
	if (pollData == "") {
		return true;
	}
	for (int i = 1; i != pollData.size(); i++) {
		if (isalpha(pollData[i]) && (i == pollData.size() - 1 || pollData[i + 1] == ',' || (!isalpha(pollData[i - 1]) && !isalpha(pollData[i + 1]))))
		{
			int j = i - 1;
			int countDigits = 0;
			while (isdigit(pollData[j])) //interpret party result
			{
				countDigits++;
				j--;
			}
			if (countDigits > 2)
				return false;
		}
	}
	return true;
}
 
//Returns true if a poll string is written with proper syntax
//false otherwise
bool hasProperSyntax(string pollData) { //debugged
	if (hasInvalidCharacters(pollData)) {
		return false;
	}
	if (pollData.size() == 1) {
		return false;
	}
		int i = 0;
		string pollForecast = "";
		string stateCode;
		while (i != pollData.size()) { //verifies state codes within poll string
			if (pollData[i] == ',' || i == pollData.size() - 1) {
				pollForecast += pollData[i];
				stateCode = char(toupper(pollForecast[0])); 
				stateCode += char(toupper(pollForecast[1])); 
				if (!isValidUppercaseStateCode((stateCode))) {
					return false;
				}
				else {
					pollForecast == "";
				}
			}
			else {
				pollForecast += pollData[i];
			}
			i++;
		}
		if (!hasProperPollResult(pollData)) {
			return false;
		}
		return true;
}

//Calculates the number of congressional seats won by a party
//Return 1 if poll string does not have proper syntax
//Return 2 if party is not a letter
//Return 0 if otherwise
int tallySeats(string pollData, char party, int& seatTally) {
	const char zero = '0';
	if (!hasProperSyntax(pollData)) {
		return 1;
		}
	if (!isalpha(party)) {
		return 2;
	}
	for (int i = 2; i != pollData.size(); i++) {
		if (toupper(pollData[i]) == toupper(party) && (i == pollData.size()-1 || pollData[i+1] == ',' || (!isalpha(pollData[i-1]) && !isalpha(pollData[i+1])))) 
		{
			int readNumber = 0;
			int j = i-1;
			int power = 0;
			if (isdigit(pollData[i - 2])) {
				readNumber += ((pollData[i-2] - zero) * 10) + (pollData[i-1]-zero);
			}
			else {
				readNumber += pollData[i-1] - zero;
			}
			seatTally += readNumber; 
			//conversion from double to int may cause mathematical inaccuracy 

		}
		else {
			continue;
		}
	
	
	}



	return 0;
}




int main() {
	/*string pollData;
	char party;
	int startingNum = -888;
	cout << "Enter poll data.";
	getline(cin, pollData);
	cout << "Which party?";
	cin >> party;
	tallySeats(pollData, party, startingNum);
	cout << startingNum; */

	assert(hasProperSyntax("Ny23D8R"));
	cout << "Test 1.1 passed" << endl;
	assert(!hasProperSyntax("HA5D9R"));
	cout << "Test 1.2 passed" << endl;
	assert(!hasProperSyntax("CA 5D"));
	cout << "Test 1.3 passed" << endl;
	assert(hasProperSyntax(""));
	cout << "Test 1.4 passed" << endl;
	assert(!hasProperSyntax("24R2D,VT23"));
	cout << "Test 1.5 passed" << endl;
	assert(hasProperSyntax("VT"));
	cout << "Test 1.6 passed" << endl;
	assert(hasProperSyntax("CA5D,TX9R,CT9I"));
	cout << "Test 1.7 passed" << endl;
	assert(hasProperSyntax("ny6R,cA8D,Mn9d"));
	cout << "Test 1.8 passed" << endl;
	assert(hasProperSyntax("aR9d7I,Vt,mA,va,Ia8d7R5e"));
	cout << "Test 1.9 passed" << endl;
	assert(!hasProperSyntax("Red Wave"));
	cout << "Test 1.10 passed" << endl;
	assert(!hasProperSyntax("CA,"));
	cout << "Test 1.11 passed" << endl;
	assert(!hasProperSyntax("N"));
	cout << "Test 1.12 passed" << endl;
	assert(!hasProperSyntax("ca2310D"));
	cout << "Test 1.13 passed" << endl;
	cout << "CHECKPOINT 1 PASSED" << endl; 
	int startSeat = 0;
	assert(tallySeats("24R2D,VT23", 'D', startSeat) == 1 && startSeat == 0);
	cout << "Test 2.1 passed" << endl;
	assert(tallySeats("Ca23D VT9R",'D', startSeat) == 1 && startSeat == 0);
	cout << "Test 2.2 passed" << endl;
	assert(tallySeats("ca23D8R,Vt12I32R", '!', startSeat) == 2 && startSeat == 0);
	cout << "Test 2.3 passed" << endl;
	assert(tallySeats("Ri12R", 'R', startSeat) == 0 && startSeat == 12);
	startSeat = 0;
	cout << "Test 2.4 passed" << endl;
	assert(tallySeats("Pa12D3R,ma9D10R", 'D', startSeat) == 0 && startSeat == 21);
	cout << "Test 2.5 passed" << endl;
	startSeat = 0;
	assert(tallySeats("Wy12R", '2', startSeat) == 2 && startSeat == 0);
	cout << "Test 2.6 passed" << endl;
	assert(tallySeats("Ca123D7R,Vt23R9D", 'D', startSeat) == 1 && startSeat == 0);
	cout << "Test 2.7 passed" << endl;
	assert(tallySeats("Ca53D0R,Or7D2I2R,wA6i9R20d", 'i', startSeat) == 0 && startSeat == 8);
	cout << "Test 2.8 passed" << endl;
	int s = -888;
	assert(tallySeats("Ca23D34R,iA33r9D,wy23D9R", 'R', s) == 0 && s == -812);
	cout << "Test 2.9 passed" << endl;
	cout << "All tests clear"; 
	

}