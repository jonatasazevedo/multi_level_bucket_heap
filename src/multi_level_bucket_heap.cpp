#include <bits/stdc++.h>
#include "multi_level_bucket_heap.h"
typedef std::pair<int,int> pii;

using namespace std;

void multi_level_bucket_heap::init(){
  mlb_size=0;
  local_size=0;
  last=0;
  levelActive=bucketActive=-1;
  bucket_top_active=0;
  level_size = std::vector<int>(k+2,0);
  levels = std::vector<std::vector<bucket>>(k+2,std::vector<bucket>());
  for(int i=1;i<=k+1;i++) levels[i] = std::vector<bucket>(delta,bucket());
  //k+1 levels, each one have delta buckets
  valueMaps = std::vector<ValueMap>(max_value+1);
  sheap = dheap(t,d,max_value); 
}

multi_level_bucket_heap::multi_level_bucket_heap(int max_key,int max_value)
  :multi_level_bucket_heap(3,max_key,max_value,5,3){
}
multi_level_bucket_heap::multi_level_bucket_heap(int k, int max_key, int max_value,int t,int d)
  :k(k), max_key(max_key), max_value(max_value),t(t),d(d){
  lgdelta = calc_lgdelta(max_key, k);
  delta = 1 << lgdelta; //2^lgdelta = delta
  top_level_range = 1 << (lgdelta*k); //delta^k
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
  if(level<=k && level>0) local_size--;
  mlb_size--;
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

int multi_level_bucket_heap::findBucketTopLevel(int key){
  return (key/top_level_range)%delta;
}

void multi_level_bucket_heap::insertLocal(int key,int value){
  int level = calc_level(key);
  int bucket = calc_bucket(key,level);
  levels[level][bucket].insert(key,value);
  level_size[level]++;
  local_size++;
  valueMaps[value] = ValueMap(level,bucket,levels[level][bucket].size-1);
  //verify if there is an active bucket, and whether it will be inserted into this bucket
  if(level==levelActive && bucket==bucketActive){
    if(levels[level][bucket].size<t)
      sheap.insert(key,value);
    else
      deactive_bucket(level,bucket);
  }
}

void multi_level_bucket_heap::insert(int key,int value){ 
  mlb_size++;
  int bucket_top_level = findBucketTopLevel(key);
  if(bucket_top_level==bucket_top_active){
    insertLocal(key%top_level_range,value);
  }
  else{
    levels[k+1][bucket_top_level].insert(key,value);
    valueMaps[value] = ValueMap(k+1,bucket_top_level,levels[k+1][bucket_top_level].size-1);
  }
}

void multi_level_bucket_heap::expand(int level, int bucket){
  std::vector<pii> bucket_vector = levels[level][bucket].b;
  levels[level][bucket].b.clear();
  levels[level][bucket].size=0;

  for(size_t i=0;i<bucket_vector.size();i++){
    pii elemento = bucket_vector[i];
    level_size[level]--;
    local_size--;
    insertLocal(elemento.first,elemento.second);
  }
}

int multi_level_bucket_heap::extract_min(){
  if(mlb_size<=0) return -1;
  if(local_size==0) fill_structure_local();

  if(!sheap.empty()){ // there is bucket active
    pii minPair = sheap.extract_min();
    ValueMap vm = valueMaps[minPair.second];
    int level = vm.level, bucket = vm.bucket, index = vm.index;
    deleteAt(level,bucket,index); //delete in bucket structure
    if(sheap.empty()) deactive_bucket(level,bucket);
    return minPair.second;
  }

  int minLevel = 1, bucketIndex=0;
  while(level_size[minLevel]==0) minLevel++;
  while(levels[minLevel][bucketIndex].size==0) bucketIndex++;
  pii minPair = levels[minLevel][bucketIndex].getMin();
  last_temp = minPair.first;
  int index = valueMaps[minPair.second].index;
  deleteAt(minLevel,bucketIndex,index); //delete in bucket structure

  if(minLevel!=1){
    if(levels[minLevel][bucketIndex].size<=t && levels[minLevel][bucketIndex].size>0)
      activate_bucket(minLevel,bucketIndex);
    else{
      last = last_temp;
      expand(minLevel,bucketIndex);
    }
  }
  else last = last_temp;

  return minPair.second;
}

void multi_level_bucket_heap::decrease_key(int newKey, int value){
  
  ValueMap vm = valueMaps[value];
  int level = vm.level, bucket = vm.bucket, index = vm.index;
  if(level==levelActive && bucket==bucketActive){
    newKey%=top_level_range;
    sheap.decrease_key(newKey,value);
    levels[level][bucket].b[index]={newKey,value};
  }
  else{
    deleteAt(level,bucket,index);
    if(level==k+1) {
      insert(newKey,value);
    }
    else {
      mlb_size++;  
      insertLocal(newKey%top_level_range,value);
    }
  }
}

void multi_level_bucket_heap::activate_bucket(int level,int bucket){
  levelActive = level;
  bucketActive = bucket;
  int bucketsize = levels[level][bucket].b.size(); 
  for(int i=0;i<bucketsize;i++){
    pii elemento = levels[level][bucket].b[i];
    sheap.insert(elemento.first,elemento.second);
  }
}

void multi_level_bucket_heap::deactive_bucket(int level,int bucket){
  levelActive=-1;
  bucketActive=-1;
  sheap.clear();
  last = last_temp;
  expand(level,bucket);
}

void multi_level_bucket_heap::fill_structure_local(){
  if(mlb_size!=0){
    bucket_top_active++;
    if(bucket_top_active==delta) bucket_top_active=0;
    levelActive=bucketActive=-1;
    last=0;
    while(levels[k+1][bucket_top_active].size>0){
      pii elemento = levels[k+1][bucket_top_active].b.back();
      levels[k+1][bucket_top_active].b.pop_back();
      levels[k+1][bucket_top_active].size--;
      insertLocal(elemento.first%top_level_range,elemento.second);
    }   
  }
}

int multi_level_bucket_heap::size(){
  return mlb_size;
}

bool multi_level_bucket_heap::empty(){
  return mlb_size==0;
}