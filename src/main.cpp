#include <bits/stdc++.h>
#include "multi_level_bucket_heap.h"
using namespace std;


int main(){
  int n=10,k=5, max_key = 1e3, max_value = 1e5, t = 3,d=3;
  cin>>n>>max_key>>max_value;
  multi_level_bucket_heap mlbh(k, max_key, max_value,t,d);
  int op,key,value;
  for(int i=0;i<n;i++){
    cin>>op;
    if(op==0) 
      cout<<"size: "<<mlbh.size()<<endl;
    else if(op==1){
      cin>>key>>value;
      cout<<"insert ("<<key<<","<<value<<")"<<endl;
      mlbh.insert(key,value);
    }
    else if(op==2){ 
      if(!mlbh.empty()){
        pii elemento = mlbh.extract_min();
        cout<<"extract min ("<<elemento.first<<","<<elemento.second<<")"<<endl;    
      }
      else cout<<"structure empty"<<endl;
    }
    else if(op==3){
      cin>>key>>value;
      int oldKey = mlbh.keyValue(value);
      mlbh.decrease_key(key,value);
      cout<<"decrease key ("<<oldKey<<","<<value<<") in ("<<key<<","<<value<<")"<<endl;
    }
  }
}