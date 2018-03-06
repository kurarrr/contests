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

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll lmod = 1e9+7,LINF=1LL<<60;
const int MAX_N = 2003;

int main(){
  double x,y; cin >> x >> y;
  int cnt = 0;
  int xx,yy; xx = int(1000*x); yy = int(1000*y);
  set<pair<ll,ll>> st;
  vector<int> X,Y;
  REP(i,-5,6)
    REP(j,-5,6){X.pb(ll(x)+i); Y.pb(ll(y)+i);}
  std::random_device seed_gen;
  std::mt19937 engine(seed_gen());
  rep(i,25){
    if((1000*X[i]==xx && 1000*Y[i]==yy)) continue;
    rep(j,int(1e6)){
      int x2 = engine()%20000 - 10000;
      ll h = ll(yy-1000*Y[i])*ll(x2-X[i]);
      if(xx-1000*X[i]==0LL) continue;
      bool ok = (h%ll(xx-1000*X[i])==0);
      if(ok){
        int y2 = Y[i] + h/(xx-1000*X[i]);
        if(abs(X[i])>10000 || abs(Y[i])>10000|| abs(x2)>10000 || abs(y2)>10000) continue;
        if((1000*x2==xx && 1000*y2==yy) || (X[i]==x2&&Y[i]==y2)) continue;
        ll g;
        if((yy-1000*y2)*(X[i]-x2)!=(Y[i]-y2)*(xx-1000*x2)) continue;
        if(yy-1000*Y[i]==0LL) g = xx-1000*X[i];
        else g = __gcd(xx-1000*X[i],yy-1000*Y[i]);
        if(st.count(Pl((xx-1000*X[i])/g,(yy-1000*Y[i])/g))) continue;
        cout << X[i] << " " << Y[i] << " " << x2 << " " << y2 << endl;
        st.insert(Pl((xx-1000*X[i])/g,(yy-1000*Y[i])/g));
        cnt++; break;
      }
    }
    if(cnt==2) break;
  }
  return 0;
}