#include <bits/stdc++.h>
#include "bucket.h"
typedef std::pair<int,int> pii;

struct ValueMap{
  int level, bucket, index;
  ValueMap()
    :level(-1), bucket(-1), index(-1){}
  ValueMap(int level, int bucket, int index)
    :level(level), bucket(bucket), index(index){ }
};

class multi_level_bucket_heap{
  public:
    int k, max_key, max_value, delta, lgdelta, last, size, inf;
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
    
    std::vector<ValueMap> valueMaps;

    void init();
    int calc_lgdelta(int max_key,int k);
    int calc_level(int key);
    int calc_bucket(int key,int level);
    int msb(int x);
    void deleteAt(int level, int bucket, int index);

  // public:
    void insert(int key,int value);
    pii extract_min();
    void decrease_key(int newKey, int value);
    multi_level_bucket_heap(int k,int max_key, int max_value);
    void expand(int level,int bucket, int rmValue);
};