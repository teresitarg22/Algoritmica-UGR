#include <iostream>
#include "../include/quickSort.h"

using namespace std;

void unir(vector<int> & vec, vector<int> & vIzq, int & pivote, vector<int> & vDcha){
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

 int comparaTres( vector<int> &vec){
    
    int ret; 
    int a = 0, b = 1, c = vec.size()-1;

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

void quickSort(vector<int> & vec){

    if(vec.size() == 1){
        //Si el tamaño es 1 entonces no hay que seguir ordenando
        return;

    }else{
        //Seleccionamos el pivote 

        int posPivote, pivote;

        if(vec.size() >=3){

            posPivote = comparaTres(vec);
            pivote = vec[posPivote];
        
        }else{
            posPivote = 0;
            pivote = vec[0];
        }

        //Dividimos el vector en dos vectores. vDcha contiene elementos mayores que el pivote y vIzq los menores o iguales

        vector<int> vDcha;
        vector<int> vIzq;

        for(int i = 0; i < vec.size() ; i ++){
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
