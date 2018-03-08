#include "bits/stdc++.h"

#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define RREP(i, x, n) for(int i = x; i >= n; i--)
#define rrep(i, n) RREP(i,n,0)
#define pb push_back
#define show_table(n, k, table) rep(i,n){ rep(j,k) cout << table[i][j] << " "; cout << endl;}

using namespace std;

template<class T> inline void chmax(T& a,T const& b){a=max(a,b);}
template<class T> inline void chmin(T& a,T const& b){a=min(a,b);}

using ll = long long;
using P = pair<int,int>;
using Pl = pair<ll,ll>;
using vi = vector<int>;
using vvi = vector<vi>;

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll lmod = 1e9+7,LINF=1LL<<60;
const int MAX_N = 100005;

P a[MAX_N];

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);
  int N,K; cin >> N >> K;
  rep(i,N) cin >> a[i].first >> a[i].second;
  rep(i,N) a[i].second *= (-1);
  sort(a,a+N);
  set<int> st;
  st.insert(-a[0].second);
  REP(i,1,N){
    auto itr = st.lower_bound(-a[i].second);
    if(itr==st.begin()){
      st.insert(-a[i].second);
    }else{
      itr--;
      st.erase(*itr);
      st.insert(-a[i].second);
    }
  }
  cout << st.size() << endl;
  return 0;
}