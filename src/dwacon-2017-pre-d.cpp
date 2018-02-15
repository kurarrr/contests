// https://beta.atcoder.jp/contests/dwacon2017-prelims/submissions/2095170

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
using Pl = pair<ll,ll>;

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll lmod = 1e9+7,LINF=1LL<<60;
const int MAX_N = 100005;

priority_queue<int,vector<int>,greater<int>> que;
int X[MAX_N],Y[MAX_N],Z[MAX_N];

int main(){
  int N,M; cin >> N >> M;
  rep(i,N) scanf("%d%d",X+i,Y+i);
  int ans = 0;
  if(N<=M){
    rep(i,N) ans += X[i];
    cout << ans << endl;
    return 0;
  }
  rep(i,N) ans += Y[i];
  // if(M==1){
  //   int ma1 = -INF, temp1 = 0;
  //   rrep(i,N-1){
  //     ma1 = max(ma1,X[i]-Y[i]-temp1);
  //     temp1 += Y[i];
  //   }
  //   cout << ans + ma1 << endl;
  //   return 0;
  // }
  int temp = 0; fill(Z,Z+N,0);
  rep(i,M-1) que.push(X[i]-Y[i]), temp += X[i] - Y[i];
  // Z[i] := [0,i) から M-1個 とった時のmax(sum(X[j]-Y[j]))
  if(M>1){
    REP(i,M-1,N){
      Z[i] = temp;
      if(que.top()<X[i]-Y[i]){
        temp += X[i]-Y[i]-que.top();
        que.pop(); que.push(X[i]-Y[i]);
      }
    }
  }
  // rep(i,N) cout << Z[i] << " ";
  // cout << "" << endl;
  temp = 0; int ma = -INF;
  RREP(i,N-1,M-1){
    ma = max(ma,X[i]-Y[i]+Z[i]-temp);
    temp += Y[i];
  }
  cout << ans + ma << endl;
  return 0;
}
