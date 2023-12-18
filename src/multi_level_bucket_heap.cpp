#include <bits/stdc++.h>
#include "multi_level_bucket_heap.h"
typedef std::pair<int,int> pii;

using namespace std;

void multi_level_bucket_heap::init(){
  mlb_size=0;
  last=0;
  level_size = std::vector<int>(k+1,0);
  levels = std::vector<std::vector<bucket>>(k+1,std::vector<bucket>());
  for(int i=1;i<=k;i++){
    levels[i] = std::vector<bucket>(delta,bucket());
  }
  //k levels, each one have delta buckets
  valueMaps = std::vector<ValueMap>(max_value+1);
}

multi_level_bucket_heap::multi_level_bucket_heap(int max_key,int max_value)
  :multi_level_bucket_heap(3,max_key,max_value){
}
multi_level_bucket_heap::multi_level_bucket_heap(int k, int max_key, int max_value)
  :k(k), max_key(max_key), max_value(max_value){
  delta = ceil(pow(max_key+1,1.0/k));
  u = pow(delta,k);
  init();
}

// int multi_level_bucket_heap::msb(int x){
//   return (x==0)? 0:__builtin_clz(1) - __builtin_clz(x);
// }

// void multi_level_bucket_heap::deleteAt(int level, int bucket, int index){
//   if(index >= levels[level][bucket].size) return;
//   if(index  < levels[level][bucket].size-1){
//     pii lastPair = levels[level][bucket].b.back();
//     levels[level][bucket].b[index] = lastPair;
//     valueMaps[lastPair.second].index = index;
//   }
//   levels[level][bucket].b.pop_back();
//   levels[level][bucket].size--;
//   level_size[level]--;
//   mlb_size--;
// }

// int multi_level_bucket_heap::calc_level(int key){
//   int mask = key^last; //turn on differents bits
//   int ind = msb(mask);
//   return (ind/lgdelta) + 1; //levels are 1-indexed
// }

// int multi_level_bucket_heap::calc_bucket(int key,int level){
//   level--; //1-indexed tranformed in 0-indexed
//   int shift = level*lgdelta, mask = (1<<lgdelta)-1;
//   return (key>>shift) & mask; //get the lgdelta bits of the key
// }

void multi_level_bucket_heap::insert(int key,int value){
  int remain = key-offset*u;
  for(int indice=activeBucket,i=1;i<=delta;i++,indice){
    if(indice>=delta) indice-=delta;
    if(remain>=(i-1)*delta && remain<=i*delta){
      levels[k][indice].insert(key,value);
      return;
    }
  }
}

// void multi_level_bucket_heap::expand(int level, int bucket){
//   std::vector<pii> bucket_vector = levels[level][bucket].b;
//   levels[level][bucket].b.clear();
//   levels[level][bucket].size=0;

//   for(size_t i=0;i<bucket_vector.size();i++){
//     pii elemento = bucket_vector[i];
//     level_size[level]--;
//     mlb_size--;
//     insert(elemento.first,elemento.second);
//   }
// }

// int multi_level_bucket_heap::extract_min(){
//   if(mlb_size<=0) return -1; //empty multi-level-bucket
//   if(!sheap.empty()){ // sheap is not empty
//     pii minPair = sheap.extract_min(); //delete and extract in sheap
//     ValueMap vm = valueMaps[minPair.second];
//     int level = vm.level, bucket = vm.bucket, index = vm.index;
//     deleteAt(level,bucket,index); //delete in bucket structure
//     if(sheap.empty()) deactive_bucket(level,bucket);
//     return minPair.second;
//   }

//   int minLevel = 1, bucketIndex=0;
//   while(level_size[minLevel]==0) minLevel++;
//   while(levels[minLevel][bucketIndex].size==0) bucketIndex++;
//   pii minPair = levels[minLevel][bucketIndex].getMin();
//   last_temp = minPair.first;

//   int index = valueMaps[minPair.second].index;
//   deleteAt(minLevel,bucketIndex,index); //delete in bucket structure
//   if(levels[minLevel][bucketIndex].size<=t && levels[minLevel][bucketIndex].size>0)
//     activate_bucket(minLevel,bucketIndex);
//   else{
//     last = last_temp;
//     expand(minLevel,bucketIndex);
//   }
  
//   return minPair.second;
// }

// void multi_level_bucket_heap::decrease_key(int newKey, int value){
//   ValueMap vm = valueMaps[value];
//   int level = vm.level, bucket = vm.bucket, index = vm.index;
//   if(level==levelActive && bucket==bucketActive){
//     sheap.decrease_key(newKey,value);
//     levels[level][bucket].b[index]={newKey,value};
//   }
//   else{
//     deleteAt(level,bucket,index);
//     insert(newKey,value);
//   }
  
  
// }

// void multi_level_bucket_heap::activate_bucket(int level,int bucket){
//   levelActive = level;
//   bucketActive = bucket;
//   int bucketsize = levels[level][bucket].b.size(); 
//   for(int i=0;i<bucketsize;i++){
//     pii elemento = levels[level][bucket].b[i];
//     sheap.insert(elemento.first,elemento.second);
//   }
// }

// void multi_level_bucket_heap::deactive_bucket(int level,int bucket){
//   levelActive=-1;
//   bucketActive=-1;
//   sheap.clear();
//   last = last_temp;
//   expand(level,bucket);
// }

int multi_level_bucket_heap::size(){
  return mlb_size;
}

bool multi_level_bucket_heap::empty(){
  return mlb_size==0;
}

int multi_level_bucket_heap::keyValue(int value){
  ValueMap vm = valueMaps[value];
  int level = vm.level, bucket = vm.bucket, index = vm.index;
  return levels[level][bucket].b[index].first;
}