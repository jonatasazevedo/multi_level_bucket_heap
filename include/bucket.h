#pragma once
#include <bits/stdc++.h>
#define int long long
typedef std::pair<int,int> pii;

class bucket{
  public:
    int size; //number of elements in the bucket
    std::vector<pii> b; //(key,value)
    bucket();
    void insert(int key,int value);
    pii getMin();
};