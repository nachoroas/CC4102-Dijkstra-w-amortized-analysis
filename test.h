#include "DijkstraHeap.h"
#include "DijkstraFibonacci.h"
#include "graph_generator.h"


void test(vector<int> vertex, vector<int> edges){

    for(int i: vertex){

        cout << "Cantidad de vertices: 2^" << i << endl;

        for(int j: edges){

            vector<double> tiempos_heap;
            vector<double> tiempos_fibonacci;
            double suma_tiempo_heap = 0;
            double suma_tiempo_fibonacci = 0;

            cout << "Test con: 2^" << j << " aristas" << endl;

            if((pow(2,i)*pow(2,i-1))/2 < pow(2,j)){

                cout << "La cantidad de aristas solicitada supera a la máxima cantidad de aristas para el grafo" << endl << endl;
                continue;
            }

            vector<vector<pair<int,double>>> grafo_test;

            // Los 50 tests

            for(int k = 0; k < 50; k++){

                // Generamos grafo

                auto start = high_resolution_clock::now();

                grafo_test = generadorGrafo(pow(2,i),pow(2,j));

                auto end = high_resolution_clock::now();

                auto duration = duration_cast<milliseconds>(end - start);

                cout << "Tiempo grafo: " << duration.count() <<" milisegundos" << endl;

                // Medimos tiempo para heap

                start = high_resolution_clock::now();

                dijkstraHeap(grafo_test,0);

                end = high_resolution_clock::now();

                duration = duration_cast<milliseconds>(end - start);

                suma_tiempo_heap += duration.count();

                tiempos_heap.push_back(duration.count());

                // Medimos tiempo para fibonacci

                start = high_resolution_clock::now();

                dijkstraFibonacci(grafo_test,0);

                end = high_resolution_clock::now();

                duration = duration_cast<milliseconds>(end - start);

                suma_tiempo_fibonacci += duration.count();

                tiempos_fibonacci.push_back(duration.count());
            }

            // Medidas de estadistica bla bla bla

            double promedio_tiempo_heap = suma_tiempo_heap / 50;

            double promedio_tiempo_fibonacci = suma_tiempo_fibonacci / 50;

            // desviaciones 

            double deviation_heap = 0;
            double deviation_fibonacci = 0;

            // Sumamos primero las diferencias con el promedio al cuadrado y luego dividimos por 50

            for(int k = 0; k < 50; k++){
                deviation_heap += (tiempos_heap[k] - promedio_tiempo_heap)*(tiempos_heap[k] - promedio_tiempo_heap);
                deviation_fibonacci += (tiempos_fibonacci[k] - promedio_tiempo_fibonacci)*(tiempos_fibonacci[k] - promedio_tiempo_fibonacci);
            }

            deviation_heap = sqrt(deviation_heap / 50);
            deviation_fibonacci = sqrt(deviation_fibonacci / 50);


            // Imprimimos 

            cout << "Medidas para heap: " << endl;
            cout << "Promedio de tiempo: " << promedio_tiempo_heap << " milisegundos" << endl;
            cout << "Desviación estandar:" << deviation_heap << " milisegundos" << endl;

            cout << "Medidas para fibonacci: " << endl;
            cout << "Promedio de tiempo: " << promedio_tiempo_fibonacci << " milisegundos" << endl;
            cout << "Desviación estandar:" << deviation_fibonacci << " milisegundos" << endl;
        }

        // Espacios para separar

        cout << endl << endl;
    }
}