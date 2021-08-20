#include <iostream>
#include <fstream>

using namespace std;

void reverseBubbleSort(int [], int);
void reverseSelectionSort(int [], int);

void printArrayToFile(ofstream &, int [], int);
void swapElements(int &, int &);

/* This program sorts an array in descending order using selection sort and
 * bubble sort.
 * It then shows the total number of comparisons and swaps in each method.
 *
 * Additionally, all the passes for each sorting method are reported in and
 * output file.
 * See q1-sorting.log in directory where program was run.
 */
int main() {
    const int test_array_size = 8;
    int test_array[test_array_size] = {50, 30, 66, 10, 168, 45, 99, 20};
    int test_array2[test_array_size] = {50, 30, 66, 10, 168, 45, 99, 20};

    // TEST reverse bubble sort
    reverseBubbleSort(test_array, test_array_size);

    // TEST reverse selection sort
    reverseSelectionSort(test_array2, test_array_size);

    return 0;
}

// Implements bubble sort in descending order.
// Side effects:
//      - prints comparison and swap count to the console
//      - prints the state array after each pass to a log file
void reverseBubbleSort(int array[], int array_size) {
    int comparison_count = 0;
    int swap_count = 0;
    int pass_count = 0;
    ofstream sort_log;

    sort_log.open("./q1-sorting.log", ios::app);
    if (!sort_log.fail()) {
        sort_log << time(NULL) << " Sorting with " << __FUNCTION__ << "\n\t  ";
        printArrayToFile(sort_log, array, array_size);

        // Sorting algorithm
        // Sorting front: all is sorted beyond the front
        for (int front = array_size; front >= 0; front--) {
            for (int i=1; i<array_size; i++) {
                if (array[i-1] < array[i]) {
                    swapElements(array[i-1], array[i]);
                    swap_count++;
                }
                comparison_count++;
            }
            pass_count++;
            sort_log << "  Pass " << pass_count << ": ";
            printArrayToFile(sort_log, array, array_size);
        }
        sort_log << endl;
        sort_log.close();
    } else
        cout << "Cannot open file to write" << endl;

    cout << "Sorting with " << __FUNCTION__ << endl
         << "   Comparisons: " << comparison_count << endl
         << "   Swaps:       " << swap_count << endl;
}

// Implements selection sort in descending order.
// Increment our front through the array, swapping it each time with the
// largest element found beyond the front. Everything to the left of the front
// is sorted, everything to the right is not.
// Side effects:
//      - prints comparison and swap count to the console
//      - prints the state array after each pass to a log file
void reverseSelectionSort(int array[], int array_size) {
    int comparison_count = 0;
    int swap_count = 0;
    int pass_count = 0;
    ofstream sort_log;

    sort_log.open("./q1-sorting.log", ios::app);
    if (!sort_log.fail()) {
        sort_log << time(NULL) << " Sorting with " << __FUNCTION__ << "\n\t  ";
        printArrayToFile(sort_log, array, array_size);

        // Sorting Algorithm
        // Everything behind the front is sorted
        for (int front = 0; front < array_size; front ++) {
            for (int compare = front+1; compare < array_size; compare++) {
                if (array[compare] > array[front]) {
                    int swap_value = array[front];
                    array[front] = array[compare];
                    array[compare] = swap_value;

                    swap_count++;
                }
                comparison_count++;
            }

            pass_count++;
            sort_log << "  Pass " << pass_count << ": ";
            printArrayToFile(sort_log, array, array_size);
        }
        sort_log << endl;
        sort_log.close();
    } else
        cout << "Cannot open file to write" << endl;

    cout << "Sorting with " << __FUNCTION__ << endl
         << "   Comparisons: " << comparison_count << endl
         << "   Swaps:       " << swap_count << endl;
}

// swaps 2 elements of, presumably, the same array.
// Passes by reference (reference arguments).
void swapElements(int &elem1, int &elem2) {
    int swap = elem1;
    elem1 = elem2;
    elem2 = swap;
}

// Prints the contents of a given array to a single line in the given file.
// Assumes file did not fail to open.
void printArrayToFile(ofstream & ofile, int array[], int array_size) {
    for (int i = 0; i < array_size; i++)
        ofile << array[i] << "  ";
    ofile << endl;
}
