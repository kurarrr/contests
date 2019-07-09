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

struct Polynomial{
  struct Item{
    map<char,int> vars;
    Item(const map<char,int>& vars):vars(vars){;}
    Item(const string& item):vars(parse_vars(item)){;}
    Item &operator*=(Item that) {
      for(auto&& p:that.vars){
        vars[p.first] += p.second;
      }
      return *this;
    }
    map<char,int> parse_vars(const string& item){
      map<char, int> res;
      // TODO
      return res;
    }
    Item operator*(Item that) const { return Item(*this) *= that; }
    string get() const{
      string res = "";
      for(auto&& p:vars){
        res += string(1,p.first) + (p.second!=1 ? "^" + to_string(p.second): ""); 
      }
      return res;
    }
    friend ostream& operator<<(ostream& st, const Item& a) { st << a.get(); return st; }
     bool operator<(const Item &that) const{
        return vars < that.vars;
    };
  };

  map<Item, int> coef;
  Polynomial(){;}
  Polynomial(const map<Item,int>& coef): coef(coef){;}
  Polynomial(const string& poly): coef(parse_polynomial(poly)){;}
  map<Item, int> parse_polynomial(const string& poly) const{
    // TODO
    map<Item, int> res;
    return res;
  }
  Polynomial &operator+=(Polynomial that) {
    for(auto&& p:that.coef){
      coef[p.first] += p.second;
    }
    return *this;
  }
  Polynomial operator+(Polynomial that) const { return Polynomial(*this) += that; }
  Polynomial &operator*=(Polynomial that) {
    auto mul = (*this) * that;
    swap(this->coef, mul.coef);
    return *this;
  }
  Polynomial operator*(Polynomial that) const {
    Polynomial res;
    for(auto&& p1: coef){
      for(auto&& p2:that.coef){
        res.coef[ p1.first * p2.first ] += p1.second * p2.second;
      }
    }
    return res;
  }
  string get() const{
    string res = "";
    for(auto itr = coef.begin(); itr != coef.end(); itr++){
      res += (itr->second != 1 ? to_string(itr->second) : "") + itr->first.get() + (next(itr)!=coef.end() ? "+": ""); 
    }
    return res;
  }
  friend ostream& operator<<(ostream& st, const Polynomial& a) { st << a.get(); return st; }
};

int main(){
  int N,M;
  map<char,int> xmp,mp1,mp2;
  xmp['x'] = 1;
  mp1['y'] = 1;
  mp2['a'] = 1; mp2['x'] = 2; mp2['x'] = 2;
  Polynomial::Item x(xmp),it1(mp1),it2(mp2); // x,y, ax^{2}y^{2} 
  map<Polynomial::Item, int> co1, co2;
  co1[x] = 1; co1[it1] = 2;
  co2[x] = 3; co2[it1] = 4;
  Polynomial p1(co1),p2(co2);
  cout << p1 << " + " << p2 << " = " << p1+p2 << endl;
  cout << p1 << " * " << p2 << " = " << p1*p2 << endl;
  return 0;
}
