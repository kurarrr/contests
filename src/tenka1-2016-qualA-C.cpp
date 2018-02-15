// https://beta.atcoder.jp/contests/tenka1-2016-quala/submissions/2078700
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
const int MAX_N = 100005;

vector<int> graph[30];
int cnt[30];

int main(){
  int N; cin >> N;
  fill(cnt,cnt+30,0);
  rep(k,N){
    string a,b;
    cin >> a >> b;
    bool update = false;
    rep(i,min(a.size(),b.size())){
      if(a[i]!=b[i]){
        graph[int(a[i]-'a')].pb(int(b[i]-'a'));
        cnt[int(b[i]-'a')]++;
        update = true; break;
      }
    }
    if(!update){
      if(a.size()>b.size()){
        cout << "-1" << endl;
        return 0;
      }
    }
  }
  bool used[30];
  fill(used,used+30,false);
  string ans = "";
  rep(i,26){
    rep(j,26){
      if(used[j]) continue;
      if(cnt[j]==0){
        ans += char('a'+j);
        used[j] = true;
        for(auto u:graph[j]){
          cnt[u]--;
        }
        break;
      }
    }
    if(ans.size()!=i+1){
      cout << "-1" << endl;
      return 0;
    }
  }
  cout << ans << endl;
  return 0;
}
