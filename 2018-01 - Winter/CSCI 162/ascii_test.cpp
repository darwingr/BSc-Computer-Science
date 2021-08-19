#include <iostream>

using namespace std;

int main() {
    char ch1 = 32;
    char ch2 = 126;

    cout << ch1 << " => " << (char) (ch1+1) << endl
         << ch2 << " => " << ch2+1 << endl;

    return 0;
}
