// https://beta.atcoder.jp/contests/arc090/submissions/2030891
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
using Pl = pair<int,ll>;

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll LINF=1LL<<60, lmod = 1e9+7;
const int MAX_N = 100005;

vector<Pl> graph[MAX_N];
ll d[MAX_N];

int main(){
  int N,M; scanf("%d%d",&N,&M);
  rep(i,M){
    int l,r; ll dd; scanf("%d%d%lld",&l,&r,&dd);
    l--; r--; graph[l].pb(Pl(r,dd)); graph[r].pb(Pl(l,-dd));
  }
  fill(d,d+N,-LINF);
  queue<int> que;
  rep(i,N){
    if(d[i]!=-LINF) continue;
    d[i] = 0LL; que.push(i);
    while(!que.empty()){
      int u = que.front(); que.pop();
      for(Pl pl: graph[u]){
        int v; ll di;
        tie(v,di) = pl;
        if(d[v]!=-LINF){
          if(d[v]!=d[u]+di){
            cout << "No" << endl;
            return 0;
          } 
        }else{
          d[v] = d[u] + di;
          que.push(v);
        }
      }
    }
  }
  cout << "Yes" << endl;
  return 0;
}
