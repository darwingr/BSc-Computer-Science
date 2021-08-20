#include <iostream>
#include <climits>
#include <cmath>
#include <cstring>

using namespace std;

int ConverBin2Dec(char [], int);
int ReadBinary(char []);

/* This program converts user inputted binary numbers into their decimal
 * equivalent. Stops running when user indicates.
 */
int main() {
    const int MAX_BITS = 8;
    bool continue_input = true;

    while (continue_input) {
        const int RESPONSE_LENGTH = 4; // includes \0 char
        char response[RESPONSE_LENGTH];

        cout << "Enter another binary number? (Yes/No) ";
        cin.get(response, RESPONSE_LENGTH);
        // Clear the cin buffer
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (strncmp(response, "Yes", 3) == 0) {
            // NOTE change number of zeros with any changes to MAX_BITS
            char user_binary[MAX_BITS+1] = "00000000";
            int seq_size = ReadBinary(user_binary);

            cout << "The decimal form is "
                 << ConverBin2Dec(user_binary, seq_size)
                 << endl << endl;
        } else if (strncmp(response, "No", 2) == 0)
            continue_input = false;
    }
    return 0;
}

/* Takes a binary sequence in a character array and the sequence size.
 * Then converts it the sequence to the decimal equivalent.
 * ONLY converts to positive decimals, assumes binary sequence is positive.
 *
 * NOTE: sequence size is all that is required, not array size.
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

/* Requests user input for a binary number that it store in the dynamic array
 * it was given as an argument.
 * Returns the number of bits read into the array.
 */
int ReadBinary(char sequence[]) {
    int bit_limit = strlen(sequence); // We ignore the \0 char
    int bit_count = 0;
    bool continue_sequence = true;

    cout << "Enter " << bit_limit << " bit binary sequence: ";
    while (continue_sequence) {
        char bit = getchar();

        if (bit == '0' || bit == '1') {
            if (bit_count >= bit_limit) {
                cout << "ERROR: exceeded bit limit" << endl;
                // Clear the cin buffer of bits before trying again
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return ReadBinary(sequence);
            }
            sequence[bit_count] = bit;
            bit_count++;
        } else if (bit_count == 0 && bit == '\n') {
            // Handle trailing newlines in the input buffer,
            // do nothing.
        } else
            continue_sequence = false;
    }
    return bit_count;
}
