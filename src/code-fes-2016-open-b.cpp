// https://beta.atcoder.jp/contests/cf16-exhibition-final-open/submissions/2012828

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

int main(){
  double x1,y1,x2,y2,x3,y3;
  cin >> x1 >> y1;
  cin >> x2 >> y2;
  cin >> x3 >> y3;
  double a,b,c,r,d,x;
  a = hypot(x1-x2,y1-y2);
  b = hypot(x2-x3,y2-y3);
  c = hypot(x3-x1,y3-y1);
  r = abs((x2-x1)*(y3-y1)-(x3-x1)*(y2-y1))/(a+b+c);
  d = max(a,max(b,c));
  x = d/(2+d/r);
  printf("%.12lf",x);
  return 0;
}
