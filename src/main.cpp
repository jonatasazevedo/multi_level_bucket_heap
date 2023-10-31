#include <bits/stdc++.h>
#include "multi_level_bucket_heap.h"
using namespace std;

const int k=3, max_key = 1e3, max_value = 1e5;

int main(){
  multi_level_bucket_heap mlbh(k, max_key, max_value);

  cout<<mlbh.delta<<endl;

  mlbh.insert(320, 1);
  mlbh.insert(321, 2);
  mlbh.insert(123, 3);

  mlbh.decrease_key(122, 1);

  std::pair<int,int> el = mlbh.extract_min();
  std::cout<<el.first<<" "<<el.second<<"\n";
  el = mlbh.extract_min();
  std::cout<<el.first<<" "<<el.second<<"\n";
  el = mlbh.extract_min();
  std::cout<<el.first<<" "<<el.second<<"\n";

  //122, 123, 321


  // std::cout<<"Testing!!!\n";
}