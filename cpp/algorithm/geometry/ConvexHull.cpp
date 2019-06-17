#include "bits/stdc++.h"

#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define RREP(i, x, n) for(int i = x; i >= n; i--)
#define rrep(i, n) RREP(i,n,0)
#define pb push_back
#define show_table(n, k, table) rep(i,n){ rep(j,k) cout << table[i][j] << " "; cout << endl;}

template<class T> void chmax(T& a,const T& b){a=max(a,b);}
template<class T> void chmin(T& a,const T& b){a=min(a,b);}

using namespace std;

using ll = long long;
using P = pair<int,int>;
using Pl = pair<ll,ll>;
using vi = vector<int>;
using vvi = vector<vi>;

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll lmod = 1e9+7,LINF=1LL<<60;
const int MAX_N = 100005;

using ld = long double;
using Point = complex<ld>;
using Polygon = vector<Point>;

const ld eps = 1e-10;

Point at(const Polygon &g, int i) {
  i %= (int)g.size();
  return g[i < 0 ? i + g.size() : i];
}

bool comp(const Point& a, const Point& b) {
  return real(a - b) * 1.347589 + imag(a - b) > 0;
}

ld dot(Point a, Point b) { return real(conj(a) * b); }
ld cross(Point a, Point b) { return imag(conj(a) * b); }

struct Segment {
  Point a, b;
  Segment (Point p, Point q) : a(p), b(q) {;}
};

struct Line {
  Point a, b;
  Line (Point p, Point q) : a(p), b(q) {;}
  explicit Line (Segment s) : a(s.a), b(s.b) {;}
};

struct Circle {
  Point p; ld r;
  Circle (Point a, ld b) : p(a), r(b) {;}
};

int ccw (Point a, Point b, Point c) {
  b -= a; c -= a;
  if (cross(b, c) > eps) return 1;   // counter clockwise
  if (cross(b, c) < -eps) return -1; // clockwise
  if (dot(b, c) < 0) return 2;       // c--a--b on line
  if (norm(b) < norm(c)) return -2;  // a--b--c on line
  return 0;                          // a--c--b on line
}

vector<Point> unique(vector<Point> ps) {
  sort(begin(ps), end(ps), comp);
  vector<Point> res;
  for (Point p: ps)
    if (res.empty() || abs(res.back() - p) > eps)
      res.push_back(p);
  return res;
}

Polygon convex_hull(vector<Point> ps) {
  int n = ps.size(), k = 0;
  sort(begin(ps), end(ps), comp);
  Polygon res(2 * n);
  for (int i = 0; i < n; res[k++] = ps[i++])
    while (k >= 2 && ccw(res[k - 2], res[k - 1], ps[i]) <= 0) --k;
  for (int i = n - 2, t = k + 1; i >= 0; res[k++] = ps[i--])
    while (k >= t && ccw(res[k - 2], res[k - 1], ps[i]) <= 0) --k;
  res.resize(k - 1);
  return res;
}


int main(){
  int N; cin >> N;
  vector<Point> ps(N);
  map<Point,int,bool(*)(const Point&,const Point&)> mp(comp);
  rep(i,N){
    ld x,y; cin >> x >> y;
    ps[i] = Point(x,y);
    mp[ps[i]] = i;
  }
  auto ch = move(convex_hull(ps));
  int M = ch.size();
  vector<ld> theta(N,0.0);
  rep(i,M){
    auto& p1 = ch[(i-1+M)%M];
    auto& p2 = ch[i];
    auto& p3 = ch[(i+1)%M];
    ld b = arg(p3-p2); ld a = arg(p2-p1);
    if(a>0.0 && b<0.0) b += 2*PI;
    // cout << b/(2*PI) << " " << a/(2*PI)  << endl;
    theta[mp[p2]] = b-a;
  }
  ld ssum = 0.0;
  for(auto i:theta) ssum += i;
  for(auto i:theta) printf("%.10Lf\n",i/ssum);
  return 0;
}