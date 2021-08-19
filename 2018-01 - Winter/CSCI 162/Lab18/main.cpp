/* Filename: main.cpp
 * ------------------
 * Class:   CSCI 162
 * Lab:     #18 (part 2)
 * Author:  Darwin Jacob Groskleg
 * Date:    March 1, 2018
 *
 * Purpose: to draw a rectangle of a given dimensions to the screen (cout)
 * while using classes to implement it. Also implement a private method that
 * is called by the draw() method (see Rectangle#drawTopOrBottom).
 *
 * Sample Output:
 * ----------------------------------------------------------------------------
 * Enter rectangle width:  8.8
 * Enter rectangle height: 3.45
 *
 * Rendering with 9x3 pixels:
 *  ---------
 * |         |
 * |         |
 * |         |
 *  ---------
 * A 8.8x3.45 rectangle.
 *
 * #> ./rect
 * Enter rectangle width:  5
 * Enter rectangle height: 0.3
 *
 * Rendering with 5x0 pixels:
 *  -----
 * A 5x0.3 rectangle.
 * ----------------------------------------------------------------------------
 */
#include <iostream>
#include "rectang.h"

using namespace std;

int main() {
    double width = 0.0;
    double height = 0.0;

    cout << "Enter rectangle width:  ";
    cin >> width;

    cout << "Enter rectangle height: ";
    cin >> height;

    Rectangle r(width, height);
    r.draw();
    r.describe();

    return 0;
}
