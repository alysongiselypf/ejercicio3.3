#include <iostream>
#include <cmath>
#include <bitset>

using namespace std;

class BoothMultiplier {
private:
    int n; // Número de bits
    int A, Q, M, Q_1, count;

    int toComplement2(int num) {
        if (num < 0)
            return ((1 << n) + num);
        return num;
    }

    void arithmeticShift() {
        int signA = (A >> (n - 1)) & 1;
        Q_1 = Q & 1;
        Q = (Q >> 1) | (A << (n - 1));
        A = (A >> 1) | (signA << (n - 1));
    }

    void addM() {
        A += M;
    }

    void subM() {
        A -= M;
    }

    void printState(string step) {
        cout << step << " A = " << bitset<5>(A) << ", Q = " << bitset<5>(Q) << ", Q-1 = " << Q_1 << "\n";
    }

public:
    BoothMultiplier(int multiplicand, int multiplier, int bits) : n(bits) {
        M = toComplement2(multiplicand);
        Q = toComplement2(multiplier);
        A = 0;
        Q_1 = 0;
        count = n;
    }

    int multiply() {
        cout << "Inicio: ";
        printState("");
        while (count > 0) {
            cout << "Evaluar: Q0 = " << (Q & 1) << ", Q-1 = " << Q_1 << "\n";
            int lastTwoBits = (Q & 1) | (Q_1 << 1);
            if (lastTwoBits == 1) {
                cout << "A = A + M: ";
                addM();
                printState("");
            }
            else if (lastTwoBits == 2) {
                cout << "A = A - M: ";
                subM();
                printState("");
            }
            cout << "Despues de corrimiento: ";
            arithmeticShift();
            printState("");
            count--;
        }
        cout << "Resultado final en A y Q: ";
        printState("");
        return (A << n) | Q;
    }
};

int main() {
    int multiplicand, multiplier, bits;
    cout << "Ingrese el multiplicando: ";
    cin >> multiplicand;
    cout << "Ingrese el multiplicador: ";
    cin >> multiplier;
    cout << "Ingrese el numero de bits: ";
    cin >> bits;

    BoothMultiplier booth(multiplicand, multiplier, bits);
    int result = booth.multiply();

    cout << "Resultado: " << result << "\n";
    return 0;
}
