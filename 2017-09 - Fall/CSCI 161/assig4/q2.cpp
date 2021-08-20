#include <iostream>

#define MAX_TABLE_COLUMNS 4

using namespace std;

int linearSearch(int, int [][MAX_TABLE_COLUMNS], int);
double calculateFinalGrade(int *, int);

/* This program prompts the user for a student ID and displays their
 * final grade.
 */
int main() {
    const int NUM_STUDENTS = 3;
    const int NUM_DATA = MAX_TABLE_COLUMNS ;
    //student grades, first column is ID, rest is scores        // FINALS
    int scores[NUM_STUDENTS][NUM_DATA] = {{2046, 97, 79, 86},   // 87.2
                                          {7634, 91, 78, 79},   // 82.3
                                          {8120, 73, 77, 82}};  // 77.8
    int student_id;

    cout << "Enter a student ID: ";
    cin >> student_id;
    // We want to search a column of the matrix
    if (linearSearch(student_id, scores, NUM_STUDENTS) == -1)
        cout << "Student with ID " << student_id << " not found" << endl;
    else {
        int row = linearSearch(student_id, scores, NUM_STUDENTS);
        int *student_record = scores[row];
        cout << "Grade for student " << student_id << " is "
             << calculateFinalGrade(student_record, NUM_DATA) << endl;
    }
    return 0;
}

/* Takes a student record, ID followed by scores, and its size then returns the
 * weighted final grade.
 */
double calculateFinalGrade(int *student_record, int record_size) {
    int percent_weights[] = {30, 30, 40};
    double grade_sum = 0;

    for (int i=1; i<record_size; i++) {
        // record must be offset for student ID
        grade_sum += student_record[i] * (double) percent_weights[i-1]/100;
    }
    return grade_sum;
}

/* Linear Search: checks the zeroth column on each row until it finds a match.
 *
 * Returns the index (location) of the key in the given array.
 * Prints out the number of comparisons made.
 */
int linearSearch(int key, int table[][MAX_TABLE_COLUMNS], int rows) {
    int location = -1;

    for (int i = 0; i < rows; i++) {
        //comparison_count++;
        if (table[i][0] == key) {
            location = i;
            break;
        }
    }
    return location;
}
