/* Filename: intQueue.cpp
 * ----------------------
 * Author:  Darwin Jacob Groskleg
 * Class:   CSCI 162
 * Lab:     #19
 * Date:    Friday, March 9th, 2018
 *
 * Purpose: implements the methods on intQueue class.
 */

#include "intQueue.h"

intQueue::intQueue(int maxsize) {
    queuearray  = new int[maxsize];
    currentsize = first = last = 0;
    arraysize   = maxsize;
}

bool intQueue::Enqueue(int value) {
    if (Full()) return false;

    queuearray[last] = value;
    last = (last + 1) % arraysize;
    currentsize++;

    return true;
}

bool intQueue::Dequeue() {
    if (Empty()) return false;

    first = (first  + 1) % arraysize;
    currentsize--;

    return true;
}

int intQueue::Front() const {
    return queuearray[first];
}
