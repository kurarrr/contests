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

int main(){
  int r,c; cin >> r >> c;
  rep(i,r) cin >> s[i+1];
  s[0] = string('*',c+1);
  s[r+1] = string('*',c+1);
  rep(i,r) s[i+1] = "*" + s[i+1] + "*";
  vector<int> node;
  REP(i,1,r+1) REP(j,1,c+1){
    if(s[i][j]=='.'){
      node.pb(i*44+j);
      rep(k,2)
        if(s[i][j+dd[k]]=='.') graph[i*44+j].pb(i*44+j+dd[k]);
      rep(k,2)
        if(s[i+dd[k]][j]=='.') graph[i*44+j].pb((i+dd[k])*44+j);
    }
  }
  int ans = 0,color[44*44],red,white;
  fill(color,color+44*44,0);
  function<void(int,int)> dfs = [&](int u,int c){
    color[u] = c;
    if(c==1) red++;
    else white++;
    for(auto v:graph[u]) if(color[v]==0) dfs(v,(c==1 ? 2 : 1));
  };
  for(auto u:node){
    if(color[u]!=0) continue;
    red = white = 0;
    dfs(u,1);
    ans += max(red,white);
  }
  cout << ans << endl;
  return 0;
}
