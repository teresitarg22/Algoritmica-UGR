
#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib> // Para usar srand y rand
#include <fstream> // Para usar ficheros
#include "../include/quickSort.h"
#include "../include/countingSort.h"
#include "../include/insertionSort.h"
#include "../include/selectionSort.h"
#include "../include/shellSort.h"

using namespace std;


int main(int argc, char **argv){

    if(argc < 4){
        printf("Faltan argumentos. Ejemplo: ./eficiencias fichero_salida 12345 tam_ejecucion_1 tam_ejecucion_2 ...\n");
        return(1);
    }else{

        unsigned long int semilla;
        int num_ejecucion = 3; //Los tres primeros elementos son el nombre del ejecutable, el nombre del fichero de salida y la semilla de rand
        semilla = atoi(argv[2]);
        srand(semilla);

        chrono::time_point<std::chrono::high_resolution_clock> t0, tf;
        unsigned long tejecucion;

        ofstream fsalida;

        // Abrimos fichero de salida
        fsalida.open(argv[1]);
        if (!fsalida.is_open()) {
            cerr<<"Error: No se pudo abrir fichero para escritura "<<argv[1]<<"\n\n";
            return 0;
        }

        while (num_ejecucion  < argc){

            vector<int> vec;
            unsigned int tam = atoi(argv[num_ejecucion]);
           
            // Generamos vector aleatorio de prueba, con componentes entre 0 y n-1
            for (int i= 0; i<tam; i++)
                vec.push_back(rand()%tam);

            cout << "Tiempo de ejecución(us) para vectores de  " << tam << " elementos." <<endl;
            fsalida<<tam<<" ";

            t0= std::chrono::high_resolution_clock::now();
            quickSort(vec);
            tf= std::chrono::high_resolution_clock::now();

            tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
            cout << "   Quick Sort: " << tejecucion << endl;
            fsalida<<tejecucion<<" ";

            t0= std::chrono::high_resolution_clock::now();
            countingSort(vec);
            tf= std::chrono::high_resolution_clock::now();

            tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
            cout << "   Counting Sort: " << tejecucion << endl;
            fsalida<<tejecucion<<" ";

            t0= std::chrono::high_resolution_clock::now();
            insertionSort(vec);
            tf= std::chrono::high_resolution_clock::now();

            tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
            cout << "   Insertion Sort: " << tejecucion << endl;
            fsalida<<tejecucion<<" ";

            t0= std::chrono::high_resolution_clock::now();
            shellSort(vec);
            tf= std::chrono::high_resolution_clock::now();

            tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
            cout << "   Shell Sort: " << tejecucion << endl;
            fsalida<<tejecucion<<" ";

            // t0= std::chrono::high_resolution_clock::now();
            // selectionSort(vec);
            // tf= std::chrono::high_resolution_clock::now();

            // tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
            // cout << "   Selection Sort: " << tejecucion << endl;
            // fsalida<<tejecucion<<" ";

            fsalida <<"\n";

            // //Muestra el vector ordenado
            // for (int i = 0; i < vec.size(); i++){
            //     cout << vec[i] << " ";
            // }

            // cout << endl; 
            
           
            
            num_ejecucion ++;

        }

        fsalida.close();
    }

   
}