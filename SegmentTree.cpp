#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<list>
#include<queue>
#include<deque>
#include<algorithm>
#include<utility>
#include<memory>
#include<cmath>
#include<stack>
#include<tuple>
#include<cassert>
 
#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define EXIST(s,e) ((s).find(e)!=(s).end())
#define pb push_back
#define DEBUG false
 
using namespace std;
 
using ll = long long;
using P = pair<int,int>;
 
const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll LINF=1LL<<60;
const int MAX_N=200005;
 
template <class Monoid> class SegmentTree{
  private:
    using T = typename Monoid::type;
    int sz, N;
    vector<T> dat;
  public:
    SegmentTree(const vector<T> &vec){
      sz = vec.size(); N = 1; while(N<sz) N<<=1;
      dat.resize(2*N);
      fill(dat.begin(),dat.end(),Monoid::id());
      copy(vec.begin(),vec.end(),dat.begin()+N-1);
      for(int i=N-2;i>=0;i--) dat[i]=Monoid::op(dat[2*i+1],dat[2*i+2]);
    }
    SegmentTree(const int n){
      sz = n; N = 1; while(N<n) N<<=1;
      dat.resize(2*N);
      fill(dat.begin(),dat.end(),Monoid::id());
      for(int i=N-2;i>=0;i--) dat[i]=Monoid::op(dat[2*i+1],dat[2*i+2]);
    }
    void update(int i,T val){
      assert(0<=i && i<sz);
      dat[i+=N-1] = val;
      while(i>0){
        i=(i-1)/2;
        dat[i]=Monoid::op(dat[2*i+1],dat[2*i+2]);
      }
      return;
    }
    T query(int a,int b){ // op[a,b)
      return query(a,b,0,0,N);}
    T query(int a,int b,int k,int l,int r){
      assert(0<=l && l<=r && r<2*N);
      if(r<=a || b<=l) return Monoid::id();
      else if(a<=l && r<=b) return dat[k];
      else{
        T lval=query(a,b,2*k+1,l,(l+r)/2);
        T rval=query(a,b,2*k+2,(l+r)/2,r);
        return Monoid::op(lval,rval);
      }
    }
};

struct RMQ{
  using type = P;
  static type id(){return P(INF,INF);}
  static type op(const type &a ,const type &b){return min(a,b);}
};
 
SegmentTree<RMQ> even(MAX_N),odd(MAX_N);
int N;
using T = tuple<P,P,P,P>;
 
int cnt=0;
 
T calc(int l,int r){
  P a,b,c;
  int val1,val2,x1,x2;
  tie(val1,x1) = (l%2==0 ? even:odd).query(l,r);
  tie(val2,x2) = (l%2==0 ? odd:even).query(x1+1,r);
  return T(P(val1,val2),P(l,x1),P(x1+1,x2),P(x2+1,r));
}
 
void solve(){
  vector<int> ans;
  priority_queue<T,vector<T>,greater<T>> que;
  que.push(calc(0,N));
  while(!que.empty()){
    P val,a,b,c;
    tie(val,a,b,c) = que.top();
    que.pop();
    ans.pb(val.first);
    ans.pb(val.second);
    if(a.first<a.second) que.push(calc(a.first,a.second)); 
    if(b.first<b.second) que.push(calc(b.first,b.second)); 
    if(c.first<c.second) que.push(calc(c.first,c.second)); 
    
    // if(cnt++>100) exit(1);
    // else cout << "["<<a.second << "," << a.second << "), [" << b.first << "," << b.second <<
    //       "), [" << c.first << "," << c.second << ")" <<  endl;
  }
  rep(i,N) printf("%d%c",ans[i],i==N-1 ? '\n':' ');
}
 
int main(){
  cin >> N ;
  rep(i,N){
    int a;
    scanf("%d",&a);
    (i%2==0 ? even:odd).update(i,P(a,i));
    (i%2==0 ? odd:even).update(i,P(INF,INF));
  }
  solve();
  return 0;
}