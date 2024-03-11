
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

            
            for (int i= 0; i<tam; i++){
                int random= rand()%tam;
                vec.push_back(random);
            }


            vector<int>v(vec);
            vector<int>v2(vec);
            vector<int>v3(vec);
            vector<int>v4(vec);
            vector<int>v5(vec);

            cout << "Tiempo de ejecución(us) para vectores de  " << tam << " elementos." <<endl;
            fsalida<<tam<<" ";

            //Algoritmo Counting Sort
            t0= std::chrono::high_resolution_clock::now();
            countingSort(v);
            tf= std::chrono::high_resolution_clock::now();

            tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
            cout << "\tCounting Sort: " << tejecucion << endl;
            fsalida<<tejecucion<<" ";

            //Algoritmo Insertion Sort
            t0= std::chrono::high_resolution_clock::now();
            insertionSort(v2);
            tf= std::chrono::high_resolution_clock::now();

            tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
            cout << "\tInsertion Sort: " << tejecucion << endl;
            fsalida<<tejecucion<<" ";

            
            //Algoritmo Quick Sort
            t0= std::chrono::high_resolution_clock::now();
            quickSort(v3);
            tf= std::chrono::high_resolution_clock::now();

            tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
            cout << "\tQuick Sort: " << tejecucion << endl;
            fsalida<<tejecucion<<" ";

            //Algoritmo SelectionSort
            t0= std::chrono::high_resolution_clock::now();
            selectionSort(vec);
            tf= std::chrono::high_resolution_clock::now();

            tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
            cout << "\tSelection Sort: " << tejecucion << endl;
            fsalida<<tejecucion<<" ";

            //Algoritmo Shell Sort
            t0= std::chrono::high_resolution_clock::now();
            shellSort(v5);
            tf= std::chrono::high_resolution_clock::now();

            tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
            cout << "\tShell Sort: " << tejecucion << endl;
            fsalida<<tejecucion<<" ";


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