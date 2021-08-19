/* main.cpp
 * --------
 * Authors: Darwin Jacob Groskleg
 * Date:    Thursday, November 21, 2019
 *
 * Purpose:
 */
#include "sort.hpp"
#include <iostream>

#include <ctime>
#include <cstdlib>

using namespace std;



int main()
{
    double start;
    double finish;
    double elapsed;

    srand((unsigned)time(0));
    const int size = 5000;
    int originalarray[size], array[size];
    // generate random numbers and store them in the array
    for(int index=0; index<size; index++){
        originalarray[index]= (rand()%10000)+1;
    }

    // 1. InsertionSort testing
    // 2. SelectionSort testing
    // 3. QuickSort testing
    // 4. MergeSort testing

    // 3. QuickSort testing
    for(int index=0; index<size; index++){
        array[index]= originalarray[index];
    }
    cout << "1a: Test quick Sort, array was unsorted: \n";
    start = double(clock()) / CLOCKS_PER_SEC;

    // Some function is called here
    QuickSort(array, 0, size-1);

    finish = double(clock()) / CLOCKS_PER_SEC;
    elapsed = finish - start;

    cout << "  The elapsed time is: "<< elapsed <<endl;

    cout << "1b: Test quick Sort, array was sorted: \n";
    start = double(clock()) / CLOCKS_PER_SEC;
    QuickSort(array, 0, size-1);

    finish = double(clock()) / CLOCKS_PER_SEC;
    elapsed = finish - start;

    cout << "  The elapsed time is: "<< elapsed <<endl;

    // 4. MergeSort testing
    for(int index=0; index<size; index++){
        array[index]= originalarray[index];
    }
    cout << "2a: Test merge Sort, array was unsorted: \n";
    start = double(clock()) / CLOCKS_PER_SEC;
    MergeSort(array, 0, size-1);

    finish = double(clock()) / CLOCKS_PER_SEC;
    elapsed = finish - start;

    cout << "  The elapsed time is: "<< elapsed <<endl;

    cout << "2b: Test merge Sort, array was sorted: \n";
    start = double(clock()) / CLOCKS_PER_SEC;
    MergeSort(array, 0, size-1);

    finish = double(clock()) / CLOCKS_PER_SEC;
    elapsed = finish - start;

    cout << " The elapsed time is: "<< elapsed <<endl;
    return 1;

}
