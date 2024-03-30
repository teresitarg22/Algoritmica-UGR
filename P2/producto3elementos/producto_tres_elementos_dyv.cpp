#include <iostream>

using namespace std;

bool ProductoTresElementos(int N, int inicio, int fin) {
    // Caso base: si el inicio supera al fin no hay solución en este rango
    if (inicio > fin) {
        return false;
    }

    int medio = (inicio + fin) / 2; 

    // Caso 1 producto == N, FIN: el producto de los tres números consecutivos en el rango medio es igual a N
    if (medio * (medio + 1) * (medio + 2) == N) {
        cout << "i: " << medio << " i+1: " << medio + 1 << " i+2: " << medio + 2 << "\n"; 
        return true;
    }

    // Caso 2, N es menor: Si N es menor que el producto de los tres números consecutivos en el rango medio,
    // buscar en la primera mitad del rango.
    if (medio * (medio + 1) * (medio + 2) > N) {
        return ProductoTresElementos(N, inicio, medio - 1);
    }
    // Caso 3, n es mayor: Si N es mayor que el producto de los tres números consecutivos en el rango medio,
    // buscar en la segunda mitad del rango.
    else {
        return ProductoTresElementos(N, medio + 1, fin);
    }
}

int main() {
    int N;
    cout << "Ingrese un número natural: ";
    cin >> N;

    if (ProductoTresElementos(N, 1, N)) {
        cout << N << " puede expresarse como producto de tres números naturales consecutivos." << endl;
    } else {
        cout << N << " no puede expresarse como producto de tres números naturales consecutivos." << endl;
    }

    return 0;
}