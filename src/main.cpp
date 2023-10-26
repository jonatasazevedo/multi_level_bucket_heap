#include <bits/stdc++.h>
#include "multi_level_bucket_heap.h"

const int k=3, max_key = 1e5;

int main(){
  multi_level_bucket_heap mlbh(k, max_key);
  mlbh.insert(123,2);
  std::pair<int,int> el = mlbh.extract_min();
  //std::cout<<el.first<<" "<<el.second<<"\n";

  std::cout<<"Testing!!!\n";
}