// https://beta.atcoder.jp/contests/apc001/submissions/2063627

#include "bits/stdc++.h"

#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define RREP(i, x, n) for(int i = x; i >= n; i--)
#define rrep(i, n) RREP(i,n,0)
#define pb push_back

using namespace std;

using ll = long long;
using P = pair<int,int>;
using Pl = pair<ll,int>;

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll lmod = 1e9+7,LINF=1LL<<60;
const int MAX_N = 200005;

int main(){
  int N; cin >> N;
  string s;
  int num[20],res[20];
  int l,r,mid;
  int lres,rres;
  num[0] = 0; num[1] = N/2;
  rep(i,20){
    cout << num[i] << endl;
    cin >> s;
    if(s=="Vacant") return 0;
    else if(s=="Male") res[i] = 1;
    else res[i] = 0;
    if(i==1){
      if((res[i]==res[i-1] && (N/2)%2==1)||((res[i]!=res[i-1] && (N/2)%2==0))){
        l = 0;
        mid = N/4;
        r = N/2;
        lres = res[0];
        rres = res[1];
      }else{
        l = N/2;
        r = N;
        mid = N*3/4;
        lres = res[1];
        rres = res[0];
      }
      num[i+1] = mid;
    }
    if(i>=2){
      if((res[i]==lres && (mid-l)%2==1)||((res[i]!=lres)&&((mid-l)%2==0))){
        r = mid; rres = res[i];
      }else if(((res[i]==rres)&&((r-mid)%2==1))||((res[i]!=rres)&&((r-mid)%2==0))){
        l = mid; lres = res[i];
      }else{
        // l = mid, lres = res[i];
      }
      mid = (l+r)/2;
      num[i+1] = mid;
    }
  }
  return 0;
}
