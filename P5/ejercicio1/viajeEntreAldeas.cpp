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

void algoritmoTiempoMinimo(vector<vector<int>> & costes, vector<vector<int>> &  P, vector<vector<int>>  & costes_min){
    
    //Inicializamos las matrices tiempos_min y P
    for(int i = 0; i < costes.size(); i++){
        for(int j = 0; j< costes.size(); j++){
            costes_min[i][j] = costes[i][j];
            
            if(costes[i][j] == infinito){
                P[i][j]  =-1;
            }else{
                P[i][j] = j;
            }
        }
    }

    for(int m = 0; m < costes.size(); m ++){

        for(int i = 0; i < costes.size(); i++){

            for(int j = i; j < costes.size(); j++){

                
                if(costes_min[i][m] != infinito && costes_min[m][j] != infinito){
                    //Si el coste mínimo de i a j es pasando por en m 
                    if( costes_min[i][j] >  (costes_min[i][m] + costes_min[m][j] ) ){
                        costes_min[i][j] = costes_min[i][m] + costes_min[m][j];
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
        cout << "Uso: " << argv[0] << " costes.txt origen destino" << endl;
        return 1;  // Salir del programa con un código de error
    }

    string nombreArchivo = argv[1];

    vector<vector<int>> costes;
    vector<vector<int>> P;
    vector<vector<int>> costes_min;

    int origen, destino;
    leerMatrizDesdeArchivo(nombreArchivo, costes);

    try {
        origen = std::stoi(argv[2]);
        if(origen <= 0 || origen > costes.size()){
            cout << "El origen tiene que ser un número en el rango [1," << costes.size() <<"]"<<endl;
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
        if(destino <=0 || destino > costes.size() || destino < origen){
            cout << "El destino tiene que ser un número en el rango [0," << costes.size() <<"] y tiene que ser mayor que el origen."<<endl;
            return 1;
        }

    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: El destino no es un número válido." << std::endl;
        return 1;
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: El destino está fuera del rango de un int." << std::endl;
        return 1;
    }


    P.resize( costes.size(),vector<int>(costes.size(), -1));
    costes_min.resize( costes.size(),vector<int>(costes.size(), -1));

    algoritmoTiempoMinimo(costes,P,costes_min);


    cout << "Coste mínimo para viajar de " << origen << " a " << destino << " es de " << costes_min[origen-1][destino-1] <<endl;
    cout << "El camino más corto recorrido es: ";
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