#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

ifstream fin("graf.txt");

const int LG = 10001;
const int INF = 1e9;

int n, m, start;
int DBel[LG];
int PBel[LG];

int DDij[LG];
int PDij[LG];
bool viz[LG];

int J[LG][LG];

vector<pair<int, int>> G[LG];

void read() {
    fin >> n >> m;
    int x, y, w;
    while (fin >> x >> y >> w) {
        G[x].push_back(make_pair(y, w));
    }
}

bool bellmanford(int s, int n) {
    //init
    for (int i = 0; i < n; i++) {
        DBel[i] = INF;
        PBel[i] = INF;
    }
    DBel[s] = 0;
    PBel[s] = 0;

    //de n-1 ori
    for (int i = 1; i <= n - 1; i++) {

        //pt fiecare arc
        for (int j = 0; j < n; j++) {
            for (auto p: G[j]) {
                //relaxeaza
                if (DBel[j] + p.second < DBel[p.first]) {
                    DBel[p.first] = DBel[j] + p.second;
                    PBel[p.first] = j;
                }
            }
        }
    }

    for (int j = 0; j < n; j++) {
        for (auto p: G[j]) {
            //relaxeaza
            if (DBel[j] + p.second < DBel[p.first]) {
                return false;
            }
        }
    }
    return true;

}

void dijkstra(int s) {
    //initializare
    for (int i = 0; i <= n; i++) {
        DDij[i] = INF;
        PDij[i] = INF;
        viz[i] = false;
    }

    DDij[s] = 0;
    PDij[s] = 0;

    //while !q.empty
    for (int i = 0; i < n - 1; i++) {

        //min=extractmin
        int min = n;
        for (int j = 0; j < n; j++) {
            if (!viz[j]) {
                if (DDij[j] < DDij[min]) {
                    min = j;
                }
            }
        }

        //pt arcele lu min
        for (auto p: G[min]) {

            //relax
            if (DDij[min] + p.second < DDij[p.first]) {
                DDij[p.first] = DDij[min] + p.second;
                PDij[p.first] = min;
            }
        }
        viz[min] = true;
    }
}

void johnson() {
    int s = n;
    for (int i = 0; i < n; i++) {
        G[s].push_back(make_pair(i, 0));
    }

    if (!bellmanford(s, n + 1)) {
        return;
    } else {

        for (int i = 0; i < n; i++) {
            for (auto& p: G[i]) {
                p.second = p.second + DBel[i] - DBel[p.first];
                cout<< i<<' '<<p.first<<' '<<p.second<<'\n';
            }
        }

        for (int i = 0; i < n; i++) {
            dijkstra(i);
            for (int j = 0; j < n; j++) {
                if(DDij[j] != INF)
                    J[i][j] = DDij[j] - DBel[i] + DBel[j];
                else
                    J[i][j] = DDij[j];
            }
        }
    }

}

int main() {
    read();

    johnson();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (J[i][j] == INF)
                cout << "inf ";
            else
                cout << J[i][j] << ' ';
        }
        cout << '\n';
    }
}