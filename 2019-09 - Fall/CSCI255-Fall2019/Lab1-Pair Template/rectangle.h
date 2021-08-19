/* ********************************************************
 * Rectangle.h
 *
 * purpose:
 *              demonstrate class concept in C++
 *
 */
#ifndef rectangle_h
#define rectangle_h
#include <iostream>
#include <iomanip>

using namespace std;

//define the Rectangle class
class Rectangle
{
    //data members, the length and widther of Retangle
    private:
    int length;
    int width;

    //methods
    public:
    Rectangle();
    Rectangle (int l, int w);  //constructor
    //get methods
    int getLength();
    int getWidth();
    //set methods
    void setLength(int l);
    void setWidth(int w);
    //method to compute the area of the Rectangle
    int computeArea(); //note that no need for arguement,
                       //length and width are already store in the object

    void display(); //display the Rectangle object

    friend ostream& operator<<(ostream& os, Rectangle& rect);
};

ostream& operator<<(ostream& os, Rectangle& rect)
{
    os << "<Rectangle info: Length = "  << rect.getLength()
    << "  width = " << rect.getWidth()
    << "  area = " << rect.computeArea() << '>';
    return os;
}

//implementation of methods
//constructor with no arguments
Rectangle::Rectangle ()
{
    length = 0;
    width = 0;
}

//constructor with two arguements
Rectangle::Rectangle (int l, int w)
{
    setLength(l);
    setWidth(w);
}

//get the length of the Rectangle
int Rectangle::getLength()
{
    return length;
}

//get the width of the Rectangle
int Rectangle::getWidth()
{
    return width;
}

//set the length of the Rectangle
void Rectangle::setLength(int l)
{
    length = l;
}

//set the width of the Rectangle
void Rectangle::setWidth(int w)
{
    width = w;
}


//method to compute the area of the Rectangle
int Rectangle::computeArea()
{
    return length * width;
}

//display the info of the Rectangle object
void Rectangle::display()
{
    cout << "Rectangle info: Length = "  << length
    << "  width = " << width
    << "  area = " << computeArea() << endl;
}
#endif
