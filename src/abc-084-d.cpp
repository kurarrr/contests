// https://beta.atcoder.jp/contests/abc084/submissions/1925316

#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<list>
#include<queue>
#include<deque>
#include<algorithm>
#include<utility>
#include<memory>
#include<cmath>
#include<stack>
#include<tuple>
#include<numeric>
#include<cassert>

#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define EXIST(s,e) ((s).find(e)!=(s).end())
#define pb push_back
#define DEBUG false

using namespace std;

using ll = long long;
using P = pair<int,int>;
using Pl = pair<int,ll>;
using Pd = pair<double,double>;
using T = tuple<double,double,int>;

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll LINF=1LL<<60;
const int MAX_N = 100005;
const ll lmod = 1e9+7;

template <typename T>
class FenwickTree {
  const int n;
  vector<T> data;
public:
  FenwickTree(int n) : n(n), data(n, 0) {}
  void add(int i, T value) {
    for (; i < n; i |= i + 1) data[i] += value;
  }
  T sum(int i) const {
    // sum of [0,i]
    T res = 0;
    for (; i >= 0; i = (i & (i + 1)) - 1) res += data[i];
    return res;
  }
  T sum(int l, int r) const { return sum(r - 1) - sum(l - 1); }
};

FenwickTree<int> tree(MAX_N);
bool isPrime[MAX_N];

void prepare(){
  fill(isPrime,isPrime+MAX_N,true);
  isPrime[1] = false;
  REP(i,2,int(sqrt(double(MAX_N))+1)){
    int a = i;
    while(true){
      a += i;
      if(a>MAX_N) break;
      isPrime[a] = false;
    }
  }
  rep(i,MAX_N/2){
    int j = 2*i + 1;
    if(isPrime[j]&&isPrime[(j+1)/2]) tree.add(j,1);
  }
}

void solve(){
  int l,r;
  scanf("%d%d",&l,&r);
  printf("%d\n",tree.sum(l,r+1));
}

int main(){
  int Q; cin >> Q ;
  prepare();
  rep(i,Q) solve();
  return 0;
}
