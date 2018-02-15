#include<stdio.h>
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
#include<cmath>
 
#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define EXIST(s,e) ((s).find(e)!=(s).end())
#define pb push_back

using namespace std;
 
typedef long long ll;
typedef pair<int,int> P;
const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const int MAX_N=300001;
vector<int> v[MAX_N];

int main(){
  int n,m;
  cin >> n >> m ;
  rep(i,m){
    int a,b;
    cin >> a >> b ;
    a--; b--;
    v[a].pb(b); v[b].pb(a);
  }
  bool ans=true;
  rep(i,n){
    if(v[i].size()<2) continue;
    int cnt=0;
    rep(j,v[i].size()-1){
      REP(k,j+1,v[i].size()){
        int x,y;
        x=v[i][j]; y=v[i][k];
        if(find(v[x].begin(),v[x].end(),y)==v[x].end()){
          cnt++;
          //cout << x << ":" << y << endl;
        }
      }
    }
    if(cnt>2){
      ans=false;
      break;
    }
  }
  if(!ans){
    cout << "NO" << endl;
  }else{
    cout << "YES" << endl;
  }
  return 0;
}