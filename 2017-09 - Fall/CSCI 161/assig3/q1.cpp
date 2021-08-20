#include <iostream>
#include <iomanip>

using namespace std;

bool isPrime(int n);
void primeTableInRange(int, int);
int countDigits(int);

/* This program takes in a number range then prints out a table for that range,
 * showing the number if it's prime and a `*` if it's composite.
 */
int main() {
    int start_num, end_num;

    cout << "startNum = ";
    cin >> start_num;
    cout << "endNum = ";
    cin >> end_num;

    cout << endl << "Table.";
    primeTableInRange(start_num, end_num);

    return 0;
}

/* Returns true if number is prime. Assumes number is positive. */
bool isPrime(int n) {
    if (n == 0 || n == 1) return false;
    if (n == 2)           return true;
    for (int i = 2; i < n; i++) {
        if (n % i == 0)   return false;
    }
    return true;
}

/* Generates a table to show whether each number in the range from startNum up
 * to endNum is a prime number. When the numebr is not a prime number, we will
 * only show a '*'. When the number is a prime number, we will show the number.
 */
void primeTableInRange(int start_num, int end_num) {
    const int TABLE_COLUMNS = 10;
    const int LEFT_PAD = 2;
    // only consider end_num, assuming start_num is positive
    const int COL_WIDTH = LEFT_PAD + countDigits(end_num);

    int range_size = end_num - start_num;
    int first_row_offset = (start_num % TABLE_COLUMNS) - 1;
    int cells = first_row_offset + range_size;

    for (int cell = 0; cell < cells; cell++) {
        int number = start_num - first_row_offset + cell;

        // Break in to rows
        if (cell % TABLE_COLUMNS == 0) cout << endl;

        // Right justified numbers
        cout << right << setw(COL_WIDTH);
        if (number < start_num)
            cout << "";
        else if (isPrime(number) == 1)
            cout << number;
        else
            cout << "*";
    }
    cout << endl;
}


/* Takes a integer and returns the number of digits including the sign. */
int countDigits(int number) {
    int digits = 0;

    if (number < 0) digits++;
    while (number) {
        number /= 10;
        digits++;
    }
    return digits;
}
