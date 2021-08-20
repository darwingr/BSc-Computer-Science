#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

/* Takes a positive integer and returns the number of digits.
 */
int countDigits(int number) {
    int digits = 0;
    while (number) {
        number /= 10;
        digits++;
    }
    return digits;
}

/* Prints out a report of a theater's gross and net box office profit for a
 * night. Asks for the name of the movie, and how many adult and child tickets
 * were sold.
 */
int main() {
    const int ADULT_TICKET_PRICE = 600; // in cents
    const int CHILD_TICKET_PRICE = 300; // in cents
    const double DISTRIBUTOR_COMMISION_RATE = 80; // a percentage
    const int COL1_WIDTH = 36;
    string movie_name = "";
    int adult_tickets_sold;
    int child_tickets_sold;
    int gross_bo_profit; // in cents
    double net_bo_profit; // in cents
    double distributor_commision; // in cents

    cout << "What movie? ";
    getline(cin, movie_name); // movie name could contain spaces
    cout << "Adult tickets sold = ";
    cin >> adult_tickets_sold;
    cout << "Child tickets sold = ";
    cin >> child_tickets_sold;
    cout << endl;

    // Calculate box office profit, in cents
    gross_bo_profit = adult_tickets_sold * ADULT_TICKET_PRICE
                    + child_tickets_sold * CHILD_TICKET_PRICE;
    net_bo_profit = ((100 - DISTRIBUTOR_COMMISION_RATE) * gross_bo_profit)/100;

    // Calculate amount paid to distributor, in cents
    distributor_commision = gross_bo_profit - net_bo_profit;

    // We want to pad left so the dollar amounts line up nicely.
    // and gross_bo_profit is the largest $ amount being outputted
    int currency_pad = countDigits(gross_bo_profit) + 1;
    // Report table
    cout << setprecision(2) << fixed; // will also do rounding
    cout << setw(COL1_WIDTH) << left
         << "Movie Name:" << movie_name << endl;
    cout << setw(COL1_WIDTH) << left
         << "Adult Tickets Sold:" << "    " <<  adult_tickets_sold << endl;
    cout << setw(COL1_WIDTH) << left
         << "Child Tickets Sold:" << "    " << child_tickets_sold << endl;
    cout << setw(COL1_WIDTH) << left << "Gross Box Office Profit:" << "$ "
         << setw(currency_pad) << right << gross_bo_profit/100. << endl;
    cout << setw(COL1_WIDTH) << left << "Net Box Office Profit:" << "$ "
         << setw(currency_pad) << right << net_bo_profit/100. << endl;
    cout << setw(COL1_WIDTH) << left << "Amount Paid to Distributor:" << "$ "
         << setw(currency_pad) << right << distributor_commision/100. << endl;

    return 0;
}
