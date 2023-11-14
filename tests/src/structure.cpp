#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

map<int,int> keyValue;
set<pii> structure;

int main(){
  int n,k,max_key,max_value,t;
  //n -> number of operations
  //k -> number of levels
  //max_key -> maximum key that can be inserted
  //max_value -> maximum value that can be inserted
  //t -> number of maximum elements in the s-heap
  cin>>n>>max_value>>max_key;
  int op,key,value;
  for(int i=0;i<n;i++){
    cin>>op;
    if(op==0) 
      cout<<"size: "<<structure.size()<<endl;
    else if(op==1){ //insert
      cin>>key>>value;
      cout<<"insert ("<<key<<","<<value<<")"<<endl;
      keyValue[value]=key;
      structure.emplace(key,value);
    }
    else if(op==2){ //extract_min
      if(!structure.empty()){
        pii elemento = *(structure.begin());
        structure.erase(structure.begin());
        cout<<"extract min ("<<elemento.first<<","<<elemento.second<<")"<<endl;    
      }
      else cout<<"structure empty"<<endl;
    }
    else if(op==3){
      cin>>key>>value;
      int oldKey = keyValue[value];
      cout<<"decrease key ("<<oldKey<<","<<value<<") in ("<<key<<","<<value<<")"<<endl;
      structure.erase({oldKey,value});
      structure.insert({key,value});
      keyValue[value] = key;
    }
  }

}