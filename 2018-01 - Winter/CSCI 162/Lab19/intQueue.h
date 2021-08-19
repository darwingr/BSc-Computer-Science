/* Filename: intQueue.h
 * --------------------
 * Author:  Darwin Jacob Groskleg
 * Class:   CSCI 162
 * Lab:     #19
 * Date:    Friday, March 9th, 2018
 *
 * Purpose: interface for intQueue objects, queue data structures for integers.
 */

#ifndef INT_Queue_H_INCLUDED
#define INT_Queue_H_INCLUDED

class intQueue {
    private:
        int currentsize;
        int arraysize;
        int first;
        int last;
        int *queuearray;
    public:
        intQueue(int maxsize = 100);
        ~intQueue() { delete [] queuearray; }

        bool Enqueue(int);
        bool Dequeue();

        int  Front() const;

        int  Size()  const { return currentsize; }

        bool Empty() const { return currentsize == 0; }
        bool Full()  const { return currentsize == arraysize; }
};

#endif // INT_Queue_H_INCLUDED
