/* benchmark_set.hpp
 * -----------------
 * CSCI 355 — Algorithm Analysis
 * Lab 1    — Amicable Numbers
 * Authors: Darwin Jacob Groskleg
 * Date:    Tuesday, January 15, 2019
 *
 * Purpose: interface to a set of benchmarks to be run one after another.
 */
#ifndef BENCHMARK_SET_HPP_INCLUDED
#define BENCHMARK_SET_HPP_INCLUDED

#include "benchmark.hpp"

/// BenchmarkSet
///     Run the same test values on a set of procedures that have the same type
///     signature.
///
/// USAGE comparing implementations of `pairs`
///     BenchmarkSet<void,int> test_pairs{ {
///         { b::pairs,     "b::pairs(n)" },
///         { c::pairs,     "c::pairs(n)" },
///         { f::fastpairs, "f::fastpairs(n)" }
///     }};
///     test_pairs.with({ 5000, 10000}).print_results();
///
template<typename ReturnType, typename ArgType>
class BenchmarkSet {
public:
    /// Pass in a list of Benchmarks you wish run.
    BenchmarkSet(std::vector<Benchmark<ReturnType, ArgType>> benchmark_list_) :
        benchmark_list{ benchmark_list_ }
    {}

    /// Pass in a list of arguments to then run a benchmark of the procedure
    auto with(std::vector<ArgType> values_of_n) -> BenchmarkSet&;

    /// Print the result for each procedure.
    void print_results() const {
        for (auto&& benchmark : benchmark_list)
            benchmark.print_results();
    };

private:
    std::vector<Benchmark<ReturnType, ArgType>> benchmark_list;
};


template<typename ReturnType, typename ArgType>
auto BenchmarkSet<ReturnType, ArgType>::
with(std::vector<ArgType> values_of_n) -> BenchmarkSet& {
    std::cout << "Running performance benchmarks...\n"
        << std::string(80, '=') << std::endl;
    for (auto&& benchmark : benchmark_list)
        benchmark.with(values_of_n);
    std::cout << "\n" << std::string(80, '=')
        << "\nBenchmark Complete: " << benchmark_list.size() << " procedures X "
        << values_of_n.size() << " values of n.\n" << std::endl;
    return *this;
}

#endif // BENCHMARK_SET_HPP_INCLUDED
