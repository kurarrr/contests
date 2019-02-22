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

using mint =  ModInt<int(1e9+7)>;
using vm = vector<mint>;

template<class T>
struct Kitamasa {
  public:
	//漸化式 an = zenka[0] * an-k+1 + zenka[1] * an-k+2 + zenka[2] * an-k+3 + ......zenka[k-1]*an-1
	Kitamasa(const vector<T>&zenka) :z_size(zenka.size()), terms(2 * z_size - 1, vector<T>(z_size)) {
		for (int i = 0; i < z_size; ++i) {
			vector<T>a(z_size, static_cast<T>(0));
			a[i] = static_cast<T>(1);
			terms[i] = (a);
		}
		if (all_of(zenka.begin(), zenka.end(), [](const T&t) {return t == static_cast<T>(1); })) {
			//(N^2)
			vector<T>plus(z_size, 1);
			for (int i = z_size; i < 2 * z_size - 1; ++i) {
				if (i != z_size) {
					for (int j = 0; j <z_size; ++j) {
						plus[j] += plus[j];
					}
					plus[i - z_size - 1] -= 1;
				}
				terms[i] = (plus);
			}

		}
		else {
			//(N^3)
			for (int i = z_size; i < 2 * z_size - 1; ++i) {
				for (int j = 0; j < z_size; ++j) {
					for (int k = 0; k < z_size; ++k) {
						terms[i][j] += zenka[k] * terms[i - z_size + k][j];
					}
				}
			}
		}
	}

	//第num項を求める
	//
	//
	//引数
	//fst_terms 初項
	//fst_terms={a0,a1,a2,.......ak-1}
	//num:求める項数
	T solve(const vector<T>&fst_terms, const long long int num) {
		assert(fst_terms.size() == z_size);
		vector<T>v(getterm(num));
		T ans(0);
		for (int i = 0; i < z_size; ++i) {
			ans += fst_terms[i] * v[i];
		}
		return ans;
	}

private:

	vector<T>getterm(const long long int num) {
		if (num < static_cast<long long int >(z_size * 2 - 1)) {
			return terms[static_cast<int >(num)];
		}
		if (num % 2) {
			return plusone(multitwo(getterm(num / 2)));
		}
		else {
			return multitwo(getterm(num / 2));
		}
	}

	vector<T>multitwo(const vector<T> f) {
		vector<T>ans(2 * z_size - 1);
		vector<T>to(z_size);
		for (int j = 0; j <z_size; ++j) {
			for (int k = 0; k < z_size; ++k) {
				ans[j + k] += f[j] * f[k];
			}
		}
		for (int j = 0; j < z_size * 2 - 1; ++j) {
			for (int k = 0; k < z_size; ++k) {
				to[k] += ans[j] * terms[j][k];
			}
		}
		return to;
	}


	vector<T>plusone(const vector<T> f) {
		vector<T>t(f.size());

		for (unsigned int i = 1; i < f.size(); ++i) {
			//t[1]=f[0]+f[k-1]*f[0]
			t[i] = f[i - 1] + f.back()*terms[z_size][i];
		}
		t[0] = f.back()*terms[z_size][0];
		return t;
	}
	const int z_size;
	vector<vector<T>> terms;
};

void _main(){
  // int N; cin >> N ;
  // int N,K; cin >> N >> K ;
  // int a,b; cin >> a >> b ;
  ll N,M; cin >> N >> M ;
  vector<mint> a(M),x(M,mint(1));
  a[0] = a[M-1] = mint(1);
  Kitamasa<mint> kt(a);
  cout << kt.solve(x,N) << endl;
}