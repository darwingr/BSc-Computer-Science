/* crypt.cpp
 * ---------
 * Class:   CSCI 162 - Assignment 1
 * Author:  Darwin Jacob Groskleg
 * Date:    19 January 2018
 *
 * Purpose:
 * This program should perform both encryption and decryption of text files.
 * It asks from the user whether to encrypt or decrypt, the file name, some
 * key value (a number) to be used in the cipher and which cipher method to
 * use. There are 3 methods: character shift, columnar transposition and a
 * combination of the 2.
 * The result is then printed to a file, its name will be displayed.
 *
 * NOTE: Currently columnar transposition does not decrypt, which means the
 * hybrid, shift transposition, also does not decrypt.
 *
 * Sample Runs:
 * ----------------------------------------------------------------------------
 *
 * Enter 1 to encrypt or enter 0 to decrypt: 1
 * Enter a (positive) key value: 3
 * Enter the input file name: test_shift.txt
 * Cipher methods:
 *   1. Shift operation (key value: offset size)
 *   2. Columnar transposition (key value: number of columns)
 *   3. Combined shift & columnar transposition
 * Enter the number for desired cipher method: 1
 * Completed encrypting.
 * Result in test_shift.txt.enc
 *
 * test_shift.txt.enc ---------------------------------------------------
 * Surjudpplqj#lv#ixq$
 * ----------------------------------------------------------------------------
 *
 * Enter 1 to encrypt or enter 0 to decrypt: 0
 * Enter a (positive) key value: 3
 * Enter the input file name: test_shift.txt.enc
 * Cipher methods:
 *   1. Shift operation (key value: offset size)
 *   2. Columnar transposition (key value: number of columns)
 *   3. Combined shift & columnar transposition
 * Enter the number for desired cipher method: 1
 * Completed decrypting.
 * Result in test_shift.txt.enc.dec
 *
 * test_shift.txt.enc.dec -----------------------------------------------------
 * Programming is fun!
 * ----------------------------------------------------------------------------
 *
 * Enter 1 to encrypt or enter 0 to decrypt: 1
 * Enter a (positive) key value: 6
 * Enter the input file name: test_shift.txt
 * Cipher methods:
 *   1. Shift operation (key value: offset size)
 *   2. Columnar transposition (key value: number of columns)
 *   3. Combined shift & columnar transposition
 * Enter the number for desired cipher method: 2
 * Completed encrypting.
 * Result in test_shift.txt.enc
 *
 * test_shift.txt.enc----------------------------------------------------------
 * gnfrgua nPmi!rms
 * oi 
 * ----------------------------------------------------------------------------
 *
 * Enter 1 to encrypt or enter 0 to decrypt: 1
 * Enter a (positive) key value: 5
 * Enter the input file name: test_shift.txt
 * Cipher methods:
 *   1. Shift operation (key value: offset size)
 *   2. Columnar transposition (key value: number of columns)
 *   3. Combined shift & columnar transposition
 * Enter the number for desired cipher method: 3
 * Completed encrypting.
 * Result in test_shift.txt.enc
 *
 * test_shift.txt.enc ---------------------------------------------------------
 * trnslnx&ws%
 * Uflkwr%z
 * ----------------------------------------------------------------------------
 */
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

char shift(char, int);
void columnar_transposition(istream &, ofstream &, int);
void columnar_transposition_decrypt(istream &, ofstream &, int);
void shift_transposition(ifstream &, ofstream &, int);

