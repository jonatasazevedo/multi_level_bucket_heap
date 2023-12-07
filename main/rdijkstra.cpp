#include <bits/stdc++.h>
#include "common.cpp"
#define all(x) x.begin(), x.end()
#define int long long
using namespace std;

void get_post_order(auto &adj, auto &res, int u) {
    for(int v : adj[u]) {
        get_post_order(adj, res, v);
    }
    res.push_back(u);
}

void rdijkstra(auto &fs, const auto &bs, auto &tr, auto &dr, auto &pr, int s, int c) {
    const int n = fs.size();

    auto erase_bs = [&](int i) {
        for(auto [j, it] : bs[i]) { // j -> i
            fs[j].erase(it);
        }
    };
    
    vector<int> ds(n, oo);
    vector<int> ps(n, -1);

    vector<int> porder;
    get_post_order(tr, porder, s);
    
    pq_t q(c,n);
    for(int i : porder) {
        ds[i] = dr[i] - dr[s];
        ps[i] = pr[i];
        erase_bs(i);
    }
    
    for(int i : porder) {
        if(!fs[i].empty()) {
            q.insert(ds[i],i);
        }
    }
    
    ps[s] = -1;

    dijkstra(fs, ds, ps, q);

    dr = move(ds);
    pr = move(ps);
}

void init_graph(const auto &adj, const auto &p, auto &fs, auto &bs, auto &tr) {
    const int n = adj.size();
    for(int i = 0; i < n; i++) {
        if(p[i] != -1) tr[p[i]].push_back(i);
        for(auto [j, w] : adj[i]) {
            fs[i].emplace_back(j, w);
            bs[j].emplace_back(i, --fs[i].end());
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    #define endl '\n'
    
    cfg_reader reader;
    string dataset_path = reader.get("dataset");
    string query_path = reader.get("query");

    auto [adj, c] = graph_reader(dataset_path);
    int n = adj.size();

    auto in = ifstream(query_path);
    int t; in >> t;
    while(t--) {
        int r, s; in >> r >> s;

        vector<int> d(n), p(n);
        pq_t q(c,n);
        init_dijkstra(d, p, q, n, r);
        dijkstra(adj, d, p, q);

        vector<vector<int>> tr(n);
        vector<list<pair<int, int>>> fs(n);
        vector<vector<pair<int, list<pair<int, int>>::iterator>>> bs(n);
        init_graph(adj, p, fs, bs, tr);
        
        timer otimer;
        rdijkstra(fs, bs, tr, d, p, s, c);
        
        print_output(reader.get("type"), d, p, otimer);
    }
    return 0;
}