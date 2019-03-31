#include "../../template/template.cpp"

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
  // *より優先順位が高いため注意
template<typename T, int FAC_MAX> struct Comb { vector<T> fac, ifac;
  Comb(){fac.resize(FAC_MAX,1);ifac.resize(FAC_MAX,1); for(int i = 1; i < FAC_MAX; i++)fac[i]=fac[i-1]*i;
    ifac[FAC_MAX-1]=T(1)/fac[FAC_MAX-1];for(int i = FAC_MAX-2; i >= 1; i--)ifac[i]=ifac[i+1]*T(i+1);}
  T aPb(int a, int b) { if (b < 0 || a < b) return T(0); return fac[a] * ifac[a - b]; }
  T aCb(int a, int b) { if (b < 0 || a < b) return T(0); return fac[a] * ifac[a - b] * ifac[b]; }
  T nHk(int n, int k) { if (n == 0 && k == 0) return T(1); if (n <= 0 || k < 0) return 0;
    return aCb(n + k - 1, k); }}; // nHk = (n+k-1)Ck : n is separator

using mint =  ModInt<int(1e9+7)>;
using vm = vector<mint>;

map<ll, ll> enumpr(ll n) {
  map<ll, ll> V;
  for (ll i = 2; 1LL * i*i <= n; i++) while (n%i == 0) V[i]++, n /= i;
  if (n>1) V[n]++;
  return V;
}

Comb<mint, int(2e5)> com;

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);
  ll N,M; cin >> N >> M ;
  auto ep = enumpr(M);
  mint ans = 1;
  for(auto p : ep) ans *= com.nHk(N, p.second);
  cout << ans << endl;
  return 0;
}
