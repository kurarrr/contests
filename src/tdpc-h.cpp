// https://beta.atcoder.jp/contests/tdpc/submissions/2115154
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
using vi = vector<int>;
using vvi = vector<vi>;

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll lmod = 1e9+7,LINF=1LL<<60;
const int MAX_N = 102 ,MAX_W = 10004;

void chmax(int &a,int b){
  a = max(a,b);
}

int main(){
  int N,W,C,cnt_c; cin >> N >> W >> C;
  vvi weight(50),value(50);
  rep(i,N){
    int w,v,c;
    scanf("%d%d%d",&w,&v,&c);
    chmax(cnt_c,c); c--;
    weight[c].pb(w); value[c].pb(v); 
  }
  vvi dp(C+1,vi(W+1));
  rep(c,cnt_c){
    vvi dp2(C+1,vi(W+1));
    rep(cc,weight[c].size()){
      rep(i,C){
        rrep(j,W){
          if(j-weight[c][cc]>=0){
            chmax(dp2[i+1][j],max(dp2[i+1][j-weight[c][cc]]+value[c][cc],dp[i][j-weight[c][cc]]+value[c][cc]));
          }
        }
      }
    }
    rep(i,C+1){
      rep(j,W+1){
        chmax(dp[i][j],dp2[i][j]);
      }
    }
    // rep(i,C+1){
    //   rep(j,W+1) cout << dp2[i][j] << " ";
    //   cout << "" << endl;
    // }
    // cout << "" << endl;
  }
  cout << dp[C][W] << endl;
  return 0;
}