// https://beta.atcoder.jp/contests/arc071/submissions/1960339

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

int p[MAX_N],q[MAX_N];

int main(){
  string S,T;
  cin >> S >> T ;
  int temp = 0;
  rep(i,S.size()) p[i+1] = (temp = (temp + int(S[i]-'A') + 1) % 3 );
  temp = 0;
  rep(i,T.size()) q[i+1] = (temp = (temp + int(T[i]-'A') + 1) % 3 );
  int Q,a,b,c,d;
  cin >> Q ;
  rep(i,Q){
    scanf("%d%d%d%d",&a,&b,&c,&d);
    if((p[b]-p[a-1]-q[d]+q[c-1])%3==0) printf("YES\n");
    else printf("NO\n");
  }
  return 0;
}
