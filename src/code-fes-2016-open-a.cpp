// https://beta.atcoder.jp/contests/cf16-exhibition-final-open/submissions/2011466

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
ll fact[MAX_N];
int right[2*MAX_N];
vector<P> vec;

int main(){
  ll N; cin >> N;
  rep(i,N){
    int a; scanf("%d",&a);
    vec.pb(P(a,1));
  }
  rep(i,N){
    int a; scanf("%d",&a);
    vec.pb(P(a,-1));
  }
  sort(ALL(vec));
  ll ans = 1LL;
  ll cnt = 0;
  int pre;
  rrep(i,2*N-1){
    if(cnt==0){
      pre = vec[i].second;
    }
    if(vec[i].second==pre){
      cnt++;
    }else{
      (ans *= cnt) %= lmod;
      cnt--;
    }
  }
  cout << ans << endl;
  return 0;
}
