// https://beta.atcoder.jp/contests/tenka1-2016-qualb/submissions/2079040

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
const int MAX_N = 33;

double comb(int n,int k){
  if(n==0){
    if(k==0) return 1.0;
    else return 0.0;
  }
  if(n<k) return 0.0;
  double res = 1.0;
  k = min(k,n-k);
  RREP(i,n,n-k+1) res *= i;
  RREP(i,k,1) res /= i;
  return res;
}

int A[MAX_N][MAX_N],N;
P ab[MAX_N];
double PP;
map<P,double> memo;

double solve(int p, int q){
  if(memo.count(P(p,q))) return memo[P(p,q)];
  int a,b; tie(a,b) = ab[p]; a = -a;
  int c = N-1-a;
  double res = .0;
  rep(j,q+1){
    double win = .0;
    // j勝する
    rep(k,j+1){
      win += comb(a,k)*comb(c,j-k)*pow(PP,max(double(c-j+2*k),0.0))*pow(1.0-PP,max(double(a+j-2*k),0.0));
    }
    if(p==N-1) res += win;
    else{
      int a2,b2; tie(a2,b2) = ab[p+1]; a2 = -a2;
      if(b<b2) res += win * solve(p+1,j);
      else res += win * solve(p+1,j-1);
    }
  }
  return memo[P(p,q)] = res;
}

int main(){
  double p,q; scanf("%d %lf/%lf",&N,&p,&q);
  PP = p/q;
  // if(abs(PP)<EPS){
  //   cout << "0.000000000000000" << endl;
  //   return 0;
  // }
  rep(i,N) rep(j,N) cin >> A[i][j];
  rep(i,N) ab[i].second = i;
  rep(i,N) rep(j,N) if(A[i][j]) ab[i].first--;
  sort(ab,ab+N);
  printf("%.10f\n",solve(0,N-1));
  return 0;
}
