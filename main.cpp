/* File Name: main.cpp
 * Authors: Dominc Renda and Shaun Butterfield
 * This program calculates and displays a table for a loan. Determining number of months required to repay loan and total interest paid
 */

#include <iostream>
//added headers to support invalid argument and stod
#include <stdexcept>
#include <string>

using namespace std;

//pass in space-delimited arguments when you call the executable
//Example: ./a.out 1 2 3.3
int main(int argc, char * argv[])
{
	if (argc > 4) 
	{
		cout << "Too many arguments. Cannot pass in more than three." << endl;
		return -1;
	}

	int i = 1;
	double loan_amount, yearly_interest_rate, monthly_payment;

	// added preset values to array to potentially avoid errors with missing values - Shaun
	double arguments [3] = {0, 0, 0};

	if (argc > 1)
	{
		while ( i < argc )
		{

			try
			{
				arguments[i-1] = stod(argv[i]);
			}
			catch(const std::invalid_argument&)
			{
				if(i==1)
					cout << "(Invalid loan amount): " << argv[i] << endl;
				else if (i==2)
					cout << "(Invalid interest rate): " << argv[i-1] << " " << argv[i] << endl;
				else
					cout << "(Invalid payment): " << argv[i-2] << " " << argv[i-1] << " " << argv[i] << endl;
				return -2;
			}
			i++;
		}
	}

	

	loan_amount = arguments[0];
	yearly_interest_rate = arguments[1];
	monthly_payment = arguments[2];

	// Shaun Butterfield
	// handles any loan amount less than or equal to 0 (return -2 ends main immediately stopping program because of invalid input)
	if (loan_amount <= 0)
		{ cout << "Invalid loan amount." << endl;
		 return -2;
		}

	// handles interest rate checks if less than 0
	if (yearly_interest_rate < 0)
		{
		cout << "Invalid interest rate." << endl;
		return -2;
		}

	// prevents infinite loop from a 0 or less payment
	if (monthly_payment <= 0)
		{ cout << "Invalid monthly payment." << endl;
		 return -2;
		}

	// calculations for month, makes it easier for follow on lines and prevents redundency errors
	double monthly_interest_rate = yearly_interest_rate / 12;
	double monthly_decimal_rate = monthly_interest_rate / 100;

	// check payment
	double first_month_interest = loan_amount * monthly_decimal_rate;
	
	// ensures balance can decrease
	if (monthly_payment <= first_month_interest)
		{ cout << "Insufficient payment." << endl;
		 return -2;
		}

	// displays the values passed in through the command line - Dominic
	cout << "Loan Amount: " << loan_amount << endl;
	cout << "Interest Rate (% per year): " << yearly_interest_rate << endl;
	cout << "Monthly Payments: " << monthly_payment << endl;
	cout << endl;
	
	//makes so dollar amounts print with 2 decimal places
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);

	//initialize variables for the table
	int currentMonth = 0;
	double interestTotal = 0;
	
	//initializes table with the headers: month, balance, payment, interest rate, principle
	cout << "************************************************************\n"
     << "\tAmortization Table\n"
     << "************************************************************\n"
     << "Month\tBalance\t\tPayment\tRate\tInterest\tPrincipal\n";

	//required start at month 0
	cout << currentMonth << "\t$" << loan_amount;
	if (loan_amount < 1000)
		{ cout << "\t";
		}
	cout << "\tN/A\tN/A\tN/A\t\tN/A\n"; //same N/A format as in the hint
	++currentMonth;

	//initalize interest, principal, payment
	double interest;
	double principal;
	double payment;

	//calculation loop
	while (loan_amount > 0)
		{ interest = loan_amount * monthly_decimal_rate;
		 payment = monthly_payment;
	//handles final month payment
		 if (loan_amount + interest < payment)
		 	{
				payment = loan_amount + interest;
				principal = loan_amount;
				loan_amount = 0;
			}
	//normal months
		 else
		 	{
				principal = payment - interest;
				loan_amount -= principal;
			}

		 interestTotal += interest;
	// prints one row: remain balance, act payment, month perc rate, int, and princ
		 cout << currentMonth << "\t$" << loan_amount;
		 if (loan_amount < 1000)
		 	{
				cout << "\t";
			}
		 cout << "\t$" << payment
			  << "\t" << monthly_interest_rate
			  << "\t$" << interest
			  << "\t$" << principal << endl;
		 ++currentMonth;
		}

	int numberOfMonths = currentMonth - 1;
	// finish off table and formatting
	cout << "************************************************************\n";
	cout << "\nIt takes " << numberOfMonths << " month";
	//gramatical for when month is supposed to be months
	if (numberOfMonths != 1)
		{
			cout << "s";
		}

	cout << " to pay off the loan.\n" << "Total interest paid is: $" << interestTotal << endl << endl;

	return 0;
}
