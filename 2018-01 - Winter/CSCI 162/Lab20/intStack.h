/* Filename: intStack.h
 * --------------------
 * Author:  Martin van Bommel & Darwin Jacob Groskleg
 * Class:   CSCI 162
 * Lab:     # 20
 * Date:    Sunday, March 18th, 2018
 *
 * Purpose: interface for intStack class.
 */
#ifndef INT_STACK_H_INCLUDED
#define INT_STACK_H_INCLUDED

class intStack
{
    private:
        int currentsize;
        int arraysize;
        int *stackarray;
    public:
        intStack(int maxsize = 100);
        ~intStack() { delete [] stackarray; }

        bool Push(int);
        bool Pop();

        int  Top()   const;

        int  Size()  const { return currentsize; }

        bool Empty() const { return currentsize == 0; }
        bool Full()  const { return currentsize == arraysize; }
};

#endif // INT_STACK_H_INCLUDED
