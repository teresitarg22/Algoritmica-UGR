#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <limits>
using namespace std;

const int infinito = numeric_limits<int>::max();

// Función para leer la matriz desde un archivo
void leerMatrizDesdeArchivo(const string& nombreArchivo, vector<vector<int>> & afinidades) {
    ifstream archivo(nombreArchivo);  // Abrir el archivo en modo lectura

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return;
    }

    int numeroFilas;
    int valor;
    archivo >> numeroFilas;  // Leer el número de filas desde el archivo

   
    afinidades.resize(numeroFilas, vector<int>(numeroFilas, -1));  // Crear la matriz

    // Leer los valores de la matriz desde el archivo
    for (int i = 0; i < numeroFilas; ++i) {

        for (int j = 0; j < numeroFilas; ++j) {
            archivo >> valor;
            if(valor != -1)
                afinidades[i][j] = valor;
            else
                afinidades[i][j] = infinito;
        }
    }
    

    archivo.close();  // Cerrar el archivo

}

void algoritmoTiempoMinimo(vector<vector<int>> & tiempos, vector<vector<int>> &  P, vector<vector<int>>  & tiempos_min){
    
    //Inicializamos las matrices tiempos_min y P
    for(int i = 0; i < tiempos.size(); i++){
        for(int j = 0; j< tiempos.size(); j++){
            tiempos_min[i][j] = tiempos[i][j];
            
            if(tiempos[i][j] == infinito){
                P[i][j]  =-1;
            }else{
                P[i][j] = j;
            }
        }
    }

    for(int m = 0; m < tiempos.size(); m ++){

        for(int i = 0; i < tiempos.size(); i++){

            for(int j = 0; j < tiempos.size(); j++){

                if(tiempos_min[i][m] != infinito && tiempos_min[m][j] != infinito){  
                    
                    //Si el tiempo mínimo de i a j es haciendo escala en m 
                    if( tiempos_min[i][j] >  (tiempos_min[i][m] + tiempos_min[m][j] + 1) ){
                        tiempos_min[i][j] = tiempos_min[i][m] + tiempos_min[m][j] + 1;
                        P[i][j] = m;
                    }
                }
            }
        }
    }

}

vector<int> algoritmoDeRecuperacion(vector<vector<int>> &  P, int origen, int destino){
    int origenInicial = origen;
    vector<int> salida;
    
    
    salida.push_back(origenInicial);
    
    while(P[origen][destino] != destino){
        salida.push_back( P[origen][destino]);
        origen = P[origen][destino];
        
    }

    if(origenInicial != destino)
        salida.push_back( destino );

    
    return salida;
    
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Uso: " << argv[0] << " tiempos.txt origen destino" << endl;
        return 1;  // Salir del programa con un código de error
    }

    string nombreArchivo = argv[1];

    vector<vector<int>> tiempos;
    vector<vector<int>> P;
    vector<vector<int>> tiempos_min;

    int origen, destino;

    leerMatrizDesdeArchivo(nombreArchivo, tiempos);

    try {
        origen = std::stoi(argv[2]);
        if(origen <= 0 || origen > tiempos.size()){
            cout << "El origen tiene que ser un número en el rango [1," << tiempos.size() <<"]"<<endl;
            return 1;
        }

    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: El origen no es un número válido." << std::endl;
        return 1;
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: El origen está fuera del rango de un int." << std::endl;
        return 1;
    }

    try {
         destino = std::stoi(argv[3]);
        if(destino <=0 || destino > tiempos.size()){
            cout << "El destino tiene que ser un número en el rango [0," << tiempos.size() <<"]"<<endl;
            return 1;
        }

    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: El destino no es un número válido." << std::endl;
        return 1;
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: El destino está fuera del rango de un int." << std::endl;
        return 1;
    }


    P.resize( tiempos.size(),vector<int>(tiempos.size(), -1));
    tiempos_min.resize( tiempos.size(),vector<int>(tiempos.size(), -1));

    algoritmoTiempoMinimo(tiempos,P,tiempos_min);


    cout << "Tiempo mínimo para viajar de " << origen << " a " << destino << " es de " << tiempos_min[origen-1][destino-1] << " horas." <<endl;
    cout << "El camino más corto es: ";
    vector<int> camino = algoritmoDeRecuperacion(P, origen-1, destino -1);

    for(int i = 0; i < camino.size(); i++){
        cout << camino [i]+1; 
       
        if(i< camino.size()-1){
            cout << " -> ";
        }
    }

    cout <<endl;

    return 0;
}