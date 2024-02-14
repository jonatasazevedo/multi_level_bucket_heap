#include <bits/stdc++.h>
#include "common.cpp"
#define all(x) x.begin(), x.end()
using namespace std;

signed main(int argc,char *argv[]) {
    int qtLevels = atoi(argv[1]);
    int tamSheap = atoi(argv[2]);
    int dSheap = 3;

    ios::sync_with_stdio(false);
    cin.tie(0);
    #define endl '\n'

    cfg_reader reader;
    string dataset_path = reader.get("dataset");
    string query_path = reader.get("query");
    auto [adj, c] = graph_reader(dataset_path);
    int n = adj.size();
    vector<int> d, p;
    auto in = ifstream(query_path);
    int t; in >> t;
    cout<<"dijkstra"<<endl;
    while(t--) {
        int r, s; in >> r >> s;
        pq_t q(qtLevels,c,n,tamSheap,dSheap);
        init_dijkstra(d, p, q, n, r);
        dijkstra(adj, d, p, q);
        pq_t q2(qtLevels,c,n,tamSheap,dSheap);
        timer otimer;
        init_dijkstra(d, p, q2, n, s);
        dijkstra(adj, d, p, q2);
        print_output(reader.get("type"), d, p, otimer);
    }
    return 0;
}
