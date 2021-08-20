#include <iostream>

using namespace std;

/* This program takes in integers less than 9999 from the user and then
 * calculates returns both the minimum and the average of the even numbers.
 */
int main() {
    const int SENTINEL = 9999; // ASSUME all numbers are less
    int input_num = 0;
    int input_count = 0;
    int running_sum = 0;
    int min = SENTINEL; // given above assumption
    double average;

    cout << "Enter integers to calculate average and min if even." << endl
         << "Enter 9999 when finished to receive result." << endl;

    while (input_num != SENTINEL) {
        cin >> input_num;

        if (input_num % 2 == 0) {
            // for calculating average
            input_count++;
            running_sum += input_num;

            // new min?
            if (input_num < min)
                min = input_num;
        }
    }
    cout << endl;

    // To avoid dividing dividing by zero or returning the wrong min
    if (input_count == 0) {
        cout << "Invalid: at least one even number required to calculate."
             << endl;
        return 1;
    }

    average = running_sum / input_count;
    cout << "The average of all even inputs is " << average << endl
         << "The smallest even number (min) is " << min << endl;

    return 0;
}
