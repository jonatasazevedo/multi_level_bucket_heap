#include <bits/stdc++.h>
#include "common.cpp"
#define int long long
using namespace std;

void get_orders(auto &adj, auto &pos_order, int u) {
    for(int v : adj[u]) {
        get_orders(adj, pos_order, v);
    }
    pos_order.push_back(u);
}

void rauction(auto &fs, const auto &bs, auto &tr, auto &dr, auto &pr, int s, int c) {
    const int n = fs.size();

    // preliminar 1
    vector<int> price(n), w(n);
    vector<int> ds(n, oo);
    vector<int> ps(n, -1);

    vector<set<tuple<int, int, int>>> bid(n); // ps + w
    pq_t q(c,n);
    
    auto create_fs_bids = [&](int i) {
        for(auto [j, c] : fs[i]) {
            bid[i].insert({c + price[j], j, c});
        }
        price[i] = (fs[i].size() ? get<0>(*bid[i].begin()) : oo);
    };

    auto erase_bs = [&](int i) {
        for(auto [j, it] : bs[i]) { // j -> i
            if(bid[j].size()) {
                auto [_, c] = *it;
                bid[j].erase({c + price[i], i, c});
            }
        }
        for(auto [j, it] : bs[i]) {
            fs[j].erase(it);
        }
    };
    
    auto add_subtree_to_answer = [&](int root) {
        int dad = pr[root];
        if(dad != -1) {
            tr[dad].erase(remove(all(tr[dad]), root), tr[dad].end());
        }

        vector<int> pos_order;
        get_orders(tr, pos_order, root);
        pos_order.pop_back(); // no root
        
        for(int i : pos_order) {
            erase_bs(i);
        }

        for(int i : pos_order) {
            ds[i] = ds[root] + (dr[i] - dr[root]);
            ps[i] = pr[i];
            create_fs_bids(i);
            w[i] = w[root] + price[i];
            if(fs[i].size()) {
                q.insert(i, w[i]);
            }
        }

        if(fs[root].size()) {
            q.insert(root, w[root]);
        }
    };
    
    ds[s] = 0; ps[s] = -1;
    create_fs_bids(s);
    w[s] = price[s];
    erase_bs(s);
    add_subtree_to_answer(s);

    while(q.size()) {
        int i = q.extract_min();
        if(fs[i].size() == 0 || get<0>(*bid[i].begin()) >= oo) { // (a)
            price[i] = w[i] = oo;
            continue;
        }
        
        auto [mn_bid, j, cij] = *bid[i].begin();
        if(price[i] < mn_bid) { // (b)
            int old_price = price[i];
            price[i] = mn_bid;
            w[i] = w[i] + price[i] - old_price;
        } else { // (c)
            ps[j] = i;
            ds[j] = ds[i] + cij - (dr[i] - dr[j]);

            erase_bs(j);
            create_fs_bids(j);
            w[j] = w[i] + price[j];
            add_subtree_to_answer(j);
        }
        
        q.insert(i, w[i]);
    }
    swap(ds, dr);
    swap(ps, pr);
}

void init_graph(const auto &adj, const auto &p, auto &fs, auto &bs, auto &d, auto &tr) {
    const int n = adj.size();
    for(int i = 0; i < n; i++) {
        if(p[i] != -1) tr[p[i]].push_back(i);
        for(auto [j, w] : adj[i]) {
            fs[i].emplace_back(j, w + (d[i] - d[j]));
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
        init_graph(adj, p, fs, bs, d, tr);

        timer otimer;
        rauction(fs, bs, tr, d, p, s, c);

        print_output(reader.get("type"), d, p, otimer);
    }
    return 0;
}