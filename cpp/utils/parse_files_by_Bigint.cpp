#include "../template/template.cpp"
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>

const long long MOD = 1000000007;

void solve(){
  namespace mult_prec = boost::multiprecision;
  using Bigint = mult_prec::cpp_int;
  int k;
  string s = "{";
  Bigint mo = Bigint(MOD);
  ll cnt = 0;
  dump(cnt);
  int lines = 50;
  auto f = [&](int x){
    return (x+1)*(x+1)/4 + 1;
  };
  // parse 2-D arrays
  //  index value
  //  ...
  // f(index(from 0)) = (size of a[i])
  REP(i,0,lines){
    k = f(i);
    s += "{";
    rep(j,k){
      Bigint a,b;
      cin >> a >> b ;
      b %= mo;
      s += b.str();
      s += (j==k-1? "}":",");
    }
    s+=(i==lines-1 ? "" : ",");
  }
  s += "}";
  cout << s << endl;
}
