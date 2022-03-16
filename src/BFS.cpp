#include "BFS.hpp"

using namespace std;

/*
███████╗██╗   ██╗███╗   ██╗ ██████╗ ██████╗ ███████╗███████╗
██╔════╝██║   ██║████╗  ██║██╔════╝██╔═══██╗██╔════╝██╔════╝
█████╗  ██║   ██║██╔██╗ ██║██║     ██║   ██║█████╗  ███████╗
██╔══╝  ██║   ██║██║╚██╗██║██║     ██║   ██║██╔══╝  ╚════██║
██║     ╚██████╔╝██║ ╚████║╚██████╗╚██████╔╝███████╗███████║
╚═╝      ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝ ╚═════╝ ╚══════╝╚══════╝
*/

void printFinal(vector<int> ordemVisitacao){
    for (int i = 0; i < static_cast<int>(ordemVisitacao.size()); i++){
        cout << ordemVisitacao[i] << "\n";
    }
}

/*
 █████╗ ██████╗ ███████╗███████╗████████╗ █████╗ 
██╔══██╗██╔══██╗██╔════╝██╔════╝╚══██╔══╝██╔══██╗
███████║██████╔╝█████╗  ███████╗   ██║   ███████║
██╔══██║██╔══██╗██╔══╝  ╚════██║   ██║   ██╔══██║
██║  ██║██║  ██║███████╗███████║   ██║   ██║  ██║
╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝╚══════╝   ╚═╝   ╚═╝  ╚═╝
*/

Aresta::Aresta(int id, int origem, int destino, double peso, bool visitado, bool direcionado){
    this->id = id;
    this->origem = origem;
    this->destino = destino;
    this->peso = peso;
    this->visitado = visitado;
    this->direcionado = direcionado;
}
Aresta::~Aresta(){}

void Aresta::printInfo(){
    cout << "--------- Aresta ---------\n";
    cout << "Id         : " << this->id << "\n" ;
    cout << "Origem     : " << this->origem << "\n" ;
    cout << "Destino    : " << this->destino << "\n" ;
    cout << "Peso       : " << this->peso << "\n" ;
    cout << "Visitado   : " << this->visitado << "\n" ;
    cout << "Direcionado: " << this->direcionado << "\n\n" ;
}

/*
██╗   ██╗███████╗██████╗ ████████╗██╗ ██████╗███████╗
██║   ██║██╔════╝██╔══██╗╚══██╔══╝██║██╔════╝██╔════╝
██║   ██║█████╗  ██████╔╝   ██║   ██║██║     █████╗  
╚██╗ ██╔╝██╔══╝  ██╔══██╗   ██║   ██║██║     ██╔══╝  
 ╚████╔╝ ███████╗██║  ██║   ██║   ██║╚██████╗███████╗
  ╚═══╝  ╚══════╝╚═╝  ╚═╝   ╚═╝   ╚═╝ ╚═════╝╚══════╝
*/

Vertice::Vertice(int id, bool visitado){
    this->id = id;
    this->visitado = visitado;
}
Vertice::~Vertice(){}

void Vertice::printInfo(){
    cout << "--------- Vertice ---------\n";
    cout << "Id                            : " << this->id << "\n" ;
    cout << "Visitado                      : " << this->visitado << "\n" ;
    cout << "Tamanho da lista de adjacencia: " << this->adjacencia.size() << "\n\n" ;
}

/*
 ██████╗ ██████╗  █████╗ ███████╗ ██████╗ 
██╔════╝ ██╔══██╗██╔══██╗██╔════╝██╔═══██╗
██║  ███╗██████╔╝███████║█████╗  ██║   ██║
██║   ██║██╔══██╗██╔══██║██╔══╝  ██║   ██║
╚██████╔╝██║  ██║██║  ██║██║     ╚██████╔╝
 ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝      ╚═════╝ 
*/

Grafo::Grafo(){}
Grafo::Grafo(int qntd_vertices, int qntd_arestas, int vertice_inicial, bool direcionado):qntd_vertices(qntd_vertices), qntd_arestas(qntd_arestas), vertice_inicial(vertice_inicial), direcionado(direcionado){}
Grafo::~Grafo(){}

void Grafo::inicializaGrafo(){

    // Leitura dos dados iniciais
    int qntd_vertices, qntd_arestas, eh_direcionado, vertice_inicial;
    bool direcionado;

    cin >> qntd_vertices >> qntd_arestas >> eh_direcionado >> vertice_inicial;
    if (eh_direcionado == 1){
        direcionado = true;
    }
    else{
        direcionado = false;
    }

    this->qntd_arestas = qntd_arestas;
    this->qntd_vertices = qntd_vertices;
    this->direcionado = direcionado;
    this->vertice_inicial = vertice_inicial;

    // Lendo vertices
    for (int i = 1; i <= this->qntd_vertices; i++){
        Vertice v(i, false);
        this->vertices.push_back(v);;
    }

    // Lendo arestas e criando listas de adjacencia
    int origem, destino;
    double peso;

    for (int i = 1; i <= this->qntd_arestas; i++){
        cin >> origem >> destino >> peso;
        
        Aresta a = Aresta(i, origem, destino, peso, false, this->direcionado);
        this->arestas.push_back(a);

        if (this->direcionado){
            this->vertices[origem - 1].adjacencia.push_back(i);
        }
        else{
            this->vertices[origem - 1].adjacencia.push_back(i);
            this->vertices[destino - 1].adjacencia.push_back(i);
        }
    }
}

vector<int> Grafo::BFS(){
    vector<int> Q;
    vector<int> ordemVisitacao;
    int verticeAtual = this->vertice_inicial;
    Vertice* v = &this->vertices[verticeAtual - 1];

    v->visitado = true;

    Q.push_back(verticeAtual);
    while (Q.size() != 0){
        
        verticeAtual = Q[0];
        v = &this->vertices[verticeAtual - 1];
        Q.erase(Q.begin());
        ordemVisitacao.push_back(verticeAtual);

        for (auto i = v->adjacencia.begin(); i != v->adjacencia.end(); ++i){
            Aresta a = this->arestas[*i - 1];
            
            if (this->direcionado){
                int destino = a.destino;

                if (this->vertices[destino - 1].visitado){
                    if (!(a.visitado)){
                        a.visitado = true;
                    }
                }
                else{
                    a.visitado = true;
                    Q.push_back(destino);
                    this->vertices[destino - 1].visitado = true;
                }
            }
            else{
                int origem = a.origem;
                int destino = a.destino;
                int vizinho;

                if (origem == v->id){
                    vizinho = destino;
                }
                else{
                    vizinho = origem;
                }

                if (this->vertices[vizinho - 1].visitado){
                    if (!(a.visitado)){
                        a.visitado = true;
                    }
                }
                else{
                    a.visitado = true;
                    Q.push_back(vizinho);
                    this->vertices[vizinho - 1].visitado = true;
                }
            }
        }
    }

    return ordemVisitacao;
}

void Grafo::printInfo(){
    cout << "--------- Grafo ---------\n";
    cout << "Qntd vertices  : " << this->qntd_vertices << "\n" ;
    cout << "Qntd arestas   : " << this->qntd_arestas << "\n" ;
    cout << "Vertice inicial: " << this->vertice_inicial << "\n" ;
    cout << "Direcionado    : " << this->direcionado << "\n\n" ;
}
