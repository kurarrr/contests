#include "bits/stdc++.h"

#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define RREP(i, x, n) for(int i = x; i >= n; i--)
#define rrep(i, n) RREP(i,n,0)
#define pb push_back
#pragma GCC optimize ("-O3")

using namespace std;

#define DEBUG_IS_VALID 

#ifdef DEBUG_IS_VALID
#define DEB 1 
#else
#define DEB 0
#endif
#define DUMPOUT cout
#define dump(...) if(DEB) DUMPOUT<<"  "<<#__VA_ARGS__<<" :["<<__LINE__<<":"<<__FUNCTION__<<"]"<<endl<<"    "; if(DEB) dump_func(__VA_ARGS__)
template<typename T1,typename T2>ostream& operator << (ostream& os, pair<T1,T2> p){cout << "(" << p.first << ", " << p.second << ")"; return os;}
template<typename T>ostream& operator << (ostream& os, vector<T>& vec) { os << "{"; for (int i = 0; i<vec.size(); i++) os << vec[i] << (i + 1 == vec.size() ? "" : ", "); os << "}"; return os; }
template<typename T>ostream& operator << (ostream& os, set<T>& st){cout << "{"; for(auto itr = st.begin(); itr != st.end(); itr++) cout << *itr << (next(itr)!=st.end() ? ", " : ""); cout << "}"; return os;}
template<typename T1,typename T2>ostream& operator << (ostream& os, map<T1,T2> mp){cout << "{"; for(auto itr = mp.begin(); itr != mp.end(); itr++) cout << "(" << (itr->first) << ", " << (itr->second) << ")" << (next(itr)!=mp.end() ? "," : ""); cout << "}"; return os; }

void dump_func(){DUMPOUT << endl;}
template <class Head, class... Tail>void dump_func(Head&& head, Tail&&... tail){ DUMPOUT << head; if (sizeof...(Tail) == 0) { DUMPOUT << " "; } else { DUMPOUT << ", "; } dump_func(std::move(tail)...);}
template<class T> inline bool chmax(T& a,T const& b){if(a>=b) return false; a=b; return true;}
template<class T> inline bool chmin(T& a,T const& b){if(a<=b) return false; a=b; return true;}
void _main();
int main(){ cin.tie(0); ios::sync_with_stdio(false); _main(); return 0;}

using ll = long long;
using P = pair<int,int>;
using Pl = pair<ll,ll>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;

const int mod=1e9+7,INF=1<<29;
const double EPS=1e-5,PI=3.1415926535897932384626;
const ll lmod = 1e9+7,LINF=1LL<<59; 

template <int MOD>
struct Matrix {
  static const ll mo = MOD, mo2 = ll(MOD) * MOD * 4LL;
  vector<vector<long long>> dat;
  Matrix(signed N):dat(N,vector<long long>(N)){};
  Matrix(const vector<vector<long long>>& dat):dat(dat){};
};
template <int MOD>
Matrix<MOD> operator*(Matrix<MOD>& a,Matrix<MOD>& b) {
  int N = a.dat.size();
	int x,y,z; Matrix<MOD> res(N);
	rep(x,N) rep(z,N) rep(y,N) {
		res.dat[x][y] += a.dat[x][z] * b.dat[z][y];
    if(res.dat[x][y] > Matrix<MOD>::mo2) res.dat[x][y] -= Matrix<MOD>::mo2;
	}
  rep(x,N) rep(y,N) res.dat[x][y] %= MOD;
	return res;
}
template<int MOD>
Matrix<MOD> operator^(Matrix<MOD> a, signed long long k) {
  assert(k>=0);
  int N = a.dat.size();
  Matrix<MOD> res(N);
  for(int i = 0; i < N; i++) res.dat[i][i] = 1;
  while (k) {
    if (k & 1) res = a * res;
    a = a * a;
    k >>= 1;
  }
  return res;
}

using Mat = Matrix<int(1e9+7)>;
