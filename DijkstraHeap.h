 
#include "Basic_definitionsHeap.h"


/**
 * @brief Función que aplica el algoritmo de Dijkstra en un grafo dado un nodo raiz como punto de partida,
 * esta versión utiliza una Heap como estructura Q.
 * 
 * @param grafo Lista de adyacencia del grafo a utilizar, donde, para v aristas, estas van identificadas de 0 a v-1
 * @param raiz  Número del nodo raíz para aplicar del algoritmo
 * 
 * @param return Un par de vectores, el primero un vector de nodos previos, donde vector[i] es el nodo previo del camino mas corto para el nodo i,
 * el segundo vector es un vector de distancias, donde vector[i] es la distancia del nodo raíz al nodo i.
 * 
*/
pair<vector<int>,vector<double>> dijkstraHeap(vector<vector<pair<int,double>>> grafo, int raiz){

    
    //Se inicializan los vectores de distancias y previos con sus valores con defecto
    vector<double> distancias(grafo.size(), INT_MAX);
    vector<int> previos(grafo.size(), INT_MIN);

    //Distancia del nodo raiz a si mismo es 0, y se define su previo como -1
    distancias[raiz] = 0;
    previos[raiz] = -1;


    //Creamos un Heap para almacenar los pares 
    QHeap cola = QHeap();


    //Creamos vector de pares, del tipo {distancia,nodo}
    vector<pair<double,int>> to_heap(grafo.size());

    //El par del elemento en lugar de la raíz debe tener distancia 0, con el nodo a distancia 0 siendo la raíz
    to_heap[raiz] = {0,raiz};


    //Para los nodos distintos a la raíz
    for (int i = 0; i < grafo.size(); i++){
        //SI el nodo no es la raíz
        if (i != raiz){
            //Su valor es del tipo {INT_MAX, nodo}
            to_heap[i] = {INT_MAX, i};
        }
    }


    //Usamos función buildHeap para hacer un heapify del vector to_heap
    cola.buildHeap(to_heap);


    //Mientras la cola no este vacía
    while(!cola.empty()){

        // Extraemos el par con la menor distancia del heap
        auto [distancia, nodo] = cola.top();
        cola.pop();


        // Por cada par {vecino, distancia_vecino} en la lista de adyacencia del nodo 
        for(auto [nodo_vecino,distancia_vecino]: grafo[nodo]){

            // Revisamos si nos conviene mas pasar por medio de nodo a nodo_vecino
            if(distancias[nodo_vecino] > distancias[nodo] + distancia_vecino){
                //Cambiamos la distancia y previo
                distancias[nodo_vecino] = distancias[nodo] + distancia_vecino;
                previos[nodo_vecino] = nodo;
                //Disminuimos el valor de la distancia del nodo_vecino
                cola.decreaseKey(nodo_vecino, distancias[nodo]+distancia_vecino);
            }
        }
    }


    //Regresamos el par de vectores
    return {previos,distancias};
    
}