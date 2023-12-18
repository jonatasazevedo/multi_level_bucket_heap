#pragma once
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
  private:
    int k, max_key, max_value, delta, last, mlb_size, u, offset,activeBucket;
    //k -> number of levels
    //max_key -> maximum key that can be inserted
    //max_value -> maximum value that can be inserted
    //delta -> base in which the keys will be represented
    //last -> last removed in the heap
    //mlb_size -> number of elements in the heap
    //u -> "definir"
    //offset -> "definir"

    std::vector<int> level_size;
    //level_size -> number of elements in level (all buckets)
    //levels -> levels[i] -> vector of buckets in level i
    std::vector<ValueMap> valueMaps;

    void init();
    // int calc_level(int key);
    // int calc_bucket(int key,int level);
    // int msb(int x);
    // void deleteAt(int level, int bucket, int index);
    // void deleteMin(ValueMap valueMap);
    // void expand(int level,int bucket);
    // void activate_bucket(int level,int bucket);
    // void deactive_bucket(int level,int bucket);

  public:
    std::vector<std::vector<bucket>> levels;
    int size();
    bool empty();
    multi_level_bucket_heap(int k,int max_key, int max_value);
    multi_level_bucket_heap(int max_key,int max_value);
    void insert(int key,int value);
    // int extract_min();
    // void decrease_key(int newKey, int value);
    int keyValue(int value);
};