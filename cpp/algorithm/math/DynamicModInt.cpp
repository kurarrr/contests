#include "bits/stdc++.h"
#include "../../template/template.cpp"

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
    return res;
  }
  res += ten * f(ten,i,y-1) + mint(i)+mint(y)-mint(1);
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
