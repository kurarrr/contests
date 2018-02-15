// https://beta.atcoder.jp/contests/soundhound2018/submissions/2076515

#include "bits/stdc++.h"

#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define RREP(i, x, n) for(int i = x; i >= n; i--)
#define rrep(i, n) RREP(i,n,0)
#define pb push_back

using namespace std;

using ll = long long;
using P = pair<int,int>;
using Pl = pair<ll,int>;

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll lmod = 1e9+7,LINF=1LL<<60;
const int MAX_N = 41;

vector<int> graph[44*44];
string s[44];
int dd[2] = {-1,1};

class BipartiteMatching {
  int size;
  vector<vector<int>> g;
  vector<int> match;
  vector<bool> used;
  bool dfs(int v) {
    used[v] = true;
    for (int u: g[v]) {
      int w = match[u];
      if (w < 0 || (!used[w] && dfs(w))) {
        match[v] = u;
        match[u] = v;
        return true;
      }
    }
    return false;
  }
public:
  BipartiteMatching(int v) : size(v), g(v), match(v), used(v) {}
  void add_edge(int u, int v) {
    g[u].push_back(v);
    // g[v].push_back(u);
  }
  int maximum_matching(void) {
    int res = 0;
    fill(begin(match), end(match), -1);
    for (int v = 0; v < size; ++v) {
      if (match[v] >= 0) continue;
      fill(begin(used), end(used), 0);
      if (dfs(v)) ++res;
    }
    return res;
  }
};

int main(){
  int r,c; cin >> r >> c;
  rep(i,r) cin >> s[i+1];
  s[0] = string('*',c+1);
  s[r+1] = string('*',c+1);
  rep(i,r) s[i+1] = "*" + s[i+1] + "*";
  map<int,int> node; int cnt = 0;
  REP(i,1,r+1) REP(j,1,c+1) if(s[i][j]=='.') node[i*44+j] = cnt++;
  BipartiteMatching bp(cnt);
  REP(i,1,r+1) REP(j,1,c+1){
    if(s[i][j]=='.'){
      rep(k,2)
        if(s[i][j+dd[k]]=='.') bp.add_edge(node[i*44+j],node[i*44+j+dd[k]]);
      rep(k,2)
        if(s[i+dd[k]][j]=='.') bp.add_edge(node[i*44+j],node[(i+dd[k])*44+j]);
    }
  }

  cout << cnt - bp.maximum_matching() << endl;
  return 0;
}
