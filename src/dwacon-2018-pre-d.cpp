// https://beta.atcoder.jp/contests/dwacon2018-prelims/submissions/1971142
#include "bits/stdc++.h"

#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define EXIST(s,e) ((s).find(e)!=(s).end())
#define pb push_back
#define DEBUG false

using namespace std;

using ll = long long;
using P = pair<int,int>;
using Pl = pair<int,ll>;

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll LINF=1LL<<60;
const int MAX_N = 21;
const ll lmod = 1e9+7;

ll x[MAX_N],sumx[1<<21],memo[1<<21];
vector<int> graph[MAX_N];
int N;

ll solve(int state){
  if(memo[state]>=0LL) return memo[state];
  ll res = LINF;
  rep(i,N){
    // 立っているbitを選んで子を立たせる
    if(((1<<i)&state)==0) continue;
    int next = state;
    for(auto u:graph[i]) next |= (1<<u);
    // cout << "next = " << next << endl;
    res = min(res,max(sumx[next],solve(next^(1<<i))));
  }
  // cout << "res = " << res << endl;
  return memo[state] = res;
}

int main(){
  cin >> N ;
  rep(i,N) cin >> x[i] ;
  rep(i,N-1){
    int a; cin >> a ;
    graph[a-1].pb(i+1);
  }
  fill(memo,memo+(1<<N),-1LL);
  memo[0] = 0LL;
  rep(i,1<<N){
    rep(j,N) if((i&(1<<j))!=0) sumx[i] += x[j];
  }
  cout << solve(1) << endl;
  return 0;
}
