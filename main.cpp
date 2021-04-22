#include <iostream>
#include <cstring>
using namespace std;

void sieve(unsigned int n) {
    bool* primes = new bool[n + 1];
    memset(primes, true, (n + 1) * sizeof(bool));
    for (int i = 4; i <= n; i += 2) { // O(n)
        primes[i] = false;
    }
    for (int i = 3; i * i <= n; i += 2) {
        if (primes[i]) {
            for (int j = i * i; j <= n; j += 2 * i) {
                primes[j] = false;
            }
        }
    }
    for (int p = 2; p <= n; p++) {
        if (primes[p]) {
            cout << p << ' ';
        }
    }
}

int main() {
    unsigned int n; cin >> n;
    sieve(n);

    return 0;
}