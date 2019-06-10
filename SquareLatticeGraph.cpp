// verify : https://abc007.contest.atcoder.jp/submissions/5723111

#ifdef DEBUG_IS_VALID
#define DEB 1 
#define _LIBCPP_DEBUG 0
#else
#define DEB 0
#define NDEBUG
#endif

#include <bits/stdc++.h>
using namespace std;

#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define RREP(i, x, n) for(int i = x; i >= n; i--)
#define rrep(i, n) RREP(i,n,0)
#define pb push_back
#pragma GCC optimize ("-O3")

using namespace std;

#define DUMPOUT cout
#define dump(...) if(DEB) DUMPOUT<<"  "<<#__VA_ARGS__<<" :["<<__LINE__<<":"<<__FUNCTION__<<"]"<<endl<<"    "; if(DEB) dump_func(__VA_ARGS__)
template<typename T1,typename T2>ostream& operator << (ostream& os, pair<T1,T2> p){cout << "(" << p.first << ", " << p.second << ")"; return os;}
template<typename T>ostream& operator << (ostream& os, vector<T>& vec) { os << "{"; for (int i = 0; i<vec.size(); i++) os << vec[i] << (i + 1 == vec.size() ? "" : ", "); os << "}"; return os; }
template<typename T>ostream& operator << (ostream& os, set<T>& st){cout << "{"; for(auto itr = st.begin(); itr != st.end(); itr++) cout << *itr << (next(itr)!=st.end() ? ", " : ""); cout << "}"; return os;}
template<typename T1,typename T2>ostream& operator << (ostream& os, map<T1,T2> mp){cout << "{"; for(auto itr = mp.begin(); itr != mp.end(); itr++) cout << "(" << (itr->first) << ", " << (itr->second) << ")" << (next(itr)!=mp.end() ? "," : ""); cout << "}"; return os; }

void dump_func(){DUMPOUT << endl;}
template <class Head, class... Tail>void dump_func(Head&& head, Tail&&... tail){ DUMPOUT << head; if (sizeof...(Tail) == 0) { DUMPOUT << " "; } else { DUMPOUT << ", "; } dump_func(std::move(tail)...);}
template<class T> inline bool chmax(T& a,T const& b){if(a>=b) return false; a=b; return true;}
template<class T> inline bool chmin(T& a,T const& b){if(a<=b) return false; a=b; return true;}

using ll = long long;
using P = pair<int,int>;
using Pl = pair<ll,ll>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;
using vp = vector<Pl>;
using vvp = vector<vp>;

const int INF = 1<<29;
const long long LINF=1LL<<59;

class SquareLatticeGraph{
  public:
    int N,M;
    vector<vector<int>> graph;
    int start = -1, goal = -1;
    vector<bool> is_wall;
    vector<int> dx = {-1,0,1,0};
    vector<int> dy = {0,-1,0,1};
    SquareLatticeGraph(const vector<string>& s){
      N = s.size();
      M = s[0].size();
      graph.resize(N*M);
      is_wall.resize(N*M);
      for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
          // other than '#', regarded as enterable
          //  e.g. '.','S','G'
          int node1 = to_node(i,j);
          if(s[i][j]=='S') start = node1;
          if(s[i][j]=='G') goal = node1;
          is_wall[node1] = (s[i][j]=='#');
        }
      }
      for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
          if(s[i][j]=='#') continue;
          int node1 = to_node(i,j);
          for(int k = 0; k < 4; k++){
              int node2 = to_node(i+dx[k],j+dy[k]);
              if(node2!=-1) graph[node1].push_back(node2);
          }
        }
      }
    }
    int to_node(int x,int y){
      // res : node number in graph
      //       -1 if out of range
      if(x<0||x>=N||y<0||y>=M) return -1;
      int res = x * M + y; 
      if(is_wall[res]) return -1;
      return res;
    }
    pair<int,int> to_point(int node_num){
      int x = node_num / M;
      int y = node_num % M;
      return make_pair(x,y);
    }
};

vector<ll> bfs(vector<vector<int>>& graph,int start = 0){
  // ! for lattice graph
  queue<int> que;
  int N = graph.size();
  vector<ll> dist(N,LINF);
  que.push(start);
  dist[start] = 0;
  while(!que.empty()){
    int u = que.front();
    que.pop();
    for(auto&& v: graph[u]){
      if(dist[u]+ 1 < dist[v]){
        dist[v] = dist[u] + 1;
        dump(v,dist[v],u);
        que.push(v);
      }
    }
  }
  return dist;
}

int main(){
  // Failed to predict input format
  int R,C,sx,sy,gx,gy;
  cin >> R >> C >> sx >> sy >> gx >> gy ;
  vector<string> s(R);
  rep(i,R) cin >> s[i] ;
  auto sqr = SquareLatticeGraph(s);
  auto dist = bfs(sqr.graph, sqr.to_node(sx-1,sy-1));
  dump(dist);
  cout << dist[sqr.to_node(gx-1,gy-1)] << endl;
  return 0;
}
