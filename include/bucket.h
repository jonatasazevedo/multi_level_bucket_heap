#include <bits/stdc++.h>
typedef std::pair<int,int> pii;

class bucket{
  public:
    int size;
    pii minimo;
    std::vector<pii> b; //(key,value)
    bucket(int inf);
};