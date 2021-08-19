#include <iostream>

using namespace std;

int fibo(int);

int main() {
    int fibs = 10;

    cout << fibs << " first numbers in fibonacci sequence:\n";
    for (int i = 1; i <= 10; i++)
        cout << fibo(i) << endl;

    return 0;
}

int fibo(int element) {
    if (element == 1 || element == 2) return 1;
    return (fibo(element-1) + fibo(element-2));
}
