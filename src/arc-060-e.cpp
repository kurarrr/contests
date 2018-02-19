#include "bits/stdc++.h"

#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define RREP(i, x, n) for(int i = x; i >= n; i--)
#define rrep(i, n) RREP(i,n,0)
#define pb push_back

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

ll N,L,x[MAX_N];
int r[MAX_N][20];

void prepare(){
  // rep(i,N) rep(k,20) r[i][k] = INF;
  rep(i,N) r[i][0] = int(upper_bound(x,x+N,x[i]+L)-x)-1;
  int lg = 0; while((1<<lg)<N) lg++;
  rep(k,18) rep(i,N) r[i][k+1] = r[r[i][k]][k];
  // rep(i,N){rep(k,lg) cout << r[i][k] << " "; cout << endl;}
}

void query(){
  int a,b; scanf("%d%d",&a,&b);
  if(a>b) swap(a,b);
  a--; b--;
  int ans = 0;
  rrep(k,18){
    if(r[a][k]<b){
      a = r[a][k];
      ans += (1<<k);
    }
  }
  cout << ans+1 << endl;
}

int main(){
  cin >> N;
  rep(i,N) scanf("%lld",x+i);
  cin >> L;
  prepare();
  int Q; cin >> Q;
  rep(i,Q) query();
  return 0;
}