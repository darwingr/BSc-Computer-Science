/* posrun.cpp
 * Result: 4
 */
#include <iostream>
using namespace std;

/* Find the longest consectutive run of positive values in an array.
*/
int posrun(int list[], int size)
{
    int count = 0;
    int maxrun = 0;

    for (int k = 0; k < size; k++)
    {
       if (list[k] > 0)
       {
           count++;
       }
       else
       {
           count = 0;
       }
       if (count > maxrun)
       {
           maxrun = count;
       }
    }

    return maxrun;
}

int main()
{
    int list[10] = {3, 0, 1, 2, 6, -2, 4, 7, 3, 7};
    cout << posrun(list, 10) << endl;

    return 0;
}
