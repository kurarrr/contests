#include "../../template/template.cpp"
#include "../graph/topological_sort.cpp"

class RollingHash
{
  using ull = unsigned long long;
  ll N;
  const ull MASK30 = (1UL << 30) - 1;
  const ull MASK31 = (1UL << 31) - 1;
  const ull MOD = (1UL << 61) - 1;
  const ull POSITIVIZER = MOD * ((1UL << 3) - 1);
  static ull Base;
  static vector<ll> powMemo;
  vector<ull> dat;
public:
  void init(){
    while(Base <= 129) Base = engine();
    if(powMemo.size() < N) {
      ll from = powMemo.size();
      powMemo.resize(N);
      powMemo[0] = 1;
      for (int i = from; i < N; i++) if(i != 0)
        powMemo[i] = CalcMod(Mul(powMemo[i - 1], Base));
    }
  }
  RollingHash(){}
  RollingHash(string s): N(s.size()), dat(s.size()+1)
  {
    init();
    for (int i = 0; i < N; i++)
      dat[i + 1] = CalcMod(Mul(dat[i], Base) + s[i]);
  }

  ull hash(int l, int r)
  {
    return CalcMod(dat[r] + POSITIVIZER - Mul(dat[l], powMemo[r-l]));
  }

  bool match(int l1, int r1, int l2, int r2){
    return hash(l1, r1) == hash(l2, r2);
  }

  ull Mul(ull l, ull r)
  {
    long long lu = l >> 31;
    long long ld = l & MASK31;
    long long ru = r >> 31;
    long long rd = r & MASK31;
    long long middleBit = ld * ru + lu * rd;
    return ((lu * ru) << 1) + ld * rd + ((middleBit & MASK30) << 31) + (middleBit >> 30);
  }

  ull CalcMod(ull val)
  {
    val = (val & MOD) + (val >> 61);
    if (val > MOD) val -= MOD;
    return val;
  }
};
std::mt19937 engine(chrono::steady_clock::now().time_since_epoch().count());
unsigned long long RollingHash::Base = engine();
vector<long long> RollingHash::powMemo = {};

void abc_135_f(){
  // https://atcoder.jp/contests/abc135/submissions/9146451
  string S,T;
  cin >> S >> T;
  ll N, M;
  N = S.size(); M = T.size();
  ll sz = 2 * max(M,N);
  string W(sz, ' ');
  rep(i,sz) W[i] = S[i%N];
  RollingHash rh1(W), rh2(T);
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
