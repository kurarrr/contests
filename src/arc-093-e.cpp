#include "bits/stdc++.h"

#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define RREP(i, x, n) for(int i = x; i >= n; i--)
#define rrep(i, n) RREP(i,n,0)
#define pb push_back
#define show_table(n, k, table) rep(i,n){ rep(j,k) cout << table[i][j] << " "; cout << endl;}

using namespace std;

template<class T> inline void chmax(T& a,T const& b){a=max(a,b);}
template<class T> inline void chmin(T& a,T const& b){a=min(a,b);}

using ll = long long;
using P = pair<int,int>;
using Pl = pair<ll,ll>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll lmod = 1e9+7,LINF=1LL<<60;
const int MAX_N = 100005;

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

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);
  int N,M; cin >> N >> M;
  ll X; cin >> X;
  priority_queue<Pl,vector<Pl>,greater<Pl>> que1,que2;
  vi u(M),v(M); vl w(M),a(M);
  rep(i,M){
    cin >> u[i] >> v[i] >> w[i];
    u[i]--; v[i]--;
    que1.push(Pl(w[i],i));
  }
  rep(i,M){
    // 辺i を必ず使う MST のコスト
    ll temp = w[i];
    UnionFindTree uft(N);
    uft.unite(u[i],v[i]);
    que2 = que1;
    while(!que2.empty()){
      ll j; ll c;
      tie(c,j) = que2.top(); que2.pop();
      if(!uft.same(u[j],v[j])){
        temp += c;
        uft.unite(u[j],v[j]);
      }
    }
    a[i] = temp;
  }
  sort(ALL(a));
  // rep(i,M) cout << a[i] << " "; cout << endl;
  function<ll(ll)> f = [&](ll x){
    // aがx以下の辺が全て同じ色である場合の数
    int num = int(upper_bound(a.begin(),a.end(),x) - a.begin());
    ll res = 2;
    if(num==0) res >>= 1;
    rep(i,M-num) (res <<= 1) %= lmod;
    // cout << "res " << res << "  num " << num << endl;
    return res;
  };
  cout << (f(X-1) - f(X) + lmod) % lmod << endl;
  return 0;
}
