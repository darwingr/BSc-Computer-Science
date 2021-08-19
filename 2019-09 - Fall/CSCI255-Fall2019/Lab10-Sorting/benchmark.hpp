/* benchmark.hpp
 * -------------
 * Authors: Darwin Jacob Groskleg
 * Date:    Thursday, November 21, 2019
 *
 * Purpose: compare performance of multiple algorithms over multiple data sets.
 */
#ifndef BENCHMARK_HPP_INCLUDED
#define BENCHMARK_HPP_INCLUDED

#include <functional>
#include <unordered_map>
#include <string>
#include <vector>
#include <tuple>

#include <ctime>

using CSorterParams = std::tuple<int*, int, int>;
using CSorter       = std::function<void (int[], int, int)>;
template<class Sig>
using return_t      = typename Sig::result_type;

// Details relating to an algorithm executed as part of a benchmark run.
template<typename R>
struct BenchmarkEntry {
    std::string label;
    double      time_in_seconds;
    // R could be void, I don't know what would happen
    R           return_value;
};


// CSortBenchmark
//
// Responsible for timing the execution of multiple sorting algorithms of the
// same type where there is an arbitrary number of possible arrays to serve as
// benchmarks.
// The benchmarking object specifically deals with c-style sorting functions
// that pass operate on an array given to them via pointer.
//
// What does benchmark need to know about?
// -  the type signature
//    - return type of sort?    no use template
//    - argument list?          yes, not variable
//
template<class F>
class CSortBenchmark {
    const std::unordered_map<std::string, F> function_list;

  public:
    // Pass a list of labels and functions
    CSortBenchmark(std::unordered_map<std::string, F> flist) :
        function_list{flist}
    {}

    // Returns labelled list of executions times in seconds.
    auto run_with(CSorterParams args)
        -> std::vector< BenchmarkEntry<return_t<F> > >;
};

// run_with
//
//  CONSTRAINTS
//  - template must be a std::function
//  - Must be able to handle return values:
//      - void
//      - Sorting Details
//  - ArgList must be copy-able!
//      - if arglist contains an array.
  template<class F>
  auto CSortBenchmark<F>::
run_with(CSorterParams args)
    -> std::vector< BenchmarkEntry<return_t<F>> >
{
    int *A, head, tail;
    std::tie(A, head, tail) = args;
    std::vector<int> copy_of_A(tail+1);
    std::vector< BenchmarkEntry<return_t<F>> > elapsed;
    return_t<F> result;

    double start;
    double finish;
    for (auto &f : function_list) {
        // copy the array befor timing
        //  no need to erase, will always be the same size so just overwrite.
        copy_of_A.assign(A, A+tail+1);

        start = static_cast<double>(clock()) / CLOCKS_PER_SEC;
        result = f.second(copy_of_A.data(), head, tail);
        finish = static_cast<double>(clock()) / CLOCKS_PER_SEC;

        elapsed.push_back({f.first, finish - start, result});
    }
    return elapsed;
}

#endif // BENCHMARK_HPP_INCLUDED
