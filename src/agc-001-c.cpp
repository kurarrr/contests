// https://beta.atcoder.jp/contests/agc001/submissions/2067996
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
const int MAX_N = 2003;

vector<int> graph[MAX_N];
bool passed[MAX_N];

int main(){
  int N,K; cin >> N >> K;
  rep(i,N-1){
    int a,b;
    scanf("%d%d",&a,&b);
    a--; b--;
    graph[a].pb(b); graph[b].pb(a);
  }
  if(K==1){
    cout << N-2 << endl;
    return 0;
  }else if(K%2==0){
    int ans = INF;
    rep(i,N){
      // i からの距離が全てK/2以下
      queue<P> que;
      fill(passed,passed+N,false);
      que.push(P(i,0));
      int rest = 0;
      while(!que.empty()){
        int u,d;
        tie(u,d) = que.front(); que.pop();
        if(d>K/2) continue;
        passed[u] = true;
        rest++;
        for(auto v:graph[u]) if(!passed[v]) que.push(P(v,d+1));
      }
      ans = min(ans,N-rest);
    }
    cout << ans << endl;
  }else{
    int ans = INF;
    rep(i,N) for(auto j:graph[i]){
      // 辺 i - j からの距離が全て(K-1)/2以下
      queue<P> que;
      fill(passed,passed+N,false);
      que.push(P(i,0)); que.push(P(j,0));
      int rest = 0;
      while(!que.empty()){
        int u,d;
        tie(u,d) = que.front(); que.pop();
        if(d>(K-1)/2) continue;
        passed[u] = true;
        rest++;
        for(auto v:graph[u]) if(!passed[v]&&v!=i&&v!=j) que.push(P(v,d+1));
      }
      ans = min(ans,N-rest);
    }
    cout << ans << endl;
  }
  return 0;
}
