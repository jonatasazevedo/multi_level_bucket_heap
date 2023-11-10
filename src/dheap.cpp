#include<bits/stdc++.h>
#include "dheap.h"
typedef std::pair<int,int> pii;

dheap::dheap(){}

dheap::dheap(int max_size,int d,int max_value)
  :max_size(max_size),d(d),max_value(max_value){
  heap = std::vector<pii>(max_size);
  valueMap = std::vector<int>(max_value+1);
}

int dheap::parent(int index){
  return (index-1)/d;
}

pii dheap::extract_min(){
  if(heap_size==0) return {-1,-1};
  if(heap_size==1){
    heap_size--;
    return heap[heap_size];
  }
  pii root = heap[0];
  heap_size--;
  heap[0] = heap[heap_size];
  minHeapify();
  return root;
}

void dheap::restore_up(int index){
  int p = parent(index);

  while(index!=0 && heap[p]>heap[index]){
    swap(heap[p],heap[index]);
    index = p;
    p = parent(index);
  }
}

void dheap::insert(int key,int value){
  if(heap_size==max_size) return;
  int index = heap_size;
  heap[index] = {key,value};
  valueMap[value] = index;
  heap_size++;
  restore_up(index);
}

void dheap::minHeapify(){
  int index = 0;
  while(1){
    int smallest = index;
    //find the smallest child that belongs to the heap
    for(int i=1; i<=d ;i++){
      int child = (index*d+i);

      if(child<heap_size){
        if(heap[smallest]>heap[child]) smallest = child;
      }
      else break;
    }  
    //if there is a child smaller than index , the heapify process continues
    if(smallest!=index){
      swap(heap[smallest],heap[index]);
      index = smallest;
    }
    else break;
  }
}

void dheap::decrease_key(int newKey,int value){
  int index = valueMap[value];
  heap[index] = {newKey,value};
  restore_up(index);
}

int dheap::size(){
  return heap_size;
}

bool dheap::empty(){
  return heap_size==0;
}

void dheap::clear(){
  heap_size=0;
}