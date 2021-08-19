/* Filename: main.cpp
 * ------------------
 * Class:   CSCI 162 -- Assignment 2
 * Date:    Feb 13th, 2018
 * Author:  Darwin Jacob Groskleg
 *
 * Purpose: to produce an updated set of account balances, a statement of the
 * months transactions for each account and report on accounts with very high
 * or low balances at the end of the month. This is all done from a set of
 * account balances and a set of transactions for the month.
 *
 * Sample Ouput:
 * ----------------------------------------------------------------------------
 * ABNORMAL ACCOUNTS REPORT (below $0 or above $10k)
 * CNum Name                  Amount
 * ---- -------------  -------------
 * 6239 R. Pat Turner  $    10230.12
 * 6543 Patrick Riley  $    11219.78
 * 7654 Tom T. Peters  $      -20.33
 * ----------------------------------------------------------------------------
 *
 * Sample balanceout.txt
 * ----------------------------------------------------------------------------
 * 1123 John T. Smith  $       98.73
 * 1456 Daniel Smith   $      245.83
 * 2416 Shannon Ross   $     1250.12
 * 2468 Betty White    $     1928.24
 * 2832 Timothy Adams  $     2606.27
 * 3893 Barney Kent    $      630.82
 * 4444 Steve Burns    $     5837.29
 * 5426 Melissa Black  $     3869.92
 * 5555 Fred G. Jones  $        0.00
 * 6239 R. Pat Turner  $    10230.12
 * 6543 Patrick Riley  $    11219.78
 * 6847 Patrick Blair  $      384.82
 * 6983 Henry Presley  $      340.99
 * 7654 Tom T. Peters  $      -20.33
 * 7736 Sara Wilson    $     9993.28
 * 8762 Julie Anderson $     1684.23
 * 8764 Jessica Stone  $        1.00
 * 8975 Lisa Gregory   $     1938.83
 * 9324 Andrew York    $        0.98
 * 9876 Jane Grant     $     1837.45
 * ----------------------------------------------------------------------------
 *
 * Sample statementout.txt
 * ----------------------------------------------------------------------------
 *            First Antigonish Bank
 *
 * Statement for  John T. Smith  
 * Customer Number 1123
 *
 * Item               Deposit   Withdrawl    Balance
 * -----------        -------   ---------   --------
 * Starting Balance:                           28.28
 *
 *  Cheque                          30.00      -1.72
 *  Overdraft                        5.00      -6.72
 *  Deposit              2.00                  -4.72
 *  Overdraft                        5.00      -9.72
 *  Payroll           1213.45                1203.73
 *  Withdrawl                      500.00     703.73
 *  Cheque                         800.00     -96.27
 *  Overdraft                        5.00    -101.27
 *  No Bk Dep          200.00                  98.73
 *
 * Final Balance:                              98.73
 *
 *
 *            First Antigonish Bank
 *
 * Statement for  Daniel Smith   
 * Customer Number 1456
 *
 * Item               Deposit   Withdrawl    Balance
 * -----------        -------   ---------   --------
 * Starting Balance:                          245.83
 *
 *
 * Final Balance:                             245.83
 *
 *
 *            First Antigonish Bank
 *
 * Statement for  Shannon Ross   
 * Customer Number 2416
 *
 * Item               Deposit   Withdrawl    Balance
 * -----------        -------   ---------   --------
 * Starting Balance:                         1248.34
 *
 *  Deposit            389.89                1638.23
 *  Withdrawl                      388.11    1250.12
 *
 * Final Balance:                            1250.12
 * ----------------------------------------------------------------------------
 */
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct balanceT {
    int customer_number;
    string customer_name;
    int amount;     // in cents
};

struct transactionT {
    int customer_number;
    string memo;
    int amount;     // in cents
};

bool ReadBalanceRecord(ifstream &, balanceT &);
bool ReadTransactionRecord(ifstream &, transactionT &);
void WriteInDollars(ostream &, int , bool endline=true, int dollarw=8);
void DisplayBalanceRecord(balanceT);
void WriteBalanceRecord(ofstream &, balanceT);
bool WriteStatement(ofstream &, balanceT &);
void WriteStatementTransaction(ofstream &, transactionT);

int main() {
    balanceT b;
    ifstream balances("data/balance.txt");
    ofstream statementout("statementout.txt");
    ofstream balanceout("balanceout.txt");

    if (balances.fail()) {
        cout << "ERROR: can't open file balance.txt" << endl;
        return -1;
    }
    if (statementout.fail()) {
        cout << "ERROR: can't open file statementout.txt" << endl;
        return -1;
    }
    if (balanceout.fail()) {
        cout << "ERROR: can't open file balanceout.txt" << endl;
        return -1;
    }

    // Report Header for task #5
    cout << "ABNORMAL ACCOUNTS REPORT (below $0 or above $10k)\n"
         << "CNum Name                  Amount\n"
         << "---- -------------  -------------"
         << endl;
    while (ReadBalanceRecord(balances, b)) {
        // Task #7
        if (!WriteStatement(statementout, b)) return -1;
        // Task #5 less than 0 or more than $1,000.00
        if (b.amount < 0 || b.amount > 1000000) DisplayBalanceRecord(b);
        // Task #6
        WriteBalanceRecord(balanceout, b);
    }

    balances.close();
    statementout.close();
    balanceout.close();


    return 0;
}

/* Function: WriteStatement
 * Usage: if (WriteStatement(stmt, bal)) return -1;
 * Side Effects: value of balance struct argument points to is updated.
 * --------------------------------------------------------------------
 * Writes the statement for a single customer, given their balance, to a file.
 * If the transactions file can't be accessed or fails the function returns
 * false.
 * Fulfills task #7 on the assignment.
 */
