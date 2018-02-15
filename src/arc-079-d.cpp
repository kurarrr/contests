// https://beta.atcoder.jp/contests/arc079/submissions/1987651
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

const int MAX_N = 202;

int main(){
  ll K; cin >> K ;
  ll k,r,N;
  N = 50;
  k = K / N; r = K % N;
  ll a = N - 1 + k - r;
  ll b = 2 * N - r + k;
  cout << N << endl;
  rep(i,N-r) cout << a << " ";
  rep(i,r) cout << b << " ";
  cout << "" << endl;
  return 0;
}
