#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int dollarDigits(double);
double newPrincipal(double principal, double rate, int years, int terms);

/* This program asks for the principal, the interest rate, and the number of
 * times the interest is compounded then displays the balance for the next
 * five years in a nice report.
 */
int main() {
    const int COL1_WIDTH = 30;
    const int COL2_WIDTH = 15;
    double principal;
    double interest_rate; // a percentage
    double balance = 0;
    int compounding_terms; // per period (1 year)

    // Ask user for information
    cout << "What is the interest rate? (i.e the percentage) ";
    cin >> interest_rate;
    cout << "How many times compounded per year? ";
    cin >> compounding_terms;
    cout << "What is the principal amount? ";
    cin >> principal;
    cout << endl << endl; // add a nice gap from report

    // Report: include user given values
    cout << setprecision(2) << fixed;
    cout << setw(COL1_WIDTH) << left << "Interest Rate"
         << setw(COL2_WIDTH-1) << right << interest_rate << "%" // offset by 1
         << endl;
    cout << setw(COL1_WIDTH) << left << "Times Compounded"
         << setw(COL2_WIDTH) << right << compounding_terms
         << endl;
    cout << setw(COL1_WIDTH) << left << "Principal"
         << setw(COL2_WIDTH - dollarDigits(principal)) << right << "$ "
         << setw(dollarDigits(principal)) << right << principal
         << endl;

    // Report: print out for each year
    for (int year = 1; year <= 5; year++) {
        balance = newPrincipal(principal, interest_rate, year, compounding_terms);
        cout << setw(19) << left << "Balance after year "
             << setw(COL1_WIDTH-19) << left << year
             << setw(COL2_WIDTH - dollarDigits(balance)) << right << "$ "
             << setw(dollarDigits(balance)) << balance
             << endl;
    }

    return 0;
}

/* Calculates a new principal from a previous one
 */
double newPrincipal(double principal, double rate, int years, int terms) {
    return principal * pow(1 + (rate/100)/terms, terms * years);
}

/* Takes a double and returns the number of digits to represent in dollars.
 * Useful for calulating necessary column width when fromatting reports.
 */
int dollarDigits(double amount) {
    int digits = 0;
    int no_cents = (int) amount; // coerce to an int to remove decimals
    while (no_cents) {
        no_cents /= 10;
        digits++;
    }
    // add 3 to account for .00
    return digits+3;
}
