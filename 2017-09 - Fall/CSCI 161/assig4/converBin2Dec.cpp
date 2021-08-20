#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

int ConverBin2Dec(char [], int);
int bin2Dec2(char []);

int main() {
    char bin1[9] = "01000111";
    cout << ConverBin2Dec(bin1, 8) << endl;

    //char bin1[9] = "01000111";
    cout << bin2Dec2(bin1) << endl;

    return 0;
}

int bin2Dec2(char binary_sequence[]) {
    bool size_found = false;
    int i = 0;
    while (!size_found) {
        if (binary_sequence[i] == '\0') {
            size_found = true;
            int sequence_size = i;
            int array_size = i + 1;
        }
    }
}

/* Takes a binary sequence in a character array and the sequence size.
 * Then converts it the sequence to the decimal equivalent.
 * ONLY converts to positive decimals, assumes binary sequence is positive.
 */
int ConverBin2Dec(char binary_sequence[], int sequence_size) {
    int decimal = 0;
    for (int bit = 0; bit < sequence_size; bit++) {
        // position within the array
        int bit_position = sequence_size - 1 - bit;

        if (binary_sequence[bit_position] == '1')
            decimal += pow(2, bit);
    }
    return decimal;
}
