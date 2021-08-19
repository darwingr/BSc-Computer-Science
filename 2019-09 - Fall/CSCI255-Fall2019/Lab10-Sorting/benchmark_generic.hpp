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

#include <ctime>


// NOTE see 'parameter pack' for use of ArgList.
template<typename Function, typename ...ArgList>
class Benchmark {
    std::unordered_map<std::string, Function> function_list;

  public:
    // Pass a list of labels and functions
    Benchmark(std::unordered_map<std::string, Function> flist) :
        function_list{flist}
    {}


    // Returns labelled list of executions times in seconds.
    // Does not return results of benchmarked algorithms.
    // Arguments must be copy-able!!!
    //
    auto run_with(ArgList... args)
        -> std::unordered_map<std::string, double>;
};


    template<typename Function, typename ...ArgList>
    auto Benchmark<Function, ArgList...>::
run_with(ArgList... args)
    -> std::unordered_map<std::string, double>
{
    double start;
    double finish;
    std::unordered_map<std::string, double> elapsed;
    for (auto &f : function_list) {
        start = static_cast<double>(clock()) / CLOCKS_PER_SEC;

        f.second(args...);

        finish = static_cast<double>(clock()) / CLOCKS_PER_SEC;
        elapsed.insert({f.first, finish - start});
    }
    return elapsed;
}

#endif // BENCHMARK_HPP_INCLUDED
