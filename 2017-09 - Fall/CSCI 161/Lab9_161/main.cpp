#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

int binarySearch(int key, int [], int);
int linearSearch(int key, int [], int);
void selectionSort(int [], int);

/* This program does 2 things:
 *
 * 1. locates at set of keys in a given array using linear search and
 *  binary search. Then prints the number of comparison made.
 *  For binary search it also prints the indices and the compared values during
 *  the search (low, high, mid).
 *
 * 2. Then performs the same as #1 for a randomly generated key.
 */
int main() {
    int lookup_array[] = { 10,  20,  30,  45,  50,  66,  73,  81,  99, 101,
                          112, 123, 137, 142, 156, 168, 172, 188, 198, 200};
    const int LOOKUP_ARRAY_SIZE = sizeof(lookup_array)/sizeof(lookup_array[0]);

    // Must sort before binarySearch
    selectionSort(lookup_array, LOOKUP_ARRAY_SIZE);

    // 1. Search on set of keys
    cout << "PART 1: search many keys" << endl;
    int keys[] = {10, 50, 188, 200, 68, 400};
    const int KEY_COUNT = sizeof(keys)/sizeof(keys[0]);

    for (int i = 0; i < KEY_COUNT; i++) {
        int position;
        int key = keys[i];

        cout << "key=" << key << endl;

        cout << "  Running linear search: " << endl;
        position = linearSearch(key, lookup_array, LOOKUP_ARRAY_SIZE);
        if (position == -1)
            cout << "\tThe key cannot be found!" << endl;
        else
            cout << "\tThe key " << key << " is at location " << position << endl;

        cout << endl << "  Running binary search: " << endl;
        position = binarySearch(key, lookup_array, LOOKUP_ARRAY_SIZE);
        if (position == -1)
            cout << "\tThe key cannot be found!" << endl;
        else
            cout << "\tThe key " << key << " is at location " << position << endl;
        cout << endl;
    }

    // 2. Search on randomly generated key
    cout << "PART 2: search for random key" << endl;
    // Set the range
    const int BOTTOM = 1;
    const int TOP = 300;

    srand(time(NULL));
    int random_key = rand() % TOP + BOTTOM;
    int position;

    cout << "random_key=" << random_key << endl;

    cout << "  Running linear search: " << endl;
    position = linearSearch(random_key, lookup_array, LOOKUP_ARRAY_SIZE);
    if (position == -1)
        cout << "\tThe key cannot be found!" << endl;
    else
        cout << "\tThe key " << random_key << " is at location " << position << endl;

    cout << endl << "  Running binary search: " << endl;
    position = binarySearch(random_key, lookup_array, LOOKUP_ARRAY_SIZE);
    if (position == -1)
        cout << "\tThe key cannot be found!" << endl;
    else
        cout << "\tThe key " << random_key << " is at location " << position << endl;
    cout << endl;

    return 0;
}

/* Binary Search: ASSUMES the array is sorted first.
 *
 * Returns the location (index) of the key in the given array.
 * Prints out the number of comparisons made, the indices & values compared,
 * the low, high, mid values during the search.
 *
 * Also generates a table of all values/indeces where comparisons were made.
 */
int binarySearch(int key, int array[], int array_size) {
    int low = 0;
    int high = array_size - 1;
    int location = -1;
    int comparison_count = 0;

    const int COL_WIDTH = 8;
    // Table header
    cout << "\t| Comp # | Low idx | Low val | Mid idx | Mid val | High val | High idx |"
         << endl
         << "\t+--------+---------+---------+---------+---------+----------+----------+"
         //<< "\t|----------------------------------------------------------------------|"
         << endl;

    while (low < high) {
        comparison_count++;
        int mid = (low + high)/2; // integer division gives the floor

        // Show comparison values and indices in a table
        cout << right << "\t|"
             << setw(COL_WIDTH-1) << comparison_count << " |"
             << setw(COL_WIDTH) << low << " |"
             << setw(COL_WIDTH) << array[low] << " |"
             << setw(COL_WIDTH) << mid << " |"
             << setw(COL_WIDTH) << array[mid] << " |"
             << setw(COL_WIDTH+1) << high << " |"
             << setw(COL_WIDTH+1) << array[high] << " |"
             << endl;

        // Actual comparison for the algorithm
        if (key <= array[mid])
            high = mid;
        else
            low = mid + 1;
    }
    if (array[high] == key) location = high; // Does not count as comparison

    cout << "\tTotal comparison count: " << comparison_count << endl;

    return location;
}

/* Linear Search: checks each element until it finds a match.
 *
 * Returns the index (location) of the key in the given array.
 * Prints out the number of comparisons made.
 */
int linearSearch(int key, int array[], int array_size) {
    int location = -1;
    int comparison_count = 0;

    for (int i = 0; i < array_size; i++) {
        comparison_count++;
        if (array[i] == key) {
            location = i;
            break;
        }
    }

    cout << "\tTotal comparison count: " << comparison_count << endl;
    return location;
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
