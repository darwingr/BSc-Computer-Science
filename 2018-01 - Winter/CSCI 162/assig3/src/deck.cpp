/* Filename: deck.cpp
 * ----------------------
 * Author:  M. van Bommel
 * Course:  CSci 162
 * Date:    8 February 2018
 * Purpose: Implementation file for deck.h - needs random to operate
 */

#include "deck.h"
#include "random.h"
#include <iostream>
#include <cstdlib>

using namespace std;

#define NumCards 52                // Number of cards in standard deck, no jokers

static cardT * deck;               // Deck of cards
static int     CardsLeft  = 0;     // Cards remaining in deck = zero -> shuffle
static bool    Randomized = false; // Only want to call Randomize once
static int     NumDecks   = 1;     // Number of decks to use in pack (default is one)

/* Function: Decks
 * Usage:    Decks(n);
 * -------------------
 * Called before first call to shuffle to set the number of decks in the pack.
 */

void Decks(int n)
{
   if (Randomized)
   {
      cout << "Cannot reset number of decks.";
      exit (0);
   }
   if (NumDecks < 1)
   {
      cout << "Cannot have that many decks.";
      exit (0);
   }
   NumDecks = n;
}


/* Function: DisplayCard
 * ---------------------
 * Displays the rank and suit of the given card.
 */

void DisplayCard(cardT card)
{
   char suits[] = "SHCD?";

   switch (card.value)
   {
      case 1:  cout << 'A'; break;
      case 10: cout << 'T'; break;
      case 11: cout << 'J'; break;
      case 12: cout << 'Q'; break;
      case 13: cout << 'K'; break;
      default: cout << card.value;
   }

   if (card.suit < Spades || card.suit > Diamonds) cout << '?';
   else cout << suits[card.suit];
}


/* Function: Shuffle
 * -----------------
 * Creates the array for the deck(s) and initializes the cards.
 * Calls randomize to seed the random number generator.
 * Sets the number of cards left to deal as NumCards * NumDecks.
 */

void Shuffle()
{
   suitT s;
   int val, d, pos = 0;

   CardsLeft = NumDecks * NumCards;

   if (!Randomized)
   {
      Randomize();
      Randomized = true;
      deck = new cardT[NumDecks * NumCards];
      if (deck == NULL)
      {
         cout << "Out of memory - too many cards\n";
         exit(0);
      }
      for (d=0; d < NumDecks; d++)
      {
         for (s = Spades; s <= Diamonds; s = (suitT) (s+1))
         {
            for (val=1; val<=13; val++)
      	    {
               deck[pos].suit = s;
               deck[pos].value = val;
               pos++;
      	    }
         }
      }
   }
}


/* Function: Draw
 * --------------
 * Chooses a random card from deck, moves last card in deck to its position,
 * decrements size of remaining deck, and evaluates and returns the card.
 */

cardT Draw()
{
   int pos;
   cardT card;

   if (!CardsLeft)
   {
      cout << "Deck is empty\n";
      card.value = 0;
      card.suit = Spades;
   } else {
      CardsLeft--;
      pos = RandomInteger(0, CardsLeft);     // pick a random remaining card
      card = deck[pos];
      deck[pos] = deck[CardsLeft];           // swap with last card in deck
      deck[CardsLeft] = card;
   }

   return card;
}


/* Function: Cards
 * ---------------
 * Returns the number of cards left to deal from the deck.
 */

int Cards()
{
   return CardsLeft;
}

/* Function: DisplayHand
 * ---------------------
 * Displays the hand of size cards, separated by spaces.
 */

void DisplayHand(cardT hand[], int size)
{
   int i;
   for (i=0; i<size; i++) {
      DisplayCard(hand[i]);
      cout << ' ';
   }
}

/* Function: SortHandBySuit
 * -------------------------
 * Sorts a hand of size cards by suit (then by value), using a bubble sort.
 */
void SortHandBySuit(cardT hand[], int size)
{
   int i,j;

   for (j=size-1; j>0; j--)
      for (i=0; i<j; i++)
      	if ( hand[i].suit > hand[i+1].suit ||
             ( hand[i].suit == hand[i+1].suit &&
               hand[i].value > hand[i+1].value ) )

           SwapCards(&hand[i], &hand[i+1]);
}

/* Function: SortHandByValue
 * -------------------------
 * Sorts a hand of size cards by value, using a bubble sort.
 */
void SortHandByValue(cardT hand[], int size)
{
   int i,j;

   for (j=size-1; j>0; j--)
      for (i=0; i<j; i++)
      	 if (hand[i].value > hand[i+1].value )
            SwapCards(&hand[i], &hand[i+1]);
}

/* Function: SwapCards
 * -------------------
 * Swaps two cards in memory.
 */
void SwapCards(cardT *p1, cardT *p2)
{
   cardT temp = *p1;
   *p1 = *p2;
   *p2 = temp;
}
