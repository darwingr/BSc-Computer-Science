/* Filename: matcher.cpp
 * ---------------------
 * Author:  Darwin Jacob Groskleg
 * Class:   CSCI 162
 * Lab:     # 20
 * Date:    Sunday, March 18th, 2018
 *
 * Purpose: implements matcher class. Defined behaviours on a set of left
 * and right, matching delimiters.
 */

#include "matcher.h"

/* Method Name: isMatching
 * -------------------------
 * Returns true if the two passed characters are matching delimiters.
 * Expects left and right arguments to be valid left and right delimiters
 * respectively.
 */
bool Matcher::isMatching(char left_delim, char right_delim) const {
    int left_position, right_position;

    for (int i=0; i<DELIMS; i++) {
        if (left_delims[i]  == left_delim)  left_position  = i;
        if (right_delims[i] == right_delim) right_position = i;
    }
    return (left_position == right_position);
}

/* Method Name: isLeft
 * -------------------------
 * Returns true if the given char is a left (opening) delimiter.
 */
bool Matcher::isLeft(char delim) const {
    for (int i=0; i<DELIMS; i++) {
        if (left_delims[i] == delim) return true;
    }
    return false;
}

/* Method Name: isRight
 * -------------------------
 * Returns true if the given char is a right (closing) delimiter.
 */
bool Matcher::isRight(char delim) const {
    for (int i=0; i<DELIMS; i++) {
        if (right_delims[i] == delim) return true;
    }
    return false;
}

