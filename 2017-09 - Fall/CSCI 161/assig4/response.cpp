#include <iostream>
#include <cstring>

using namespace std;

int main() {
    char response[4];
    char remaining;

    cout << "Less than " << 4 << " chars: ";
    cin >> response;
    cin >> remaining;

    cout << endl << "Response:  " << response
         << endl << "Resp size: " << strlen(response)
         << endl << "Remaining: " << remaining;

    return 0;
}
