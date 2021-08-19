/* Filename: crib.h
 * ------------------
 * Author:  Darwin Jacob Groskleg
 * Date:    Sunday, March 11th, 2018
 * Class:   CSCI 162
 * Assignment:  #3
 */
#ifndef CRIB_H_INCLUDED
#define CRIB_H_INCLUDED

#include "deck.h"

/* Usage: (same for all points functions)
 *  int points = 0;
 *  points += pointsForFifteens(hand, 4, turn_card);
 * -------------------------------------------------
 * Returns points in a given hand for each of the five ways to gain points in
 * a hand of cribbage. Specifically at the end of a round.
 * To count all the points in a hand you must sum the result of all 5 functions.
 */
extern int pointsForFifteens(cardT [], int, cardT);
extern int pointsForPairs(cardT [], int, cardT);
extern int pointsForRuns(cardT [], int, cardT);
extern int pointsForFlushes(cardT [], int, cardT);
extern int pointsForJack(cardT [], int, cardT);

// TODO Implement algorithm for picking cards to discard to crib pile.
//      Different method depending if player or dealer.
//cardT discardBest(cardT [], int);     // or find best Hand
//cardT discardWorst(cardT [], int);

#endif
