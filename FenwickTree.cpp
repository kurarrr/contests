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
const int MAX_N = 10004, MAX_C = 102;
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

int main(){
  FenwickTree<int> hoge(1000);
  hoge.add(0,1);
  hoge.add(1,3);
  hoge.add(600,30);
  cout << hoge.sum(0) << endl;
  cout << hoge.sum(1) << endl;
  cout << hoge.sum(2) << endl;
  cout << hoge.sum(599) << endl;
  cout << hoge.sum(999) << endl;
	return 0;
}