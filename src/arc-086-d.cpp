// https://beta.atcoder.jp/contests/arc086/submissions/1987086
#include "bits/stdc++.h"

#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define EXIST(s,e) ((s).find(e)!=(s).end())
#define pb push_back

using namespace std;

using ll = long long;
using P = pair<int,int>;

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll LINF=1LL<<60, lmod = 1e9+7;

const int MAX_N = 51;
int a[MAX_N];

vector<P> ans;

int main(){
  int N; cin >> N ;
  int _min = INF, _max = -INF;
  int argmin,argmax;
  rep(i,N){
    scanf("%d",a+i);
    if(a[i]<_min){
      _min = a[i];
      argmin = i;
    }
    if(a[i]>_max){
      _max = a[i];
      argmax = i;
    }
  }
  if(_min<0 && _max>0){
    if(abs(_min)>abs(_max)){
      // 全部負にする
      rep(i,N){
        if(a[i]<0) continue;
        ans.pb(P(argmin+1,i+1));
      }
    }else{
      // 全部正にする
      _min = 1;
      rep(i,N){
        if(a[i]>0) continue;
        ans.pb(P(argmax+1,i+1));
      }
    }
  }
  if(_min>=0){
    rep(i,N-1) ans.pb(P(i+1,i+2));
  }else{
    for(int i=N;i>1;i--) ans.pb(P(i,i-1));
  }
  cout << ans.size() << endl;
  rep(i,ans.size()) cout << ans[i].first << " " << ans[i].second << endl;
  return 0;
}
