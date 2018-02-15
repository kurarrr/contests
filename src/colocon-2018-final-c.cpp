// https://beta.atcoder.jp/contests/colopl2018-final-open/submissions/2026373

#include "bits/stdc++.h"

#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define RREP(i, x, n) for(int i = x; i >= n; i--)
#define rrep(i, n) RREP(i,n,0)
#define pb push_back

using namespace std;

using ll = long long;
using P = pair<int,int>;
using Pl = pair<int,ll>;

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll LINF=1LL<<60, lmod = 1e9+7;
const int MAX_N = 100005;

template<class Data>
struct ConvexHullTrick {
  deque<pair<Data, Data>> l;
  bool check(pair<Data, Data> l3) {
    const auto l1 = *prev(end(l), 2);
    const auto l2 = *prev(end(l), 1);
    Data a = (l2.first - l1.first) * (l3.second - l2.second);
    Data b = (l2.second - l1.second) * (l3.first - l2.first);
    return a >= b;
  }
  bool empty() const { return l.empty(); }
  void add(Data a, Data b) {
    if (!empty()) assert (l.back().first >= a);
    pair<Data, Data> n(a, b);
    while ((int)l.size() >= 2 && check(n)) l.pop_back();
    l.emplace_back(n);
  }
  Data f(int k, Data x) { return l[k].first * x + l[k].second; }
  Data minimum(Data x) {
    assert (!empty());
    while ((int)l.size() >= 2 && f(0, x) >= f(1, x)) l.pop_front();
    return f(0, x);
  }
};

ConvexHullTrick<ll> cht;

int main(){
  int N; cin >> N;
  for(ll j = 1LL; j <= ll(N); j++){
    ll a; scanf("%lld",&a);
    cht.add(-2*j,j*j+a);
  }
  for(ll i = 1LL; i <= ll(N); i++){
    cout << i*i+cht.minimum(i) << endl;
  }
  return 0;
}