int main() {
    bool encrypt_mode;
    int key_value = -1;
    string input_filename;
    string output_filename;
    ifstream infile;
    ofstream outfile;
    int cipher_method = 0;
    char ch;

    cout << "Enter 1 to encrypt or enter 0 to decrypt: ";
    cin >> encrypt_mode;

    // can't be negative
    while (key_value < 0) {
        cout << "Enter a (positive) key value: ";
        cin >> key_value;
    }

    cout << "Enter the input file name: ";
    cin.ignore();
    getline(cin, input_filename);
    //cin >> input_filename;
    // Make the output file name
    if (encrypt_mode)
        output_filename = input_filename + ".enc";
    else
        output_filename = input_filename + ".dec";

    infile.open(input_filename.c_str());
    if (infile.fail()) {
        cout << input_filename << " failed to open!" << endl;
        return -1;
    }

    // create the file
    outfile.open(output_filename.c_str());
    if (outfile.fail()) {
        cout << output_filename << " failed to open!";
        infile.close();
        return -1;
    }

    // Cipher menu
    cout << "Cipher methods:\n"
         << "  1. Shift operation (key value: offset size)\n"
         << "  2. Columnar transposition (key value: number of columns)\n"
         << "  3. Combined shift & columnar transposition\n"
         << "Enter the number for desired cipher method: ";
    cin >> cipher_method;

    switch (cipher_method) {
        case 1: infile.get(ch);
                if (!encrypt_mode) key_value *= -1;
                while (!infile.eof()) {
                    outfile << shift(ch, key_value);
                    infile.get(ch);
                }
                break;
        case 2: if (encrypt_mode)
                    columnar_transposition(infile, outfile, key_value);
                else
                    columnar_transposition_decrypt(infile, outfile, key_value);
                break;
        case 3: shift_transposition(infile, outfile, key_value);
                break;
    }

    infile.close();
    outfile.close();

    if (encrypt_mode) cout << "\nCompleted encrypting.\n";
    else
        cout << "\nCompleted decrypting.\n";
    cout << "Result in " << output_filename << endl;

    return 0;
}

// Ciphers

// Method 1
// Adds and substracts (for encryption and decryption respectively) a fixed
// value (the key value) from the given character value.
// Only shifts for those ASCII values in the range 32 to 126.
char shift(char ascii_char, int offset) {
    char encrypted_char;
    if (ascii_char >= 32 && ascii_char <= 126) {
        encrypted_char = ((ascii_char + offset)/127)*32
                       + (ascii_char + offset)%127;
    } else
        encrypted_char = ascii_char;

    return encrypted_char;
}

// Method 2
// Columnar transposition. The original message is aranged into a number of
// columns (the key value) and then the columns are written out reading down
// one column at a time.
// Function reads and writes directly to/from files.
void columnar_transposition(istream &message, ofstream &outfile,
        int column_count) {
    int char_count = 0;
    char ch;

    for (int col=1; col <= column_count+1; col++) {
        message.clear();
        message.seekg(0, ios::beg);
        message.get(ch);
        char_count++;

        while (!message.eof()) {
            if (((char_count+2) % column_count) + 1 == col) outfile << ch;

            message.get(ch);
            char_count++;
        }

        char_count = 0;
    }
}

void columnar_transposition_decrypt(istream &message, ofstream &outfile,
        int columns) {
    char ch;
    int total_chars = 0;
    int rows = 0;
    int next_col = 0;       // index in the file
    int column = 0;         // index out of columns

    while (message.get(ch)) total_chars++;
    message.clear();
    message.seekg(0, ios::beg);

    rows = total_chars / columns;
    if (total_chars % columns > 0) rows++;
    for (int r=0; r<rows; r++) {
        for (int l=0; l<total_chars; l++) {
            message.get(ch);
            if (l == next_col) {
                if (message.eof()) cout << ' ';
                else cout << ch;

                column++;
                next_col += rows;
                if (total_chars % columns != 0) next_col++;
                //if (next_col > total_chars) {
                if (column >= columns)
                    next_col = r;
                    column = 0;
                }
            }
        }
        message.clear();
        message.seekg(0, ios::beg);
    }
}

// Method 3
// A Hybrid of the shift cipher and the columnar transposition cipher.
// Key value is used for shift offset and number of intermediate columns.
void shift_transposition(ifstream &infile, ofstream &outfile, int key_value) {
    char ch;
    ofstream temp_outfile;
    ifstream temp_infile;

    // dotfile so it's hidden to user
    temp_outfile.open(".tempfile.txt");
    infile.get(ch);
    while (!infile.eof()) {
        temp_outfile << shift(ch, key_value);
        infile.get(ch);
    }
    temp_outfile.close();

    temp_infile.open(".tempfile.txt");
    columnar_transposition(temp_infile, outfile, key_value);
    temp_infile.close();
    remove(".tempfile.txt"); // delete the tempfile
}
