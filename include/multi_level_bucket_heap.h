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
    int k, max_key, max_value, delta, lgdelta, last, mlb_size, t,
    levelActive,bucketActive,last_sheap;
    //k -> number of levels
    //max_key -> maximum key that can be inserted
    //delta -> base in which the keys will be represented
    //lgdelta -> log(delta)
    //last -> last removed in the heap
    //mlb_size -> number of elements in the heap
    //t -> number of maximum elements in the s-heap
    //levelActive -> index of level active
    //bucketActive -> index of bucket active
    //last_sheap -> last removed in the sheap

    std::vector<std::vector<bucket>> levels;
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

  public:
    int size();
    multi_level_bucket_heap(int k,int max_key, int max_value,int t);
    void insert(int key,int value);
    pii extract_min();
    void decrease_key(int newKey, int value);
    
};