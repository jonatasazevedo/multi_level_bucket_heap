#include <bits/stdc++.h>
#include "bucket.h"

using namespace std;

bucket::bucket()
  :size(0){ }

void bucket::insert(int key, int value){
  b.emplace_back(key,value);
  size++;
}

pii bucket::getMin(){
  if(b.empty()) return pii(-1,-1);
  pii ans = b[0];
  for(size_t i=1;i<b.size();i++)
    ans = std::min(ans,b[i]);
  return ans;
}
