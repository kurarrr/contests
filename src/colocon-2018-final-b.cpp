// https://beta.atcoder.jp/contests/colopl2018-final-open/submissions/1994662

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

int al,ar;
string s,ans;
vector<int> dot[MAX_N];
int lev = 0;

void solve(int l,int r){
  // cout << l << "," << r << endl;
  // cout << al << endl;
  lev++;
  if(s[l]=='+'||s[l]=='*'||s[l]=='-'||s[l]=='/'){
    ans[al++] = '(';
    int last = l+1;
    int kak = 0;
    int ll = int(lower_bound(dot[lev].begin(),dot[lev].end(),l) - dot[lev].begin());
    int rr = int(upper_bound(dot[lev].begin(),dot[lev].end(),r) - dot[lev].begin());
    for(int i = ll; i < rr; i+=2){
      solve(dot[lev][i],dot[lev][i+1]);
      ans[al++] = s[l];
    }
    al--;
    ans[al++] = ')';
  }else{
    REP(i,l,r) ans[al++] = s[i];
  }
  lev--;
}

int main(){
  cin >> s;
  al = 0;
  ans = string(MAX_N,' ');
  int kak = 0;
  rep(i,s.size()){
    if(s[i]==','){
      dot[kak].pb(i);
      dot[kak].pb(i+1);
    }else if(s[i]=='('){
      kak++;
      dot[kak].pb(i+1);
    }else if(s[i]==')'){
      dot[kak].pb(i);
      kak--;
    }
  }
  solve(0,s.size());
  cout << ans.substr(0,al) << endl;
  return 0;
}
