#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <vector>
#include <queue>
using namespace std;

const int INF = 1000000000;

struct Aresta {
    int destino, reversa;
    int capacidade;
};

class Grafo {
public:
    vector<vector<Aresta>> adjacencia;
    int tamanho;

    Grafo(int tamanho);
    void adicionar_aresta(int de, int para, int capacidade);
    int bfs(int origem, int destino, vector<int>& nivel, vector<size_t>& aresta_pai);
    int dfs(int u, int destino, int fluxo, vector<int>& nivel, vector<size_t>& ponteiro);
    int fluxo_maximo(int origem, int destino);
};

#endif
