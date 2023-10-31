#include "bucket.h"

bucket::bucket(int inf):
  mi(inf, inf), size(0){ }

void bucket::insert(int key, int value){
  b.emplace_back(key,value);
  size++;
  if(mi.first>key) mi = {key,value};
}