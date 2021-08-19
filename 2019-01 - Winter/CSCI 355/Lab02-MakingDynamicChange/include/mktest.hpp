/* mktest.hpp
 * ----------
 * Authors: Darwin Jacob Groskleg
 * Date:    Saturday, October 27, 2018
 *
 * Purpose: 
 *
 * SYNOPSIS
 *      INFO( A )
 *      TEST( f )
 *
 *      DEBUG_PRINT( A )
 *      ASSERT( c )
 *      ASSERT_APPROX_EQUAL( x, y, tolerance )
 *
 * TODO
 *  - Printing Order: save debug and INFO buffer to be printed after assertions,
 *      at the end of the TEST.
 *  - Documentation
 *      - Better name
 *      - Attribution
 *      - How to setup, use and run
 *      - Comments on #endif and #else directives
 *      - Better argument names
 *
 * REFERENCE
 *  Used with written permission from John Armstrong, author of
 *  "C++ for Financial Mathematics". Derived from unit testing code in FMLib6,
 *  a section meant to introduce TDD to people learning C++.
 *  Macros were chosen in order to get file names and lines for tests.
 */
#ifndef MKTEST_HPP_INCLUDED
#define MKTEST_HPP_INCLUDED

#include <stdexcept>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <cassert>

/*  Is debugging currently enabled */
inline bool isDebugEnabled();
/*  Enabled/disable debug */
inline void setDebugEnabled( bool enabled );


static std::stringstream MKTEST_LOGGER;
static bool NEW_LOGGER_STATEMENT = true;
static void fresh_log() {
    MKTEST_LOGGER.clear();
    MKTEST_LOGGER.str("");
    NEW_LOGGER_STATEMENT = true;
}
static void cut_log() {
    std::cerr << MKTEST_LOGGER.str();
    NEW_LOGGER_STATEMENT = false;
}
// End of ruby unit tests:
//  3 tests, 4 assertions, 1 failures, 0 errors
static struct test_harness {
    int tests = 0;
    int assertions = 0;
    int failures = 0;
    int errors = 0;
} HARNESS;


// BEGIN testing.cpp

/* Whether debug messages are enabled
 * REMINDER static variables are restricted to internal linkage.
 */
static bool debugEnabled = false;

inline bool isDebugEnabled() {
    return debugEnabled;
}

inline void setDebugEnabled( bool enable ) {
    debugEnabled = enable;
}
// END testing.cpp


///  Log an information statement from within a test.
//std::cerr << "INFO: " << __FILE__ <<":"<<__LINE__ << ": " << A <<"\n";
#define INFO( A ) {                                                             \
    if (NEW_LOGGER_STATEMENT) {                                                 \
        MKTEST_LOGGER << "INFO: " << __FILE__ <<":"<<__LINE__ << ": ";          \
        NEW_LOGGER_STATEMENT = false;                                           \
    }                                                                           \
    MKTEST_LOGGER << A ;                                                        \
}

/// Registers the unit-test to be run.
#define TEST( f ) do {                                                          \
    fresh_log();                                                                \
    std::cerr<<"Calling "<<#f<<"()\n";                                          \
    try {                                                                       \
        f();                                                                    \
    } catch (...) {                                                             \
        std::cerr<<"\n";                                                        \
        std::cerr<<"******* "<<#f<<"() FAILED. ********\n";                     \
        cut_log();                                                              \
        std::cerr<<"\n";                                                        \
        exit(1);                                                                \
    }                                                                           \
    std::cerr<<""<<#f<<"() passed.\n";                                          \
    std::cerr<<"\n";                                                            \
} while (false)



// on Windows we define debug mode to be when _DEBUG is set
#ifdef _DEBUG
#define DEBUG_MODE 1
#endif

// on UNIX we define debug mode to be when _GLIBCXX is set
#ifdef _GLIBCXX_DEBUG
#define DEBUG_MODE 1
#endif

#ifdef DEBUG
#define DEBUG_MODE 1
#endif


// Our assertion macros do nothing in production.
#ifndef DEBUG_MODE

#define DEBUG_PRINT( A )
#define ASSERT( c ) do {} while (0)
#define ASSERT_APPROX_EQUAL( x, y, tolerance ) do {} while (0)


#else // DEBUG_MODE

/// Write A to std:cerr so long as debug is enabled
#define DEBUG_PRINT( A ) {                                                      \
    if (isDebugEnabled()) {                                                     \
        std::cerr << "DEBUG:\n" << __FILE__ <<":"<<__LINE__ <<":\n"<< A <<"\n"; \
    }                                                                           \
}


/// ASSERT
/// JUnit style: assert(expected == actual)
/// testNG: Expected [x] but found [y]
#define ASSERT( c ) do {                                                        \
    if (!(c)) {                                                                 \
        std::stringstream testing_ss_;                                          \
        testing_ss_ << "ASSERTION FAILED\n  ";                                  \
        testing_ss_ << __FILE__ << ":" << __LINE__ << ": " << #c;               \
        std::cerr << testing_ss_.str();                                         \
        throw std::runtime_error(testing_ss_.str());                            \
    }                                                                           \
} while (false)


/// ASSERT_APPROX_EQUAL (expected, actual)
/// Purpose: we need to assert equality between floating point numbers but
///          a typical assert function will not work for this.
#define ASSERT_APPROX_EQUAL( x, y, tolerance ) do {                             \
    if (!(std::abs((x)-(y))<=(tolerance))) {                                    \
        std::stringstream testing_ss_;                                          \
        testing_ss_ << "ASSERTION FAILED \n";                                   \
        testing_ss_ << "Expected " << (x) << "\n";                              \
        testing_ss_ << "Actual " << (y) << "\n";                                \
        testing_ss_ << __FILE__ << ":" << __LINE__ << ":\n";                    \
        std::cerr << testing_ss_.str();                                         \
        throw std::runtime_error(testing_ss_.str());                            \
    }                                                                           \
} while (false)


#endif // DEBUG_MODE

#endif // MKTEST_HPP_INCLUDED
