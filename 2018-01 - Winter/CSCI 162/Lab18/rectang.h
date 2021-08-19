/* Filename: rectang.cpp
 * ---------------------
 * Class:   CSCI 162
 * Lab:     #18 (part 2)
 * Author:  Darwin Jacob Groskleg and Martin van Bommel
 * Date:    March 1, 2018
 *
 * Purpose: interface for rectangle objects. So far it is not appropriate for
 * our getters and setters to be public.
 */
#ifndef RECTANG_H_INCLUDED
#define RECTANG_H_INCLUDED

class Rectangle
{
    private:
        double width;
        double height;
        void   setWidth  (double);
        void   setHeight (double);
        double getWidth  () const { return width; }
        double getHeight () const { return height; }
        void   drawTopOrBottom(int) const;
    public:
        // Constructor
        Rectangle(double w, double h) {
            setWidth(w);
            setHeight(h);
        }
        void   describe  () const;
        void   draw      () const;
        double getArea   () const { return height * width; }
};

#endif // RECTANG_H_INCLUDED
