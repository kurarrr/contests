#include "../../template/template.cpp"

vector<int> topological_sort(const vector<vector<int>>& graph){
  // if graph is not DAG, return {}
  // else topological sorted vertices
  int N = graph.size();
  stack<int> st;
  vector<int> h(N), res;
  for(int i = 0; i < N; i++)
    for(auto& v: graph[i]) h[v]++;
  for(int i = 0; i < N; i++)
    if(h[i] == 0) st.push(i);
  while(st.size()) {
    int u = st.top(); st.pop();
    res.push_back(u);
    for(auto& v: graph[u]){
      h[v]--;
      if(h[v] == 0) st.push(v);
    }
  }
  if(res.size() != N) res.clear();
  return res;
}

void GRL_4_B(){
  int N,M; cin >> N >> M;
  vvi g(N);
  rep(i,M){
    int s,t; cin >> s >> t;
    g[s].pb(t);
  }
  auto ts = topological_sort(g);
  rep(i,N) cout << ts[i] << endl;
}

void solve(){
  GRL_4_B();
}
