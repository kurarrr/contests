// https://beta.atcoder.jp/contests/apc001/submissions/2064641

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
const int MAX_N = 100005;

template <typename T>
struct UnionFindTree{
  T par[MAX_N],rank[MAX_N],size[MAX_N];
  UnionFindTree(int N){
    fill(rank,rank+N,0);
    fill(size,size+N,1);
    rep(i,N) par[i] = i;
  }
  T find(T x){
    if(par[x]==x) return x;
    else return par[x] = find(par[x]);
  }
  void unite(T x,T y){
    x = find(x);
    y = find(y);
    if(x==y)  return ;
    if(rank[x] < rank[y]){
      par[x] = y;
    }else{
      par[y] = x;
      if(rank[x]==rank[y])  ++rank[x];
    }
    size[x] = size[y] = size[x] + size[y];
  }
  bool same(T x,T y){
    return find(x)==find(y);
  }
};

Pl a[MAX_N];
bool used[MAX_N];

int main(){
  int N,M; cin >> N >> M;
  UnionFindTree<int> uft(N);
  rep(i,N){
    scanf("%lld",&a[i].first);
    a[i].second = i;
  }
  rep(i,M){
    int x,y; scanf("%d%d",&x,&y);
    uft.unite(x,y);
  }
  if(2*(N-M-1)>N){
    cout << "Impossible" << endl;
    return 0;
  }else if(M==N-1){
    cout << "0" << endl;
    return 0;
  }
  sort(a,a+N);
  unordered_set<int> st;
  ll ans = 0LL; int cnt = 0;
  rep(i,N){
    if(st.count(uft.find(a[i].second))){
      if(cnt < N-M-2) ans += a[i].first, cnt++;
    }else{
      st.insert(uft.find(a[i].second));
      ans += a[i].first;
    }
  }
  cout << ans << endl;
  return 0;
}
