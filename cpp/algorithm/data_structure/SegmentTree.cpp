#include "../../template/template.cpp"

template <typename T>
struct SegmentTree{
  using F = function<T(T,T)>;
  int n;
  F f;
  T ti;
  vector<T> dat;

  SegmentTree(){}
  SegmentTree(F f,T ti):f(f),ti(ti){}

  void init(int n_){
    n=1;
    while(n<n_) n<<=1;
    dat.assign(n<<1,ti);
  }

  void build(const vector<T> &v){
    int n_=v.size();
    init(n_);
    for(int i=0;i<n_;i++) dat[n+i]=v[i];
    for(int i=n-1;i;i--)
      dat[i]=f(dat[(i<<1)|0],dat[(i<<1)|1]);
  }

  void update(int k,T x){
    dat[k+=n]=x;
    while(k>>=1)
      dat[k]=f(dat[(k<<1)|0],dat[(k<<1)|1]);
  }

  T query(int a,int b){
    if(a>=b) return ti;
    T vl=ti,vr=ti;
    for(int l=a+n,r=b+n;l<r;l>>=1,r>>=1) {
      if(l&1) vl=f(vl,dat[l++]);
      if(r&1) vr=f(dat[--r],vr);
    }
    return f(vl,vr);
  }

  template<typename C>
  int find(int st,C &check,T &acc,int k,int l,int r){
    if(l+1==r){
      acc=f(acc,dat[k]);
      return check(acc)?k-n:-1;
    }
    int m=(l+r)>>1;
    if(m<=st) return find(st,check,acc,(k<<1)|1,m,r);
    if(st<=l&&!check(f(acc,dat[k]))){
      acc=f(acc,dat[k]);
      return -1;
    }
    int vl=find(st,check,acc,(k<<1)|0,l,m);
    if(~vl) return vl;
    return find(st,check,acc,(k<<1)|1,m,r);
  }

  template<typename C>
  int find(int st,C &check){
    T acc=ti;
    return find(st,check,acc,1,0,n);
  }
};

template <typename T>
struct Compression{
  vector<T> ary;
  Compression() : ary(vector<T>()) {;}
  void push(T val){
    ary.push_back(val);
  }
  void build(){
    sort(ary.begin(), ary.end());
    ary.erase(unique(ary.begin(), ary.end()), ary.end());
  }
  int size(){
    return ary.size();
  }
  T f(int idx){
    assert(0 <= idx && idx < ary.size());
    return ary[idx];
  }
  int inv(T val){
    int idx = int(lower_bound(ary.begin(), ary.end(), val) - ary.begin());
    return idx;
  }
};

void solve(){
  ll N, M;
  cin >> N >> M;
  using Pd = pair<double, double>;
  auto f = [&](Pd l, Pd r){return Pd(l.fi * r.fi, r.fi * l.se + r.se);};
  SegmentTree<Pd> seg(f, Pd(1.0, 0.0));
  vi p(M);
  vector<double> a(M), b(M);
  Compression<ll> comp;
  rep(i, M){
    cin >> p[i] >> a[i] >> b[i];
    comp.push(p[i]);
  }
  comp.build();
  int sz = comp.size();
  seg.init(sz+2);
  double ma = 1.0, mi = 1.0;
  rep(i, M){
    dump(comp.inv(p[i]));
    seg.update(comp.inv(p[i]), Pd(a[i], b[i]));
    Pd val = seg.query(0, sz);
    dump(val);
    chmax(ma, val.fi + val.se);
    chmin(mi, val.fi + val.se);
  }
  cout << mi << endl;
  cout << ma << endl;
}