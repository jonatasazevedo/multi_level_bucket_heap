#include <bits/stdc++.h>
#include "common.cpp"
#define all(x) x.begin(), x.end()
#define int long long
using namespace std;

void get_orders(auto &adj, auto &vis, auto &pos_order, int u) {
    for(int v : adj[u]) {
        if(!vis[v]){
            get_orders(adj, vis, pos_order, v);
        }
    }
    pos_order.push_back(u);
}

void rauction(const auto &fs, auto &tr, auto &dr, auto &pr, int s, int c) {
    const int n = fs.size();

    // preliminar 1
    vector<int> price(n), w(n);
    vector<int> ds(n, oo);
    vector<int> ps(n, -1);
    vector<bool> vis(n);

    vector<int> best_bid(n);
    vector<vector<tuple<int, int, int>>> bid(n); // ps + w
    pq_t q(c,n);
    
    auto create_fs_bids = [&](int i) {
        for(auto [j, c] : fs[i]) {
            if(!vis[j]) {
                bid[i].emplace_back(c + price[j], j, c);
            }
        }
        sort(all(bid[i]));
        price[i] = (bid[i].size() ? get<0>(bid[i][0]) : oo);
    };

    auto erase_bs = [&](int i) {
        vis[i] = true;
    };
    auto update_best_bid = [&](int i) {
        for(int &it = best_bid[i]; it < bid[i].size(); it++) {
            int j = get<1>(bid[i][it]);
            if(!vis[j]) {
                return;
            }
        }
    };
    auto has_child = [&](int i) {
        update_best_bid(i);
        return best_bid[i] < bid[i].size();
    };
    
    auto add_subtree_to_answer = [&](int root) {

        vector<int> pos_order;
        get_orders(tr, vis, pos_order, root);
        pos_order.pop_back(); // no root
        
        for(int i : pos_order) {
            erase_bs(i);
        }

        for(int i : pos_order) {
            ds[i] = ds[root] + (dr[i] - dr[root]);
            ps[i] = pr[i];
            create_fs_bids(i);
            w[i] = w[root] + price[i];
            if(has_child(i)) {
                q.insert(i, w[i]);
            }
        }

        if(has_child(root)) {
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
        if(!has_child(i) || get<0>(bid[i][best_bid[i]]) >= oo) { // (a)
            price[i] = w[i] = oo;
            continue;
        }
        
        const auto &[mn_bid, j, cij] = bid[i][best_bid[i]];
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

void init_graph(const auto &adj, const auto &p, auto &d, auto &fs, auto &tr) {
    const int n = adj.size();
    for(int i = 0; i < n; i++) {
        if(p[i] != -1) tr[p[i]].push_back(i);
        for(auto [j, w] : adj[i]) {
            fs[i].emplace_back(j, w + (d[i] - d[j]));
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
        graph_t fs(n);
        init_graph(adj, p, d, fs, tr);

        timer otimer;
        rauction(fs, tr, d, p, s, c);

        print_output(reader.get("type"), d, p, otimer);
    }
    return 0;
}