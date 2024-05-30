
#include "Basic_definitionsHeap.h"

pair<vector<int>,vector<double>> dijkstraHeap(vector<vector<pair<int,double>>> grafo, int raiz){
    
    vector<double> distancias(grafo.size(), INT_MAX);
    vector<int> previos(grafo.size(), INT_MIN);

    distancias[raiz] = 0;
    previos[raiz] = -1;

    QHeap cola = QHeap(grafo.size());

    vector<pair<double,int>> to_heap(grafo.size());

    to_heap[0] = {0,raiz};

    for (int i = 0; i < grafo.size(); i++){
        if (i != raiz){
            to_heap[i] = {INT_MAX, i};
        }
    }

    cola.buildHeap(to_heap);


    while(!cola.empty()){


        auto [distancia, nodo] = cola.top();
        cola.pop();

        for(auto [nodo_vecino,distancia_vecino]: grafo[nodo]){

            if(distancias[nodo_vecino] > distancias[nodo] + distancia_vecino){
                distancias[nodo_vecino] = distancias[nodo] + distancia_vecino;
                previos[nodo_vecino] = nodo;
                cola.decreaseKey(nodo_vecino, distancias[nodo]+distancia_vecino);
            }
        }
    }

    return {previos,distancias};
    
}
