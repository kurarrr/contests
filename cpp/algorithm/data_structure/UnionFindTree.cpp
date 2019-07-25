#include "../../template/template.cpp"

struct UnionFindTree{
  vector<int> par, rank, size;
  UnionFindTree(int N)
  : par(vector<int>(N,0)), rank(vector<int>(N,0)), size(vector<int>(N,1LL))
  {
    iota(par.begin(), par.end(), 0);
  }
  int find(int x){
    if(par[x] == x) return x;
    else return par[x] = find(par[x]);
  }
  void unite(int x,int y){
    x = find(x);
    y = find(y);
    if(x == y)  return ;
    if(rank[x] < rank[y]){
      par[x] = y;
    }else{
      par[y] = x;
      if(rank[x] == rank[y]) ++rank[x];
    }
    size[x] = size[y] = size[x] + size[y];
  }
  bool same(int x,int y){
    return find(x) == find(y);
  }
};

void atc001_b(){
  ll N, Q;
  cin >> N >> Q ;
  UnionFindTree uft(N);
  rep(i,Q){
    int p,a,b; cin >> p >> a >> b ;
    if(p) cout << (uft.same(a,b) ? "Yes" : "No") << endl;
    else uft.unite(a,b);
  }
}

void solve(){
  atc001_b();
}