/* test_linked_list_delete.cpp
 * ---------------------------
 * Authors: Darwin Jacob Groskleg
 * Date:    Tuesday, March 10, 2020
 *
 * Purpose: 
 */
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "linked_list_delete.hpp"


void build_ll(LinkedList& ll, std::vector<int> vals) {
    std::reverse(std::begin(vals), std::end(vals));
    for (auto &v : vals)
        ll.addToHead(v);
}

TEST_CASE("Degenerate Case: 0 elements") {
    LinkedListD ll;

    INFO( "Before: " << ll.print());
    ll.deleteIthNode(0);
    INFO( "After:  " << ll.print() );

    CHECK(ll.isEmpty() == true);
    REQUIRE(ll.validEnds());
}

TEST_CASE("Trivial Case: 1 element") {
    LinkedListD ll;
    build_ll(ll, {1});

    SECTION("BUT i is out of range") {
        CHECK(ll.isEmpty() == false);
        INFO( "Before: " << ll.print());
        ll.deleteIthNode(1);
        INFO( "After:  " << ll.print() );

        CHECK(ll.isEmpty() == false);
        REQUIRE(ll.validEnds());
    }

    SECTION("delete it, list is empty") {
        CHECK(ll.isEmpty() == false);
        INFO( "Before: " << ll.print());
        ll.deleteIthNode(0);
        INFO( "After:  " << ll.print() );

        CHECK(ll.isEmpty() == true);
        REQUIRE(ll.validEnds());
    }
}

TEST_CASE("Repetitive Case: 2 elements") {
    LinkedListD ll;
    build_ll(ll, {1, 2});
    INFO( "Before: " << ll.print());

    SECTION("delete first node") {
        LinkedListD expect;
        build_ll(expect, {2});

        CHECK(ll.isEmpty() == false);
        ll.deleteIthNode(0);
        INFO( "After:  " << ll.print() );

        CHECK(ll.isEmpty() == false);
        CHECK(ll.validEnds());
        REQUIRE(ll.same(expect));
    }

    SECTION("delete second node") {
        LinkedListD expect;
        build_ll(expect, {1});

        CHECK(ll.isEmpty() == false);
        ll.deleteIthNode(1);
        INFO( "After:  " << ll.print() );

        CHECK(ll.isEmpty() == false);
        CHECK(ll.validEnds());
        REQUIRE(ll.same(expect));
    }
}

TEST_CASE("Repetitive Case: 3 elements") {
    LinkedListD ll;
    build_ll(ll, {0, 1, 2});
    INFO( "Before: " << ll.print());

    SECTION("delete head node (i=0)") {
        LinkedListD expect;
        build_ll(expect, {1, 2});

        CHECK(ll.isEmpty() == false);
        ll.deleteIthNode(0);
        INFO( "After:  " << ll.print() );

        CHECK(ll.isEmpty() == false);
        CHECK(ll.validEnds());
        REQUIRE(ll.same(expect));
    }

    SECTION("delete middle node (i=1)") {
        LinkedListD expect;
        build_ll(expect, {0, 2});

        CHECK(ll.isEmpty() == false);
        ll.deleteIthNode(1);
        INFO( "After:  " << ll.print() );

        CHECK(ll.isEmpty() == false);
        CHECK(ll.validEnds());
        REQUIRE(ll.same(expect));
    }

    SECTION("delete tail node (i=2)") {
        LinkedListD expect;
        build_ll(expect, {0, 1});

        CHECK(ll.isEmpty() == false);
        ll.deleteIthNode(2);
        INFO( "After:  " << ll.print() );

        CHECK(ll.isEmpty() == false);
        CHECK(ll.validEnds());
        REQUIRE(ll.same(expect));
    }

    SECTION("try to delete out of range node (i=3)") {
        LinkedListD expect;
        build_ll(expect, {0, 1, 2});

        CHECK(ll.isEmpty() == false);
        ll.deleteIthNode(3);
        INFO( "After:  " << ll.print() );

        CHECK(ll.isEmpty() == false);
        CHECK(ll.validEnds());
        REQUIRE(ll.same(expect));
    }
}
