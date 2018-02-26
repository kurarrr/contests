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
const int MAX_N = 100005;

unordered_map<int,ll> now,nxt;

void update(int f,ll x){
  if(nxt.count(f)){
    (nxt[f] += x) %= lmod;
  }else{
    nxt[f] = x;
  }
}

int main(){
  int T,a,b,c,d,e,f,g;
  cin >> T;
  cin >> a >> b >> c >> d >> e;
  now[0] = 1;
  rep(i,T){
    nxt.clear();
    for(auto u:now){
      tie(f,g) = u;
      update(f+a,g);
      update(f+b,g);
      update(f+c,g);
      update(f-a,g);
      update(f-b,g);
      update(f-c,g);
    }
    swap(now,nxt);
  }
  ll ans = 0LL;
  for(auto u:now){
    tie(f,g) = u;
    if(f>=d && f<=e) (ans += g) %= lmod;
  }
  cout << ans << endl;
  return 0;
}