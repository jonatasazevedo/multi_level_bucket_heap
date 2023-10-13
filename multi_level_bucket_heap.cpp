#include <bits/stdc++.h>
#include "multi_level_bucket_heap.h"
typedef std::pair<int,int> pii;

void multi_level_bucket_heap::init(){
  level_bucket = std::vector<std::vector<std::vector<pii>>>(k,
    std::vector<std::vector<pii>>());
    for(int i=0;i<k;i++) level_bucket[i] = std::vector<std::vector<pii>>(base,std::vector<pii>());
  //k levels, each one have base buckets
}

multi_level_bucket_heap::multi_level_bucket_heap(int base_,int max_key_){
  base = base_;
  max_key = max_key_;
  k = log(max_key)/log(base) + 2; //plus 2 because 1-indexed
  init();
}