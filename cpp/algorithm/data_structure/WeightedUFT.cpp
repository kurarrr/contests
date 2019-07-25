#include "../../template/template.cpp"

struct WeightedUFT{
  vector<int> par, rank, size;
  vector<long long> diff_weight;
  WeightedUFT(int N)
  : par(vector<int>(N,0)), rank(vector<int>(N,0)),
    diff_weight(vector<long long>(N, 0LL))
  {
    iota(par.begin(), par.end(), 0);
  }
  long long weight(int x){
    // weight(x) - weight(find(x))
    // note: weight(find(x)) == 0 after propagation
    find(x);
    return diff_weight[x];
  }
  long long diff(int x, int y){
    return weight(x) - weight(y);
  }
  int find(int x){
    if(par[x] == x) return x;
    int r = find(par[x]);
    diff_weight[x] += diff_weight[par[x]];
    return par[x] = r;
  }
  bool unite(int x, int y, long long w){
    // unite x and y
    // s.t. weight(x) - weight(y) = w
    w += weight(y) - weight(x);
    // This w satisfies
    //     weight(find(x)) - weight(find(y)) = w
    x = find(x);
    y = find(y);
    dump(x,y,w);
    if(x == y){
      if(w == 0LL) return true;
      else return false; // contradiction
    }
    if(rank[x] > rank[y]) swap(x, y), w = -w;
    if(rank[x] == rank[y]) ++rank[y];
    par[x] = y;
    diff_weight[x] = w;
    return true;
  }
  bool same(int x,int y){
    return find(x) == find(y);
  }
};

void abc087_d(){
  int N, M; cin >> N >> M ;
  WeightedUFT uft(N);
  bool res = true;
  rep(i,M){
    ll l, r, d;
    cin >> l >> r >> d ;
    l--; r--;
    res &= uft.unite(l,r,d);
    if(!res){
      cout << "No" << endl;
      return;
    }
  }
  cout << "Yes" << endl;
}

void solve(){
  abc087_d();
}