/* MaybeMatrixTest.cpp
 * -------------------
 * Authors: Darwin Jacob Groskleg
 * Date:    Saturday, March 02, 2019
 */
#include "mktest.hpp"
#include "MaybeMatrix.hpp"

namespace test_flat_matrix {
    void can_construct_with_Zero_columns() {
        MaybeMatrix<bool> flat_matrix{1,0};
        ASSERT(flat_matrix.has(0,0) == false);
    }

    void with_Zero_columns_is_always_empty() {
        MaybeMatrix<bool> flat_matrix{1,0};
        bool zeroth    = flat_matrix.has(0,0);
        bool hundredth = flat_matrix.has(100,100);
        bool negative  = flat_matrix.has(-1, -100);
        ASSERT(zeroth    == false);
        ASSERT(hundredth == false);
        ASSERT(negative  == false);
    }

    void can_construct_with_Zero_rows() {
        MaybeMatrix<bool> flat_matrix{0,1};
        ASSERT(flat_matrix.has(0,0) == false);
    }

    void with_Zero_rows_is_always_empty() {
        MaybeMatrix<bool> flat_matrix{0,1};
        bool zeroth    = flat_matrix.has(0,0);
        bool hundredth = flat_matrix.has(100,100);
        bool negative  = flat_matrix.has(-1, -100);
        ASSERT(zeroth    == false);
        ASSERT(hundredth == false);
        ASSERT(negative  == false);
    }

    void null_matrix_is_always_empty() {
        MaybeMatrix<bool> null_matrix{0,0};
        bool zeroth    = null_matrix.has(0,0);
        bool hundredth = null_matrix.has(100,100);
        bool negative  = null_matrix.has(-1, -100);
        ASSERT(zeroth    == false);
        ASSERT(hundredth == false);
        ASSERT(negative  == false);
    }
    void can_emplace_anywhere_positive() {
        MaybeMatrix<int> null_matrix{0,0};
        MaybeMatrix<int> flat_row_matrix{1,0};
        MaybeMatrix<int> flat_column_matrix{0,1};
        bool exceptionThrown = false;
        try {
            null_matrix.emplace(10,10,101);
            flat_row_matrix.emplace(10,10,101);
            flat_column_matrix.emplace(10,10,101);
        } catch (...) {
            exceptionThrown = true;
        }
        ASSERT(exceptionThrown == false);
    }
}; // namespace test_flat_matrix

void test_new_unit_matrix_is_empty() {
    MaybeMatrix<bool> unit_matrix{1, 1};
    bool init_state = unit_matrix.has(0,0);
    ASSERT(init_state == false);
}

void test_new_unit_matrix_can_emplace() {
    MaybeMatrix<int> unit_matrix{1, 1};
    bool initial_state = unit_matrix.has(0,0);
    unit_matrix.emplace(0,0,101);
    bool filled_state  = unit_matrix.has(0,0);
    ASSERT(initial_state == false);
    ASSERT(filled_state  == true);
}

void test_constructor_and_element_access_should_have_same_argument_order() {
    int rows     =   3;
    int columns  =  10;
    int expected = 999;
    MaybeMatrix<int> wide_matrix{rows, columns};
    wide_matrix.emplace(rows-1, columns-1, expected);
    ASSERT(wide_matrix.has(  rows-1, columns-1) == true);
    ASSERT(wide_matrix.value(rows-1, columns-1) == expected);
}

void test_reversing_argument_order_fails() {
    int rows     =   3;
    int columns  =  10;
    int expected = 999;
    MaybeMatrix<int> wide_matrix{rows, columns};
    bool exceptionThrown = false;
    try {
        wide_matrix.emplace(columns-1, rows-1, expected);
    } catch (...) { exceptionThrown = true; }
    ASSERT(exceptionThrown == true);
    ASSERT(wide_matrix.has(columns-1, rows-1) == false);
}

int main() {
    TEST(test_flat_matrix::can_construct_with_Zero_columns);
    TEST(test_flat_matrix::with_Zero_columns_is_always_empty);
    TEST(test_flat_matrix::can_construct_with_Zero_rows);
    TEST(test_flat_matrix::with_Zero_rows_is_always_empty);
    TEST(test_flat_matrix::null_matrix_is_always_empty);
    TEST(test_flat_matrix::can_emplace_anywhere_positive);
    TEST(test_new_unit_matrix_is_empty);
    TEST(test_new_unit_matrix_can_emplace);

    TEST(test_constructor_and_element_access_should_have_same_argument_order);
    TEST(test_reversing_argument_order_fails);

    return 0;
}
