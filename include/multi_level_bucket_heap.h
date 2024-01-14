#pragma once
#include <bits/stdc++.h>
#include "bucket.h"
#include "dheap.h"
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
    int k, max_key, max_value, delta, lgdelta,top_level_range,bucket_top_active,last, mlb_size, local_size, t,
    levelActive,bucketActive,last_temp,d;
    //k -> number of levels
    //max_key -> maximum key that can be inserted
    //max_value -> maximum value that can be inserted
    //delta -> base in which the keys will be represented
    //lgdelta -> log(delta)
    //top_level_range -> range of top level buckets
    //bucket_top_active -> represents bucket active in top level
    //last -> last removed in the heap
    //mlb_size -> number of elements in the heap
    //local_size -> number of elements in local strucuture
    //t -> number of maximum elements in the s-heap
    //levelActive -> index of level active
    //bucketActive -> index of bucket active
    //last_temp -> temporary last
    //d -> type of d-heap

    std::vector<int> level_size;
    dheap sheap;
    //level_size -> number of elements in level (all buckets)
    //levels -> levels[i] -> vector of buckets in level i
    //s-heap, size-sensitive heap
    std::vector<ValueMap> valueMaps;

    void init();
    int calc_lgdelta(int max_key,int k);
    int calc_level(int key);
    int calc_bucket(int key,int level);
    int msb(int x);
    void deleteAt(int level, int bucket, int index);
    void deleteMin(ValueMap valueMap);
    void expand(int level,int bucket);
    void activate_bucket(int level,int bucket);
    void deactive_bucket(int level,int bucket);
    void fill_structure_local();
    void insertLocal(int key,int value);
    int findBucketTopLevel(int key);

  public:
    std::vector<std::vector<bucket>> levels;
    int size();
    bool empty();
    multi_level_bucket_heap(int k,int max_key, int max_value,int t,int d);
    multi_level_bucket_heap(int max_key,int max_value);
    void insert(int key,int value);
    int extract_min();
    void decrease_key(int newKey, int value);
    int keyValue(int value);
};