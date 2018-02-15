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
const int MAX_N = 5003;
const ll lmod = 1e9+7;

int N,K,a[MAX_N];
bool dp[MAX_N*2];

int main(){
  scanf("%d%d",&N,&K);
  int temp = 0;
  a[temp++] = 0; //dummy
  rep(i,N){
    int b;
    scanf("%d",&b);
    if(b<K) a[temp++] = b;
  }
  N = temp;
  sort(a,a+N);
  a[N] = K; //dummy
  int l = 0,r = N+1,mid;
  while(abs(r-l)>1){
    mid = (l+r)/2;
    fill(dp,dp+K,false);
    dp[0] = true;
    rep(j,N){
      if(j==mid) continue;
      for(int k=K; k>=a[j]; k--){
        dp[k] |= dp[k-a[j]];
      }
    }
    bool need = false;
    REP(j,K-a[mid],K) need |= (dp[j]);
    if(!need) l = mid;
    else r = mid;
  }
  cout << l << endl;
  return 0;
}
