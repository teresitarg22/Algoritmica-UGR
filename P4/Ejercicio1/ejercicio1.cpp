#include <iostream>
#include <fstream>
#include <vector>
#include <set>
using namespace std;

// Función para leer la matriz desde un archivo
void leerMatrizDesdeArchivo(const string& nombreArchivo, vector<vector<int>> & afinidades) {
    ifstream archivo(nombreArchivo);  // Abrir el archivo en modo lectura

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return;
    }

    int numeroFilas;
    archivo >> numeroFilas;  // Leer el número de filas desde el archivo

    if (numeroFilas % 2 != 0) {
        cout << "El número de filas debe ser par." << endl;
        archivo.close();
        return;
    }

     afinidades.resize(numeroFilas, vector<int>(numeroFilas, -1));  // Crear la matriz

    // Leer los valores de la matriz desde el archivo
    for (int i = 0; i < numeroFilas; ++i) {

        for (int j = 0; j < numeroFilas; ++j) {
            archivo >> afinidades[i][j];
        }
    }
    

    archivo.close();  // Cerrar el archivo

}


int crearParejas(const vector<vector<int>> & matrizAfinidad, vector<int> &parejas){
    set<int> candidatos;

    for(long unsigned int i = 0; i < parejas.size(); i++){
        candidatos.insert(i);
    }

    int afinidadTotal = 0; 

    while(candidatos.size() > 0){

        int alumno = *candidatos.begin();
        candidatos.erase(alumno);

        int mayorAfinidad = 0; 
        int pareja = -1;

        for(auto j = candidatos.begin();  j != candidatos.end(); j++){
            int afinidad = matrizAfinidad[alumno][*j] * matrizAfinidad[*j][alumno];

            if ( afinidad > mayorAfinidad){
                mayorAfinidad = afinidad;
                pareja = *j;
            }
        }

        parejas[alumno] = pareja;
        parejas[pareja] = alumno;

        afinidadTotal += mayorAfinidad;
        candidatos.erase(pareja);

    }

    return afinidadTotal;
}

int crearParejasBackTracking(const vector<vector<int>> & matrizAfinidad, vector<int> &parejas, set<int>&disponibles, vector<int> &parejasTemporal,int afinidad, int &afinidadMaxima){
    
    //Ultima pareja
    if(disponibles.size() == 2){
        //Escogemos la primera persona disponible
        auto alumno = disponibles.begin();
        auto pareja = alumno++;
        //Asignamos al alumno su pareja y viceversa
        parejasTemporal[*alumno] = *pareja;
        parejasTemporal[*pareja] = *alumno;

        afinidad += matrizAfinidad[*alumno][*pareja]* matrizAfinidad[*pareja][*alumno];
        if (afinidad > afinidadMaxima){
            afinidadMaxima = afinidad;
            parejas = parejasTemporal;
        }

    }else{

        set<int> disponiblesDespuesDeElegir = disponibles;
        int afinidadHastaElMomento = afinidad;
        for( auto i =  disponibles.begin(); i != disponibles.end(); i++){
            //cout << "paso por aqui" <<endl;
            disponiblesDespuesDeElegir.erase(*i);
            
            
            for(auto j = disponibles.begin(); j != disponibles.end(); j++){

                if(i!=j){
                    parejasTemporal[*i] = *j;
                    parejasTemporal[*j] = *i;

                    afinidad += matrizAfinidad[*i][*j]* matrizAfinidad[*j][*i];

                    
                    disponiblesDespuesDeElegir.erase(*j);


                    crearParejasBackTracking(matrizAfinidad, parejas,disponiblesDespuesDeElegir,parejasTemporal, afinidad, afinidadMaxima);
                    disponiblesDespuesDeElegir.insert(*j);
                }
                afinidad = afinidadHastaElMomento;
                
            }

            disponiblesDespuesDeElegir.insert(*i);
            
        }

    }

    
    return afinidad;

}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Uso: " << argv[0] << " afinidades.txt" << endl;
        return 1;  // Salir del programa con un código de error
    }

    string nombreArchivo = argv[1];

    vector<vector<int>> afinidades;
    leerMatrizDesdeArchivo(nombreArchivo, afinidades);

    vector<int> parejas (afinidades.size(),-1);
    vector<int> parejasTemporal (afinidades.size(),-1);
    set<int> disponibles;
    int afinidad = 0;

    for(long unsigned int i = 0; i < afinidades.size(); i ++){
        disponibles.insert(i);
    }

    //int afinidadTotal = crearParejas(afinidades,parejas);
    int afinidadTotal =0;
    crearParejasBackTracking(afinidades, parejas, disponibles,parejasTemporal, afinidad, afinidadTotal);

    // // Mostrar la matriz en la consola
   
    // for (long unsigned int i = 0; i < afinidades.size(); ++i) {
    //     for (long unsigned int j = 0; j < afinidades[i].size(); ++j) {
    //         cout << afinidades[i][j] << " ";
    //     }
    //     cout << endl;
    // }


    //Mostrar las parejas elegidas

    for(long unsigned int i = 0; i < parejas.size(); i++){
        cout << parejas[i] << " ";
    }

    cout << endl << "Afinidad total: " << afinidadTotal <<endl;

    return 0;
}