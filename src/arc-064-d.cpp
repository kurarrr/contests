// https://beta.atcoder.jp/contests/arc064/submissions/1986990
#include "bits/stdc++.h"

#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define EXIST(s,e) ((s).find(e)!=(s).end())
#define pb push_back
#define DEBUG false

using namespace std;

using ll = long long;
using P = pair<int,int>;
using Pl = pair<int,ll>;

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll LINF=1LL<<60;
const int MAX_N = 2003;
const ll lmod = 1e9+7;

int main(){
  string s; cin >> s; int N = s.size();
  cout << ((N%2==0 ^ s[0]==s[N-1]) ? "Second" : "First") << endl;
  return 0;
}
