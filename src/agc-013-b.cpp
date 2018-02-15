// https://beta.atcoder.jp/contests/agc013/submissions/1991681
#include "bits/stdc++.h"

#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define EXIST(s,e) ((s).find(e)!=(s).end())
#define pb push_back

using namespace std;

using ll = long long;
using P = pair<int,int>;

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll LINF=1LL<<60, lmod = 1e9+7;

const int MAX_N = 100005;
vector<int> graph[MAX_N];
bool passed[MAX_N];

int main(){
  int N,M;
  cin >> N >> M;
  rep(i,M){
    int a,b;
    scanf("%d%d",&a,&b);
    graph[a-1].pb(b-1);
    graph[b-1].pb(a-1);
  }
  deque<int> deq;
  deq.push_back(0);
  deq.push_back(graph[0][0]);
  while(true){
    bool ok = true;
    int s = deq.front();
    int e = deq.back();
    passed[s] = passed[e] = true;
    bool update = false;
    for(auto u:graph[s]){
      if(!passed[u]){
        deq.push_front(u);
        update = true;
        break;
      }
    }
    if(update) continue;
    for(auto u:graph[e]){
      if(!passed[u]){
        deq.push_back(u);
        update = true;
        break;
      }
    }
    if(update) continue;
    break;
  }
  cout << deq.size() << endl;
  for(auto u:deq) cout << u+1 << " ";
  cout << "" << endl;
  return 0;
}
