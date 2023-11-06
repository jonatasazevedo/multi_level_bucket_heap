#include <bits/stdc++.h>
#include "multi_level_bucket_heap.h"
typedef std::pair<int,int> pii;

void multi_level_bucket_heap::init(){
  size=0;
  last=0;
  level_size = std::vector<int>(k+2,0);
  levels = std::vector<std::vector<bucket>>(k+2,std::vector<bucket>());
  for(int i=1;i<=k+1;i++) levels[i] = std::vector<bucket>(delta,bucket());
  //k+1 levels, each one have delta buckets

  valueMaps = std::vector<ValueMap>(max_value+1);
}

multi_level_bucket_heap::multi_level_bucket_heap(int k, int max_key, int max_value,int t)
  :k(k), max_key(max_key), max_value(max_value),t(t){
  lgdelta = calc_lgdelta(max_key, k);
  delta = 1 << lgdelta;
  init();
}

int multi_level_bucket_heap::calc_lgdelta(int max_key,int k){
  int N = 1;
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

void multi_level_bucket_heap::deleteAt(int level, int bucket, int index){
  if(index >= levels[level][bucket].size) return;
  if(index  < levels[level][bucket].size-1){
    pii lastPair = levels[level][bucket].b.back();
    levels[level][bucket].b[index] = lastPair;
    valueMaps[lastPair.second].index = index;
  }
  levels[level][bucket].b.pop_back();
  levels[level][bucket].size--;
  level_size[level]--;
  size--;
}

int multi_level_bucket_heap::calc_level(int key){
  int mask = key^last; //turn on differents bits
  int ind = msb(mask);
  return (ind/lgdelta) + 1; //levels are 1-indexed
}

int multi_level_bucket_heap::calc_bucket(int key,int level){
  level--; //1-indexed tranformed in 0-indexed
  int shift = level*lgdelta, mask = (1<<lgdelta)-1;
  return (key>>shift) & mask; //get the lgdelta bits of the key
}

void multi_level_bucket_heap::insert(int key,int value){
  int level = calc_level(key);
  int bucket = calc_bucket(key,level);
  levels[level][bucket].insert(key,value);

  //verify the use of s-heap
  if(levels[level][bucket].size>t){
    levels[level][bucket].active = false;
    expand(level,bucket);
    if(levels[level][bucket].size<=t){
      levels[level][bucket].active = true;
      levels[level][bucket].copy_for_sheap();
    }
  }

  level_size[level]++;
  size++;
  valueMaps[value] = ValueMap(level,bucket,levels[level][bucket].size-1);

}

void multi_level_bucket_heap::expand(int level, int bucket){
  while(levels[level][bucket].size>0){
    pii elemento = levels[level][bucket].b.back();
    levels[level][bucket].b.pop_back();
    insert(elemento.first,elemento.second);
    levels[level][bucket].size--;
    level_size[level]--;
  }
}

pii multi_level_bucket_heap::extract_min(){
  if(size<=0) return {-1,-1}; //empty heap

  int minLevel = 1, bucketIndex=0;
  pii minPair;
  while(level_size[minLevel]==0) minLevel++;
  while(levels[minLevel][bucketIndex].size==0) bucketIndex++;
  minPair = levels[minLevel][bucketIndex].getMin();
  last = minPair.first;

  int index = valueMaps[minPair.second].index;
  deleteAt(minLevel,bucketIndex,index); //delete in bucket structure
  if(levels[minLevel][bucketIndex].active)
    levels[minLevel][bucketIndex].pop_sheap(); //delete in s-heap

  if(!levels[minLevel][bucketIndex].active){
    if(levels[minLevel][bucketIndex].size<=t){
      levels[minLevel][bucketIndex].active = true;
      levels[minLevel][bucketIndex].copy_for_sheap();
    //less than t elements and not active, so active bucket
    }
    else expand(minLevel,bucketIndex);
  }
  
  return minPair;
}

// void multi_level_bucket_heap::decrease_key(int newKey, int value){
//   ValueMap vm = valueMaps[value];
//   int level = vm.level, bucket = vm.bucket, index = vm.index;
//   deleteAt(level, bucket, index);
//   insert(newKey,value);
// }