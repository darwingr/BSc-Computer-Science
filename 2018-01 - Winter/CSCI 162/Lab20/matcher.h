/* Filename: matcher.h
 * -------------------
 * Author:  Darwin Jacob Groskleg
 * Class:   CSCI 162
 * Lab:     # 20
 * Date:    Sunday, March 18th, 2018
 *
 * Purpose: interface for matcher class. Defined behaviours on a set of left
 * and right, matching delimiters.
 */

#ifndef MATCHER_H_INCLUDED
#define MATCHER_H_INCLUDED

class Matcher {
    private:
        static const int DELIMS = 6;
        char left_delims[DELIMS]  = {'(', '[', '{', '\'', '"', '<'};
        char right_delims[DELIMS] = {')', ']', '}', '\'', '"', '>'};
    public:
        Matcher() {};
       ~Matcher() {};

        bool isMatching(char left_delim, char right_delim) const;
        bool isLeft(char delim) const;
        bool isRight(char delim) const;
};

#endif // MATCHER_H_INCLUDED
