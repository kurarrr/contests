#include "../template/template.cpp"
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
// when you compule by g++ -fsanitize=undefined,
// you should add also -fvisibility=hidden

const long long MOD = 1000000007;

void solve(){
  namespace mult_prec = boost::multiprecision;
  using Bigint = mult_prec::cpp_int;
  Bigint mo = Bigint(MOD);
  Bigint a = Bigint("12345678912345");
  cout << mo * mo * a << endl;
}
