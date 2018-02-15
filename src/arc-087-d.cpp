// https://beta.atcoder.jp/contests/arc070/submissions/1941602

#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<list>
#include<queue>
#include<deque>
#include<algorithm>
#include<utility>
#include<memory>
#include<cmath>
#include<stack>
#include<tuple>
#include<numeric>
#include<cassert>

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
using Pd = pair<double,double>;
using T = tuple<double,double,int>;

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll LINF=1LL<<60;
const int MAX_N = 8003;
const ll lmod = 1e9+7;

int cnt[2][MAX_N];
bool dp[4][MAX_N];

int main(){
  string S; int N,x,y,a;
  cin >> S >> x >> y ;
  N = S.length();
  S = S + "T";
  a = 0;
  while(S[a]=='F') a++;
  x -= a;
  fill(dp[0],dp[0]+MAX_N*4,false);
  int cnt = 0, flag = 0;
  dp[0][0] = dp[1][0] = dp[2][0] = dp[3][0] = true;
  int xprev = 0 ,xnow = 1 ,yprev = 2 ,ynow = 3;
  REP(i,a,N+1){
    if(S[i]=='F') cnt++;
    else{
      if(cnt!=0){
        int now,prev;
        if(!flag) prev = xprev, now = xnow, swap(xprev,xnow);
        else prev = yprev, now = ynow, swap(yprev,ynow);
        fill(dp[now],dp[now]+N,false);
        rep(i,N+1){
          if(i+cnt<MAX_N) dp[now][i+cnt] |= dp[prev][i];
          dp[now][abs(i-cnt)] |= dp[prev][i];
          // if(dp[now][i+cnt]) cout << "flag = " << flag << ", i+cnt = " << i+cnt << endl;
          // if(dp[now][abs(i-cnt)]) cout << "flag = " << flag << ", i-cnt = " << i-cnt << endl;
        }
      }
      cnt = 0;
      (flag += 1) %= 2;
    }
  }
  cout << (((dp[xprev][abs(x)] && dp[yprev][abs(y)])) ? "Yes" : "No") << endl;
  return 0;
}
