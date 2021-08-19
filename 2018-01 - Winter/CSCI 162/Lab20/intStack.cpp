/* Filename: intStack.cpp
 * ----------------------
 * Author:  Martin van Bommel & Darwin Jacob Groskleg
 * Class:   CSCI 162
 * Lab:     # 20
 * Date:    Sunday, March 18th, 2018
 *
 * Purpose: implementation for intStack class.
 */
#include "intStack.h"

intStack::intStack(int maxsize)
{
    stackarray  = new int[maxsize];
    currentsize = 0;
    arraysize   = maxsize;
}

bool intStack::Push(int value)
{
    if (Full()) return false;

    stackarray[currentsize] = value;
    currentsize++;

    return true;
}

bool intStack::Pop()
{
    if (Empty()) return false;

    currentsize--;

    return true;
}

int intStack::Top() const
{
    return stackarray[currentsize-1];
}
