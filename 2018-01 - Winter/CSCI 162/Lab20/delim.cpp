/* Filename: delim.cpp
 * -------------------
 * Author:  Darwin Jacob Groskleg
 * Class:   CSCI 162
 * Lab:     # 20
 * Date:    Sunday, March 18th, 2018
 *
 *
 * Purpose: implement a delimited text checker using an integer stack. Should
 * work for the following delimiters:
 *      parenthesis ( )
 *      brackets [ ]
 *      braces { }
 *      single quotes ' '
 *      double quotes " "
 *      angle brackets < >
 * Should detect these problems in text:
 *  - missing left delimiter  (unexpected close)
 *  - missing right delimiter (unclosed)
 *
 *
 * Console
 * ----------------------------------------------------------------------------
 * $> echo "yey'ey)<>" | ./delim
 * WARNING: expected right delimiter for ' before column 7
 * WARNING: missing left delimiter for ) in column 7
 *
 * $> echo "jkl{abba(\"yeyey\"<<><riroio>>)}asdf{[a],'pp'}vb" | ./delim
 * Text is properly delimited.
 *
 * $> echo "message(for: [\"Jane\", 'H'], <Hello END;" | ./delim
 * WARNING: missing right delimiter for < in column 39 (end of the input text)
 * WARNING: missing right delimiter for ( in column 39 (end of the input text)
 *
 * ----------------------------------------------------------------------------
 */

#include <iostream>

#include "intStack.h"   // original, unchanged
#include "matcher.h"

using namespace std;

int main() {
    bool success = true;
    char ch;
    int input_count = 0;

    const int MAX_LEFT_DELIMETERS = 100;
    intStack leftDelimStack(MAX_LEFT_DELIMETERS); // Be explicit
    Matcher m;

    while (cin.get(ch) && ch != '\n') {
        input_count++;

        if (!isalpha(ch)) {

            // NOTE This can be refactored to be much smaller but the result
            // is much less explicit and obvious at first read.
            if (m.isRight(ch)) {

                if (m.isMatching(leftDelimStack.Top(), ch))
                    leftDelimStack.Pop();

                else if (m.isLeft(ch))      // Treat like a left delim?
                    leftDelimStack.Push(ch);


                else {                      // if right and no match
                    success = false;
                    if(!leftDelimStack.Empty()) {
                        cout << "WARNING: expected right delimiter for "
                             << (char) leftDelimStack.Top()
                             << " before column " << input_count
                             << endl;
                        leftDelimStack.Pop();
                    }

                    cout << "WARNING: missing left delimiter for "
                         << ch << " in column "
                         << input_count
                         << endl;
                }

            } else if (m.isLeft(ch))
                leftDelimStack.Push(ch);
        }
    }

    // Handle what is left in the stack at the end of input
    while (!leftDelimStack.Empty()) {
        success = false;
        cout << "WARNING: missing right delimiter for "
             << (char) leftDelimStack.Top()
             << " in column " << input_count << " (end of the input text)"
             << endl;
        leftDelimStack.Pop();
    }

    if (success)
        cout << "Text is properly delimited." << endl;

    return 0;
}

