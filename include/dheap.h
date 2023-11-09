#include<bits/stdc++.h>
typedef std::pair<int,int> pii;

class dheap{
  private:
    int max_size,d,heap_size,max_value;
    std::vector<pii> heap;
    std::vector<int> valueMap;
    int parent(int i);
    void minHeapify();
    void restore_up(int index);
  public:
    int size;
    dheap(int max_size,int k,int max_value);
    void insert(int key,int value);
    pii extractmin();
    void decrease_key(int key,int value);
};