#include <bits/stdc++.h>
#include "bucket.h"
typedef std::pair<int,int> pii;

class multi_level_bucket_heap{
  private:
    int k, max_key, delta, lgdelta, delta, last, size, inf;
    //k -> number of levels
    //max_key -> maximum key that can be inserted
    //delta -> base in which the keys will be represented
    //lgdelta -> log(delta)
    //last -> last removed in the heap
    //size -> number of elements in the heap
    //inf -> infinity

    std::vector<std::vector<bucket>> levels;
    std::vector<int> level_size;
    //level_size -> number of elements in level (all buckets)
    //levels -> levels[i] -> vector of buckets in level i

    void init();
    int calc_lgdelta(int max_key,int k);
    int calc_level(int key);
    int calc_bucket(int key,int level);
    int msb(int x);
  public:
    void insert(int key,int value);
    pii extract_min();
    multi_level_bucket_heap(int k,int max_key_);
    void expand(int level,int bucket, int rmValue);
};