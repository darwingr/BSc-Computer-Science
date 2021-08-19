#ifndef PAIR_H_INCLUDED
#define PAIR_H_INCLUDED

#include <iostream>

template<class T>
class Pair {
    T first_;
    T second_;

public:
    // null object
    Pair() :
        first_(nullptr),
        second_(nullptr)
        {};

    Pair(T first, T second) :
        first_(first),
        second_(second)
        {};

    void display();

    void setElement(int element, T value);
};

template<class T>
void Pair<T>::display() {
    std::cout << '<' << first_ << ' ' << second_ << ">\n";
}

template<class T>
void Pair<T>::setElement(int element, T value) {
    if (element == 1)
        first_ = value;
    else if(element == 2)
        second_ = value;
}

#endif // PAIR_H_INCLUDED
