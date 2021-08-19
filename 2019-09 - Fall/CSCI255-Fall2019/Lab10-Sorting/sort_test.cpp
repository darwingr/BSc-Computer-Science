/* sort_test.cpp
 * -------------
 *  Executable.
 */
#include <algorithm>
#include <vector>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "sort.hpp"

//using namespace std;
//using namespace Catch;
using Catch::Equals;

// MergeSort()==================================================================
TEST_CASE("MergeSort with 1 element", "[merge]") {
    std::vector<int> a{1};

    SECTION("same value 1, same place") {
        MergeSort(a.data(), 0, 0);
        REQUIRE(1 == a[0]);
    }

    // implementation testing, very bad, acceptable on the degenerate case.
    SECTION("0 value comparisons and 0 moves") {
        auto d = MergeSort(a.data(), 0, 0);
        REQUIRE(0 == d.moves);
        REQUIRE(0 == d.comparisons);
    }
}

TEST_CASE("MergeSort with 0 elements", "[merge]") {
    std::vector<int> a{};

    SECTION("no exceptions with start=0, end=0") {
        REQUIRE_NOTHROW(MergeSort(a.data(), 0, 0));
    }

    // implementation testing, very bad, acceptable on the degenerate case.
    SECTION("0 value comparisons and 0 moves") {
        auto d = MergeSort(a.data(), 0, 0);
        REQUIRE(0 == d.moves);
        REQUIRE(0 == d.comparisons);
    }
}

// smallest case without no operation
TEST_CASE("MergeSort with 2 elements", "[merge]") {
    std::vector<int> a{2, 1};

    SECTION("result is ordered") {
        MergeSort(a.data(), 0, 1);
        REQUIRE_THAT(a, Equals(std::vector<int>{1,2}));
    }

    // implementation testing, very bad, acceptable on the small cases.
    SECTION("1 value comparison and 2 moves(1 swap)") {
        auto d = MergeSort(a.data(), 0, 1);
        REQUIRE(1 == d.comparisons);
        REQUIRE(2 == d.moves);
    }
}

TEST_CASE("MergeSort with 3 elements", "[merge]") {
    std::vector<int> a{3, 2, 1};

    SECTION("result is ordered") {
        MergeSort(a.data(), 0, 2);
        REQUIRE_THAT(a, Equals(std::vector<int>{1, 2, 3}));
    }

    // implementation testing, very bad, acceptable on the small cases.
    SECTION("3 value comparisons and 2 moves when sorted in reverse") {
        auto d = MergeSort(a.data(), 0, 2);
        REQUIRE(5 == d.moves);
        REQUIRE(2 == d.comparisons);
    }

    // implementation testing, very bad, acceptable on the small cases.
    SECTION("details on half sorted") {
        a = {1, 3, 2};
        auto d = MergeSort(a.data(), 0, 2);
        REQUIRE(2 == d.moves);
        REQUIRE(3 == d.comparisons);
    }
}

TEST_CASE("MergeSort with 10 elements(even) is ordered", "[merge]") {
    std::vector<int> a{10, 9, 8, 7, 6,
                        5, 4, 3, 3, 1};

    SECTION("sorting the left half") {
        MergeSort(a.data(), 0, 4);
        std::vector<int> expected{6, 7, 8, 9, 10, 5, 4, 3, 3, 1};
        REQUIRE_THAT(a, Equals(expected));
    }

    SECTION("sorting the right half") {
        MergeSort(a.data(), 5, 9);
        std::vector<int> expected{10, 9, 8, 7, 6, 1, 3, 3, 4, 5};
        REQUIRE_THAT(a, Equals(expected));
    }

    SECTION("sorting on all but the last element") {
        MergeSort(a.data(), 0, 8);
        std::vector<int> expected{3, 3, 4, 5, 6, 7, 8, 9, 10, 1};
        REQUIRE_THAT(a, Equals(expected));
    }

    SECTION("sorting on the whole array") {
        MergeSort(a.data(), 0, 9);
        std::vector<int> expected{1, 3, 3, 4, 5, 6, 7, 8, 9, 10};
        REQUIRE_THAT(a, Equals(expected));
    }
}


