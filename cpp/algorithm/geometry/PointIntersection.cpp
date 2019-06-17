// unverified
// the attribute doesn't match [-Wattributes]
#include "../../template/template.cpp"

const string YES = "Yes";
const string NO = "No";
void yn(bool ok){
  cout << (ok ? YES : NO) << endl;
}

const double EPS = 1e-8;
const double DINF = 1e12;
#define X real()
#define Y imag()
#define curr(P, i) P[i]
#define next(P, i) P[(i+1)%P.size()]
#define prev(P, i) P[(i+P.size()-1) % P.size()]
#define diff(P, i) (next(P, i) - curr(P, i))
#define EQ(a,b) (abs((a)-(b)) < EPS)

namespace std{
  using Point = complex<double>;
  bool std::operator < (const std::Point &lhs, const std::Point &rhs) {
    return real(lhs) != real(rhs) ? real(lhs) < real(rhs) : imag(lhs) < imag(rhs);
  }
}
//overflow注意
int distance2(const Point &a, Point &b){ return (a.real() - b.real()) * (a.real() - b.real()) * (a.imag() - b.imag()) * (a.imag() - b.imag()); }

//外積
double cross(const Point &a, const Point &b) { return imag(conj(a)*b); }

//内積
double dot(const Point &a, const Point &b) { return real(conj(a)*b); }

// 直線
struct Line : public vector<Point> {
  Line(const Point &a, const Point &b) {
    push_back(a); push_back(b);
  }
}; 
// 線分
struct LineSegment : public vector<Point> {
  LineSegment(const Point &a, const Point &b) {
    push_back(a); push_back(b);
  }
}; 
Line to_line(const LineSegment& s){
  return Line(s[0],s[1]);
}

int ccw(Point a, Point b, Point c) {
  b -= a; c -= a;
  if (cross(b, c) > 0)   return +1;       // counter clockwise
  if (cross(b, c) < 0)   return -1;       // clockwise
  if (dot(b, c) < 0)     return +2;       // c--a--b on line
  if (norm(b) < norm(c)) return -2;       // a--b--c on line
  return 0;
}

//多角形
using Poly = vector<Point>;

//円
struct Circle {
  Point p; double r;
  Circle(const Point &p, double r) : p(p), r(r) { }
};


//交差判定達 (L = 直線, P = 点, S = 線分)

bool intersectLL(const Line &l, const Line &m) {
  return abs(cross(l[1]-l[0], m[1]-m[0])) > EPS || // non-parallel
    abs(cross(l[1]-l[0], m[0]-l[0])) < EPS;   // same line
}

bool intersectLS(const Line &l, const LineSegment &s) {
  return cross(l[1]-l[0], s[0]-l[0])*       // s[0] is left of l
    cross(l[1]-l[0], s[1]-l[0]) < EPS; // s[1] is right of l
}

bool intersectLP(const Line &l, const Point &p) {
  return abs(cross(l[1]-p, l[0]-p)) < EPS;
}

bool intersectSS(const LineSegment &s, const LineSegment &t) {
  return ccw(s[0],s[1],t[0])*ccw(s[0],s[1],t[1]) <= 0 &&
    ccw(t[0],t[1],s[0])*ccw(t[0],t[1],s[1]) <= 0;
}

bool intersectSP(const LineSegment &s, const Point &p) {
  return abs(s[0]-p)+abs(s[1]-p)-abs(s[1]-s[0]) < EPS; // triangle inequality
}

//線分lに対する、点pの射影
Point projection(const Line &l, const Point &p) {
  double t = dot(p-l[0], l[0]-l[1]) / norm(l[0]-l[1]);
  return l[0] + t*(l[0]-l[1]);
}

double distanceLP(const Line &l, const Point &p) {
  return abs(p - projection(l, p));
}

//-1 交差しない
//0 接する
//1 一箇所で交差する
//2 二箇所で交差する
int intersectSC(const LineSegment &s, const Circle &c) {
  int ins = 0;
  for(int i = 0; i < 2; i++ ) {
    if (abs(s[i]-c.p)<c.r) ins++;
    else if (EQ(abs(s[i]-c.p), c.r)) return 0;
  }
  if (ins == 2) return -1;
  if (ins == 1) return 1;
  double d = distanceLP(to_line(s), c.p);
  if (d-c.r > EPS) return -1;
  Point nor=(s[0]-s[1]) * Point(0, 1);
  if (ccw(c.p, c.p+nor, s[0]) * ccw(c.p, c.p+nor, s[1]) < 0) return 2;
  return -1;
}

