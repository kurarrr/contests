// https://beta.atcoder.jp/contests/agc020/submissions/1982083
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
const int MAX_N = 2003;
const ll lmod = 1e9+7;

bitset<MAX_N * MAX_N> dp;
int a[MAX_N];

int main(){
  int N; cin >> N ;
  rep(i,N) scanf("%d",a+i);
  int _sum = 0;
  rep(i,N) _sum += a[i];
  dp[0] = 1; 
  rep(i,N) dp |= (dp << a[i]);
  REP(i,(_sum+1)/2,_sum+1){
    if(dp[i]){
      cout << i << endl;
      return 0;
    }
  }
  return 0;
}
