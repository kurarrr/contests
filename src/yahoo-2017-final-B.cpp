// https://beta.atcoder.jp/contests/yahoo-procon2017-final-open/submissions/2077141
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
const int MAX_N = 100005;

int a[MAX_N],b[MAX_N];

int main(){
  int N,M,K; cin >> N >> M >> K;
  rep(i,N) scanf("%d",a+i);
  rep(i,M) scanf("%d",b+i);
  sort(a,a+N);
  sort(b,b+M);
  int l = -1, r = 1e9, mid;
  while(abs(r-l)>1){
    mid = (l+r)/2;
    int cnt = 0;
    for(int i=0,j=0;i<N&&j<M;i++){
      int lb = a[i] - mid, ub = a[i] + mid;
      while(j<M&&b[j]<lb) j++;
      if(b[j]<=ub) cnt++,j++;
    }
    if(cnt>=K) r = mid;
    else l = mid;
  }
  cout << r << endl;
  return 0;
}
