// https://beta.atcoder.jp/contests/agc017/submissions/1989095
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

const int MAX_N = 500005;
bool used[MAX_N];

ll N,A,B,C,D,E;

int main(){
  cin >> N >> A >> B >> C >> D ;
  E = B - A;
  ll l = 0, r = N-1, mid;
  fill(used,used+N+1,false);
  while(true){
    mid = (l+r)/2;
    if(used[mid]) break;
    // + を N-1-mid , - を mid 回使う
    ll _min = C * (N-1-mid);
    ll _max = D * (N-1-mid);
    _min -= D * mid;
    _max -= C * mid;
    if(E>=_min && E<=_max){
      // cout << mid << "," << _min << "," << _max << endl;
      cout << "YES" << endl;
      return 0;
    }else if(E<_min){
      // - を増やす
      l = mid;
    }else{
      r = mid;
    }
    used[mid] = true;
  }
  cout << "NO" << endl;
  return 0;
}
