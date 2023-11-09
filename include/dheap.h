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
    int size();
    dheap();
    dheap(int max_size,int d,int max_value);
    void insert(int key,int value);
    pii extract_min();
    void decrease_key(int newKey,int value);
};