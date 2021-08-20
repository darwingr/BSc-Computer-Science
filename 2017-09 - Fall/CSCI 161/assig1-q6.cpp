#include <iostream>

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

/* Takes a positive integer number and reverses it.
 */
int main() {
    int input_number;
    int reversed_number = 0;
    int digits;

    cout << "Enter the number = ";
    cin >> input_number;

    // Takes each digit from the right of input_number, stores in reversed_number
    for (digits = countDigits(input_number); digits > 0; digits--) {
        reversed_number *= 10;
        reversed_number += input_number % 10;
        input_number /= 10;
    }

    cout << "The reverse is " << reversed_number << endl;

    return 0;
}
