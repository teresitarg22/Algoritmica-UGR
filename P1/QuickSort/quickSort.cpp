#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib> // Para usar srand y rand
#include <fstream> // Para usar ficheros

using namespace std;

void unir(vector<long int> & vec, vector<long int> & vIzq, long int & pivote, vector<long int> & vDcha){
    // for(int i = 0; i < vDcha.size(); i ++){
    //         vec[i] = vDcha[i];
    //     }

    //     vec[vDcha.size()] = pivote;

    //     for(int i = 0 ; i < vIzq.size(); i++){
    //         vec[vDcha.size()+1+i] = vIzq[i];
    //     }
    

    vec = vIzq;

    vec.push_back(pivote);
    
    for(int i = 0; i < vDcha.size(); i++){
        vec.push_back(vDcha[i]);
    }

    
}

long int comparaTres( vector<long int> &vec){
    
    long int ret; 
    long int a = 0, b = 1, c = vec.size()-1;

    if(vec[a] >= vec[b]){
        if(vec[a]>= vec[c]){
            ret =  a;
        }else{
            ret = c;
        }
    }else{
        if(vec[b] >= vec[c]){
            ret = b;
        }else{
            ret = c;
        }
    }

    return ret;
}

void quickSort(vector<long int> & vec){

    if(vec.size() == 1){
        //Si el tamaño es 1 entonces no hay que seguir ordenando
        return;

    }else{
        //Seleccionamos el pivote 

        long int posPivote, pivote;

        if(vec.size() >=3){

            posPivote = comparaTres(vec);
            pivote = vec[posPivote];
        
        }else{
            posPivote = 0;
            pivote = vec[0];
        }

        //Dividimos el vector en dos vectores. vDcha contiene elementos mayores que el pivote y vIzq los menores o iguales

        vector<long int> vDcha;
        vector<long int> vIzq;

        for(long int i = 0; i < vec.size() ; i ++){
            if(i != posPivote){
                if (vec[i] <= pivote){
                    vIzq.push_back(vec[i]);
                }else{
                    vDcha.push_back(vec[i]);
                }
            }
        }

        //Ejecutamos de nuevo QuickSort a los subvectores que hemos creado
        if(vDcha.size() >0){
            quickSort(vDcha);
        }

        if(vIzq.size() >0){
            quickSort(vIzq);
        }

        unir(vec,vIzq,pivote,vDcha);
    }
}


int main(int argc, char **argv){

    if(argc < 4){
        printf("Faltan argumentos. Ejemplo: ./quickSort fichero_salida 12345 tam_ejecucion_1 tam_ejecucion_2 ...\n");
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

            vector<long int> vec;
            unsigned long int tam = atoi(argv[num_ejecucion]);
           
            // Generamos vector aleatorio de prueba, con componentes entre 0 y n-1
            for (int i= 0; i<tam; i++)
                vec.push_back(rand()%tam);


            t0= std::chrono::high_resolution_clock::now();
            quickSort(vec);
            tf= std::chrono::high_resolution_clock::now();

            // //Muestra el vector ordenado
            // for (int i = 0; i < vec.size(); i++){
            //     cout << vec[i] << " ";
            // }

            // cout << endl; 
            
            tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
            cout << "Tiempo de ejecución: " << tejecucion << "(us) para vectores de  " << tam << " elementos." <<endl;
            fsalida<<tam<<" "<<tejecucion<<"\n";
            
            num_ejecucion ++;

            // vector<long int> vec;
            // cout << vec.max_size()<<endl;
            // num_ejecucion ++;
        }

        fsalida.close();
    }

   
}