//線分lに対する、点pの反射
//反射とは、lを対称軸とした時にpと線対称の位置にある点
Point reflection(const Line &l, const Point &p) {
  return p + Point(2, 0) * (projection(l, p) - p);
}

//距離達 (L = 直線, P = 点, S = 線分)

double distancePP(const Point &a, const Point &b){
  return abs(a - b);
}

double distanceLL(const Line &l, const Line &m) {
  return intersectLL(l, m) ? 0 : distanceLP(l, m[0]);
}
double distanceLS(const Line &l, const LineSegment &s) {
  if (intersectLS(l, s)) return 0;
  return min(distanceLP(l, s[0]), distanceLP(l, s[1]));
}
double distanceSP(const LineSegment &s, const Point &p) {
  const Point r = projection(to_line(s), p);
  if (intersectSP(s, r)) return abs(r - p);
  return min(abs(s[0] - p), abs(s[1] - p));
}
double distanceSS(const LineSegment &s, const LineSegment &t) {
  if (intersectSS(s, t)) return 0;
  return min(min(distanceSP(s, t[0]), distanceSP(s, t[1])),
      min(distanceSP(t, s[0]), distanceSP(t, s[1])));
}

//交点達
Point crosspointLL(const Line &l, const Line &m) {
  double A = cross(l[1] - l[0], m[1] - m[0]);
  double B = cross(l[1] - l[0], l[1] - m[0]);
  if (abs(A) < EPS && abs(B) < EPS) return m[0]; // same line
  if (abs(A) < EPS) assert(false); // !!!PRECONDITION NOT SATISFIED!!!
  return m[0] + B / A * (m[1] - m[0]);
}

vector<Point> crosspointCL(const Circle &c, const Line &l){
  vector<Point> res;
  double d = distanceLP(l, c.p);
  if(d < c.r + EPS){
    double len = (d > c.r) ? 0.0 : sqrt(c.r * c.r - d * d);
    Point nor = (l[0] - l[1]) / abs(l[0] - l[1]);
    res.push_back(projection(l, c.p) + len * nor);
    res.push_back(projection(l, c.p) - len * nor);
  }
  return res;
}

vector<Point> crosspointCS(const Circle &c, const LineSegment &s){
  vector<Point> v = crosspointCL(c, to_line(s)), res;
  for(int k = 0; k < v.size(); k++) if(ccw(s[0], v[k], s[1]) == -2) res.push_back(v[k]);
  return res;
}

vector<Point> crosspointCC(const Circle &c1, const Circle &c2){
  vector<Point> res;
  double d = abs(c1.p - c2.p);
  double rc = (d * d + c1.r * c1.r - c2.r * c2.r) / (2 * d);
  double dfr = c1.r * c1.r - rc * rc;
  if(EQ(dfr, 0.0)) dfr = 0.0;
  else if(dfr < 0.0) return res;
  double rs = sqrt(dfr);
  Point diff = (c2.p - c1.p) / d;
  res.push_back(c1.p + diff * Point(rc, rs));
  res.push_back(c1.p + diff * Point(rc, -rs));
  return res;
}

//直交かどうか
bool orthogonalLL(const Line &l1, const Line &l2){
  return (dot(l1[0]-l1[1], l2[0]-l2[1]) <= EPS && dot(l1[0]-l1[1], l2[0]-l2[1]) >= -EPS);
}

//平行かどうか
bool parallel(const Line &l1, const Line &l2){
  return (cross(l1[0]-l1[1], l2[0]-l2[1]) <= EPS && cross(l1[0]-l1[1], l2[0]-l2[1]) >= -EPS);
}

//多角形の面積
double area2(const Poly &P) {
  double A = 0.0;
  for (int i = 0; i < P.size(); ++i)
    A += cross(curr(P, i), next(P, i));
  return A / 2.0;
}

//凸性判定
//ただし、凸性の定義(全ての角が180度未満)より、0度の角があるようなものも凸とする。
//convex_hullして点の数を比較したほうが安全な気がする
bool isconvex(const Poly &P) {
  for (int i = 0; i < P.size(); ++i)
    if (ccw(prev(P, i), curr(P, i), next(P, i)) == 1) return false;
  return true;
}

