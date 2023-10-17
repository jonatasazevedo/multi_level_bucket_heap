#include <bits/stdc++.h>
#include "multi_level_bucket_heap.h"
typedef std::pair<int,int> pii;

void multi_level_bucket_heap::init(){
  emptylevel = std::vector<bool>(k+1,true);
  levels = std::vector<std::vector<std::vector<pii>>>(k,
    std::vector<std::vector<pii>>());
    for(int i=0;i<k;i++) levels[i] = std::vector<std::vector<pii>>(delta,std::vector<pii>());
  //k levels, each one have delta buckets
}

multi_level_bucket_heap::multi_level_bucket_heap(int k_, int max_key_){
  k = k_;
  max_key = max_key_;
  inf = max_key+1;
  lgdelta = calc_lgdelta(max_key, k);
  delta = 1 << lgdelta;
  //std::cout<<delta<<" "<<lgdelta<<"\n";
  init();
}

int multi_level_bucket_heap::calc_lgdelta(int max_key,int k){
  int N = 1<<k;
  int i=0;
  while(N<(max_key+1)){
    N<<=k;
    i++;
  }
  return i;
}

int multi_level_bucket_heap::msb(int x){
  return __builtin_clz(1) - __builtin_clz(x);
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

void multi_level_bucket_heap::insert(int key,int value){
  int level = calc_level(key);
  int bucket = calc_bucket(key,level);
  levels[level][bucket].emplace_back(key,value);
  size++;
  //std::cout<<"level: "<<level<<" "<<"bucket: "<<bucket<<"\n";
}

// pii multi_level_bucket_heap::extract_min(){
//   int levelmin = 1;
//   while(emptylevel[levelmin]) levelmin++;
//   for(int b=0;b<=delta;b++){

//   }
//   size--;
//   return {0,0};
// }

