#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

double getMedian(int [], int);
void selectionSort(int [], int);

/* This program reads a list of salaries from a file, sorts them by amount,
 * then returns the median salary and the sorted list.
 */
int main() {
    const int SALARIES_ARRAY_SIZE = 100; // ASSUME is larger than # of salaries
    int salaries[SALARIES_ARRAY_SIZE];
    int salary_count = 0;
    int salary;
    const int MAX_SALARY_DIGITS = 8; // ASSUME

    ifstream inputfile;
    inputfile.open("./salaries.in");

    if (!inputfile.fail()) {
        while (inputfile >> salary) {
            if (salary_count == SALARIES_ARRAY_SIZE) {
                cout << "Too Many entries! Use " << SALARIES_ARRAY_SIZE
                     << " or fewer salaries in file." << endl;
                break;
            }

            salaries[salary_count] = salary;
            salary_count++;
        }
        inputfile.close();
    } else
        cout << "Cannot open file!" << endl;

    selectionSort(salaries, salary_count); // Must happen before getMedian

    cout << endl << "The median salary is: $ "
         << getMedian(salaries, salary_count) << endl << endl;

    cout << "The salaries in ascending order are as follows: " << endl;
    for (int i=0; i<salary_count; i++) {
        cout << "\t$ " << setw(MAX_SALARY_DIGITS) << right << salaries[i]
             << endl;
    }

    return 0;
}

// ASSUMES array is sorted!
// Returns the average of the middle values of a sorted set.
double getMedian(int array[], int array_size) {
    if (array_size % 2 != 0) return array[array_size/2];

    // If the set size is even, we need the mean of 2 middle values
    int left = array_size/2 - 1;
    int right = array_size/2;
    return (array[left]+array[right])/2;
}

// Increment our front through the array, swapping it each time with the
// smallest element found beyond the front. Everything to the left of the front
// is sorted, everything to the right is not.
void selectionSort(int array[], int array_size) {
    for (int front = 0; front < array_size; front++) {
        for (int comparison = front+1; comparison < array_size; comparison++) {
            if (array[comparison] < array[front]) {
                int swap_value = array[front];
                array[front] = array[comparison];
                array[comparison] = swap_value;
            }
        }
    }
}
