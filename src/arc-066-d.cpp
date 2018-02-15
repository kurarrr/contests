// https://beta.atcoder.jp/contests/arc066/submissions/2048339

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
using Pl = pair<ll,int>;

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll lmod = 1e9+7,LINF=1LL<<60;
const int MAX_N = 1003;

int main(){
  ll N; cin >> N;
  map<ll,ll> mp;
  mp[0] = 1LL; mp[1] = 2LL;
  function<ll(ll)> solve = [&](ll n){
    if(mp.count(n)) return mp[n];
    return mp[n] = (solve(n/2) + solve((n-1)/2) + solve(n/2-1)) % lmod;
  };
  cout << solve(N) << endl;
  return 0;
}
