#include "../../template/template.cpp"

// 素数
struct Primes{
  // enumerate primes less than or equal to n
  // complexity: O(n loglog(n))
  // nums.size() ~ O(n/log(n))
  vector<bool> is_prime;
  vector<ll> nums;
  Primes(ll n):is_prime(n+1,true){
    is_prime[0] = is_prime[1] = false;
    for(ll i = 2; i <= n; i++){
      if(!is_prime[i]) continue;
      for(ll j = 2; j*i <= n; j++) is_prime[j*i] = false;
      nums.push_back(i);
    }
  }
};

// 約数の列挙
vector<ll> divisors(ll n) {
  vector<ll> res;
  for(int i=1; i*i<=n; i++) {
    if(n % i == 0) {
      res.push_back(i);
      if(n / i != i) res.push_back(n/i);
    }
  }
  return res;
}

// 素因数の列挙
vector<ll> prime_factors(ll n) {
  // NOTE: not sorted
  vector<ll> res;
  for(ll i=2; i*i<=n; i++) {
    if(n % i == 0) {
      res.push_back(i);
      while(n % i == 0) n /= i;
    }
  }
  if(n != 1) res.push_back(n);
  return res;
}

void solve() {
  auto pr = Primes(2000);
  dump(pr.nums.size());
  auto fa = prime_factors(600);
  dump(fa);
  auto div = divisors(36);
  dump(div);
}
