// https://beta.atcoder.jp/contests/arc069/submissions/1964041
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
const int MAX_N = 100005;
const ll lmod = 1e9+7;

int next(int pre,int now,const char &c){
  int res;
  if(!now){
    // now -> 'S'
    if(c=='o') res = pre;
    else res = pre^1;
  }else{
    // now -> 'W'
    if(c=='o') res = pre^1;
    else res = pre;
  }
  return res;
}

int main(){
  int N; string S;
  cin >> N >> S;
  map<int,string> mp;
  mp[0] = "S"; mp[1] = "W";
  rep(i,2) rep(j,2){
    int pre,now;
    pre = i; now = j;
    string ans = mp[i] + mp[j];
    rep(k,N-1){
      pre = next(pre,now,S[k+1]);
      if(k!=N-2) ans += mp[pre];
      swap(now,pre);
    }
    if(now==i&&next(j,i,S[0])==pre){
      cout << ans << endl;
      return 0;
    }
  }
  cout << "-1" << endl;
  return 0;
}