//点-多角形包含判定
enum { OUT, ON, IN };
int contains(const Poly &g, const Point &p) {
  bool in = false;
  for (int i = 0; i < g.size(); ++i) {
    Point a = curr(g,i) - p, b = next(g,i) - p;
    if (imag(a) > imag(b)) swap(a, b);
    if (imag(a) <= 0 && 0 < imag(b))
      if (cross(a, b) < 0) in = !in;
    if (cross(a, b) == 0 && dot(a, b) <= 0) return ON;
  }
  return in ? IN : OUT;
}

//凸包
Poly convex_hull(Poly &ps) {
  int n = ps.size(), k = 0;
  sort(ps.begin(), ps.end());
  Poly ch(2*n);
  for (int i = 0; i < n; ch[k++] = ps[i++]) // lower-hull
    while (k >= 2 && ccw(ch[k-2], ch[k-1], ps[i]) == -1) --k;
  for (int i = n-2, t = k+1; i >= 0; ch[k++] = ps[i--]) // upper-hull
    while (k >= t && ccw(ch[k-2], ch[k-1], ps[i]) == -1) --k;
  ch.resize(k-1);
  return ch;
}

//凸多角形の直径
//直径とは、ある頂点と別の頂点が結ぶ距離の最長のこと
double convex_diameter(const Poly &pt) {
  const int n = pt.size();
  int is = 0, js = 0;
  for (int i = 1; i < n; ++i) {
    if (imag(pt[i]) > imag(pt[is])) is = i;
    if (imag(pt[i]) < imag(pt[js])) js = i;
  }
  double maxd = norm(pt[is]-pt[js]);

  int i, maxi, j, maxj;
  i = maxi = is;
  j = maxj = js;
  do {
    if (cross(diff(pt,i), diff(pt,j)) >= 0) j = (j+1) % n;
    else i = (i+1) % n;
    if (norm(pt[i]-pt[j]) > maxd) {
      maxd = norm(pt[i]-pt[j]);
      maxi = i; maxj = j;
    }
  } while (i != is || j != js);
  return maxd; /* farthest pair is (maxi, maxj). */
}

//最近点対 (求めるのは距離だけで、ペアの2点は求めない)
//多角形gで呼び出す時は、convex_radius(&g[0], N)みたいに配列になおしてください！
//また、gはあらかじめcompare_xでソートして下さい。
double compare_x(const Point &a, const Point &b){
  return a.X != b.X ? a.X < b.X : a.Y < b.Y;
}

double compare_y(const Point &a, const Point &b){
  return a.Y != b.Y ? a.Y < b.Y : a.X < b.X;
}

double convex_radius(Point *a, int n){
  if(n <= 1) return DINF;
  int m = n / 2;
  double x = a[m].X;
  double d = min(convex_radius(a, m), convex_radius(a + m, n - m));
  sort(a, a + n, compare_y);
  vector<Point> b;
  for(int i = 0; i < n; ++i){
    if(fabs(a[i].X - x) >= d) continue;
    for(int j = 0; j < (int)b.size(); ++j){
      Point p0 = a[i], p1 = b[(int)(b.size()) - j - 1];
      if(p0.Y - p1.Y >= d) break;
      d = min(d, abs(p0 - p1));
    }
    b.push_back(a[i]);
  }
  return d;
}

// 凸多角形の直線カット
// 凸多角形を直線で切断し、その左側(直線と交差する点も含む)だけを残す

Poly convex_cut(const Poly &g, const Line &l){
  Poly Q;
  for(int i = 0; i < g.size(); i++){
    Point A = curr(g, i), B = next(g, i);
    if(ccw(l[0], l[1], A) != -1) Q.push_back(A);
    if(ccw(l[0], l[1], A) * ccw(l[0], l[1], B) < 0) Q.push_back(crosspointLL(Line(A, B), l));
  }
  return Q;
}

// ベクトルの回転
Point rotation(Point v, double r){
  return Point(v.real() * cos(r) - v.imag() * sin(r), v.real() * sin(r) + v.imag() * cos(r));
}

//2ベクトル間の角度
// atan2(x1 * y2 - x2 * y1, x1 * x2 + y1 * y2);

int main(){
  // Failed to predict input format
  double x,y,a,b;
  cin >> x >> y >> a >> b ;
  double sx,sy,tx,ty;
  cin >> sx >> sy >> tx >> ty ;
  yn(intersectSS(LineSegment(Point(0,a),Point(x,b)),
      LineSegment(Point(sx,sy),Point(tx,ty))));
  return 0;
}