// QuickSort()==================================================================
TEST_CASE("QuickSort with 1 element", "[quick]") {
    std::vector<int> a{1};

    SECTION("same value 1, same place") {
        QuickSort(a.data(), 0, 0);
        REQUIRE(1 == a[0]);
    }

    // implementation testing, very bad, acceptable on the degenerate case.
    SECTION("0 value comparisons and 0 moves") {
        auto d = QuickSort(a.data(), 0, 0);
        REQUIRE(0 == d.moves);
        REQUIRE(0 == d.comparisons);
    }
}

TEST_CASE("QuickSort with 0 elements", "[quick]") {
    std::vector<int> a{};

    SECTION("no exceptions with start=0, end=0") {
        REQUIRE_NOTHROW(QuickSort(a.data(), 0, 0));
    }

    // implementation testing, very bad, acceptable on the degenerate case.
    SECTION("0 value comparisons and 0 moves") {
        auto d = QuickSort(a.data(), 0, 0);
        REQUIRE(0 == d.moves);
        REQUIRE(0 == d.comparisons);
    }
}

// smallest case without no operation
TEST_CASE("QuickSort with 2 elements", "[quick]") {
    std::vector<int> a{2, 1};

    SECTION("result is ordered") {
        QuickSort(a.data(), 0, 1);
        REQUIRE_THAT(a, Equals(std::vector<int>{1,2}));
    }

    // implementation testing, very bad, acceptable on the small cases.
    SECTION("value comparison and moves when pre-sorted in reverse") {
        auto d = QuickSort(a.data(), 0, 1);
        REQUIRE(2 == d.comparisons);
        REQUIRE(2 == d.moves);
    }
}

TEST_CASE("QuickSort with 3 elements", "[quick]") {
    std::vector<int> a{3, 2, 1};

    SECTION("result is ordered") {
        QuickSort(a.data(), 0, 2);
        REQUIRE_THAT(a, Equals(std::vector<int>{1, 2, 3}));
    }

    // implementation testing, very bad, acceptable on the small cases.
    SECTION("value comparisons and moves when sorted in reverse") {
        auto d = QuickSort(a.data(), 0, 2);
        REQUIRE(3 == d.moves);
        REQUIRE(7 == d.comparisons);
    }

    // implementation testing, very bad, acceptable on the small cases.
    SECTION("details on half sorted") {
        a = {1, 3, 2};
        auto d = QuickSort(a.data(), 0, 2);
        REQUIRE(3 == d.moves);
        REQUIRE(7 == d.comparisons);
    }
}

TEST_CASE("QuickSort with 10 elements(even) is ordered", "[quick]") {
    std::vector<int> a{10, 9, 8, 7, 6,
                        5, 4, 3, 3, 1};

    SECTION("sorting the left half") {
        QuickSort(a.data(), 0, 4);
        std::vector<int> expected{6, 7, 8, 9, 10, 5, 4, 3, 3, 1};
        REQUIRE_THAT(a, Equals(expected));
    }

    SECTION("sorting the right half") {
        QuickSort(a.data(), 5, 9);
        std::vector<int> expected{10, 9, 8, 7, 6, 1, 3, 3, 4, 5};
        REQUIRE_THAT(a, Equals(expected));
    }

    SECTION("sorting on all but the last element") {
        QuickSort(a.data(), 0, 8);
        std::vector<int> expected{3, 3, 4, 5, 6, 7, 8, 9, 10, 1};
        REQUIRE_THAT(a, Equals(expected));
    }

    SECTION("sorting on the whole array") {
        QuickSort(a.data(), 0, 9);
        std::vector<int> expected{1, 3, 3, 4, 5, 6, 7, 8, 9, 10};
        REQUIRE_THAT(a, Equals(expected));
    }
}


