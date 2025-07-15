#include "grafo.hpp"

// Construtor
Grafo::Grafo(int tamanho) {
    this->tamanho = tamanho;
    adjacencia.resize(tamanho);
}

// Cria aresta entre dois nós para passar o peso do nó para a aresta interna
void Grafo::adicionar_aresta(int de, int para, int capacidade) {
    adjacencia[de].push_back({para, (int)adjacencia[para].size(), capacidade});
    adjacencia[para].push_back({de, (int)adjacencia[de].size() - 1, 0});
}

// BFS pra montar o nível de cada nó a partir da origem
int Grafo::bfs(int origem, int destino, vector<int>& nivel, vector<size_t>& aresta_pai) {
    nivel.assign(tamanho, -1);
    aresta_pai.assign(tamanho, -1);

    queue<int> fila;
    fila.push(origem);
    nivel[origem] = 0;

    while (!fila.empty()) {
        int u = fila.front();
        fila.pop();

        for (size_t i = 0; i < adjacencia[u].size(); ++i) {
            Aresta& a = adjacencia[u][i];
            if (a.capacidade > 0 && nivel[a.destino] == -1) {
                nivel[a.destino] = nivel[u] + 1;
                aresta_pai[a.destino] = i;
                fila.push(a.destino);
            }
        }
    }

    return nivel[destino] != -1;
}

// DFS para aumentar fluxo enquanto der
int Grafo::dfs(int u, int destino, int fluxo, vector<int>& nivel, vector<size_t>& ponteiro) {
    if (u == destino) return fluxo;

    for (; ponteiro[u] < adjacencia[u].size(); ++ponteiro[u]) {
        Aresta& a = adjacencia[u][ponteiro[u]];

        if (a.capacidade > 0 && nivel[a.destino] == nivel[u] + 1) {
            int empurrado = dfs(a.destino, destino, min(fluxo, a.capacidade), nivel, ponteiro);
            if (empurrado > 0) {
                a.capacidade -= empurrado;
                adjacencia[a.destino][a.reversa].capacidade += empurrado;
                return empurrado;
            }
        }
    }

    return 0;
}

// Calculo do fluxo máximo 
int Grafo::fluxo_maximo(int origem, int destino) {
    int fluxo_total = 0;
    vector<int> nivel(tamanho);
    vector<size_t> aresta_pai(tamanho);

    while (bfs(origem, destino, nivel, aresta_pai)) {
        vector<size_t> ponteiro(tamanho, 0);
        while (int empurrado = dfs(origem, destino, INF, nivel, ponteiro)) {
            fluxo_total += empurrado;
        }
    }

    return fluxo_total;
}
