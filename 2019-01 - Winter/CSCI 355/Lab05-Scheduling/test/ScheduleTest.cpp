/* ScheduleTest.cpp
 * ----------------
 * Authors: Darwin Jacob Groskleg
 * Date:    Sunday, March 17, 2019
 */
#include "mktest.hpp"

#include <vector>
#include <initializer_list>
#include "Assignment.hpp"

// Assume you will not have a day without an assignment
class Schedule {
    std::vector<Assignment> assigs;
    size_t final_day;
public:
    Schedule(std::initializer_list<Assignment> assig_list):
        assigs{assig_list}
    {
        final_day = Assignment::FinalDeadline(assig_list);
    }

    // Assumes already optimally ordered
    double total_percentage() const {
        double running_sum = 0.0;
        for (size_t i=0; i < final_day; i++)
            running_sum += assigs.at(i).percentage();
        return running_sum;
    }

    // Assumes already optimally ordered
    std::string order() const {
        std::string assig_order{"", final_day};
        for (size_t i=0; i < final_day; i++)
            assig_order.at(i) = assigs.at(i).letter();
        return assig_order;
    }
};

// Degerate cases
void test_empty_schedule_gets_a_0() {
    Schedule sched({});
    auto total_perc = sched.total_percentage();
    ASSERT_APPROX_EQUAL(0.0, total_perc, 0.01);
}

void test_empty_schedule_has_nothing_to_order() {
    Schedule sched({});
    auto order = sched.order();
    ASSERT(order.empty());
}

// Regular cases
void test_one_entry_comes_first() {
    Schedule sched{ {'a', 1, 10} };
    auto order = sched.order();
    ASSERT('a' == order.front());
}

void test_one_entry_has_that_percentage() {
    Schedule sched{ {'a', 1, 10} };
    auto total_perc = sched.total_percentage();
    ASSERT_APPROX_EQUAL(10.0, total_perc, 0.01);
}

void test_set_of_5_and_enough_time_gets_a_68() {
    Schedule sched{
        {'b', 1, 15},
        {'d', 3,  8},
        {'e', 3, 20},
        {'f', 4, 10},
        {'h', 5, 15}
    };
    auto total_perc = sched.total_percentage();
    ASSERT_APPROX_EQUAL(68.0, total_perc, 0.01);
}

void test_provided_assignment_set_should_yield_order_bdefh() {
    Schedule sched{
        {'a', 1, 10}, {'b', 1, 15}, {'c', 2,  5},
        {'d', 3,  8}, {'e', 3, 20}, {'f', 4, 10},
        {'g', 5,  5}, {'h', 5, 15}
    };
    auto order = sched.order();
    INFO(order);
    ASSERT("bdefh" == order);
}

int main() {
    // Degerate cases
    TEST(test_empty_schedule_gets_a_0);
    TEST(test_empty_schedule_has_nothing_to_order);

    // Regular cases
    TEST(test_one_entry_comes_first);
    TEST(test_one_entry_has_that_percentage);

    TEST(test_set_of_5_and_enough_time_gets_a_68);
    TEST(test_provided_assignment_set_should_yield_order_bdefh);

    return 0;
}
