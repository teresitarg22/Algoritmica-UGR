#include <iostream>
#include <chrono>
#include <cstdlib> // Para usar srand y rand
#include <fstream> // Para usar ficheros

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

int main(int argc, char **argv){

    if(argc < 4){
        printf("Faltan argumentos. Ejemplo: ./producto_tres_elementos_basico <fichero_salida> 12345 tam_ejecucion_1 tam_ejecucion_2 ...\n");
        return(1);
    }else{
        unsigned long int semilla;
        int num_ejecucion = 3; //Los tres primeros elementos son el nombre del ejecutable, el nombre del fichero de salida y la semilla de rand
        semilla = atoi(argv[2]);
        srand(semilla);

        chrono::time_point<std::chrono::high_resolution_clock> t0, tf;
        unsigned long tejecucion;

        ofstream fsalida;

        // ----------------------------
        // Abrimos fichero de salida
        fsalida.open(argv[1]);
        if (!fsalida.is_open()) {
            cerr<<"Error: No se pudo abrir fichero para escritura "<<argv[1]<<"\n\n";
            return 0;
        }

        while (num_ejecucion  < argc){

            unsigned long int num = atoi(argv[num_ejecucion]);

            t0= std::chrono::high_resolution_clock::now();
            if (ProductoTresElementos(num,1,num)) {
                cout << num << " puede expresarse como producto de tres números naturales consecutivos." << endl;
            } else {
                cout << num << " no puede expresarse como producto de tres números naturales consecutivos." << endl;
            }

            tf= std::chrono::high_resolution_clock::now();
            
            tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
            cout << "Tiempo de ejecución: " << tejecucion << "(us) para número  " << num <<endl;
            fsalida<<num<<" "<<tejecucion<<"\n";
            
            num_ejecucion ++;
        }

        fsalida.close();
    }
}