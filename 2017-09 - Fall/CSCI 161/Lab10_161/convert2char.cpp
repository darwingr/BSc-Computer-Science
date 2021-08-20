#include <iostream>
#include <fstream>

using namespace std;

/* This program reads integers in a file, converts each integer to an ascii
 * character and outputs each character.
 */
int main() {
    int char_num;
    int char_count = 0;

    ifstream inputfile;
    inputfile.open("./flints.txt");

    if (!inputfile.fail()) {
        // The shovel operator >> will skip whitespace on filestream in
        // addition to newlines.
        while (inputfile >> char_num) {
            char_count++;
            // converts integer to corresponding ASCII character
            cout << static_cast<char>(char_num) << " ";
        }
        inputfile.close();
        cout << endl << "Total characters: " << char_count;
    } else
        cout << "Cannot open file!" << endl;

    return 0;
}
