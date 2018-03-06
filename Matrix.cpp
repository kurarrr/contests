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

struct Mat {
  vector<vector<ll>> v;
  Mat(int n):v(n,vector<ll>(n)){};
  Mat(const vector<vector<ll>>& v):v(v){};
};
Mat mulmat(Mat& a,Mat& b) {
  int n = a.v.size();
	ll mo2=4*lmod*lmod;
	int x,y,z; Mat r(n);
	rep(x,n) rep(y,n) r.v[x][y]=0;
	rep(x,n) rep(z,n) rep(y,n) {
		r.v[x][y] += a.v[x][z]*b.v[z][y];
		if(r.v[x][y]>mo2) r.v[x][y] -= mo2;
	}
	rep(x,n) rep(y,n) r.v[x][y]%=lmod;
	return r;
}

Mat powmat(ll p,Mat a) {
  int n = a.v.size();
	int i,x,y; Mat r(n);
	rep(x,n) rep(y,n) r.v[x][y]=0;
	rep(i,n) r.v[i][i]=1;
	while(p) {
		if(p%2) r=mulmat(r,a);
		a=mulmat(a,a);
		p>>=1;
	}
	return r;
}

Mat A(8);

int main(){
  ll N; cin >> N;
  A.v ={{1,1,1,0,0,0,0,1},
        {1,1,1,1,1,0,0,1},
        {1,1,1,1,1,1,0,1},
        {0,1,1,1,1,0,0,1},
        {0,1,1,1,1,1,0,1},
        {0,0,1,0,1,1,0,1},
        {1,1,1,1,1,1,1,0},
        {0,0,0,0,0,0,0,1}};
  auto An = powmat(N,A);
  vector<ll> v = {0,0,0,0,0,0,0,1};
  ll ans = 0LL;
  rep(i,7) rep(j,8){
    (ans += An.v[i][j] * v[j]) %= lmod;
  }
  cout << ans << endl;
  return 0;
}