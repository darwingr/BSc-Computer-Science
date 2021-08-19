/* lis.cpp
 * -------
 * CSCI 355 Algorithm Analysis
 * Lab 3    Longest Increasing Subsequence
 *
 * Authors: Darwin Jacob Groskleg
 * Date:    Tuesday, February 05, 2019
 *
 * Purpose: 
 */
#include "lis.hpp"

#include <algorithm>
#include <iostream>

bool is_increasing(int, int);
void print(const std::deque<int>&, std::ostream& = std::cout);
auto get_subsequence(
        const std::vector<int>&,
        const std::vector<int>&,
        const std::vector<int>&,
        int)
    -> std::deque<int>;


/// Part I — lis_length
///
///     Dynamic Approach
///
/// Model Given:
/// length[ i ] is the MAXIMUM length that can be found by adding array[ i ] to
/// the end of each of the LIS found that end with the element in array[ j ]
/// where possible, for each j < i, or just by starting a new LIS which just
/// contains array[ i ].
///
/// ANALYSIS
///     Basic Operation:    is_increasing(i, j)
///     Input Size:         n = sequence length
///
///     T(n) = (1 + 2 + ... + (n-2) + (n-1)) + O(n)
///          = 0.5 * n^2 + O(n)
///          = O(n^2)
///
///     It helps to visualize as half of a square:
///             i
///     ================...=
///     \                  |
///      \                 |
///       \                |  j
///        \               |
///         \              |
///          /             .
///                        .
///                        .
///                     /  |
///                      \ |
///                       \|
///
int part1::lis_length(const std::vector<int> sequence) {
    size_t n_seq_size{ sequence.size() };                           // Θ(1)
    if (n_seq_size == 0) return 0;

    // For each position i, the element will store the length of the longest
    // increasing subsequence (LIS) up to position i that includes the
    // value in position i of the sequence.
    // length[n]
    std::vector<int> lengths;                               // O(1)
    // set capacity but not size
    lengths.reserve(n_seq_size);                            // O(1) since empty

    lengths.emplace_back(1);
    for (size_t i=1; i<n_seq_size; i++) {                           // n * 1
        bool i_is_longest = true;
        int max = 1;

        for (size_t j=0; j<i; j++) {                                //  n*n/2
            // Check if array[i] > array[j]
            //  holds for all 0 ≤ j < i
            if ( !is_increasing(sequence.at(j), sequence.at(i)) )
                i_is_longest = false;

            // array[i] > array[j] for any j
            if ( is_increasing(sequence.at(j), sequence.at(i)) ) {  // n*j
                int new_ss = 1 + lengths.at(j);
                if (new_ss > max)
                    max = new_ss;
            }
        }

        // if array[ i ] > array[ j ] for all 0 ≤ j < i
        //     length[ i ] = 1
        //if (i_is_longest)
        //    lengths.emplace_back(1);
        lengths.emplace_back(max);
    }
    return *std::max_element(lengths.cbegin(), lengths.cend());     // O(n)
}


/// is_increasing
/// Checks if second is an increase form first
///
bool is_increasing(int first, int second) {
    return (second > first);
}




/// Part II — lis_generate
///
/// ANALYSIS
///     Where n = size of the sequence,
///     T(n) = n^2 + Θ(n)
///          = Θ(n^2)
///
///     All that is added is the recursive call to get_sequence,
///     which is of lower order than the lis_length algorithm anyways.
///
std::deque<int>
part2::lis_generate(const std::vector<int>& sequence) {
    size_t n_seq_size{ sequence.size() };                           // Θ(1)
    if (n_seq_size == 0) return {};

    // store the position of the last largest element for every subsequence
    std::vector<int> prev;
    prev.reserve(n_seq_size);


    std::vector<int> lengths;                               // O(1)
    // set capacity but not size
    lengths.reserve(n_seq_size);                            // O(1) since empty

    int max_i = 0;
    lengths.emplace_back(1);
    for (size_t i=1; i<n_seq_size; i++) {                           // n * 1
        bool i_is_longest = true;
        int max = 1;
        int max_j = i;

        for (size_t j=0; j<i; j++) {                                //  n*n/2
            // Check if array[i] > array[j]
            //  holds for all 0 ≤ j < i
            if ( !is_increasing(sequence.at(j), sequence.at(i)) )
                i_is_longest = false;

            // array[i] > array[j] for any j
            if ( is_increasing(sequence.at(j), sequence.at(i)) ) {  // n*j
                int new_ss = 1 + lengths.at(j);
                if (new_ss > max) {
                    max = new_ss;
                    max_j = j;
                }
            }
        }

        if (max > sequence.at(max_i))
            max_i = i;
        // if array[ i ] > array[ j ] for all 0 ≤ j < i
        //     length[ i ] = 1
        //if (i_is_longest)
        //    lengths.emplace_back(1);
        lengths.emplace_back(max);
        prev.emplace_back(max_j);
    }

    return { get_subsequence(sequence, prev, lengths, max_i) };         // Θ(n)
}


/// Part II — lis_print
///
/// ANALYSIS
///     Where n = size of the sequence,
///     T(n) = Θ(n^2) + Θ(n)
///          = Θ(n^2)
///
///     Printing separately from generating the lis may take more time but
///     not an order of time greater so the testability and flexibility is
///     worth it.
///
void part2::lis_print(std::vector<int> sequence, std::ostream& out) {
    // Generate lis (move, don't copy)
    auto lis { lis_generate(sequence) };                            // Θ(n^2)

    out << "The longest increasing subsequence contains "
        << lis.size()                                               // O(1)
        << " elements:\n";
    print(lis, out);                                                // Θ(n)
    out << '\n';
}


/// print
///
/// Prints a container's contents out to a stream object.
///
/// ANALYSIS
///     Where n = size of the container
///     T(n) = Θ(n)
///
void print(const std::deque<int>& container, std::ostream& out) {
    out << '{';
    for (const auto& e: container)
        out << ' ' << e << ',';                                     // Θ(n)
    out << '}';
}

/// Build the subsequence starting from the tail.
/// Required container that can append to head in constant time.
///
/// ANALYSIS
///     Where n = length[tail], worst case the length of sequence
///     T(n) = Θ(n)
///
auto get_subsequence(
        const std::vector<int>& sequence,
        const std::vector<int>& prev,
        const std::vector<int>& length,
        int tail)
    -> std::deque<int>
{
    auto el = sequence.at(tail);                                    // Θ(1)
    if (length.at(tail) == 1)
        return { el };
    auto ss { get_subsequence(sequence, prev, length, prev.at(tail)) };// Θ(n-1)
    ss.emplace_back(el);                                            // Θ(1)
    return ss;                                                      // Θ(1)
}

/// Recursive is same as:
///
//auto get_subsequence(
//        const std::vector<int>& sequence,
//        const std::vector<int>& prev,
//        const std::vector<int>& length,
//        int tail)
//    -> std::deque<int>
//{
//    std::deque<int> ss;
//    while (length.at(tail) >= 1) {
//        auto el = sequence.at(tail);
//        ss.emplace_front(el);
//        tail = prev.at(tail);
//    }
//    return ss;
//}
