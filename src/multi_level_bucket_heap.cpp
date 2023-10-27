#include <bits/stdc++.h>
#include "multi_level_bucket_heap.h"
typedef std::pair<int,int> pii;

void multi_level_bucket_heap::init(){
  size=0;
  last=0;
  level_size = std::vector<int>(k+1,0);
  levels = std::vector<std::vector<bucket>>(k+1,std::vector<bucket>());
  for(int i=0;i<=k;i++) levels[i] = std::vector<bucket>(delta,bucket(inf));
  //k levels, each one have delta buckets
}

multi_level_bucket_heap::multi_level_bucket_heap(int k_, int max_key_){
  k = k_;
  max_key = max_key_;
  inf = max_key+1;
  lgdelta = calc_lgdelta(max_key, k);
  delta = 1 << lgdelta;
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
  return (x==0)? 0:__builtin_clz(1) - __builtin_clz(x);
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
  levels[level][bucket].b.emplace_back(key,value);
  level_size[level]++;
  levels[level][bucket].size++;
  if(levels[level][bucket].minimo.first>key) levels[level][bucket].minimo = {key,value};
  size++;
  //std::cout<<"level: "<<level<<" "<<"bucket: "<<bucket<<"\n";
}

void multi_level_bucket_heap::expand(int level, int bucket){
  while(levels[level][bucket].size>0){
    pii elemento = levels[level][bucket].b.back();
    levels[level][bucket].b.pop_back();
    if(last!=elemento.first) insert(elemento.first,elemento.second);
    levels[level][bucket].size--;
    level_size[level]--;
  }
}

pii multi_level_bucket_heap::extract_min(){
  int levelmin = 1,b=0;
  pii minPair;

  while(level_size[levelmin]==0) levelmin++;
  while(levels[levelmin][b].size==0) b++;
  minPair = levels[levelmin][b].minimo;
  last = minPair.first;
  
  expand(levelmin,b);
  size--;
  
  return minPair;
}
