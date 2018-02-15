#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<list>
#include<queue>
#include<deque>
#include<algorithm>
#include<utility>
#include<memory>
 
#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define EXIST(s,e) ((s).find(e)!=(s).end())
#define INF 1<<25
#define pb push_back
 
typedef long long ll;

using namespace std;

const int mod=1e9+7;
ll dp[10][2][10]; //pos,less,count(1)が何個存在するか

int main(){
  int N;
  cin >> N ;
  int n=0; //桁数
  int a[9];
  int temp = N;
  while(temp){
    temp/=10; n++;
  }
  temp = N;
  rep(i,n){
    a[n-1-i] = temp % 10; temp/=10;
  }
  int lim;
  rep(i,10) rep(j,2) rep(k,10) dp[i][j][k]=0;
  dp[0][0][0]=1;
  rep(i,n) rep(j,2) rep(k,10){
    lim = j ? 9 : a[i];
    rep(l,lim+1){
      dp[i+1][j||l<lim][k+(l==1)]+=dp[i][j][k];
   }
  }

  ll ans=0;
  rep(j,2) rep(k,10)  ans += k * dp[n][j][k];
  cout << ans << endl;

  return 0;
}