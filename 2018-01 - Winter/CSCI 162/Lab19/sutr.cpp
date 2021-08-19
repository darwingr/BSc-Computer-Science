/* Filename: sutr.cpp
 * ------------------
 * Author:  Darwin Jacob Groskleg
 * Class:   CSCI 162
 * Lab:     #19
 * Date:    Friday, March 9th, 2018
 *
 * Purpose: to implement an example of a queue data structure being used to
 * solve a problem. Following the given algorithm and using an intQueue
 * determine the suiter that gets to marry the princess. Do this for suiter
 * line sizes of 2 through 20.
 *
 * Console
 * ----------------------------------------------------------------------------
 * $> ./sutr
 * Out of a line of 2 suitors, princess Eve selects suitor 2
 * Out of a line of 3 suitors, princess Eve selects suitor 2
 * Out of a line of 4 suitors, princess Eve selects suitor 1
 * Out of a line of 5 suitors, princess Eve selects suitor 4
 * Out of a line of 6 suitors, princess Eve selects suitor 1
 * Out of a line of 7 suitors, princess Eve selects suitor 4
 * Out of a line of 8 suitors, princess Eve selects suitor 7
 * Out of a line of 9 suitors, princess Eve selects suitor 1
 * Out of a line of 10 suitors, princess Eve selects suitor 4
 * Out of a line of 11 suitors, princess Eve selects suitor 7
 * Out of a line of 12 suitors, princess Eve selects suitor 10
 * Out of a line of 13 suitors, princess Eve selects suitor 13
 * Out of a line of 14 suitors, princess Eve selects suitor 2
 * Out of a line of 15 suitors, princess Eve selects suitor 5
 * Out of a line of 16 suitors, princess Eve selects suitor 8
 * Out of a line of 17 suitors, princess Eve selects suitor 11
 * Out of a line of 18 suitors, princess Eve selects suitor 14
 * Out of a line of 19 suitors, princess Eve selects suitor 17
 * Out of a line of 20 suitors, princess Eve selects suitor 20
 * ----------------------------------------------------------------------------
 */

#include <iostream>
#include <iomanip>

#include "intQueue.h"

using namespace std;

int EvesChoiceFrom(int);
void FormulaAnalysis();

int main() {
    for (int suitors=2; suitors<=20; suitors++) {
        cout << "Out of a line of " << suitors
             << " suitors, princess Eve selects suitor "
             << EvesChoiceFrom(suitors)
             << endl;
    }

    return 0;
}


/* Function Name: EvesChoiceFrom
 * Usage: int choice = EvesChoiceFrom(7);
 * --------------------------------------
 * Implements the algorithm for how the princess Eve selects a mate out of a
 * line of suitors.
 *
 *  1. Move first 2 suitors to end of line
 *  2. Eliminate 3rd suitor
 *  3. Repeat until 1 suitor remains.
 *
 * General Formula:
 *
 *
 *
 *
 *
 *
 *
 *
 */
int EvesChoiceFrom(int line_size) {
    const int SKIPS = 2;
    int skips_left = SKIPS;
    int suitor;
    intQueue suitor_line(line_size);

    for (int s=1; s<=line_size; s++)
        suitor_line.Enqueue(s);

    while (suitor_line.Size() > 1) {
        suitor = suitor_line.Front();
        suitor_line.Dequeue();
        if (skips_left > 0) {
            suitor_line.Enqueue(suitor);
            skips_left--;
        }
        else
            skips_left = SKIPS;
    }
    return suitor_line.Front();
}


/* FunctionName: formulaAnalysis
 * -----------------------------
 * NOT CALLED
 * Implemented as a spike for attemting to find a pattern in the suitor
 * selection formula.
 * See EvesChoiceFrom for general formula.
 */
void FormulaAnalysis() {
    int cycle = 0;
    int cycle_size = 0;
    int last_choice = 100;

    for (int suitors=1; suitors<=100; suitors++) {
        int choice = EvesChoiceFrom(suitors);
        if (choice < last_choice) {
            cycle++;
            cycle_size = 1;
            cout << " ---- ---- --- ---\n";
        } else {
            cycle_size++;
        }
        last_choice = choice;

        cout << setw(5) << suitors
             << setw(5) << choice
             << setw(4) << cycle
             << setw(4) << cycle_size
             << endl;
    }
}
