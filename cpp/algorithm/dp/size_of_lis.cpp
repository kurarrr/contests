#include "../../template/template.cpp"

int size_of_lis(const vector<ll>& vec){
  // size of longest increasing subarray
  int N = vec.size();
  vector<ll> dp(N+1,LINF);
  dp[0] = -LINF;
  rep(i,N){
    // upperで<=, lowerで<
    int num = int(upper_bound(dp.begin(),dp.end(),vec[i]) - dp.begin());
    dp[num] = min(dp[num],vec[i]);
  }
  return int(lower_bound(dp.begin(),dp.end(),LINF) - dp.begin()) - 1;
}

void solve(){
  cin.tie(0);
  ios::sync_with_stdio(false);
  vl vec = {ll(1e9), ll(1e9-3), ll(1e7), 1, ll(1e9)};
  cout << size_of_lis(vec) << endl;
}