// InsertionSort()==============================================================
TEST_CASE("InsertionSort with 1 element", "[insertion]") {
    std::vector<int> a{1};

    SECTION("same value 1, same place") {
        InsertionSort(a.data(), 0, 0);
        REQUIRE(1 == a[0]);
    }

    // implementation testing, very bad, acceptable on the degenerate case.
    SECTION("0 value comparisons and 0 moves") {
        auto d = InsertionSort(a.data(), 0, 0);
        REQUIRE(0 == d.moves);
        REQUIRE(0 == d.comparisons);
    }
}

TEST_CASE("InsertionSort with 0 elements", "[insertion]") {
    std::vector<int> a{};

    SECTION("no exceptions with start=0, end=0") {
        REQUIRE_NOTHROW(InsertionSort(a.data(), 0, 0));
    }

    // implementation testing, very bad, acceptable on the degenerate case.
    SECTION("0 value comparisons and 0 moves") {
        auto d = InsertionSort(a.data(), 0, 0);
        REQUIRE(0 == d.moves);
        REQUIRE(0 == d.comparisons);
    }
}

// smallest case without no operation
TEST_CASE("InsertionSort with 2 elements", "[insertion]") {
    std::vector<int> a{2, 1};

    SECTION("result is ordered") {
        InsertionSort(a.data(), 0, 1);
        REQUIRE_THAT(a, Equals(std::vector<int>{1,2}));
    }

    // implementation testing, very bad, acceptable on the small cases.
    SECTION("value comparison and moves when pre-sorted in reverse") {
        auto d = InsertionSort(a.data(), 0, 1);
        REQUIRE(2 == d.comparisons);
        REQUIRE(2 == d.moves);
    }
}

TEST_CASE("InsertionSort with 3 elements", "[insertion]") {
    std::vector<int> a{3, 2, 1};

    SECTION("result is ordered") {
        InsertionSort(a.data(), 0, 2);
        REQUIRE_THAT(a, Equals(std::vector<int>{1, 2, 3}));
    }

    // implementation testing, very bad, acceptable on the small cases.
    SECTION("value comparisons and moves when sorted in reverse") {
        auto d = InsertionSort(a.data(), 0, 2);
        REQUIRE(5 == d.moves);
        REQUIRE(5 == d.comparisons);
    }

    // implementation testing, very bad, acceptable on the small cases.
    SECTION("details on half sorted") {
        a = {1, 3, 2};
        auto d = InsertionSort(a.data(), 0, 2);
        REQUIRE(3 == d.moves);
        REQUIRE(3 == d.comparisons);
    }
}

TEST_CASE("InsertionSort with 10 elements(even) is ordered", "[insertion]") {
    std::vector<int> a{10, 9, 8, 7, 6,
                        5, 4, 3, 3, 1};

    SECTION("sorting the left half") {
        InsertionSort(a.data(), 0, 4);
        std::vector<int> expected{6, 7, 8, 9, 10, 5, 4, 3, 3, 1};
        REQUIRE_THAT(a, Equals(expected));
    }

    SECTION("sorting the right half") {
        InsertionSort(a.data(), 5, 9);
        std::vector<int> expected{10, 9, 8, 7, 6, 1, 3, 3, 4, 5};
        REQUIRE_THAT(a, Equals(expected));
    }

    SECTION("sorting on all but the last element") {
        InsertionSort(a.data(), 0, 8);
        std::vector<int> expected{3, 3, 4, 5, 6, 7, 8, 9, 10, 1};
        REQUIRE_THAT(a, Equals(expected));
    }

    SECTION("sorting on the whole array") {
        InsertionSort(a.data(), 0, 9);
        std::vector<int> expected{1, 3, 3, 4, 5, 6, 7, 8, 9, 10};
        REQUIRE_THAT(a, Equals(expected));
    }
}


