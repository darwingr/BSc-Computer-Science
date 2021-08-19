#include "intQueue.h"
#include "intStack.h"

#include <iostream>
using namespace std;

int main()
{
    intStack myStack;
    intQueue myQueue;

    char ch;

    while ( cin.get(ch) && ch != '\n' )
    {
        if (isalpha(ch))
        {
            ch = tolower(ch);
            myStack.Push(ch);
            myQueue.Enqueue(ch);

        }
    }

    while (!myStack.Empty() && myStack.Top() == myQueue.Front())
    {
        myStack.Pop();
        myQueue.Dequeue();
    }

    if (myQueue.Empty())
    {
        cout << "It is a palindrome\n";
    } else {
        cout << "It is not a palindrome\n";
    }

    return 0;
}
