#include "DijkstraHeap.h"
#include "graph_generator.h"

int main(int argc, char* argv[]) {


    auto start = high_resolution_clock::now();

    vector<vector<pair<int, double>>> graf = generadorGrafo(pow(2,atoi(argv[1])),(pow(2,atoi(argv[2]))));

    cout << "Grafo generado." << endl << endl;

    cout << "Aplicando Dijkstra con heap al grafo generado" << endl;

    pair<vector<int>,vector<double>> X = dijkstraHeap(graf,0);

    cout << "Listo" << endl;

    auto end = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(end - start);

    cout << duration.count() << endl;

    return 0;
}
