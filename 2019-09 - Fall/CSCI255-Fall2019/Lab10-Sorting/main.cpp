/* main.cpp
 * --------
 * Authors: Darwin Jacob Groskleg
 * Date:    Thursday, November 21, 2019
 *
 * QUESTIONS:
 * 1. Are the set of timings for n=5000 as you expected?
 *      I expected either QuickSort or MergeSort to be fastest given their
 *      average running time of O(n log n), leaning towards QuickSort since
 *      there's no need to make copies. This was true for case A.
 *
 *      Case B (pre-sorted) with InsertionSort being fastest was a surprise
 *      given its time complexity of O(n^2) but makes sense when you notice that
 *      it had the fewest number of comparisons by far. This from its adaptive
 *      property.
 *
 *      MergeSort winning case C is reasonable given its time complexity, while
 *      Quicksort had significantly fewer moves MergeSort made 3 magnitudes of
 *      fewer comparisons. This makes sense since the MergeSort implementation
 *      used does a few more moves than is necessary while still correct.
 *
 * 2. Which algorithm is better for data already almost ordered?
 *      The generally poor InsertionSort is the best algorithm to use for data
 *      that is almost ordered. Performing significantly better than the others.
 *
 * 3. Is the timings with n=50 as expected?
 *      The timings with n=50 were not as expected if making predictions based
 *      on time and spacde complexity of the algorithms. Overall InsertionSort
 *      faired the best, with it being tied with SelectionSort for
 *      reverse-ordered data. This is expected because InsertionSort has a
 *      smaller constant factor than QuickSort/MergeSort (i.e. overhead) so when
 *      n is small those factors are more prominent in the performance.
 *      The overhead does however seem algorithmic, using optimizations does not
 *      seem to improve performance.
 *
 * CONSOLE SAMPLE
================================================================================
$> gmake
clang++ -std=c++14 -stdlib=libc++ -Wpedantic -Wall -Wextra -g -D_GLIBCXX_DEBUG -O0 -o main.o -c main.cpp
clang++ -std=c++14 -stdlib=libc++ -Wpedantic -Wall -Wextra -g -D_GLIBCXX_DEBUG -O0 -o sort.o -c sort.cpp
clang++ -std=c++14 -stdlib=libc++ -Wpedantic -Wall -Wextra -g -D_GLIBCXX_DEBUG -O0 -o main.out main.o sort.o

$> time ./main.out
time ./main.out
A) Sorting an unordered array of 5000 random integers:
	  InsertionSort took  19479.0 μs,  6222810 moves,  6222810 comparisons
	  SelectionSort took  26618.0 μs,    10000 moves, 12497500 comparisons
	*     QuickSort took    487.0 μs,    26681 moves,    79745 comparisons
	      MergeSort took   1602.0 μs,    55243 moves,    55256 comparisons
B) Sorting a pre-sorted array of 5000 random integers:
	* InsertionSort took     23.0 μs,     4999 moves,     4999 comparisons
	  SelectionSort took  24959.0 μs,    10000 moves, 12497500 comparisons
	      QuickSort took  31422.0 μs,     4999 moves, 12512497 comparisons
	      MergeSort took   1222.0 μs,     2339 moves,    32430 comparisons
C) Sorting a pre-sorted array of 5000 in reverse order:
	  InsertionSort took  39624.0 μs, 12501232 moves, 12501232 comparisons
	  SelectionSort took  28290.0 μs,    10000 moves, 12497500 comparisons
	      QuickSort took  31107.0 μs,     7497 moves, 12507501 comparisons
	*     MergeSort took   1289.0 μs,    61808 moves,    29804 comparisons
D) Sorting an unordered array of 50 random integers:
	* InsertionSort took      4.0 μs,      553 moves,      553 comparisons
	  SelectionSort took      7.0 μs,      100 moves,     1225 comparisons
	      QuickSort took      4.0 μs,      121 moves,      322 comparisons
	      MergeSort took     13.0 μs,      216 moves,      220 comparisons
E) Sorting a pre-sorted array of 50 random integers:
	* InsertionSort took      1.0 μs,       49 moves,       49 comparisons
	  SelectionSort took      3.0 μs,      100 moves,     1225 comparisons
	      QuickSort took      6.0 μs,       49 moves,     1372 comparisons
	      MergeSort took     10.0 μs,        0 moves,      153 comparisons
F) Sorting a pre-sorted array of 50 in reverse order:
	  InsertionSort took      5.0 μs,     1274 moves,     1274 comparisons
	* SelectionSort took      4.0 μs,      100 moves,     1225 comparisons
	      QuickSort took      6.0 μs,       74 moves,     1322 comparisons
	      MergeSort took     11.0 μs,      286 moves,      133 comparisons
================================================================================
 */
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

