#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

/* This program prints out a table of results for 2x, x^2 and sqrt(x)
 * for values of x between 1 and 10, by increments of 1/2.
 */
int main() {
    const int COL_WIDTH = 10;

    // Header row
    cout << setw(COL_WIDTH) << "X"
         << setw(COL_WIDTH) << "2X"
         << setw(COL_WIDTH) << "x^2"
         << setw(COL_WIDTH) << "sqrt(x)"
         << endl;

    // Table values
    cout << setprecision(2) << fixed;
    // We want to increment by 0.5 and stop at 10.
    for (double n = 1; n <= 10; n += 0.5) {
        cout << setw(COL_WIDTH) << n
             << setw(COL_WIDTH) << 2 * n
             << setw(COL_WIDTH) << n * n
             << setw(COL_WIDTH) << sqrt(n)
             << endl;
    }
    return 0;
}
