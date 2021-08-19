/* strmanip.hpp
 * ------------
 * CSCI 355 — Algorithm Analysis
 * Lab 1    — Amicable Numbers
 * Authors: Darwin Jacob Groskleg
 * Date:    Tuesday, January 15, 2019
 *
 * Purpose: helper functions for formatting and manipulating strings.
 */
#ifndef STRMANIP_HPP_INCLUDED
#define STRMANIP_HPP_INCLUDED

#include <sstream>

/// print_pair
/// Prints a two integers to a string stream as a pair.
///
inline std::string print_pair(int x, int y) {
    std::ostringstream buffer{" for (", std::ios_base::ate};
    buffer << x << ", " << y << ")";
    return buffer.str();
};

/// Section Underline
/// Return an underlined section title string with an optional trailing number.
///
inline std::string section_underline(std::string title) {
    std::ostringstream buffer{"\n", std::ios_base::ate};
    buffer << title << '\n';
    buffer << std::string((int) buffer.tellp()-2, '=') << std::endl;
    return buffer.str();
}

inline std::string section_underline(std::string title, int n) {
    std::ostringstream buffer{"\n", std::ios_base::ate};
    buffer << title << n << '\n';
    buffer << std::string((int) buffer.tellp()-2, '=') << std::endl;
    return buffer.str();
}

#endif // STRMANIP_HPP_INCLUDED
