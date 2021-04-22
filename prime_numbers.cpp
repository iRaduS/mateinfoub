#include <iostream>
using namespace std;

unsigned int c[450000], k;
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
            c[k++] = p;
        }
    }
}

int main () {
    unsigned int n; cin >> n;
    sieve(n);

    // Numarul de divizori & Suma tuturor divizorilor (inclusiv 1, n)
    long long i = 0, p, nrDiv = 1, sumaDiv = 1, sumaDivPrimi = 0;
    while (c[i] * c[i] <= n) {
        p = 0;
        while (n % c[i] == 0) {
            n /= c[i];
            p++;
        }
        nrDiv *= (p + 1);

        sumaDiv *= (pow(c[i], p + 1) - 1) / (c[i] - 1);
        if (p)
            sumaDivPrimi += c[i];
        i++;
    }
    if (n > 1) {
        nrDiv *= 2;
        sumaDiv *= (n + 1); // n^2 - 1 = (n - 1)*(n + 1)

        sumaDivPrimi += n;
    }
//    while (n != 1) {
//        p = 0;
//        while (n % c[i] == 0) {
//            n /= c[i];
//            p++;
//        }
//        nrDiv *= (p + 1);
//
//        sumaDiv *= (pow(c[i], p + 1) - 1) / (c[i] - 1);
//        i++;
//    }
    cout << "Numarul de divizori este: " << nrDiv << "\nSuma divizorilor este: " << sumaDiv;

    // Sa se afiseze suma tuturor divizorilor lui N care nu sunt primi
    // Se scade suma divizorilor primi din suma tutror divizorilor
    cout << "\nSuma divizorilor care nu sunt primi: " << sumaDiv - sumaDivPrimi;

    return 0;
}