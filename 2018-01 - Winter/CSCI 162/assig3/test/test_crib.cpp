#include "test_crib.h"

#include "crib.h"
#include "testing.h"
#include "deck.h"

static void testRunWithTwoPairs() {
    const int CARDS_DEALT = 4;
    cardT player1[CARDS_DEALT];
    cardT player2[CARDS_DEALT];
    cardT dealer [CARDS_DEALT];
    cardT turned_card;

    Shuffle();

    for (int i=0; i<CARDS_DEALT; i++) {
        player1[i] = Draw();
        player2[i] = Draw();
        dealer [i] = Draw();
    }

    player1[0].value =  9;
    player1[1].value =  9;
    player1[2].value = 10;
    player1[3].value = 10;

    turned_card = Draw();
    turned_card.value = 11;

    int points;
    points = pointsForRuns(player1, CARDS_DEALT, turned_card);

    INFO("Points on run with 2 pairs: "<<points<<"(expect 12)\n");
    ASSERT( points==12 );
}

static void testRunOfFour() {
    const int CARDS_DEALT = 4;
    cardT player1[CARDS_DEALT];
    cardT player2[CARDS_DEALT];
    cardT dealer [CARDS_DEALT];
    cardT turned_card;

    Shuffle();

    for (int i=0; i<CARDS_DEALT; i++) {
        player1[i] = Draw();
        player2[i] = Draw();
        dealer [i] = Draw();
    }

    player1[0].value =  3;
    player1[1].value =  6;
    player1[2].value =  7;
    player1[3].value =  8;

    turned_card = Draw();
    turned_card.value =  9;

    int points;
    points = pointsForRuns(player1, CARDS_DEALT, turned_card);

    INFO("Points for 4 run: "<<points<<"(expect 4)\n");
    ASSERT( points==3 );
}

static void testRunPairTriple() {
    const int CARDS_DEALT = 4;
    cardT player1[CARDS_DEALT];
    cardT player2[CARDS_DEALT];
    cardT dealer [CARDS_DEALT];
    cardT turned_card;

    Shuffle();

    for (int i=0; i<CARDS_DEALT; i++) {
        player1[i] = Draw();
        player2[i] = Draw();
        dealer [i] = Draw();
    }

    player1[0].value =  8;
    player1[1].value =  8;
    player1[2].value =  9;
    player1[3].value =  9;

    turned_card = Draw();
    turned_card.value =  9;

    int points;
    points = pointsForRuns(player1, CARDS_DEALT, turned_card);

    INFO("Points for pair & triple: "<<points<<"(expect 0)\n");
    ASSERT( points==0 );
}

static void testRunPair() {
    const int CARDS_DEALT = 4;
    cardT player1[CARDS_DEALT];
    cardT player2[CARDS_DEALT];
    cardT dealer [CARDS_DEALT];
    cardT turned_card;

    Shuffle();

    for (int i=0; i<CARDS_DEALT; i++) {
        player1[i] = Draw();
        player2[i] = Draw();
        dealer [i] = Draw();
    }

    player1[0].value =  8;
    player1[1].value =  8;
    player1[2].value =  9;
    player1[3].value = 10;

    turned_card = Draw();
    turned_card.value = 11;

    int points;
    points = pointsForRuns(player1, CARDS_DEALT, turned_card);

    INFO("Points for one pair: "<<points<<"(expect 8)\n");
    ASSERT( points==8 );
}

static void testRunGap() {
    const int CARDS_DEALT = 4;
    cardT player1[CARDS_DEALT];
    cardT player2[CARDS_DEALT];
    cardT dealer [CARDS_DEALT];
    cardT turned_card;

    Shuffle();

    for (int i=0; i<CARDS_DEALT; i++) {
        player1[i] = Draw();
        player2[i] = Draw();
        dealer [i] = Draw();
    }

    player1[0].value =  3;
    player1[1].value =  4;
    player1[2].value =  6;
    player1[3].value =  8;

    turned_card = Draw();
    turned_card.value =  9;

    int points;
    points = pointsForRuns(player1, CARDS_DEALT, turned_card);

    INFO("Points for gap, no runs: "<<points<<"(expect 0)\n");
    ASSERT( points==0 );
}

//static void testDiscardWorst() {
//}

void test_crib() {
    Decks(1);
    TEST( testRunWithTwoPairs );
    TEST( testRunOfFour );
    TEST( testRunPairTriple );
    TEST( testRunPair );
    TEST( testRunGap );
}
