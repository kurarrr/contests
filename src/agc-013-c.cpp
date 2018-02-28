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

int N,w[MAX_N];
ll T,L,x[MAX_N];

int main(){
  cin >> N >> L >> T;
  rep(i,N) scanf("%lld %d",x+i,w+i);
  ll cnt = 0LL;
  rep(i,N){
    if(w[i]==1) cnt += (T+x[i])/L;
    else cnt -= (T-x[i]+L-1)/L;
  }
  cout << cnt << endl;
  cnt = (cnt % N + N) % N;
  rep(i,N){
    if(w[i]==1) x[i] = (x[i]+T)%L;
    else x[i] = ((x[i]-T)%L+L)%L;
  }
  sort(x,x+N);
  rep(i,N) printf("%lld\n",x[(i+cnt)%N]);
  return 0;
}