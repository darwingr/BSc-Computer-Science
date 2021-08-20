#include <iostream>

using namespace std;

/* This program accepts a wind speed from the user
 * and returns the category of hurrican that it falls under.
 */
int main() {
    int category; // 1, 2, 3, 4 or 5
    int wind_speed; // in km/h

    cout << "Enter a wind speed in km/h: ";
    cin >> wind_speed;

    // Negative speeds are not possible
    if (wind_speed < 0) {
        cout << "Invalid speed entered" << endl;
        return 1;
    }

    // Determine if not a hurricane
    if (wind_speed < 119) {
        cout << "Speed lower than hurricane speed." << endl;
        return 0;
    }

    // Decide category
    if (wind_speed <= 153) {
        category = 1;
    } else if (wind_speed <= 177) {
        category = 2;
    } else if (wind_speed <= 208) {
        category = 3;
    } else if (wind_speed <= 251) {
        category = 4;
    } else if (wind_speed >= 252) {
        category = 5;
    }

    cout << "category " << category << " hurricane" << endl;
    return 0;
}
