// https://beta.atcoder.jp/contests/arc072/submissions/2014391

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

char res[101][101];

bool solve(int i,int j,char t){
  if(res[i][j]!='X'){
    return res[i][j] == t;
  }
  bool ret;
  if(t=='A'){
    ret = false;
    REP(k,1,i/2+1) ret |= solve(i-2*k,j+k,'B');
    REP(k,1,j/2+1) ret |= solve(i+k,j-2*k,'B');
    if(ret) res[i][j] = 'A';
    else res[i][j] = 'B';
  }else{
    ret = true;
    REP(k,1,i/2+1) ret &= solve(i-2*k,j+k,'A');
    REP(k,1,j/2+1) ret &= solve(i+k,j-2*k,'A');
    if(ret) res[i][j] = 'B';
    else res[i][j] = 'A';
  }
  return ret;
}

int main(){
  ll X,Y; cin >> X >> Y;
  // rep(i,100) rep(j,100) res[i][j] = 'X';
  // res[0][0] = res[0][1] = res[1][0] = res[1][1] = 'B';
  // rep(i,10){
  //   rep(j,10){
  //     cout << (solve(i,j,'A') ? 'A' : 'B') << " ";
  //   }
  //   cout << "" << endl;
  // }
  if(abs(X-Y)>1) cout << "Alice" << endl;
  else cout << "Brown" << endl;
  return 0;
}
