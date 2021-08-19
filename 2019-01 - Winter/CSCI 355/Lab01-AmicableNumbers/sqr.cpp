/* sqr.cpp
 * -------
 * Authors: Darwin Jacob Groskleg
 * Date:    Tuesday, January 22, 2019
 *
 * Purpose: 
 */
#include <iostream>
#include <cmath>

int main() {
    int x = 5000;
    std::cout << "Running for x = " << x << std::endl;
    for (int i = 2; i*i < x; i++)
        std::cout << i << ' ';
    std::cout << std::endl;
    for (int i = 2; i <= std::sqrt(x); i++)
        std::cout << i << ' ';
    return 0;
}
