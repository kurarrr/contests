#include "bits/stdc++.h"

#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define RREP(i, x, n) for(int i = x; i >= n; i--)
#define rrep(i, n) RREP(i,n,0)
#define pb push_back
#define show_table(n, k, table) rep(i,n){ rep(j,k) cout << table[i][j] << " "; cout << endl;}

template<class T> void chmax(T& a,const T& b){a=max(a,b);}
template<class T> void chmin(T& a,const T& b){a=min(a,b);}

using namespace std;

using ll = long long;
using P = pair<int,int>;
using Pl = pair<ll,ll>;
using vi = vector<int>;
using vvi = vector<vi>;

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll lmod = 1e9+7,LINF=1LL<<60;
const int MAX_N = 302;

int main(){
  int Q,K; cin >> Q >> K;
  priority_queue<ll> max_que;
  priority_queue<ll,vector<ll>,greater<ll>> min_que;
  rep(i,Q){
    int t; scanf("%d",&t);
    if(t==1){
      ll u,v; scanf("%lld",&v);
      if(max_que.size()<K){
        max_que.push(v);
      }else{
        max_que.push(v);
        v = max_que.top();
        max_que.pop();
        min_que.push(v);
      }
    }else{
      if(max_que.size()<K){
        printf("-1\n");
      }else{
        printf("%lld\n",max_que.top());
        max_que.pop();
        if(!min_que.empty()){
          ll u = min_que.top();
          max_que.push(u);
          min_que.pop();
        }
      }
    }
  }
  return 0;
}