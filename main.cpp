#include "DijkstraHeap.h"
#include "graph_generator.h"


int main(int argc, char* argv[]) {


    auto start = high_resolution_clock::now();

    vector<vector<pair<int, double>>> graf = generadorGrafo(pow(2,atoi(argv[1])),(pow(2,atoi(argv[2]))));

    pair<vector<int>,vector<double>> X = dijkstraHeap(graf,0);


    auto end = high_resolution_clock::now();

    auto duration = duration_cast<seconds>(end - start);

    cout << duration.count() << endl;

    return 0;
}
