/* main.cpp
 * --------
 * Authors: Darwin Jacob Groskleg
 * Date:    Tuesday, November 26, 2019
 *
 * Purpose: Submit the Huffman tree and the Huffman code for the symbols in
 *          question 1.
 */
#include <iostream>
#include <cstdio>
#include "huffman_tree.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    // Construct a huffman tree
    HuffmanTree htree;
    htree.add('A', 0.39);
    htree.add('B', 0.09);
    htree.add('C', 0.12);
    htree.add('D', 0.18);
    htree.add('E', 0.22);

    // A string with the same letter ratios as above              Ratios
    string sample = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"   // 0.39
                    "BBBBBBBBB"                                 // 0.09
                    "CCCCCCCCCCCC"                              // 0.12
                    "DDDDDDDDDDDDDDDDDD"                        // 0.18
                    "EEEEEEEEEEEEEEEEEEEEEE";                   // 0.22

    // generate the Huffman code for the symbols
    htree.make_decode_tree();

    clog << "# Begin Huffman Coded Message " << string(10, '#') << '\n'
         << htree.huffman_code()
         << "\n# End of Message " << string(23, '#')
         // Source: 
         // http://huffman.ooz.ie/tree.dot?text=AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBCCCCCCCCCCCCDDDDDDDDDDDDDDDDDDEEEEEEEEEEEEEEEEEEEEEE
         << "\nExpected:\n0.10.110.1110.1111"
         << '\n';

    if (argc > 1 && string(argv[1]) == "--to-dot")
        cout << htree.to_dot();

    return 0;
}
