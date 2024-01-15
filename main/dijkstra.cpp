#include <bits/stdc++.h>
#include "common.cpp"
#define all(x) x.begin(), x.end()
#define int long long
using namespace std;

signed main() {
    //ios::sync_with_stdio(false);
    //cin.tie(0);
    #define endl '\n'
    

    cfg_reader reader;
    string dataset_path = reader.get("dataset");
    string query_path = reader.get("query");
    auto [adj, c] = graph_reader(dataset_path);
    int n = adj.size();
    vector<int> d, p;
    auto in = ifstream(query_path);
    int t; in >> t;
    while(t--) {
        int r, s; in >> r >> s;
        pq_t q(c,n);
        init_dijkstra(d, p, q, n, r);
        dijkstra(adj, d, p, q);
        pq_t q2(c,n);
        timer otimer;
        init_dijkstra(d, p, q2, n, s);
        dijkstra(adj, d, p, q2);
        cout<<"Antes"<<endl;
        print_output(reader.get("type"), d, p, otimer);
        cout<<"Depois"<<endl;
    }
    return 0;
}
