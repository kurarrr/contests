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
using Pl = pair<ll,ll>;
using vi = vector<int>;
using vvi = vector<vi>;

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll lmod = 1e9+7,LINF=1LL<<60;
const int MAX_N = 102;

double dp[MAX_N][102][50][30];

int main(){
  int N; ll D; cin >> N >> D;
  int cnt2=0,cnt3=0,cnt5=0;
  while(D%2LL==0) D/=2LL,cnt2++;
  while(D%3LL==0) D/=3LL,cnt3++;
  while(D%5LL==0) D/=5LL,cnt5++;
  if(D!=1LL){
    cout << "0.0" << endl;
    return 0;
  }
  dp[0][0][0][0] = 1.0;
  rep(i,N) rep(j,cnt2+1) rep(k,cnt3+1) rep(l,cnt5+1){
    dp[i+1][j][k][l] += dp[i][j][k][l]/6;
    dp[i+1][min(j+1,cnt2)][k][l] += dp[i][j][k][l]/6;
    dp[i+1][j][min(k+1,cnt3)][l] += dp[i][j][k][l]/6;
    dp[i+1][min(j+2,cnt2)][k][l] += dp[i][j][k][l]/6;
    dp[i+1][j][k][min(l+1,cnt5)] += dp[i][j][k][l]/6;
    dp[i+1][min(j+1,cnt2)][min(k+1,cnt3)][l] += dp[i][j][k][l]/6;
  }
  printf("%.10lf",dp[N][cnt2][cnt3][cnt5]);
  return 0;
}