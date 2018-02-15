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

ll comb(int n,int k){
  ll dp[n+1][n+1];
  rep(i,n){
    dp[i][0]=1;
    dp[i][i+1]=1;
  }
  rep(i,n-1){
    REP(j,1,i+2)  dp[i+1][j]=dp[i][j-1]+dp[i][j];
  }
  return dp[n-1][k];
}

int main(){
  int N,A,B,temp;
  cin >> N >> A >> B;
  temp=A;
  ll a,prea=0,ans=0;
  double ave;
  bool first=true;
  map<ll,int,greater<ll>> mp;
  rep(i,N){
    cin >> a ;
    if(EXIST(mp,a)){
      mp[a]++;
    }else{
      mp[a]=1;
    }
  }

  auto itr=mp.begin();
  while(itr!=mp.end()){
    if((temp - itr->second <= 0) && first){
      REP(i,A,min(itr->second,B)+1)  ans+=comb(itr->second,i);
      ave=itr->first;
      printf("%.6lf\n",ave);
      cout << ans << endl;
      return 0;
    }else if (temp - itr->second <= 0){
      ans=comb(itr->second,temp);
      ave = (ave + itr->first * temp)/A;
      printf("%.6lf\n",ave);
      cout << ans << endl;
      return 0;
    }
    temp -= itr->second;
    ave += itr->first * itr->second;
    first=false;
    ++itr;
  }

  return 0;
}