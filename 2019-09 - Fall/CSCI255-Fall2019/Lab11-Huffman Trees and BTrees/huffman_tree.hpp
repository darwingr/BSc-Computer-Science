/* huffman_tree.hpp
 * ----------------
 * Authors: Darwin Jacob Groskleg
 * Date:    Tuesday, November 26, 2019
 */
#ifndef HUFFMAN_TREE_HPP_INCLUDED
#define HUFFMAN_TREE_HPP_INCLUDED

#include <list>
#include <unordered_map>
#include <string>     // default args
#include <memory>     // ptr on HFNode

using SymbolToFrequencyMap = std::unordered_map<char, double>;

// Purpose: generating variable-length binary character codes.
//
// Prefix Codes: desirable because they simplify decoding. No codeword is a
// prefix of any other, the codeword that begins an encoded file is unambiguous.
//
// So the Huffman Tree constructs an optimal prefix code called Huffman code.
// In this case it is implemented using a greedy algorithm.
//
// Usage:
//  1. Construct a instance, either empty or by passing a map of chars to their
//     respective occurence ratios.
//  2. Add new char => frequency pairs as necessary, even overwritting existing
//     values.
//  3. Generate decode tree via the state change operaton `make_decode_tree`.
//  4. Use the decode tree to get the huffman code.
class HuffmanTree {
  public:
    HuffmanTree(void) {}

    // Construct from a set of n characters.
    //  CLRS page 431
    //HuffmanTree(std::string text) {
    //    text.size();
    //}

    // Construct from a map of chars & freqs, that is a probability value [0,1]
    // of the occurence of each symbol.
    //HuffmanTree(SymbolToFrequencyMap freq_map)
    //{
    //    freq_map.size();
    //}

    ~HuffmanTree(void) {};

    // Add a single node tree to the list.
    void add(char c, double frequency);

    void make_decode_tree(void);

    std::string decode_message(std::string code) const;

    // Usage:
    //      ht.to_dot()
    //      ...compile then run:
    //      ./a.out | dot -Tgif > huff.gif
    //      open huff.gif
    std::string to_dot() const;

    // Returns a huffman coded message,
    // a string of 1's and 0's.
    // ...use strong types for binary string: convertible to and from string.
    //std::string encode_message(std::string message) {
    //}

    // Return the concatenated Huffman code in use.
    std::string huffman_code() const;

  private:
    class HFNode
    {
      public:
        HFNode();
        HFNode(char c, double fr);
        HFNode(char c, double fr, HFNode* l, HFNode* r);
        HFNode(HFNode&&) = default;
       ~HFNode()         = default;

        std::string huffman_code(std::string prefix="") const;
        bool operator<(const HFNode& rhs) const;

        // Readers
        inline char   symbol()    const { return   ch; }
        inline double frequency() const { return freq; }
        inline auto   leftp ()    const { return  left.get(); }
        inline auto   rightp()    const { return right.get(); }
      private:
        const char ch;
        const double freq;
        std::unique_ptr<HFNode> left;
        std::unique_ptr<HFNode> right;
    };

    std::list<HFNode> node_list; // will destruct all the nodes
};


#endif // HUFFMAN_TREE_HPP_INCLUDED
