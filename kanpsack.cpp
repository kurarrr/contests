#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<list>
#include<queue>
#include<deque>
#include<algorithm>
#include<utility>
#include<memory>
#include<cmath>
 
#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define EXIST(s,e) ((s).find(e)!=(s).end())
#define pb push_back

using namespace std;
 
typedef long long ll;
typedef pair<int,int> P;
typedef pair<ll,ll> PL;
const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const int MAX_N=202,MAX_X=200001;

int N;
ll v[MAX_N],w[MAX_N],dp[MAX_N][MAX_X];
ll W,sum_w,sum_v;

ll calc1(){
  //Nが30以下 -> 半分全列挙
  vector<PL> p1,p2;
  int n1=N/2;
  int n2=N-n1;
  rep(i,1<<n1){
    ll tw=0,tv=0;
    rep(j,n1){
      if(i>>j & 1){
        tw+=w[j]; tv+=v[j];
      }
    }
    p1.pb({tw,tv});
  }
  sort(ALL(p1));
  int m=1;
  p2.pb(p1[0]);
  REP(i,1,1<<n1){
    if(p2[m-1].second<p1[i].second){
      //順序がおかしいものはスキップ,必要なpairのvalueより大きいものを取っていく
      p2.pb(p1[i]);
      m++;
    }
  }
  ll res=0;
  rep(i,1<<n2){
    ll sw=0,sv=0;
    rep(j,n2){
      if(i>>j & 1){
        sw+=w[n1+j]; sv+=v[n1+j];
      }
    }
    if(sw>W) continue;
    ll tv=(lower_bound(p2.begin(),p2.end(),PL(W-sw+1,0))-1)->second;
    res=max(res,sv+tv);
  }
  return res;
}

ll calc2(){
  //wが全て1000以下
  if(W>=sum_w){
    //全部入る
    ll S=0;
    rep(i,N) S+=v[i];
    return S;
  }
  fill(dp[0],dp[MAX_N-1],0);
  //dp[i][j]:=i番目までの荷物で重さjの荷物を持った時の価値の最大値
  rep(i,N){ 
    rep(j,W+1){
      if(j-w[i]>=0) dp[i+1][j]=max(dp[i][j],dp[i][j-w[i]]+v[i]);
      else dp[i+1][j]=dp[i][j];
    }
  }
  return dp[N][W];
}

ll calc3(){
  //vが全て1000以下
  fill(dp[0],dp[MAX_N-1],INF);
  rep(i,N+1) dp[i][0]=0;
  //dp[i][j]:=i番目までの荷物でjの価値を達成した時の重さの最小値
  rep(i,N){
    rep(j,sum_v){
      dp[i+1][j]=min(dp[i][max(0LL,j-v[i])]+w[i],dp[i][j]);
    }
  }
  ll res;
  rep(j,sum_v){
    if(dp[N][j+1]>W){
      res=j;
      break;
    }
  }
  return res;
}

int main(){
  cin >> N >> W ;
  ll max_w=sum_w=sum_v=0;
  rep(i,N){
    scanf("%lld%lld",&v[i],&w[i]);
    max_w=max(max_w,w[i]);
    sum_w+=w[i];
    sum_v+=v[i];
  }
  //cout << calc2() << endl;
  if(N<=30) printf("%lld\n",calc1());
  else if(max_w<=1000) printf("%lld\n",calc2());
  else printf("%lld\n",calc3());

  return 0;
}
