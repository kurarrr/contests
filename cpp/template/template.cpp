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
#define REP(i, x, n) for(Int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define RREP(i, x, n) for(Int i = x; i >= n; i--)
#define rrep(i, n) RREP(i,n,0)
#define pb push_back
#define fi first
#define se second
#pragma GCC optimize ("-O3")

using namespace std;

#define DUMPOUT cout
#define dump(...) if(DEB) DUMPOUT<<"  "<<#__VA_ARGS__<<" :["<<__LINE__<<":"<<__FUNCTION__<<"]"<<endl<<"    "; if(DEB) dump_func(__VA_ARGS__)
template<typename T1,typename T2>ostream& operator << (ostream& os, pair<T1,T2> p){cout << "(" << p.first << ", " << p.second << ")"; return os;}
template<typename T>ostream& operator << (ostream& os, vector<T>& vec) { os << "{"; for (int i = 0; i<vec.size(); i++) os << vec[i] << (i + 1 == vec.size() ? "" : ", "); os << "}"; return os; }
template<typename T>ostream& operator << (ostream& os, set<T>& st){cout << "{"; for(auto itr = st.begin(); itr != st.end(); itr++) cout << *itr << (next(itr)!=st.end() ? ", " : ""); cout << "}"; return os;}
template<typename T1,typename T2>ostream& operator << (ostream& os, map<T1,T2> mp){cout << "{"; for(auto itr = mp.begin(); itr != mp.end(); itr++) cout << "(" << (itr->first) << ", " << (itr->second) << ")" << (next(itr)!=mp.end() ? "," : ""); cout << "}"; return os; }
template<typename T1,typename T2>ostream& operator << (ostream& os, unordered_map<T1,T2> mp){cout << "{"; for(auto itr = mp.begin(); itr != mp.end(); itr++) cout << "(" << (itr->first) << ", " << (itr->second) << ")" << (next(itr)!=mp.end() ? "," : ""); cout << "}"; return os; }
template <size_t N = 0, typename T> void print_tuple(ostream& os, const T& val) {
  if constexpr(N == 0) os << "("s;
  if constexpr(N + 1 < std::tuple_size<T>::value) {
    os << std::get<N>(val) << ", "s;
    print_tuple<N+1>(os, val);
  }else if constexpr(N + 1 == std::tuple_size<T>::value){
    os << std::get<N>(val) << ")"s;
  }
}
template<typename ...T> ostream& operator << (ostream& os, tuple<T...> val){ print_tuple(os, val); return os; }

template < typename T > struct is_pair : std::false_type { } ;
template < typename T1, typename T2 > struct is_pair< std::pair<T1, T2> > : std::true_type { } ;
template < typename T > constexpr bool is_pair_v = is_pair<T>::value ;
template < typename Iterator >
class with_index_iterator : public Iterator {
  std::size_t i = 0;
public:
  with_index_iterator( Iterator iter ) : Iterator( iter ) {}
  auto & operator ++(){
    ++i ;
    this->Iterator::operator ++() ;
    return *this ;
  }
  auto operator *() const noexcept
  {
    if constexpr ( is_pair_v< typename std::iterator_traits<Iterator>::value_type > ) {
      auto & pair = *static_cast<Iterator const &>(*this) ;
      return std::make_tuple( i, pair.first, pair.second ) ;
    } else {
      return std::make_pair( i, *static_cast<Iterator const &>(*this) ) ;
    }
  }
};

template < typename Range >
class with_index {
  Range& range ;
public:
  with_index( Range & range ) : range(range) {}
  auto begin() const { return with_index_iterator{ std::begin(range) } ; }
  auto end() const { return with_index_iterator{ std::end(range) } ; }
};


void dump_func(){DUMPOUT << endl;}
template <class Head, class... Tail>void dump_func(Head&& head, Tail&&... tail){ DUMPOUT << head; if (sizeof...(Tail) == 0) { DUMPOUT << " "; } else { DUMPOUT << ", "; } dump_func(std::move(tail)...);}
template<class T> inline bool chmax(T& a,T const& b){if(a>=b) return false; a=b; return true;}
template<class T> inline bool chmin(T& a,T const& b){if(a<=b) return false; a=b; return true;}
void solve();
int main(void) {
  std::cout << std::fixed << std::setprecision(15);
  solve();
	return 0;
}

using Int = long long;
using ll = long long;
using P = pair<Int,Int>;
using vi = vector<Int>;
using vvi = vector<vi>;
using vp = vector<P>;
using vvp = vector<vp>;

const Int INF = (1LL<<50);

void solve(){
}