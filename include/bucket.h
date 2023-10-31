#include <bits/stdc++.h>
typedef std::pair<int,int> pii;

class bucket{
  public:
    int size; //number of elements in the bucket
    pii mi; //min element
    std::vector<pii> b; //(key,value)
    bucket(int inf);
    void insert(int key,int value);
};