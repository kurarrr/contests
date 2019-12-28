#include "../../template/template.cpp"

vector<bool> reachable_from(const vector<vector<int>>& g, int from){
  // 有向グラフg上でfromから到達するかを返す
  int N = g.size();
  vector<bool> pass(N,false);
  function<void(int)> dfs = [&](int u){
    pass[u] = true;
    for(auto& v:g[u]) if(!pass[v]) dfs(v);
  };
  dfs(from);
  return pass;
}

vector<bool> reachable_to(const vector<vector<int>>& g, int target){
  // 有向グラフg上でtargetに到達するかを返す
  int N = g.size();
  vector<vector<int>> rev(N);
  for(int u = 0; u < N; u++)
    for(auto v:g[u]) rev[v].push_back(u);
  return reachable_from(rev, target);
}
