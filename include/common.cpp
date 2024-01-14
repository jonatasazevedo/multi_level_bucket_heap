#include <bits/stdc++.h>
#include "multi_level_bucket_heap.h"
#include "priority_queues.cpp"
#define all(x) x.begin(), x.end()
using namespace std;

using pq_t = multi_level_bucket_heap;
// using pq_t = radix_heap_custom; 
// using pq_t = priority_queue_custom;

using graph_t = vector<list<pair<int, int>>>;

const int oo = 1e18;

void init_dijkstra(auto &d, auto &p, pq_t &q, const int n, const int s) {
    d = vector<int>(n, oo);
    p = vector<int>(n, -1);
    d[s] = 0;
    q.insert(0,s);
}

void dijkstra(const auto &adj, auto &d, auto &p, pq_t &q) {
    while(q.size()) {
        int u = q.extract_min();
        cout<<u<<endl;
        for(auto [v, w] : adj[u]) {
            if(d[v] > d[u] + w) {
                int old = d[v];
                p[v] = u;
                d[v] = d[u] + w;
                if(old == oo) q.insert(d[v],v);
                else q.decrease_key(d[v],v);
            }
        }
    }
};

struct cfg_reader {
    map<string, string> res;
    cfg_reader() {
        string config_path = getenv("RSPP_ROOT");
        config_path += "config";
        cout<<config_path<<endl;

        ifstream in(config_path);
        string line;
        while(getline(in, line)) {
            istringstream linestream(line);
            string key, value;
            getline(linestream, key, '=');
            getline(linestream, value);
            res[key] = value;
        }
    };
    string get(string s) {
        return res[s];
    }
};

auto graph_reader(string path) {
    graph_t adj;

    int n = -1, m = 0, c = 0;
    string line, tmp;
    ifstream in(path);

    while(getline(in, line)) {
        stringstream ss(line);
        if(path.back() == 'r') {
            if(line[0] == 'p') {
                ss >> tmp >> tmp >> n >> m;
                n++;
                adj.resize(n);
            } else if(line[0] == 'a') {
                int a, b, w; ss >> tmp >> a >> b >> w;
                adj[a].emplace_back(b, w);
                c = max(c, w);
            }
        } else if(path.back() == 't') {
            if(n != -1) {
                int a, b, w;
                ss >> a;
                if(a == -1) break;

                ss >> b >> w;
                adj[a].emplace_back(b, w);
                c = max(c, w);
                m++;
            } else {
                ss >> n;
                n++;
                adj.resize(n);
            }
        } else if(path.back() == 'n') {
            if(n != -1) {
                int a, b, w;
                ss >> a;
                if(a == 0) break;

                ss >> b >> tmp >> w;
                adj[a].emplace_back(b, w);
                c = max(c, w);
                m++;
            } else {
                ss >> n;
                n++;
                adj.resize(n);
            }
        }
    }
    
    return make_pair(adj, c);
}

struct timer {
    chrono::_V2::system_clock::time_point begin;
    timer() {
        begin = chrono::high_resolution_clock::now();
    }
    void restart() {
        begin = chrono::high_resolution_clock::now();
    }
    int elapsed() {
        auto end = chrono::high_resolution_clock::now();
        return chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    }
};

int check_sum(auto &v) {
    int res = 0;
    for(auto x : v) {
        res += x;
    }
    return res;
}

void print_output(string type, auto &d, auto &p, auto &otimer) {
    if(type.find("main_time") != string::npos) {
        cout << otimer.elapsed() << endl;
    }
    if(type.find("check_sum") != string::npos){
        cout << check_sum(d) << endl;
    }
}
