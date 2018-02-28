// https://beta.atcoder.jp/contests/arc068/submissions/2123226

#include "bits/stdc++.h"

#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define RREP(i, x, n) for(int i = x; i >= n; i--)
#define rrep(i, n) RREP(i,n,0)
#define pb push_back
#define show_table(n, k, table) rep(i,n){ rep(j,k) cout << table[i][j] << " "; cout << endl;}

template<class T> void chmax(T& a,const T& b){a=max(a,b);}
template<class T> void chmin(T& a,const T& b){a=min(a,b);}

using namespace std;

using ll = long long;
using P = pair<int,int>;
using Pl = pair<ll,ll>;
using vi = vector<int>;
using vvi = vector<vi>;

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll lmod = 1e9+7,LINF=1LL<<60;
const int MAX_N = 300005;

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

P lr[MAX_N];

int main(){
  int N,M; cin >> N >> M;
  rep(i,N) scanf("%d%d",&lr[i].first,&lr[i].second);
  sort(lr,lr+N,[](P x,P y){return x.second-x.first < y.second-y.first;});
  FenwickTree<ll> tree(M+2);
  int next = 0;
  REP(i,1,M+1){
    int ans = N - next;
    for(int j=1;j*i<=M;j++){
      ans += int(tree.sum(j*i));
    }
    while(next<N && lr[next].second-lr[next].first==i-1){
      // add 1 to [l,r] 
      tree.add(lr[next].first,1LL);
      tree.add(lr[next].second+1,-1LL);
      next++;
    }
    // cout << next << " " << ans << endl;
    printf("%d\n",ans);
  }
  return 0;
}