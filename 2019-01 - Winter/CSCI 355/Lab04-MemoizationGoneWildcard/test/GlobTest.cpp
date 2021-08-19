/* GlobTest.cpp
 * ------------
 * Authors: Darwin Jacob Groskleg
 * Date:    Saturday, March 02, 2019
 */
#include "mktest.hpp"
#include "Glob.hpp"

void test_null_should_match_null() {
    Glob g{"", ""};

    ASSERT(g.match() == true);
}

void test_null_pattern_should_not_match_A() {
    Glob g{"", "A"};

    ASSERT(g.match() == false);
}

void test_letter_should_not_match_null_phrase() {
    Glob g{"A", ""};

    ASSERT(g.match() == false);
}

void test_Star_should_match_null_phrase() {
    Glob g{"*", ""};

    ASSERT(g.match() == true);
}

void test_many_Stars_should_match_null_phrase() {
    Glob g{"***", ""};

    ASSERT(g.match() == true);
}

void test_Star_should_match_letter() {
    Glob g{"*", "A"};

    ASSERT(g.match() == true);
}

void test_Star_should_match_many_letters() {
    Glob g{"*", "AAAAAA"};

    ASSERT(g.match() == true);
}

void test_QuestionMark_should_not_match_null_phrase() {
    Glob g{"?", ""};

    ASSERT(g.match() == false);
}

void test_QuestionMark_should_match_letter() {
    Glob g{"?", "A"};

    ASSERT(g.match() == true);
}

void test_QuestionMark_should_not_match_2letters() {
    Glob g{"?", "AA"};

    ASSERT(g.match() == false);
}

void test_A_should_match_A() {
    Glob g{"A", "A"};

    ASSERT(g.match() == true);
}

int main() {
    TEST(test_null_should_match_null);
    TEST(test_null_pattern_should_not_match_A);
    TEST(test_letter_should_not_match_null_phrase);
    TEST(test_Star_should_match_null_phrase);
    TEST(test_many_Stars_should_match_null_phrase);
    TEST(test_Star_should_match_letter);
    TEST(test_Star_should_match_many_letters);
    TEST(test_QuestionMark_should_not_match_null_phrase);
    TEST(test_QuestionMark_should_match_letter);
    TEST(test_QuestionMark_should_not_match_2letters);
    TEST(test_A_should_match_A);

    return 0;
}
