/* AssignmentTest.cpp
 * ------------------
 * Authors: Darwin Jacob Groskleg
 * Date:    Sunday, March 17, 2019
 */
#include "mktest.hpp"
#include "Assignment.hpp"

// Degenerates
void test_grade_base_yield_rate() {
    Assignment assig{'h', 5, 15};
    auto yield_rate = assig.yield_rate();
    ASSERT_APPROX_EQUAL(3., yield_rate, 0.01);
}

void test_yield_rate_day_0_is_same_as_day_1() {
    Assignment assig{'h', 5, 15};
    auto yield_rate = assig.yield_rate(0);
    ASSERT_APPROX_EQUAL(3., yield_rate, 0.01);
}

void test_yield_rate_day_before_schedule_same_as_day_1() {
    Assignment assig{'h', 5, 15};
    auto yield_rate = assig.yield_rate(0);
    ASSERT_APPROX_EQUAL(3., yield_rate, 0.01);
}


// Reasonable cases
void test_yield_rate_on_first_day() {
    Assignment assig{'h', 5, 15};
    auto yield_rate = assig.yield_rate(1);
    ASSERT_APPROX_EQUAL(3., yield_rate, 0.01);
}

void test_yield_rate_1_day_left() {
    Assignment assig{'h', 5, 15};
    auto yield_rate = assig.yield_rate(4);
    ASSERT_APPROX_EQUAL(7.5, yield_rate, 0.01);
}


// Ends
void test_yield_rate_on_deadline() {
    Assignment assig{'h', 5, 15};
    auto yield_rate = assig.yield_rate(5);
    ASSERT_APPROX_EQUAL(15.0, yield_rate, 0.01);
}

void test_yield_rate_with_missed_deadline() {
    Assignment assig{'h', 5, 15};
    auto yield_rate = assig.yield_rate(6);
    ASSERT_APPROX_EQUAL(0.0, yield_rate, 0.01);
}

int main() {
    // Degenerate cases
    TEST(test_grade_base_yield_rate);
    TEST(test_yield_rate_day_0_is_same_as_day_1);
    TEST(test_yield_rate_day_before_schedule_same_as_day_1);

    // Reasonable cases
    TEST(test_yield_rate_on_first_day);
    TEST(test_yield_rate_1_day_left);

    // End cases
    TEST(test_yield_rate_on_deadline);
    TEST(test_yield_rate_with_missed_deadline);
    return 0;
}
