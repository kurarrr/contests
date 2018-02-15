// https://beta.atcoder.jp/contests/arc075/submissions/2049663
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
using Pl = pair<ll,int>;

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll lmod = 1e9+7,LINF=1LL<<60;
const int MAX_N = 200005;

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

ll a[MAX_N],s[MAX_N];

int main(){
  int N; ll K; cin >> N >> K;
  rep(i,N) scanf("%lld",a+i);
  ll _sum = 0LL;
  rep(i,N+1){
    s[i] = _sum - ll(i) * K;
    _sum += a[i];
  }
  vector<ll> s_cp(N+1);
  rep(i,N+1) s_cp[i] = s[i];
  sort(ALL(s_cp));
  s_cp.erase(unique(ALL(s_cp)),s_cp.end());
  FenwickTree<int> tree(N+1);
  ll ans = 0LL;
  rep(i,N+1){
    int index = int(lower_bound(s_cp.begin(),s_cp.end(),s[i])-s_cp.begin());
    ans += ll(tree.sum(index));
    tree.add(index,1);
  }
  cout << ans << endl;
  return 0;
}
