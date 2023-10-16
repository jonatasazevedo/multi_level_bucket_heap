#include <bits/stdc++.h>
#include "multi_level_bucket_heap.h"
typedef std::pair<int,int> pii;

void multi_level_bucket_heap::init(){
  levels = std::vector<std::vector<std::vector<pii>>>(k,
    std::vector<std::vector<pii>>());
    for(int i=0;i<k;i++) levels[i] = std::vector<std::vector<pii>>(delta,std::vector<pii>());
  //k levels, each one have base buckets
}

int multi_level_bucket_heap::calc_lgdelta(int max_key,int k){
  int N = 1<<k;
  int i=0;
  while(N<(max_key+1)){
    N<<k;
    i++;
  }
  return i;
}

int multi_level_bucket_heap::calc_level(int key){
  int mask = key^last; //turn on differents bits 
  int ind = msb(mask);
  return (ind/lgdelta) + 1; //levels are 1-indexed
}

int multi_level_bucket_heap::calc_bucket(int key,int level){
  level--; //1-indexed tranformed in 0-indexed
  int shift = level*lgdelta;
  return key>>shift;
}

int multi_level_bucket_heap::msb(int x){
    return __builtin_clz(1) - __builtin_clz(x);
}

void multi_level_bucket_heap::insert(int key,int value){
    int level = calc_level(key);
    int bucket = calc_bucket(key,level);
    levels[level][bucket].push_back({key,value});
}

multi_level_bucket_heap::multi_level_bucket_heap(int k_, int max_key_)
{
    k = k_;
    max_key = max_key_;
    lgdelta = calc_lgdelta(max_key, k);
    delta = 2 << lgdelta;
    init();
}
