/* ThiefTest.cpp
 * -------------
 * CSCI 355 Algorithms Analysis
 * Lab 7    A Knapsack of Algorithms
 *
 * Authors: Darwin Jacob Groskleg, Martin van Bommel (where indicated)
 * Date:    Tuesday, March 26, 2019
 */

#include "mktest.hpp"
#include "Thief.hpp"
#include "loot.hpp"

void test_default_thief_is_a_dummy() {
    Thief thief {10};
    auto knapsack = thief.fill_knapsack({ loot{1} });
    ASSERT(knapsack.empty());
}


int main() {
    TEST(test_default_thief_is_a_dummy);

    return 0;
}
