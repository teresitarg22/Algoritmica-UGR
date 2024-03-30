#include <iostream>
using namespace std;

bool ProductoTresElementos(int N) {
    for (int i = 1; i <= N / 3; i++) {
        if (N % i == 0 && N % (i + 1) == 0 && N % (i + 2) == 0) { 
            if ( i * (i + 1) * (i + 2) == N) {   
                cout << "i: " << i << " i+1: " << i + 1 << " i+2: " << i + 2 << "\n"; 
                return true;
            }
        }
    }
    return false;
}

int main() {
    int N;
    cout << "Ingrese un número natural: ";
    cin >> N;

    if (ProductoTresElementos(N)) {
        cout << N << " puede expresarse como producto de tres números naturales consecutivos." << endl;
    } else {
        cout << N << " no puede expresarse como producto de tres números naturales consecutivos." << endl;
    }

    return 0;
}