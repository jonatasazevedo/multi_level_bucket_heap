#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

set<pii> structure;
vector<int> keyValue;

int generate_random_number(int a, int b){
  return (rand()%(b-a+1))+a;
}

int main(){
  srand(time(NULL));
  int n=10000,max_value=100000,max_key=100000;
  int last=0;
  cout<<n<<" "<<max_value<<" "<<max_key<<endl;
  //1 -> Insert
  //2 -> extract min
  //3 -> decrease key
  keyValue = vector<int>(max_value+1,-1);
  while(n--){
    int op = (structure.empty())? 1:generate_random_number(1,3);
    cout<<op;
    if(op==1){
      int key = generate_random_number(last,max_key);
      int value;
      do{
        value = generate_random_number(0,max_value);
      }while(keyValue[value]!=-1);
      keyValue[value] = key;
      structure.insert({key,value});
      cout<<" "<<key<<" "<<value;
    }
    else if(op==2){
      auto it = structure.begin();
      pii elemento = *it;
      last = elemento.first;
      keyValue[elemento.second] = -1;
      structure.erase(it);
    }
    else if(op==3){
      int ind = generate_random_number(0,structure.size()-1);
      int i=0; auto it=structure.begin();
      while(i<ind){
        it++;
        i++;
      }
      pii el = *it;
      structure.erase(it);
      int newKey;
      if(last==el.first) newKey=el.first;
      else newKey = generate_random_number(last,el.first-1);
      structure.insert({newKey,el.second});
      keyValue[el.second] = newKey;
      cout<<" "<<newKey<<" "<<el.second;
    }
    cout<<endl;
  }
}