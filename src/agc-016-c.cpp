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
const int MAX_N = 100005;

int main(){
  int H,W,h,w; cin >> H >> W >> h >> w;
  if(H%h==0 && W%w==0){
    cout << "No" << endl;
    return 0;
  }else{
    cout << "Yes" << endl;
  }
  if(h==1){
    REP(i,1,H+1){
      REP(j,1,W+1){
        if(j%w==1) cout << int(1e6)-1 << " ";
        else if(j%w==0) cout << int(-1e6) << " ";
        else cout << "0 ";
      }
      cout << "" << endl;
    }
  }else if(w==1){
    REP(i,1,H+1){
      REP(j,1,W+1){
        if(i%h==1) cout << int(1e6)-1 << " ";
        else if(i%h==0) cout << int(-1e6) << " ";
        else cout << "0 ";
      }
      cout << "" << endl;
    }

  }
  else REP(i,1,H+1){
    REP(j,1,W+1){
      if(i%h==1 && j%w==1) cout << int(1e6)-1 << " ";
      else if(i%h==0 && j%w==0) cout << int(-1e6) <<  " " ;
      else cout << "0 ";
    }
    cout << "" << endl;
  }
  return 0;
}