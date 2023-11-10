#include <bits/stdc++.h>
#include "multi_level_bucket_heap.h"
using namespace std;

const int k=3, max_key = 1e3, max_value = 1e5, t = 3;

int main(){
  multi_level_bucket_heap mlbh(k, max_key, max_value,t);
  cout<<mlbh.size()<<endl;
  mlbh.insert(320, 1);
  cout<<mlbh.size()<<endl;
  mlbh.insert(321, 2);
  cout<<mlbh.size()<<endl;
  mlbh.insert(123, 3);
  cout<<mlbh.size()<<endl;

  pair<int,int> el = mlbh.extract_min();
  cout<<el.first<<" "<<el.second<<"\n";
  cout<<mlbh.size()<<endl;
  
  el = mlbh.extract_min();
  cout<<el.first<<" "<<el.second<<"\n";
  el = mlbh.extract_min();
  cout<<el.first<<" "<<el.second<<"\n";

  //122, 123, 321


  cout<<"Testing!!!\n";
}