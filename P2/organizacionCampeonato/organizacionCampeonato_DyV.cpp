#include <iostream>
#include <vector>
#include <set>
#include <chrono>
#include <math.h>
#include <fstream> // Para usar ficheros

using namespace std;

int organizacionCampeonato(vector< vector<int> > & calendario, vector <int> equipos, vector<int> rivales){
    //caso base
    int jornadaActual;
    int ultimaAsignada;

    if(equipos.size() == 1){
        
        calendario[0][equipos[0]] = rivales[0];
        calendario[0][rivales[0]] = equipos[0];

        return 1;
    }

    else{

        vector<int> equipos1, equipos2;
        vector<int> rivales1, rivales2;

        //Dividimos por la mitad tanto los rivales como los equipos para dividir cada uno en dos subvectores de equipos y rivales
        for(unsigned long int i = 0; i < equipos.size()/2; i++){
            
            equipos1.push_back(equipos[i]);
            equipos2.push_back(rivales[i]);
        
            rivales1.push_back(equipos[i+equipos.size()/2]);
            rivales2.push_back(rivales[i+equipos.size()/2]);
            

        }


        //Llamamos recursivamente para que ejecute la función con los nuevos subvectores
        jornadaActual = organizacionCampeonato(calendario,equipos1,rivales1);
        organizacionCampeonato(calendario, equipos2, rivales2);

        //Una vez se han organizado en esa llamada, solo falta enfrentar a los equipos con sus rivales en las siguientes jornadas
         set<int> restantes;
         set<int> jugadosJornada;
         
        for(unsigned long int equipo = 0; equipo < equipos.size(); equipo++){
            int jornada = jornadaActual;
            restantes.clear();

            //Rellenamos los rivales que existen
            for(unsigned long int i = 0; i < rivales.size(); i++){
                restantes.insert(rivales[i]);
            }                  

            //Recorremos el set de rivales restantes para insertar el que se pueda en la jornada

            auto rival = restantes.begin();

            
            while(restantes.size() != 0){
                jugadosJornada.clear();
                //Comprobamos contra que rivales se ha jugado esta jornada
                for(unsigned long int i = 0; i < equipo; i++){
                    jugadosJornada.insert(calendario[jornada][equipos[i]]);
                }

                if(jugadosJornada.find(*rival) == jugadosJornada.end()){
                    
                    
                    calendario[jornada][equipos[equipo]] = *rival;
                    calendario[jornada][*rival] = equipos[equipo];

                    restantes.erase(*rival);

                    rival = restantes.begin();
                    jornada++;

                }else{
                    
                    rival++;
                    
                    if(rival==restantes.end()){
                        rival = restantes.begin();
                    }
                }

            }

            ultimaAsignada = jornada;
            
        }


        jornadaActual = ultimaAsignada;

        return jornadaActual;  
    }
   
}


int main (int argc, char **argv){

    if(argc < 3){
        printf("Faltan argumentos. Ejemplo: ./organizacionCampamento_Basico salida.txt exponente_1 exponente_2 ... \n");
        return(1);
    }else{

        int numEquipos;
        vector< vector<int>> calendario; 
        vector<int> equipos, rivales;
        chrono::time_point<std::chrono::high_resolution_clock> t0, tf;

        ofstream fsalida;


        unsigned long tejecucion;

        fsalida.open(argv[1]);
        if (!fsalida.is_open()) {
            cerr<<"Error: No se pudo abrir fichero para escritura "<<argv[1]<<"\n\n";
            return 0;
        }
        
        for(int i = 2; i < argc; i++ ){

            numEquipos= atoi(argv[i]);

            if(numEquipos == 0 || numEquipos > 29){
                printf("El exponente tiene que ser mayor que 0 y menor que 30\n");
                return 1;
            }

            numEquipos = pow(2,numEquipos);
            calendario = vector<vector<int>>(numEquipos-1, vector<int> (numEquipos,-1));
            equipos.clear();
            rivales.clear();


            for(int i = 0; i < numEquipos/2; i++){
                equipos.push_back(i);
                rivales.push_back(i+numEquipos/2);
            }


            t0= std::chrono::high_resolution_clock::now();

            organizacionCampeonato(calendario,equipos,rivales);


            tf= std::chrono::high_resolution_clock::now();

            tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();

            cout << "Tiempo de ejecución: " << tejecucion <<  "(us) para competición con  " << numEquipos << " equipos." <<endl;
            fsalida<<numEquipos<<" "<<tejecucion<<"\n";

        ///////DESCOMENTAR LAS LINEAS DE ABAJO SI SE QUIERE VER EL RESULTADO FINAL (CADA FILA ES UNA JORNADA, CADA COLUMNA UN EQUIPO)

            // for(unsigned long int i = 0; i < calendario.size(); i++){
            //     for( unsigned long int j = 0; j < calendario[i].size(); j++){
            //         if (calendario[i][j] < 10 && calendario[i][j] >= 0)
            //             cout << calendario [i][j] << "  ";
            //         else
            //              cout << calendario [i][j] << " ";
            //     }

            //     cout << endl;
            // }
        }

        fsalida.close();
    }
    
    
}