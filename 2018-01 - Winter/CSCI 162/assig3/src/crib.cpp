/* Filename: crib.cpp
 * ------------------
 * Author:  Darwin Jacob Groskleg
 * Date:    Sunday, March 11th, 2018
 * Class:   CSCI 162
 * Assignment:  #3
 *
 * Purpose: implements crib hand counting and decision functions.
 */
#include "crib.h"
#include <cmath>

static int cribValue(cardT);
static void incrementBitArray(int [], int);

/*
 * One for the nob
 * - 1 point: for jack of same suit as turned card (one for the nob)
 */
int pointsForJack(cardT hand[], int hand_size, cardT turned_card) {
    int points = 0;

    for (int card=0; card<hand_size; card++) {
        if (hand[card].suit == turned_card.suit && hand[card].value == 11)
            points = 1;
    }

    return points;
}

/*
 * Determines number runs of atleast 3 cards in a set of cards, considering
 * double runs from pairs and triples in a hand. A run being 3 cards of
 * consecutive value.
 * 1 point: for each card in a run (minimum 3 cards)
 * Implementation is specific to a 5-card hand, there is a more general/pretty
 * way of doing this but I ran out of time figuring it out.
 *
 * Observations:
 *  - Can't have more than 2 pairs
 *  - Can't have a quad
 *  - Can't have a triple and a pair
 *  - Can't have 2 different runs
 *  + Can have 2 pairs
 *  + Can have 1 pair
 *  + Can have 1 triple
 */
int pointsForRuns(cardT hand[], int hand_size, cardT turned_card) {
    int points = 0;
    const int CARDS = hand_size + 1;
    cardT full_hand[CARDS];

    for (int i=0; i<hand_size; i++)
        full_hand[i] = hand[i];
    full_hand[hand_size] = turned_card;
    SortHandByValue(full_hand, CARDS);

    int left_card = 0;
    int next_left = left_card + 1;
    while (left_card < CARDS-1) {
        int count = 1; // cards in a run

        int duplicates = 0;     // max 2, for a triple
        int pair_sets  = 0;     // max 2
        int triple_sets = 0;    // max 1


        for (int right_card=left_card+1; right_card<CARDS; right_card++) {
            next_left = right_card; // next left can't overlap past runs
            if (full_hand[left_card].value == full_hand[right_card].value-1) {
                duplicates = 0;
                count++;
                left_card = right_card;
            } else if (full_hand[left_card].value == full_hand[right_card].value) {
                duplicates++;
                if (duplicates > 1) {
                    pair_sets--;
                    triple_sets++;
                } else
                    pair_sets++;
            } else                      // end of the run
                break;
        }

        if (count >= 3) {
            points += count * pow(2, pair_sets) * pow(3, triple_sets);
        }

        left_card = next_left;
    }
    return points;
}

/*
 * Calculates points for a hand with atleast 4 cards of the same suit.
 * - 1 point: for each card in a flush (min 4 cards in hand of same suit)
 *   - 5 card flush considering turned up card
 */
int pointsForFlushes(cardT hand[], int hand_size, cardT turned_card) {
    int points = 0;
    int suit_count[4] = { 0 };

    for (int card=0; card<hand_size; card++) {
        suit_count[hand[card].suit]++;
    }

    for (int suit=0; suit<4; suit++) {
        if (suit_count[suit] >= 4) {
            points += suit_count[suit];
            if (turned_card.suit == suit)
                points++;
        }
    }

    return points;
}

/*
 * Calculates points from duplicate cards in a hand.
 * 2, 6 or 12 points for pair, pair royal or double pair royal respectively.
 * Note that rank is considered for a pair with face cards.
 * i.e. J and Q are not a pair but J and J are a pair.
 */
int pointsForPairs(cardT hand[], int hand_size, cardT turned_card) {
    int points = 0;
    const int CARDS = hand_size + 1;
    cardT full_hand[CARDS];

    for (int i=0; i<hand_size; i++)
        full_hand[i] = hand[i];
    full_hand[hand_size] = turned_card;
    SortHandByValue(full_hand, CARDS);

    int left_card = 0;
    while (left_card < CARDS) {
        int count = 1; // atleast one card of given value
        int next_left = left_card + 1;

        for (int right_card=left_card+1; right_card<CARDS; right_card++) {
            if (full_hand[left_card].value == full_hand[right_card].value) {
                count++;
                next_left = right_card+1;
            }
        }

        switch (count) {
            case 2: points += 2; break;     // Pair
            case 3: points += 6; break;     // Pair Royal
            case 4: points += 12; break;    // Double Pair Royal
        }

        left_card = next_left;
    }

    return points;
}

/*
 * Calculates number of combinations of card values that add to 15. Note that
 * ace is value 1 and face cards are value 10.
 * Implemented using a bit array of the same size as the hand. We increment
 * through all the values of the bit array like a binary number, multiplying
 * each time the bit array values with hand values at the same index. Summing
 * the result and checking if it's equal to 15 allows us to try all possible
 * combinations of the hand.
 *
 * Permutations to get 15:
 * Looking for integer solutions to a + b + c + d + x = 15 where each term has
 * coefficient of 0 or 1. Consider a..d as hand cards and x the turn card.
 */
int pointsForFifteens(cardT hand[], int hand_size, cardT turned_card) {
    int fifteens_found = 0;
    const int CARDS = hand_size + 1;
    int perm_array[CARDS]; // bit array
    for (int i=0; i<CARDS; i++) perm_array[i] = 0;
    int permutations = pow(2, CARDS);

    // for each permutation of 5 bits,
    //   does the sum of the permutation * the hand = 15 ?
    for (int perm=0; perm<permutations; perm++) {
        int sum = 0;

        // cards 1 to 4
        for (int card=0; card<hand_size; card++) {
            sum += cribValue(hand[card]) * perm_array[card];
        }

        // card 5
        sum += cribValue(turned_card) * perm_array[hand_size];

        if (sum == 15)
            fifteens_found++;
        incrementBitArray(perm_array, CARDS);
    }

    return (2 * fifteens_found);
}

/*
 * Returns the value of a card where we consider all face cards, except for
 * ace, to have a value of 10.
 */
int cribValue(cardT card) {
    if (card.value > 10)
        return 10;
    return card.value;
}

/*
 * Increments a bit array, an array that has only 1 or 0 as values, by a value
 * of 1 in the same way one would treat a binary number.
 */
void incrementBitArray(int bit_array[], int size) {
    int carry = 1; // initial increment
    // start from the right, like a binary number
    for (int i=size-1; i>=0; i--) {
        bit_array[i] += carry;
        if (bit_array[i] > 1) {
            carry = bit_array[i]/2;
            bit_array[i] %= 2;
        } else
            carry = 0;
    }
}
