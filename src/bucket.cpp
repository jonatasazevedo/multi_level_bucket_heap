#include <bits/stdc++.h>
#include "bucket.h"

bucket::bucket()
  :size(0){ }

void bucket::insert(int key, int value){
  b.emplace_back(key,value);
  if(active) pq.push({key,value});
  size++;
}

pii bucket::getMin(){
  if(b.empty()) return pii(-1,-1);
  pii ans;
  if(active)
    ans = pq.top();
  else{
    ans = b[0];
    for(size_t i=1;i<b.size();i++)
      ans = std::min(ans,b[i]);
  }
  return ans;
}

void bucket::copy_for_sheap(){
  for(size_t i=1;i<b.size();i++)
    pq.push(b[i]);
}

void bucket::pop_sheap(){
  pq.pop();
}