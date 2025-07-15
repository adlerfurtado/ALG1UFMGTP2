#include <iostream>
#include <vector>
#include "auxs.hpp"
#include "grafo.hpp"

using namespace std;

// Cada célula é representada por dois nós, entrada e saída (passar o peso pras arestas)
// Função para calcular o índice do nó entrada de um nó dividido
int no_entrada(int i, int j, int m) {
    return (i * m + j) * 2;
}

// Função para calcular o índice do nó saída de um nó dividido
int no_saida(int i, int j, int m) {
    return (i * m + j) * 2 + 1;
}

int main() {
    int n, m;
    cin >> n >> m;  // Leitura do tamanho do mapa (linhas n e colunas m)

    // Leitura dos valores do mapa, onde cada posição tem um valor inteiro
    vector<vector<int>> mapa(n, vector<int>(m));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> mapa[i][j];

    int cx, cy;
    cin >> cx >> cy; // Coordenadas da capital
    cx--, cy--;      // Ajuste para índice base 0

    // Vetor para marcar visitados pro BFS e DFS
    vector<vector<bool>> visitado(n, vector<bool>(m, false));

    // Divide os nós em entrada e saída
    int total_nos = n * m * 2 + 2;
    
    // Adiciona o nó de origem (das bordas) e o de destino (cidade)
    int origem = total_nos - 2;    
    int destino = total_nos - 1; 

    // Cria e constrói o grafo
    Grafo g(total_nos);  
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (mapa[i][j] == 0) continue;  // Se for montanha ignora 

            int entrada = no_entrada(i, j, m);  // Nó entrada da célula
            int saida = no_saida(i, j, m);      // Nó saída da célula

            // Aresta interna do nó fica com o fluxo total, e a volta é só pra retorno
            g.adicionar_aresta(entrada, saida, mapa[i][j]);

            // Se a célula está na borda, conecta a origem ao nó de entrada da célula 
            if (i == 0 || j == 0 || i == n - 1 || j == m - 1) {
                g.adicionar_aresta(origem, entrada, INF);
            }

            // Para cada direção verifica a célula vizinha
            for (int d = 0; d < 4; ++d) {
                int ni = i + dx[d];
                int nj = j + dy[d];
                if (dentro_do_mapa(ni, nj, n, m) && mapa[ni][nj] != 0) {
                    int vizinho_entrada = no_entrada(ni, nj, m);
                    // Conecta célula de saída - celula de entrada da vizinha
                    g.adicionar_aresta(saida, vizinho_entrada, INF);
                }
            }
        }
    }

    // Conecta a entrada da capital ao destino com capacidade infinita
    int capital_entrada = no_entrada(cx, cy, m);
    g.adicionar_aresta(capital_entrada, destino, INF);

    // Calcula o fluxo máximo entre origem e destino
    int soldados_total = g.fluxo_maximo(origem, destino);

    // Imprime a quantidade minima de soldados necessários utilizados 
    cout << soldados_total << endl;

    return 0;
}
