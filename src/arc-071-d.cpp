// https://beta.atcoder.jp/contests/arc071/submissions/1960290
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
const int MAX_N = 100005;
const ll lmod = 1e9+7;

ll part(ll t){
  ll res = 0LL;
  ll p[MAX_N];
  rep(i,t){
    scanf("%lld",p+i);
  }
  rep(i,t-1){
    res = (res + (i+1) * (t-i-1) * (p[i+1]-p[i])) % lmod;
  }
  return res;
}

int main(){
  ll n,m; cin >> n >> m;
  ll x = part(n);
  ll y = part(m);
  cout << (x*y) % lmod << endl;
  return 0;
}
