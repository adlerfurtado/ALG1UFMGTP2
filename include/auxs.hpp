#ifndef AUXS_HPP
#define AUXS_HPP

#include <vector>
#include <queue>
#include "grafo.hpp"

using namespace std;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

typedef pair<int, int> posicao;

bool dentro_do_mapa(int x, int y, int n, int m);

void bfs_bordas(const vector<vector<int>>& mapa, vector<vector<bool>>& visitado);

bool capital_esta_segura(const vector<vector<bool>>& visitado, int cx, int cy);

#endif
