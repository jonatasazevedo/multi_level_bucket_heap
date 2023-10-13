#include <bits/stdc++.h>
typedef std::pair<int,int> pii;
class multi_level_bucket_heap{
  private:
    int base,k,size=0,last=0,max_key;
    //k -> number of levels
    //last -> last removed in the heap
    std::vector<std::vector<std::vector<pii>>> level_bucket;
    void init();
    
  public:
    multi_level_bucket_heap(int base_,int max_key_);
    

  
};