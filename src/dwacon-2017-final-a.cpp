// https://beta.atcoder.jp/contests/dwacon2017-honsen/submissions/1996438

#include "bits/stdc++.h"

#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define RREP(i, x, n) for(int i = x; i >= n; i--)
#define rrep(i, n) RREP(i,0,n)
#define EXIST(s,e) ((s).find(e)!=(s).end())
#define pb push_back

using namespace std;

using ll = long long;
using P = pair<int,int>;

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll LINF=1LL<<60, lmod = 1e9+7;

const int MAX_N = 55;

P dp[MAX_N][MAX_N][MAX_N];
string s;

P solve(int l, int r, int k){
  // cout << l << "," << r << endl;
  if(dp[l][r][k].first!=INF) return dp[l][r][k];
  if(l==r){
    if(k!=0) return dp[l][r][k] = P(9,0);
    else if(s[l]=='+'|s[l]=='-') return dp[l][r][k] = P(-INF,-INF);
    else{
      int res = int(s[l]-'0');
      return dp[l][r][k] = P(res,res);
    }
  }
  int _max = -INF, _min = INF;
  P p1,p2;
  if(s[r]=='+'){
    REP(i,l,r-1){
      REP(j,0,k+1){
        p1 = solve(l,i,j); p2 = solve(i+1,r-1,k-j);
        if(p1.first==-INF||p2.first==-INF) continue;
        _max = max(_max,p1.first+p2.first);
        _min = min(_min,p1.second+p2.second);
      }
    }
  }else if(s[r]=='-'){
    REP(i,l,r-1){
      REP(j,0,k+1){
        p1 = solve(l,i,j); p2 = solve(i+1,r-1,k-j);
        if(p1.first==-INF||p2.first==-INF) continue;
        _max = max(_max,p1.first-p2.second);
        _min = min(_min,p1.second-p2.first);
      }
    }
  }
  if(k!=0){
    REP(i,l,r-1){
      REP(j,0,k){
        p1 = solve(l,i,j); p2 = solve(i+1,r-1,k-j-1);
        if(p1.first==-INF||p2.first==-INF) continue;
        _max = max(_max,p1.first+p2.first);
        _max = max(_max,p1.first-p2.second);
        _min = min(_min,p1.second-p2.first);
        _min = min(_min,p1.second+p2.second);
      }
    }
  }
  return dp[l][r][k] = P(_max,_min);
}

int main(){
  int K;
  cin >> K >> s;
  rep(i,MAX_N) rep(j,MAX_N) rep(k,MAX_N) dp[i][j][k] = P(INF,INF);
  P ans = solve(0,s.size()-1,K);
  if(ans.first==-INF) cout << "NG" << endl;
  else{
    cout << "OK" << endl;
    cout << ans.first << endl;
  }
  return 0;
}
