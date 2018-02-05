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

int main(){
  int n,m,ta,tb;
  std::cin >> n >> m;
  int a[m],b[m],c[m];
  int d[n+1][n+1];
  fill(d[0],d[n+1],INF);
  int ans=0,temp=1;

  rep(i,m){
    std::cin >> ta >> tb >> c[i];
    a[i]=ta-1,b[i]=tb-1;
    d[a[i]][b[i]]=c[i];
    d[b[i]][a[i]]=c[i];
  }
  rep(i,n){
    d[i][i]=0;
  }
  rep(k,n){
    rep(i,n){
      rep(j,n){
        d[i][j]=min(d[i][j],d[i][k]+d[j][k]);
        d[j][i]=d[i][j];
      }
    }
  }
  rep(k,m){
    temp=1;
    rep(i,n){
      if(d[i][a[k]]+c[k]==d[i][b[k]]){
        temp*=0;
        break;
      }
    }
    ans+=temp;
  }
  cout << ans << endl;

}
