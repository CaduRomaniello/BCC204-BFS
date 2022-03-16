#ifndef BFS_H
#define BFS_H

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iterator>

using namespace std;

class Aresta{
    public:

        //Atributos
        int id;
        int origem;
        int destino;
        double peso;
        bool visitado;
        bool direcionado;

        //Metodos
        Aresta(int id = -1, int origem = -1, int destino = -1, double peso = -1.0, bool visitado = false, bool direcionado = false);
        ~Aresta();

        void printInfo();
};

class Vertice{
    public:

        //Atributos
        int id;
        bool visitado;
        list<int> adjacencia;

        //Metodos
        Vertice(int id, bool visitado = false);
        ~Vertice();

        void printInfo();
};

class Grafo{
    public:

        //Atributos
        int qntd_vertices;
        int qntd_arestas;
        int vertice_inicial;
        bool direcionado;
        vector<Vertice> vertices;
        vector<Aresta> arestas;

        //Metodos
        Grafo();
        Grafo(int qntd_vertices, int qntd_arestas, int vertice_inicial, bool direcionado);
        ~Grafo();

        void inicializaGrafo();
        vector<int> BFS();

        void printInfo();
};

void printFinal(vector<int> ordemVisitacao);

#endif
