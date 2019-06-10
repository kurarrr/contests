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

class DynamicModInt {
  public:
  static int MOD;
  unsigned x; DynamicModInt() : x(0) { }
  DynamicModInt(signed sig) { x = sig < 0 ? sig % MOD + MOD : sig % MOD; }
  DynamicModInt(signed long long sig) { x = sig < 0 ? sig % MOD + MOD : sig % MOD; }
  int get() const { return (int)x; }
  DynamicModInt &operator+=(DynamicModInt that) { if ((x += that.x) >= MOD) x -= MOD; return *this; }
  DynamicModInt &operator-=(DynamicModInt that) { if ((x += MOD - that.x) >= MOD) x -= MOD; return *this; }
  DynamicModInt &operator*=(DynamicModInt that) { x = (unsigned long long)x * that.x % MOD; return *this; }
  DynamicModInt &operator/=(DynamicModInt that) { return *this *= that.inverse(); }
  DynamicModInt operator+(DynamicModInt that) const { return DynamicModInt(*this) += that; }
  DynamicModInt operator-(DynamicModInt that) const { return DynamicModInt(*this) -= that; }
  DynamicModInt operator*(DynamicModInt that) const { return DynamicModInt(*this) *= that; }
  DynamicModInt operator/(DynamicModInt that) const { return DynamicModInt(*this) /= that; }
  DynamicModInt inverse() const { long long a = x, b = MOD, u = 1, v = 0;
    while (b) { long long t = a / b; a -= t * b; std::swap(a, b); u -= t * v; std::swap(u, v); }
    return DynamicModInt(u); }
  bool operator==(DynamicModInt that) const { return x == that.x; }
  bool operator!=(DynamicModInt that) const { return x != that.x; }
  DynamicModInt operator-() const { DynamicModInt t; t.x = x == 0 ? 0 : MOD - x; return t; }
};
ostream& operator<<(ostream& st, const DynamicModInt a) { st << a.get(); return st; };
DynamicModInt operator^(DynamicModInt a, unsigned long long k) {
  DynamicModInt r = 1; while (k) { if (k & 1) r *= a; a *= a; k >>= 1; } return r; }
  // *より優先順位が高いため注意
int DynamicModInt::MOD;
void set_mod(signed mod){DynamicModInt::MOD = mod;}
using mint = DynamicModInt;

ll L,A,B;

ll ub(ll x){
  // uppber_bound
  ll left,right,middle;
  if(A>=x) return 0;
  left = 0;
  right = L;
  while(abs(left-right)>1){
    middle = (left+right)/2LL;
    ll y = A+B*middle;
    if(y>=x) right = middle;
    else left = middle;
  }
  return right;
}

mint g(mint ten,ll y){
  // ten^{y-1} + ten^{y-2} + .. + ten^{0}
  if(y==0) return mint(0);
  if(y%2==0){
    return (mint(1)+(ten^(y/2)))*g(ten,y/2);
  }
  return mint(1)+ten*g(ten,y-1);
}

mint f(mint ten,ll i,ll y){
  // ten^{y-1} * i + ten^{y-2} * (i+1) + .. + ten^{0} * (i+y-1)
  if(y==1){
    return mint(i);
  }
  mint res(0);
  if(y%2==0){
    res = (f(ten,i,y/2)*((ten^(y/2))+mint(1))+g(ten,y/2)*mint(y/2));
    dump(ten,i,y,res);
    return res;
  }
  res += ten * f(ten,i,y-1) + mint(i)+mint(y)-mint(1);
  dump(ten,i,y,res);
  return res;
}

void solve(){
  mint x = 0;
  mint nxt;
  rep(k,18){
    ll temp = 1; // 10^k
    rep(j,k) temp *= 10LL;
    ll i = ub(temp);
    if(i==L) break;
    temp *= 10LL;
    ll i2 = ub(temp);
    ll y = i2-i;
    if(y==0) continue;
    mint ten(temp);
    nxt = 0;
    nxt += (ten^y) * x;
    nxt += g(ten,y) * mint(A);
    nxt += f(ten,i,y) * mint(B);
    x = nxt;
    dump(i,y,x);
  }
  cout << nxt << endl;
}


int main(){
  ll M;
  scanf("%lld",&L);
  scanf("%lld",&A);
  scanf("%lld",&B);
  scanf("%lld",&M);
  set_mod(M);
  solve();
  return 0;
}
