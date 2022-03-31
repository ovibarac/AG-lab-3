#include <iostream>
#include <fstream>
#include <queue>
#include <string>

using namespace std;

ifstream f("graf.txt");

const int MAX = 101;
const int INF = 1e9;

int ma[MAX][MAX];
int nrV;
int E;
int sursa;
int d[MAX];
queue<int> q;

void citireGraf() {
    f >> nrV >> E >> sursa;
    int x, y, w;
    while (f >> x >> y >> w) {
        ma[x][y] = w;
    }
}

void initializare() {
    for (int i = 1; i <= nrV; i++){
        d[i] = INF;
    }
    d[sursa] = 0;
}

void relax(int u, int v){
    if(d[v] > d[u] + ma[u][v]){
        d[v] = d[u] + ma[u][v];
    }
}

bool bellman_ford() {
    initializare();
    for (int i = 1; i <= nrV - 1; i++) {
        for (int j = 1; j <= nrV; j++) {
            for (int k = 1; k <= nrV; k++) {
                if (ma[j][k] > 0) {
                    relax(j, k);
                }
            }

        }
    }

    for (int j = 1; j <= nrV; j++) {
        for (int k = 1; k <= nrV; k++) {
            if (d[k] > d[j] + ma[j][k]){
                return false;
            }
        }

    }
    return true;
}

int main(int argc, char **argv) {
    citireGraf();
    bellman_ford();
    for (int i = 1; i <= nrV; i++){
        if(d[i] == INF){
            cout<<"INF ";
        }else
            cout<<d[i]<<' ';
    }


    return 0;
}