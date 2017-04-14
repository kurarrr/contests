#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<list>
#include<queue>
#include<deque>
#include<stack>
#include<algorithm>
#include<utility>
#include<memory>
 
#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define EXIST(s,e) ((s).find(e)!=(s).end())
#define pb push_back
 
using namespace std;

typedef long long ll;
typedef pair<ll,int> P;//toまでの最短距離,to

const int mod=1e9+7;
const int INF=1<<30;

struct edge{ll cost;int to;};
vector<edge> e1[100001],e2[100001];
ll d1[100001],d2[100001];

void dijkstra(vector<edge> graph[],ll d[]){
  priority_queue<P,vector<P>,greater<P>> que;
  fill(d,d+100000,INF);
  d[0]=0;
  que.push(P(0,0));
  while(!que.empty()){
    P p=que.top(); que.pop();
    int v=p.second; //行き先
    if(d[v]<p.first)  continue;
    rep(i,graph[v].size()){
      edge e=graph[v][i];
      if(d[v]+e.cost<d[e.to]){
        d[e.to]=d[v]+e.cost;
        que.push(P(d[e.to],e.to));
      }
    }
  }
  return ;
}

int main(){
  int N,M;
  ll T;
  cin >> N >> M >> T ;
  ll A[N];
  rep(i,N) cin >> A[i] ;
  int a,b;
  ll c;
  rep(i,M){
    edge e,re;
    cin >> a >> b >> c;
    a--; b--;
    e.cost=re.cost=c;
    e.to=b; re.to=a;
    e1[a].pb(e); e2[b].pb(re);
  }
  dijkstra(e1,d1);
  dijkstra(e2,d2);
  
  ll ans=0;
  rep(i,N){
    if(T<d1[i]+d2[i]) continue;
    ans=max(ans,(T-d1[i]-d2[i])*A[i]);
  }
  cout << ans << endl;
  return 0;
}
