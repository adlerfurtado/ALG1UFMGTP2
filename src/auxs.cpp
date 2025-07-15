#include "auxs.hpp"

// Checa se a posicao tá dentro do mapa (para n acessar lixo)
bool dentro_do_mapa(int x, int y, int n, int m) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

// Começa BFS pelas bordas do mapa pra ver até onde o inimigo pode chegar
void bfs_bordas(const vector<vector<int>>& mapa, vector<vector<bool>>& visitado) {
    int n = static_cast<int>(mapa.size());
    int m = static_cast<int>(mapa[0].size());
    queue<posicao> fila;

    // Percorre as bordas verticais
    for (int i = 0; i < n; ++i) {
        int j = 0;
        if (mapa[i][j] != 0 && !visitado[i][j]) {
            fila.push({i, j});
            visitado[i][j] = true;
        }
        j = m - 1;
        if (mapa[i][j] != 0 && !visitado[i][j]) {
            fila.push({i, j});
            visitado[i][j] = true;
        }
    }

    // Percorre as bordas horizontais
    for (int j = 0; j < m; ++j) {
        int i = 0;
        if (mapa[i][j] != 0 && !visitado[i][j]) {
            fila.push({i, j});
            visitado[i][j] = true;
        }
        i = n - 1;
        if (mapa[i][j] != 0 && !visitado[i][j]) {
            fila.push({i, j});
            visitado[i][j] = true;
        }
    }

    // BFS para criar os níveis
    while (!fila.empty()) {
        int x = fila.front().first;
        int y = fila.front().second;
        fila.pop();

        for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d];
            int ny = y + dy[d];

            if (dentro_do_mapa(nx, ny, n, m) && !visitado[nx][ny] && mapa[nx][ny] != 0) {
                visitado[nx][ny] = true;
                fila.push({nx, ny});
            }
        }
    }
}

// Confere se a capital foi visitada
bool capital_esta_segura(const vector<vector<bool>>& visitado, int cx, int cy) {
    return !visitado[cx][cy];
}