// SelectionSort()==============================================================
TEST_CASE("SelectionSort with 1 element", "[selection]") {
    std::vector<int> a{1};

    SECTION("same value 1, same place") {
        SelectionSort(a.data(), 0, 0);
        REQUIRE(1 == a[0]);
    }

    // implementation testing, very bad, acceptable on the degenerate case.
    SECTION("0 value comparisons and 0 moves") {
        auto d = SelectionSort(a.data(), 0, 0);
        REQUIRE(0 == d.moves);
        REQUIRE(0 == d.comparisons);
    }
}

TEST_CASE("SelectionSort with 0 elements", "[selection]") {
    std::vector<int> a{};

    SECTION("no exceptions with start=0, end=0") {
        REQUIRE_NOTHROW(SelectionSort(a.data(), 0, 0));
    }

    // implementation testing, very bad, acceptable on the degenerate case.
    SECTION("0 value comparisons and 0 moves") {
        auto d = SelectionSort(a.data(), 0, 0);
        REQUIRE(0 == d.moves);
        REQUIRE(0 == d.comparisons);
    }
}

// smallest case without no operation
TEST_CASE("SelectionSort with 2 elements", "[selection]") {
    std::vector<int> a{2, 1};

    SECTION("result is ordered") {
        SelectionSort(a.data(), 0, 1);
        REQUIRE_THAT(a, Equals(std::vector<int>{1,2}));
    }

    // implementation testing, very bad, acceptable on the small cases.
    SECTION("value comparison and moves when pre-sorted in reverse") {
        auto d = SelectionSort(a.data(), 0, 1);
        REQUIRE(1 == d.comparisons);
        REQUIRE(4 == d.moves);
    }
}

TEST_CASE("SelectionSort with 3 elements", "[selection]") {
    std::vector<int> a{3, 2, 1};

    SECTION("result is ordered") {
        SelectionSort(a.data(), 0, 2);
        REQUIRE_THAT(a, Equals(std::vector<int>{1, 2, 3}));
    }

    // implementation testing, very bad, acceptable on the small cases.
    SECTION("value comparisons and moves when sorted in reverse") {
        auto d = SelectionSort(a.data(), 0, 2);
        REQUIRE(6 == d.moves);
        REQUIRE(2 == d.comparisons);
    }

    // implementation testing, very bad, acceptable on the small cases.
    SECTION("details on half sorted") {
        a = {1, 3, 2};
        auto d = SelectionSort(a.data(), 0, 2);
        REQUIRE(6 == d.moves);
        REQUIRE(1 == d.comparisons);
    }
}

TEST_CASE("SelectionSort with 10 elements(even) is ordered", "[selection]") {
    std::vector<int> a{10, 9, 8, 7, 6,
                        5, 4, 3, 3, 1};

    SECTION("sorting the left half") {
        SelectionSort(a.data(), 0, 4);
        std::vector<int> expected{6, 7, 8, 9, 10, 5, 4, 3, 3, 1};
        REQUIRE_THAT(a, Equals(expected));
    }

    SECTION("sorting the right half") {
        SelectionSort(a.data(), 5, 9);
        std::vector<int> expected{10, 9, 8, 7, 6, 1, 3, 3, 4, 5};
        REQUIRE_THAT(a, Equals(expected));
    }

    SECTION("sorting on all but the last element") {
        SelectionSort(a.data(), 0, 8);
        std::vector<int> expected{3, 3, 4, 5, 6, 7, 8, 9, 10, 1};
        REQUIRE_THAT(a, Equals(expected));
    }

    SECTION("sorting on the whole array") {
        SelectionSort(a.data(), 0, 9);
        std::vector<int> expected{1, 3, 3, 4, 5, 6, 7, 8, 9, 10};
        REQUIRE_THAT(a, Equals(expected));
    }
}
