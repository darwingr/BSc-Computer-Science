/* Filename: rectang.h
 * -------------------
 * Class:   CSCI 162
 * Lab:     #18 (part 2)
 * Author:  Darwin Jacob Groskleg and Martin van Bommel
 * Date:    March 1, 2018
 *
 * Purpose: implements methods on Rectangle object.
 */
#include "rectang.h"
#include <iostream>
#include <cmath>

using namespace std;

/* Prints a description of the rectangle, its dimensions.
 */
void Rectangle::describe() const {
    cout << "A " << width << "x" << height << " rectangle.\n" << endl;
}

/* Sets the width while checking for valid input.
 */
void Rectangle::setWidth(double w) {
    if (w < 0) {
        cout << "INVALID INPUT: Cannot have negative width (given " << w
             << ") of rectangle!" << endl;
        exit(0);
    }
    else width = w;
}

/* Sets the height while checking for valid input.
 */
void Rectangle::setHeight(double h) {
    if (h < 0) {
        cout << "INVALID INPUT: Cannot have negative height (given " << h
             << ") of rectangle!" << endl;
        exit(0);
    }
    else height = h;
}

/* Method: draw
 * Usage: rectange.draw();
 * -----------------------
 * Prints to characters to stdout that represent the rectangle with its proper
 * dimensions so that it can be displayed on the console screen. In order to do
 * this the dimensions are rounded to the nearest integer value. Note that even
 * an empty rectangle (0x0) will take up 2 empty lines of space, or 2 rows and
 * 2 columns minimum.
 */
void Rectangle::draw() const {
    int w = (int) nearbyint(width);
    int h = (int) nearbyint(height);

    cout << "\nRendering with " << w << 'x' << h << " pixels:"<< endl;
    drawTopOrBottom(w);
    for (int row=1; row<h+1; row++) {
        for (int col=0; col<w+2; col++) {
            if (col==0 || col==w+1)
                cout << '|';        // Side
            else
                cout << ' ';        // Inside
        }
        cout << endl;
    }
    // The vertical gap is too big, just draw a line
    if (h != 0) drawTopOrBottom(w);
}

/* Method: drawTopOrBottom
 * -----------------------
 * Pivate method used to print the top and bottom edges of the rectangle in
 * ascii to stdout.
 */
void Rectangle::drawTopOrBottom(int draw_width) const {
    cout << ' ';                    // Corners
    for (int col=1; col<draw_width+1; col++)
        cout << '-';                // Top & Bottom Edges
    cout << ' ' << endl;            // Corners
}
