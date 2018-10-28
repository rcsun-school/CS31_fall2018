//Ryan Sun CS31 Smallberg fall 2018
//program receives user input from console to calculate a customer's charge from "Yentl's Rentals"


#include <iostream>
#include <string>
using namespace std;

int main()
{
	//variables used to describe rates in calculating rental cost
	int luxRate = 61;
	int nonLuxRate = 33;
	double normMileageRate = 0.27;
	double winterRate = 0.27;
	double nonWinterRate = 0.21;
	double addRate = 0.21; //rate for every mile over 400
	int firstTier = 100; //variable used to contain the first capstone mileage when calculating cost
	int secondTier = 400; //variable used to contain the second capstone mileage when calculating cost

	//print dialogue on console, take in user input
	cout.setf(ios::fixed);
	cout.precision(2);
	cout << "Odometer at the start: ";
	int startOdometer;
	cin >> startOdometer;
	cout << "Odometer at the end: ";
	int endOdometer;
	cin >> endOdometer;
	cout << "Rental days: ";
	int rentalDays;
	cin >> rentalDays;
	cin.ignore(10000, '\n');
	cout << "Customer name: ";
	string clientName;
	std::getline(cin, clientName);
	cout << "Luxury car? (y/n): ";
	string luxuryCar;
	std::getline(cin,luxuryCar);
	cout << "Month (1=Jan, 2=Feb, etc.): ";
	int month;
	cin >> month;
	cout << "---" << endl;

	//evaluating appropriate final message
	double totalCharge = 0;
	int mileage = endOdometer - startOdometer;
	if (startOdometer < 0)
	{
		cout << "The starting odometer reading must be nonnegative.";
	}
	else if (mileage < 0)
	{
		cout << "The final odometer reading must be at least as large as the starting reading.";
	}
	else if (rentalDays <= 0)
	{
		cout << "The number of rental days must be positive.";
	}
	else if (clientName == "")
	{
		cout << "You must enter a customer name.";
	}
	else if (luxuryCar != "y" && luxuryCar != "n")
	{
		cout << "You must enter y or n.";
	}
	else if (month < 1 || month > 12)
	{
		cout << "The month number must be in the range 1 through 12.";
	}
	else
	{
		//calculating final cost
		if (luxuryCar == "y")
		{
			totalCharge += rentalDays * luxRate;
		}
		if (luxuryCar == "n")
		{
			totalCharge += rentalDays * nonLuxRate;
		}

		if (mileage < firstTier)
		{
			totalCharge += mileage * normMileageRate;
		}

		else if (mileage > firstTier && mileage < secondTier) {
			mileage -= firstTier;
			totalCharge += firstTier * normMileageRate;
			if (month == 12 || (month >= 1 && month <= 3)) {
				totalCharge += mileage * winterRate;
			}
			else {
				totalCharge += mileage * nonWinterRate;
			}
		}
		else {
			mileage -= secondTier;
			totalCharge += firstTier * normMileageRate;
			if (month == 12 || (month >= 1 && month <= 3)) {
				totalCharge += (secondTier-firstTier) * winterRate;
			}
			else {
				totalCharge += (secondTier-firstTier) * nonWinterRate;
			}
			totalCharge += mileage * addRate;
		}
		cout << "The rental charge for " << clientName << " is $" << totalCharge;
	}
	return 1;
}