// Example program
#include <iostream>
#include <cstring>

using namespace std;

int myStrLen(char []);

int main()
{
  const int SIZE = 20;
  char animal[SIZE] = "Bonobo";

  cout << myStrLen(animal) << endl;
  cout << strlen(animal);

  return 0;
}

int myStrLen(char myString[]) {
    int char_count = 0;
    while (myString[char_count] != '\0') char_count++;
    return char_count;
}
