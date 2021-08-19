/* Filename: main.cpp
 * ------------------
 * Author:  Darwin Jacob Groskleg
 * Date:    Sunday, March 11th, 2018
 * Class:   CSCI 162
 * Assignment:  #3
 *
 * Purpose: Write a program to determine the odds of a perfect 29 hand in
 * cribbage by running a simulation of dealing many hands, and displaying the
 * statistics of the point values achieved.
 *
 * Cribbage Rules (six card cribbage):
 * - 1 dealer + 2 other players: 1 hand each + the crib hand
 *   Show (from 4 cards in hand + turned up card)
 * Points:
 * - 2 points: all combinations of cards adding up to 15
 * - 2, 6 or 12 points: pair, pair royal or double pair royal respectively
 * - 1 point: for each card in a run
 * - 1 point: for each card in a flush (min 4 cards in hand of same suit)
 *   - 5 card flush considering turned up card
 * - 1 point: for jack of same suit as turned card (one for the nob)
 *
 * Output:
 * ----------------------------------------------------------------------------
 *
 * Simulating 10000000 rounds of Cribbage...
 * Points
 * inHand Occurences Percent
 * ------ ---------- -------
 * 0          777588  7.8 %
 * 1           77282  0.8 %
 * 2         2166642 21.7 %
 * 3          387695  3.9 %
 * 4         2196736 22.0 %
 * 5          535622  5.4 %
 * 6         1385623 13.9 %
 * 7          578378  5.8 %
 * 8          875132  8.8 %
 * 9          277827  2.8 %
 * 10         299132  3.0 %
 * 11          39751  0.4 %
 * 12         244448  2.4 %
 * 13          15149  0.2 %
 * 14          68818  0.7 %
 * 15           6980  0.1 %
 * 16          44826  0.4 %
 * 17           8654  0.1 %
 * 18           2107  0.0 %
 * 19              0  0.0 %
 * 20           6229  0.1 %
 * 21           1925  0.0 %
 * 22            314  0.0 %
 * 23            260  0.0 %
 * 24           2825  0.0 %
 * 25              0  0.0 %
 * 26              0  0.0 %
 * 27              0  0.0 %
 * 28             53  0.0 %
 * 29              4  0.0 %
 * Mean points: 4.77, Standard Deviation: 3.13
 *
 * The odds of a perfect 29 hand in cribbage is 4 out of 10000000 rounds,
 * or 0.0% of the time, for player1 (3 player games).
 * ----------------------------------------------------------------------------
 */
#include <iostream>
#include <iomanip>

#include "deck.h"
#include "crib.h"
#include "array_stats.h"

using namespace std;

void simulateCribRounds(int, int [], int);
int pointsForPlayer1();


int main() {
    // Simulate a round from player 1's perspective.
    //   Get the resulting points for hand
    // Run the simulation 1000 times
    //   track the points per simulation by the index on an array
    //   An array from 0 to 32, anything above 29 should always be zero
    // Display a report
    //   Mean, Standard Deviation, Median and Mode of points
    //   Occurrence per hand
    //   Percentage point per hand
    const int POINT_RANGE = 30;     // 0 to 29
    int point_count[POINT_RANGE] = { 0 };
    const double ROUNDS = 10000000;

    Decks(1);
    simulateCribRounds(ROUNDS, point_count, POINT_RANGE);

    // Report Header
    cout << "Points\n"
         << "inHand Occurences Percent\n"
         << "------ ---------- -------"
         << endl;
    // Report Body
    for (int i=0; i<POINT_RANGE; i++) {
        cout << left << setprecision(0) << fixed
             << setw(2) << i << setw(5) << ' '
             << setw(10) << right << point_count[i] << ' '
             << setprecision(1) << fixed
             << setw(4) << 100 * point_count[i] / ROUNDS
             << setw(3) << left << " %"
             << endl;
    }
    // Summary Statistics
    cout << "Mean points: " << setprecision(2) << fixed
         << arrayIndexMean(point_count, POINT_RANGE)
         << ", Standard Deviation: "
         << arrayIndexStdDeviation(point_count, POINT_RANGE)
         << endl;

    // Answer to key assignment question
    cout << setprecision(0) << fixed
         << "\nThe odds of a perfect 29 hand in cribbage is "
         << point_count[29] << " out of " << ROUNDS << " rounds, \n"
         << setprecision(1) << fixed
         << "or " << 100 * point_count[29] / ROUNDS << "% of the time,."
         << "for player1 (3 player games)."
         << endl;

    return 0;
}

void simulateCribRounds(int rounds, int point_count[], int point_range) {
    int points;
    cout << "Simulating " << rounds << " rounds of Cribbage..." << endl;
    for (int r=0; r<rounds; r++) {
        points = pointsForPlayer1();
        if (points >= point_range)
            cout << "ERROR: points(" << points << ") out of range!" << endl;
        else
            point_count[points]++;
    }
}


int pointsForPlayer1() {
    int points_in_hand = 0;
    const int CARDS_DEALT = 4; // TODO set to 6, each discarding 2 to crib
    //const int PLAYERS = 3;
    cardT player1[CARDS_DEALT];
    cardT player2[CARDS_DEALT];
    cardT dealer [CARDS_DEALT];
    //cardT crib[2*PLAYERS];
    cardT turned_card;

    Shuffle();

    for (int i=0; i<CARDS_DEALT; i++) {
        player1[i] = Draw();
        player2[i] = Draw();
        dealer [i] = Draw();
    }
    turned_card = Draw();

    points_in_hand += pointsForFifteens(player1, CARDS_DEALT, turned_card);
    points_in_hand += pointsForPairs(player1, CARDS_DEALT, turned_card);
    points_in_hand += pointsForRuns(player1, CARDS_DEALT, turned_card);
    points_in_hand += pointsForFlushes(player1, CARDS_DEALT, turned_card);
    points_in_hand += pointsForJack(player1, CARDS_DEALT, turned_card);

    return points_in_hand;
}
