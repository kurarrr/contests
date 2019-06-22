// https://atcoder.jp/contests/joi2011ho/submissions/5996252
#include "../../template/template.cpp"

template <typename T> class FenwickTree2D {
  const int N,M;
  std::vector<vector<T>> data;
public:
  // 0-indexed
  FenwickTree2D(){ ; }
  FenwickTree2D(int N, int M) : N(N), M(M), data(N, vector<T>(M)) { ; }
  // add value to (n, m)
  // @complexity $O(\\log^2(n))$
  void add(int n, int m, const T &value) {
    assert(0 <= n && n < N);
    assert(0 <= m && m < M);
    for (int i = n; i < N; i |= i + 1){
      for (int j = m; j < M; j |= j + 1){
        data[i][j] += value;
      }
    }
  }
  // sum_{i \in [0,n), j \in [0,m)}
  // @complexity $O(\\log^2(n))$
  T sum(int n, int m) const {
    assert(0 <= n && n <= N);
    assert(0 <= m && m <= M);
    T res = 0;
    for (int i = n - 1; i >= 0; i = (i & (i + 1)) - 1) {
      for (int j = m - 1; j >= 0; j = (j & (j + 1)) - 1) {
        res += data[i][j];
      }
    }
    return res;
  }
  // sum_{i \in [n1,n2), j \in [m1,m2)}
  // @complexity $O(\\log^2(n))$
  T sum(int n1, int m1, int n2, int m2) const {
    assert(0 <= n1 && n1 <= n2 && n2 <= N);
    assert(0 <= m1 && m1 <= m2 && m2 <= M);
    return sum(n2,m2) - sum(n1,m2) - sum(n2,m1) + sum(n1,m1);
  }
  using value_type = T;
  using update_type = T;
};


int main(){
  int N,M;
  cin >> M >> N ;
  FenwickTree2D<ll> J(M+1,N+1),O(M+1,N+1),I(M+1,N+1);
  int K;
  cin >> K ;
  rep(i,M){
    string s;
    cin >> s ;
    rep(j,N){
      if(s[j]=='J') J.add(i,j,1LL); 
      if(s[j]=='O') O.add(i,j,1LL); 
      if(s[j]=='I') I.add(i,j,1LL); 
    }
  }
  rep(i,K){
    int a,b,c,d;
    cin >> a >> b >> c >> d ;
    a--; b--; c--; d--;
    cout << J.sum(a,b,c+1,d+1) << " " << O.sum(a,b,c+1,d+1) 
        << " " << I.sum(a,b,c+1,d+1) << endl;
  }
  return 0;
}
