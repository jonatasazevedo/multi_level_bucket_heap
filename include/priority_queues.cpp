#include <bits/stdc++.h>
#include "radix_heap.h"
#define int long long
using namespace std;

struct priority_queue_inter {
    virtual void insert(int key, int value) = 0;
    virtual int extract_min() = 0;
    virtual void decrease_key(int key, int value) = 0;
    virtual int size() = 0;
};

// struct ml_bucket : priority_queue_inter {
//     vector<vector<vector<pair<int, int>>>> b;
//     int32_t level_mask;
//     vector<int> level_sz;
//     const int oo = 1e18;
//     int k = -1;
//     int delta = -1;
//     int sz = 0;
//     int c = -1;
//     int deltapk = -1; // delta ^ k
//     ml_bucket(int c_) {
//         c = c_;
//         // k = ceil(log2(c) / (2.0 * log2(log2(c))));
//         k = min(25ll, (int) log2(c));

//         //we set ∆ to the smallest power of two greater than or equal to (C + 1) ^ (1/k)
//         int delta_lb = ceil(pow(c + 1, 1.0 / k));
//         delta = next_power_of_two(delta_lb);
//         deltapot2 = __builtin_ctz(delta);

//         b = vector<vector<vector<pair<int, int>>>>(k, vector<vector<pair<int, int>>>(delta));
//         level_sz.resize(k);
//         last_extracted = 0;
//         level_mask = 0;

//         deltapk = 1;
//         for(int i = 0; i < k; i++) {
//             if(log10(delta) + log10(deltapk) <= 17) {
//                 deltapk *= delta;
//             } else {
//                 assert(false);
//             }
//         }
//         // debug(k, delta, deltapot2, deltapk);
//     }

//     unsigned int next_power_of_two(unsigned int x) {
//         x--;
//         x |= x >> 1;
//         x |= x >> 2;
//         x |= x >> 4;
//         x |= x >> 8;
//         x |= x >> 16;
//         x |= x >> 32;
//         return x + 1;
//     }


//     int deltapot2 = 1;
//     int get_msb_dif_basedelta(int a, int b) {
//         int xor_res = a ^ b;
//         int first_dif = sizeof(int) * 8 - 1 - __builtin_clz(xor_res);
//         int pos = first_dif / deltapot2;
//         return pos;
//     }
//     int get_bit_basedelta(int x, int i) {
//         return x / (1ll << (i * deltapot2)) % deltapot2;
//     }

//     int last_extracted = 0;
//     pair<int, int> get_position(const int val) {
//         int i = min(get_msb_dif_basedelta(val, last_extracted), k - 1);
//         int j = get_bit_basedelta(val, i);
//         if(i == k - 1) {
//             j = (val / deltapk) % delta;
//         }
//         return {i, j};
//     }
    
//     void expand(auto &bucket) {
//         auto tmp = bucket;
//         bucket.clear();
//         for(auto &[val, u] : tmp) {
//             insert(u, val);
//         }
//     };

//     void upt_size(int l, int val) {
//         sz += val;
//         level_sz[l] += val;
//         if(level_sz[l] > 0) level_mask |= (1ll << l);
//         else level_mask &= ~(1ll << l);
//     }

//     int li = -1, lj = -1;
//     void insert(int u, int val) {
//         auto [i, j] = get_position(val);
//         upt_size(i, +1);

//         b[i][j].emplace_back(val, u);
//     }

//     void decrease_key(int u, int oldval, int val) {
//         // assert(val_ >= last_extractedf);

//         auto [i, j] = get_position(oldval);

//         auto it = find(b[i][j].begin(), b[i][j].end(), make_pair(oldval, u));
//         if(it != b[i][j].end()) {
//             b[i][j].erase(it);
//             upt_size(i, -1);
//         }

//         insert(u, val);
//     }

//     int extract_min() {
//         auto get_lowest_nonempty_lvl = [&]() {
//             return __builtin_ctz(level_mask);
//         };

//         auto get_first_nonempty_bucket = [&](int i, int bg) {
//             if(i != k - 1) {
//                 for(int j = bg; j < delta; j++) {
//                     if(b[i][j].size()) return j;
//                 }
//             } else {
//                 bg = (last_extracted / deltapk) % delta;
//                 for(int j = bg; ; j++) {
//                     if(b[i][j].size()) {
//                         return j;
//                     }
//                     if(j == delta - 1) j = 0;
//                 }
//             }
//             assert(false);
//         };

//         int i = get_lowest_nonempty_lvl();
//         int j = get_first_nonempty_bucket(i, get_bit_basedelta(last_extracted, i));

//         if(i == 0) {
//             auto [val, u] = b[i][j].back();
//             last_extracted = val;
//             b[i][j].pop_back();

//             upt_size(i, -1);
//             return u;
//         } else {
//             auto it = min_element(b[i][j].begin(), b[i][j].end());
//             auto [val, u] = *it;
//             b[i][j].erase(it);
//             upt_size(i, -1);

//             last_extracted = val;
//             upt_size(i, -b[i][j].size());
//             expand(b[i][j]);
//             return u;
//         }
//     }
//     int size() {
//         return sz;
//     }
// };

// struct set_pq : priority_queue_inter {
//     set<pair<int, int>> s;
//     set_pq(){};
//     set_pq(int c){};
//     void insert(int u, int val) {
//         s.insert({val, u});
//     }
//     void decrease_key(int u, int oldval, int val) {
//         s.erase({oldval, u});
//         s.insert({val, u});
//     }
//     int extract_min() {
//         int u = s.begin()->second;
//         s.erase(s.begin());
//         return u;
//     }
//     int size(){
//         return s.size();
//     }
// };


struct radix_heap_custom : priority_queue_inter {
    radix_heap::pair_radix_heap<int, int> s;
    int real_size = 0;
    vector<int> keys;
    radix_heap_custom(){};
    radix_heap_custom(int c,int n){};
    void insert(int key, int value) {
        real_size++;
        s.emplace(key,value);
        if(value >= keys.size()) keys.resize(value + 1);
        keys[value] = key;
    }
    void decrease_key(int key, int value) {
        s.emplace(key, value);
        if(value >= keys.size()) keys.resize(value + 1);
        keys[value] = key;
    }
    int extract_min() {
        int u = -1, d = -1;
        do {
            u = s.top_value();
            d = s.top_key();
            s.pop();
        } while(d > keys[u]);
        keys[u] = -1e18;
        real_size--;

        return u;
    }
    int size(){
        return real_size;
    }
};

struct priority_queue_custom : priority_queue_inter {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> s;
    vector<int> key;
    priority_queue_custom(){};
    priority_queue_custom(int c){};
    void insert(int u, int val) {
        s.emplace(val, u);
        if(u >= key.size()) key.resize(u + 1);
        key[u] = val;
    }
    void decrease_key(int u, int oldval, int val) {
        insert(u, val);
    }
    int extract_min() {
        int u, d;
        do {
            u = s.top().second;
            d = s.top().first;
            s.pop();
        } while(key[u] < d);
        key[u] = -1e18;

        return u;
    }
    int size(){
        return s.size();
    }
};