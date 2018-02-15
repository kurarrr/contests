// https://beta.atcoder.jp/contests/arc074/submissions/2014546
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

ll a[3*MAX_N],dp1[MAX_N],dp2[MAX_N];
priority_queue<ll> max_que;
priority_queue<ll,vector<ll>,greater<ll>> min_que;

int main(){
  int N; cin >> N;
  rep(i,3*N) scanf("%lld",a+i);
  ll temp = 0LL;
  rep(i,N){
    temp += a[i];
    min_que.push(a[i]);
  }
  dp1[0] = temp;
  rep(i,N){
    ll m = min_que.top();
    if(a[N+i]>m){
      dp1[i+1] = dp1[i] + a[N+i] - m;
      min_que.pop();
      min_que.push(a[N+i]);
    }else{
      dp1[i+1] = dp1[i];
    }
  }
  temp = 0LL;
  RREP(i,3*N-1,2*N){
    temp += a[i];
    max_que.push(a[i]);
  }
  dp2[0] = temp;
  rep(i,N){
    ll m = max_que.top();
    if(a[2*N-i-1]<m){
      dp2[i+1] = dp2[i] + a[2*N-i-1] - m;
      max_que.pop();
      max_que.push(a[2*N-i-1]);
    }else{
      dp2[i+1] = dp2[i];
    }
  }
  ll ans = -LINF;
  rep(i,N+1){
    ans = max(ans,dp1[i]-dp2[N-i]);
  }
  cout << ans << endl;
  return 0;
}
