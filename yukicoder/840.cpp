#ifdef DEBUG_IS_VALID
#define DEB 1 
#define _LIBCPP_DEBUG 0
#else
#define DEB 0
#define NDEBUG
#endif

#include <bits/stdc++.h>
using namespace std;

#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define RREP(i, x, n) for(int i = x; i >= n; i--)
#define rrep(i, n) RREP(i,n,0)
#define pb push_back
#define fi first
#define se second
#pragma GCC optimize ("-O3")

using namespace std;

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
void solve();
int main(void) {
  std::cout << std::fixed << std::setprecision(15);
  solve();
	return 0;
}

using ll = long long;
using P = pair<int,int>;
using Pl = pair<ll,ll>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;
using vp = vector<Pl>;
using vvp = vector<vp>;

const int INF = 1<<29;
const long long LINF=1LL<<59;

template<int MOD> struct ModInt {
  static const int Mod = MOD; unsigned x; ModInt() : x(0) { }
  ModInt(signed sig) { x = sig < 0 ? sig % MOD + MOD : sig % MOD; }
  ModInt(signed long long sig) { x = sig < 0 ? sig % MOD + MOD : sig % MOD; }
  int get() const { return (int)x; }
  ModInt &operator+=(ModInt that) { if ((x += that.x) >= MOD) x -= MOD; return *this; }
  ModInt &operator-=(ModInt that) { if ((x += MOD - that.x) >= MOD) x -= MOD; return *this; }
  ModInt &operator*=(ModInt that) { x = (unsigned long long)x * that.x % MOD; return *this; }
  ModInt &operator/=(ModInt that) { return *this *= that.inverse(); }
  ModInt operator+(ModInt that) const { return ModInt(*this) += that; }
  ModInt operator-(ModInt that) const { return ModInt(*this) -= that; }
  ModInt operator*(ModInt that) const { return ModInt(*this) *= that; }
  ModInt operator/(ModInt that) const { return ModInt(*this) /= that; }
  ModInt inverse() const { long long a = x, b = MOD, u = 1, v = 0;
    while (b) { long long t = a / b; a -= t * b; std::swap(a, b); u -= t * v; std::swap(u, v); }
    return ModInt(u); }
  bool operator==(ModInt that) const { return x == that.x; }
  bool operator!=(ModInt that) const { return x != that.x; }
  ModInt operator-() const { ModInt t; t.x = x == 0 ? 0 : Mod - x; return t; }
};
template<int MOD> ostream& operator<<(ostream& st, const ModInt<MOD> a) { st << a.get(); return st; };
template<int MOD> ModInt<MOD> operator^(ModInt<MOD> a, unsigned long long k) {
  ModInt<MOD> r = 1; while (k) { if (k & 1) r *= a; a *= a; k >>= 1; } return r; }
template<typename T, int FAC_MAX> struct Comb { vector<T> fac, ifac;
  Comb(){fac.resize(FAC_MAX,1);ifac.resize(FAC_MAX,1); for(int i = 1; i < FAC_MAX; i++)fac[i]=fac[i-1]*i;
    ifac[FAC_MAX-1]=T(1)/fac[FAC_MAX-1];for(int i = FAC_MAX-2; i >= 1; i--)ifac[i]=ifac[i+1]*T(i+1);}
  T aPb(int a, int b) { if (b < 0 || a < b) return T(0); return fac[a] * ifac[a - b]; }
  T aCb(int a, int b) { if (b < 0 || a < b) return T(0); return fac[a] * ifac[a - b] * ifac[b]; }
  T nHk(int n, int k) { if (n == 0 && k == 0) return T(1); if (n <= 0 || k < 0) return 0;
    return aCb(n + k - 1, k); }}; // nHk = (n+k-1)Ck : n is separator

using mint =  ModInt<998244353>;
using vm = vector<mint>;

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

using Mat = Matrix<998244353>;

void solve(){
  ll N, K; cin >> N >> K ;
  Mat mat(K*K*K);
  auto enc = [&](int j, int k, int l){ return K*K*j+K*k+l;};
  auto dec = [&](int d){ vl res = {d/(K*K),(d%(K*K))/K, d%K}; return res; };
  rep(j,K) rep(k,K) rep(l,K){
    auto e = enc(j,k,l);
    mat.dat[enc((j+1)%K,k,l)][e]++; // (j,k,l) -> (j+1,k,l)
    mat.dat[enc(j,(j+k)%K,l)][e]++; //         -> (j,j+k,l)
    mat.dat[enc(j,k,(k+l)%K)][e]++; //         -> (j,k,k+l)
  }
  auto matn = mat^N;
  ll ans = 0;
  rep(j,K) rep(k,K) (ans += matn.dat[enc(j,k,0)][0]) %= Mat::mo;
  cout << ans << endl;
}