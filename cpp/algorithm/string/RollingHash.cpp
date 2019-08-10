#include "../../template/template.cpp"
#include "../graph/topological_sort.cpp"

struct HashTuple {
  static const vector<long long> Mod;
  static const int base;
  vector<long long> val;
  HashTuple(): val(Mod.size()) {}
  HashTuple(signed x): val(Mod.size(), x) {}
  HashTuple &operator+=(HashTuple that) {
    for(int i = 0; i < Mod.size(); i++) if ((val[i] += that.val[i]) >= Mod[i]) val[i] -= Mod[i];
    return *this;
  }
  HashTuple &operator-=(HashTuple that) {
    for(int i = 0; i < Mod.size(); i++) if ((val[i] += Mod[i] - that.val[i]) >= Mod[i]) val[i] -= Mod[i];
    return *this;
  }
  HashTuple operator+(HashTuple that) const { return HashTuple(*this) += that; }
  HashTuple operator-(HashTuple that) const { return HashTuple(*this) -= that; }
  HashTuple &operator*=(signed that) {
    for(int i = 0; i < Mod.size(); i++)
      val[i] = (unsigned long long)val[i] * that % Mod[i];
    return *this;
  }
  HashTuple operator*(signed that) const { return HashTuple(*this) *= that; }
  HashTuple &operator*=(HashTuple that) {
    for(int i = 0; i < Mod.size(); i++)
      val[i] = (unsigned long long)val[i] * that.val[i] % Mod[i];
    return *this;
  }
  HashTuple operator*(HashTuple that) const { return HashTuple(*this) *= that; }
  bool operator==(HashTuple that) const { return val == that.val; }
  bool operator!=(HashTuple that) const { return val != that.val; }
};
const vector<long long> HashTuple::Mod = {999999937LL, 1000000007LL};
const int HashTuple::base = 9973;

template<typename Hash>
struct RollingHash {
  int N, tuple_size = Hash::Mod.size();
  static vector<Hash> pw;
  vector<Hash> hs;
  RollingHash(){}
  RollingHash(const string &s)
  : N(s.size()), hs(N+1) {
    assert(N <= pw.size());
    for (int j = 0; j < N; j++) {
      hs[j+1] = hs[j] * Hash::base + s[j];
    }
  }
  static void init(int MAX_N){
    pw.resize(MAX_N+1);
    pw[0] = Hash(1);
    for(int j = 0; j < MAX_N; j++)
      pw[j+1] = pw[j] * Hash::base;
  }
  Hash hash(int l, int r) {
    // i-th hash[l,r)
    assert(0 <= l && l <= r && r <= N);
    return hs[r] - hs[l] * pw[r-l];
  }
};
template<typename Hash> vector<Hash> RollingHash<Hash>::pw;

void abc_135_f(){
  string S,T;
  cin >> S >> T;
  ll N, M;
  N = S.size(); M = T.size();
  ll sz = 2 * max(M,N);
  string W(sz, ' ');
  rep(i,sz) W[i] = S[i%N];
  RollingHash<HashTuple>::init(sz);
  RollingHash<HashTuple> rh1(W), rh2(T);
  vvi g(N);
  auto h2 = rh2.hash(0,M);
  rep(i,N){
    auto h1 = rh1.hash(i,i+M);
    if(h1 == h2) g[i].pb((i+M)%N);
  }
  dump(g);
  auto ts = topological_sort(g);
  if(ts.size() != N){
    cout << -1 << endl;
    return;
  }
  vl dp(N);
  for(auto u:ts){
    for(auto v:g[u]) chmax(dp[v], dp[u]+1LL);
  }
  cout << *max_element(ALL(dp)) << endl;
}

int main(){
  abc_135_f();
  return 0;
}
