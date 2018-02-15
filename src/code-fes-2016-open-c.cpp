// https://beta.atcoder.jp/contests/cf16-exhibition-final-open/submissions/2013543
#include "bits/stdc++.h"

#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define RREP(i, x, n) for(int i = x; i >= n; i--)
#define rrep(i, n) RREP(i,n,0)
#define EXIST(s,e) ((s).find(e)!=(s).end())
#define pb push_back

using namespace std;

using ll = long long;
using P = pair<int,int>;

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll LINF=1LL<<60, lmod = 1e9+7;

const int MAX_N = 100005;

int a[MAX_N],b[32];

int main(){
  int N; cin >> N;
  rep(i,N) scanf("%d",a+i);
  sort(a,a+N);
  int ans = 0,bit = 0;
  fill(b,b+32,0);
  rep(i,N){
    bit ^= a[i];
    rep(j,32){
      if((a[i]&(1<<j))!=0){
        b[j]++; break;
      }
    }
  }
  rrep(j,31){
    if((bit&(1<<j))==0) continue;
    if(b[j]!=0) ans++;
    else{
      cout << "-1" << endl;
      return 0;
    }
    bit ^= ((1<<j)-1);
  }
  cout << ans << endl;
  return 0;
}
