#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<list>
#include<queue>
#include<deque>
#include<algorithm>
#include<utility>
#include<memory>
#include<cmath>
 
#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define EXIST(s,e) ((s).find(e)!=(s).end())
#define pb push_back
 
using namespace std;
 
typedef long long ll;
typedef pair<int,int> P;
const int mod=1e9+7;
const int INF=1<<30;
const int MAX_N=100001;

struct UnionFindTree{
  vector<int> par,rank,size;
  UnionFindTree(int N){
    par = rank = vector<int>(N,0);
    size = vector<int>(N,1);
    for(int i = 0; i < N; i++) par[i] = i;
  }
  int find(int x){
    if(par[x] == x) return x;
    else return par[x] = find(par[x]);
  }
  void unite(int x,int y){
    x = find(x);
    y = find(y);
    if(x == y)  return ;
    if(rank[x] < rank[y]){
      par[x] = y;
    }else{
      par[y] = x;
      if(rank[x] == rank[y]) ++rank[x];
    }
    size[x] = size[y] = size[x] + size[y];
  }
  bool same(int x,int y){
    return find(x) == find(y);
  }
};

UnionFindTree u(100);

int main(){
  u.unite(1,3);
  u.unite(0,3);
  cout << (u.same(0,1) ? "yes": "no") << endl;
  cout << (u.same(0,2) ? "yes": "no") << endl;
  return 0;
}