#include <time.h>
#include <stdlib.h>

#include "sort.hpp"
#include "benchmark.hpp"

using namespace std;
using DetailedCSorter        = std::function<SortingDetails (int[], int, int)>;
using DetailedBenchmarkEntry = BenchmarkEntry<SortingDetails>;

void display_results(vector<DetailedBenchmarkEntry>);

int main() {
    CSortBenchmark< DetailedCSorter > benchmark({
        {"InsertionSort", InsertionSort},
        {"SelectionSort", SelectionSort},
        {"QuickSort",     QuickSort},
        {"MergeSort",     MergeSort}
    });

    srand((unsigned)time(NULL));

    // BUILD 5000 random element array
    vector<int> rand5000(5'000);
    // generate random numbers and store them in the array
    for(size_t index=0; index<rand5000.size(); index++)
        rand5000.at(index) = (rand()%10'000)+1;
    auto args_5_000 = make_tuple(rand5000.data(), 0, rand5000.size()-1);

    // A) an unordered array of 5000 random integers
    clog << "A) Sorting an unordered array of 5000 random integers:\n";
    display_results(benchmark.run_with(args_5_000));

    // B) a pre-sorted array of 5000
    clog << "B) Sorting a pre-sorted array of 5000 random integers:\n";
    std::sort(rand5000.begin(), rand5000.end());
    display_results(benchmark.run_with(args_5_000));

    // C) a pre-sorted array of 5000 in reverse order
    clog << "C) Sorting a pre-sorted array of 5000 in reverse order:\n";
    std::sort(rand5000.begin(), rand5000.end(), std::greater<>());
    display_results(benchmark.run_with(args_5_000));


    // BUILD an array of 50 random elements
    vector<int> rand50(50);
    // generate random numbers and store them in the array
    for(size_t index=0; index<rand50.size(); index++)
        rand50.at(index) = (rand()%10'000)+1;
    auto args_50 = make_tuple(rand50.data(), 0, rand50.size()-1);

    // D) an unordered array of 50 random integers
    clog << "D) Sorting an unordered array of 50 random integers:\n";
    display_results(benchmark.run_with(args_50));

    // E) a pre-sorted array of 50
    clog << "E) Sorting a pre-sorted array of 50 random integers:\n";
    std::sort(rand50.begin(), rand50.end());
    display_results(benchmark.run_with(args_50));

    // F) a pre-sorted array of 50 in reverse order
    clog << "F) Sorting a pre-sorted array of 50 in reverse order:\n";
    std::sort(rand50.begin(), rand50.end(), std::greater<>());
    display_results(benchmark.run_with(args_50));

    return 0;
}

void display_results(vector<DetailedBenchmarkEntry> results) {
    auto cmp = [] (DetailedBenchmarkEntry& l, DetailedBenchmarkEntry& r) {
        return l.time_in_seconds < r.time_in_seconds;
    };
    auto fastest = std::min_element(results.begin(), results.end(), cmp);
    char fastc;
    for (auto& entry : results) {
        fastc = (entry.label == fastest->label) ? '*' : ' ';
        clog << '\t' << fastc
            << setw(14) << entry.label << " took " << fixed << setprecision(1)
            << setw(8)  << entry.time_in_seconds * 1'000'000 << " μs, "
            << setw(8)  << entry.return_value.moves << " moves, "
            << setw(8)  << entry.return_value.comparisons << " comparisons\n";
    }
}
