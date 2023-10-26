#include <bits/stdc++.h>
#include "bucket.h"
typedef std::pair<int,int> pii;

class multi_level_bucket_heap{
  private:
    int delta,k,size,last,max_key,lgdelta,inf;
    //k -> number of levels
    //last -> last removed in the heap
    //delta -> base in which the keys will be represented
    //lgdelta -> log(delta)
    std::vector<std::vector<bucket>> levels;
    std::vector<int> level_size;
    void init();
    int calc_lgdelta(int max_key,int k);
    int calc_level(int key);
    int calc_bucket(int key,int level);
    int msb(int x);
  public:
    void insert(int key,int value);
    pii extract_min();
    multi_level_bucket_heap(int k,int max_key_);
    void expand(int level,int bucket);
    
};