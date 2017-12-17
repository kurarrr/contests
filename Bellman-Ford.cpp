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
typedef pair<int,ll> PL;
const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const int MAX_N=1001;

bool reach[MAX_N];
vector<PL> v[MAX_N];
vector<int> rv[MAX_N];
int N,M,cnt=0;
ll d[MAX_N];
ll INFL=1LL<<50;

void search(int to){
  reach[to]=true;
  rep(i,rv[to].size()){
    if(!reach[rv[to][i]]) search(rv[to][i]);
  }
  return ;
}

void bf(){
  rep(i,N) d[i]=-INFL;
  d[0]=0;
  while(true){
    bool update=false;
    rep(i,N){
      rep(j,v[i].size()){
        PL p=v[i][j];
        if(d[i]!=-INFL && (reach[p.first] && d[p.first]<d[i]+p.second)){
          d[p.first]=d[i]+p.second;
          //cout << p.first << ":" << d[p.first] << endl;
          update=true;
        }
      }
    }
    if(update)  cnt++;
    if(!update) break;
    if(cnt>=N) break;
  }
  return ;
}

int main(){
  cin >> N >> M ;
  rep(i,M){
    int a,b; ll c;
    cin >> a >> b >> c ;
    a--; b--;
    v[a].pb(PL(b,c));
    rv[b].pb(a);
  }
  fill(reach,reach+N,false);
  search(N-1);
  //rep(i,N) cout << i << ":" << (reach[i] ? "ok" : "no") << endl;
  bf();
  if(cnt>=N) cout << "inf" << endl;
  else cout << d[N-1] << endl;
  return 0;
}