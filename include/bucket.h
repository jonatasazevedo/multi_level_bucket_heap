#include <bits/stdc++.h>
typedef std::pair<int,int> pii;
typedef std::priority_queue<pii,std::vector<pii>,std::greater<pii>> prioq;
class bucket{
  public:
    int size; //number of elements in the bucket
    std::vector<pii> b; //(key,value)
    prioq pq; //s-heap 
    bool active;
    bucket();
    void insert(int key,int value);
    pii getMin();
    void copy_for_sheap();
    void pop_sheap();
};