#include <iostream>

#include "pair.h"
#include "rectangle.h"

using namespace std;

int main() {
    Pair<int> p1(1,3);
    Pair<char> p2('A', 'B');

    cout << "the Pair p1 is: ";
    p1.display();

    cout << "the Pair p2 is: ";
    p2.display();

    p1.setElement(1, 11);
    p2.setElement(2, 'D');

    cout << "the Pair p1 is now: ";
    p1.display();

    cout << "the Pair p2 is now: ";
    p2.display();

    Pair<Rectangle> two_rectangles{ Rectangle(1, 3), Rectangle(11, 3) };
    two_rectangles.display();

    return 0;
}
