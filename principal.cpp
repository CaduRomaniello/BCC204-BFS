#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include "BFS.hpp"

using namespace std;

int main(){

    // Criacao e inicializacao do grafo
    Grafo grafo = Grafo();
    grafo.inicializaGrafo();

    // BFS
    vector<int> ordemVisitacao = grafo.BFS();

    // Print final
    printFinal(ordemVisitacao);

    return 0;

}