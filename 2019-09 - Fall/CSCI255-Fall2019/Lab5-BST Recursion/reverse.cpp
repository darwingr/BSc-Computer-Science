/* reverse.cpp
 * -----------
 * Authors: Darwin Jacob Groskleg
 * Date:    Tuesday, October 15, 2019
 *
 * Purpose: 
 */
#include <iostream>

using namespace std;

void reverse() {
    char ch;
    cin.get(ch);
    if (ch != '\n')
        reverse();
    cout.put(ch);
}

int main() {
    reverse();
    return 0;
}