bool WriteStatement(ofstream &outfile, balanceT &b) {
    transactionT t;
    ifstream transactions("data/trans.txt");

    if (transactions.fail()) {
        cout << "ERROR: can't open file trans.txt" << endl;
        return false;
    }

    // Statement Header
    outfile << setw(34) << "First Antigonish Bank\n\n"
        << "Statement for  " << b.customer_name << "\n"
        << "Customer Number " << b.customer_number << "\n\n"
        << "Item               Deposit   Withdrawl    Balance\n"
        << "-----------        -------   ---------   --------\n"
        << left << setw(38) << "Starting Balance: " << right;
    WriteInDollars(outfile, b.amount);
    outfile << endl;
    while (ReadTransactionRecord(transactions, t)) {
        if (t.customer_number == b.customer_number) {
            WriteStatementTransaction(outfile, t);
            b.amount += t.amount;
            // print balance in right column
            WriteInDollars(outfile, b.amount);
            // Task #4
            if (b.amount < 0) {
                transactionT od = { b.customer_number, "Overdraft", -500 };
                WriteStatementTransaction(outfile, od);
                b.amount += od.amount;
                // print balance in right col
                WriteInDollars(outfile, b.amount);
            }
        }
    }
    transactions.close();
    outfile << left << setw(39) << "\nFinal Balance: " << right;
    WriteInDollars(outfile, b.amount);
    outfile << endl << endl;

    return true;
}

/* Function: WriteInDollars
 * Usage: WriteInDollars(cout, 10000);
 * Defaults: endline=true, dollarw=8
 * ---------------------------------
 * Given a number of cents, writes the dollar representation to some ostream
 * (i.e. cout or ofstream). By default it always follows up with an endline
 * and uses 8 characters to represent dollar digits (11 total), which is needed
 * for numbers up to 99,999,999.99 .
 */
void WriteInDollars(ostream &outstr, int cents, bool endline, int dollarw) {
    outstr << right << setw(dollarw) << (cents / 100) << '.'
           << setfill('0') << setw(2) << abs(cents % 100)
           << setfill(' ');
    if (endline) outstr << endl;
}

/* Function: ReadTransactionRecord
 * Usage: while(ReadTransactionRecord(trans, t)
 *          { do something with t; }
 * Side Effects: value of transaction struct pointed to in arguments is changed.
 * ----------------------------------------------------------------------------
 * This function read transaction records from a file and assigns the values to
 * the proper attributes of a struct. If it fails to read from file it returns
 * false.
 * Fulfills task #2 from assignment.
 */
bool ReadTransactionRecord(ifstream &infile, transactionT &t) {
    string dollars;
    char c;

    if (infile >> t.customer_number) {
        infile.get(c);  // get rid of singe space
        getline(infile, t.memo, '$');

        getline(infile, dollars, '.');
        infile >> t.amount;
        t.amount += stoi(dollars) * 100;

        return true;
    }
    return false;
}

/* Function: WriteBalanceRecord
 * Usage: WriteBalanceRecord(balanceout, balance);
 * -----------------------------------------------
 * Takes a balance record and writes it to a file that stores balance records.
 * Fulfills task #6 from assignment.
 */
void WriteBalanceRecord(ofstream &outfile, balanceT b) {
    outfile << left << setw(5) << b.customer_number
            << setw(15) << b.customer_name
            << "$ ";
    WriteInDollars(outfile, b.amount);
}

/* Function: WriteStatementTransaction
 * Usage: WriteStatementTransaction(statementfile, trans);
 * -------------------------------------------------------
 * Takes a transaction record and writes it to a statement file, placing the
 * amount in the appropriate column depending on whether it's a withdrawal
 * or a deposit.
 * Fulfills the intention of task #3 on the assignment.
 */
void WriteStatementTransaction(ofstream &outfile, transactionT t) {
    int col_width = 4, tail_width = 12;
    if (t.amount < 0) {     // write in separate col if withdrawal
        col_width += tail_width;
        tail_width = 0;
    }

    outfile << left << ' '
            << setw(18) << t.memo
            << right << setw(col_width) << abs(t.amount / 100) << '.'
            << setfill('0') << setw(2) << abs(t.amount % 100)
            << setfill(' ') << setw(tail_width) << "";
}

/* Function: ReadBalanceRecord
 * Usage: while (ReadBalanceRecord(balancefile, b) { do something with b; }
 * Side Effects: value of balance struct pointed to in arguments is changed.
 * ---------------------
 * This function read balance records from a file and assigns the values to
 * the proper attributes of a struct. If it fails to read from file it returns
 * false.
 * Fulfills task #2 on assignment.
 */
bool ReadBalanceRecord(ifstream &infile, balanceT &b) {
    string dollars;
    char c;

    if (infile >> b.customer_number) {
        infile.get(c);    // get rid of single space
        getline(infile, b.customer_name, '$'); // leaves trailing whitespace

        getline(infile, dollars, '.');
        infile >> b.amount;
        b.amount += stoi(dollars) * 100;

        return true;
    }
    return false;
}

/* Function: DisplayBalanceRecord
 * Usage: DisplayBalanceRecord(balance);
 * -------------------------------------
 * This function takes a balance record in the form of a struct and displays
 * it in a row via cout.
 * Fulfills part of task #5 from assignment.
 */
void DisplayBalanceRecord(balanceT b) {
    cout << left << setw(5) << b.customer_number
         << setw(15) << b.customer_name
         << "$ ";
    WriteInDollars(cout, b.amount);
}
