/* benchmark.hpp
 * -------------
 * CSCI 355 — Algorithm Analysis
 * Lab 1    — Amicable Numbers
 * Authors: Darwin Jacob Groskleg
 * Date:    Tuesday, January 15, 2019
 *
 * Purpose: serve as interface to an object that runs benchmarks on a procedure.
 */
#ifndef BENCHMARK_HPP_INCLUDED
#define BENCHMARK_HPP_INCLUDED

#include <functional>
#include <vector>
#include <chrono>
#include <iostream>
#include <iomanip>

/// Benchmark
///
/// Run a set of performance tests on a procedure or a function using different
/// values of n.
///
/// Usage:
///     Benchmark<int, int> test_fibonacci{ fibonacci };
///     test_fibonacci.with({ 1, 10, 100, 1000, 10000 }).print_results();
///
template<class ReturnType, class ArgType>
class Benchmark {
    const std::function<ReturnType(ArgType)> procedure;
    const std::string proc_label;

public:
    /// Pass a procedure for benchmarking.
    /// Template parameters:
    ///     ReturnType - return type of the procedure
    ///     ArgType    - argument type of the procedure's first argument
    Benchmark(std::function<ReturnType(ArgType)> proc, std::string label) :
        procedure{proc},
        proc_label{label}
    {}

    /// Pass in a list of arguments to then run a benchmark of the procedure
    auto with(std::vector<ArgType> values_of_n) -> Benchmark&;

    /// Print the performance on each argument the procedure was run with.
    void print_results() const;


private:
    struct TestCase {
        const ArgType   n;
        const long long mu_seconds;
    };

    std::vector<TestCase> test_cases;

    long long execution_time_for(ArgType n) const;

}; // Benchmark


template<class ReturnType, class ArgType> auto Benchmark<ReturnType, ArgType>::
with(std::vector<ArgType> values_of_n) -> Benchmark& {
    test_cases.clear();
    for (size_t i=0; i<values_of_n.size(); i++) {
        int n = values_of_n.at(i);
        TestCase test { n, execution_time_for(n) };
        test_cases.push_back(test);
    }
    return *this;
}


template<class ReturnType, class ArgType> auto Benchmark<ReturnType, ArgType>::
print_results() const -> void {
    //auto biggest_n = std::max_element(test_cases.begin(), test_cases.end(),
    //        [](const TestCase &a, const TestCase &b) { return a.n < b.n; });
    using namespace std::chrono;
    int default_precision = std::cout.precision();
    std::cout << "Benchmark Results for `" << proc_label << "` :\n";
    for (const auto& test : test_cases)
        std::cout << test.n << ": "
            << std::setprecision(3) << std::fixed
            << test.mu_seconds / 1000000.
            << std::defaultfloat << std::setprecision(default_precision)
            << " seconds (" << test.mu_seconds << " μs)\n";
    std::cout << '\n';
}

template<class ReturnType, class ArgType> auto Benchmark<ReturnType, ArgType>::
execution_time_for(ArgType n) const -> long long {
    using namespace std::chrono;
    const auto start{ high_resolution_clock::now() };
    procedure(n);
    const auto   end{ high_resolution_clock::now() };
    auto execution_time = duration_cast<microseconds>(end - start).count();
    return execution_time;
}

#endif // BENCHMARK_HPP_INCLUDED
