#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>
#define repi(i,a,b) for(ll i=(a);i<(b);++i)
#define rep(i,a) repi(i,0,a)
#define repdi(i,a,b) for(ll i=(a)-1;i>=(b);--i)
#define repd(i,a) repdi(i,a,0)
#define itr(it,a) for( auto it = (a).begin(); it != (a).end(); ++it )
#define abigint(a) (a).begin(), (a).end()
#define rabigint(a) (a).rbegin(), (a).rend()
#define endl '\n'
#define debug(x) std::cerr << #x << " = " << (x) << endl;

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }

using ll = long long;

typedef boost::multiprecision::cpp_int bigint;

std::map<bigint, bigint> prime_factor( bigint x ) {
  std::map<bigint, bigint> mp;
  
  for( bigint i = 2; i*i <= x; ++i ) {
    while( x%i == 0 ) {
      ++mp[i];
      x /= i;
    }
  }

  if( x != 1 )
    ++mp[x];

  return mp;
}

bigint A, B;
std::map<bigint, bigint> S;
std::vector<bigint> vs;

bigint gcd( bigint a, bigint b )
{ return b ? gcd(b,a%b) : a; }

bigint lcm( bigint a, bigint b )
{ return a/gcd(a,b)*b; }

bigint tmp[100];
bigint two[100];

int main() {
  std::cin >> A >> B;

  bigint coef = 1;

  if( A == 1 ) {
    coef = 2;
    ++A;
  }

  for( bigint i = A; i <= B; ++i ) {
    auto mp = prime_factor(i);

    itr( it, mp ) {
      ++S[it->first];
    }
  }

  ll C = (ll)(B-A+1);

  two[0] = 1;
  rep( i, B-A+1 )
    two[i+1] = two[i]*2;

  rep( i, 40 ) {
    tmp[i] = two[C];

    if( C-i > 0 ) {
      tmp[i] -= i*(two[C-i]);
      tmp[i] -= two[C-i];
    }
  }

  itr( it, S ) if( it->second > 1 )
    vs.emplace_back(it->first);

  ll N = vs.size();

  bigint ans = 0;

  rep( bit, 1ll<<N ) {
    bigint M = 1;

    ll cnt = 0;
    ll sum = 0;

    rep( i, N ) if( bit>>i&1 ) {
      M = vs[i];

      cnt = (ll)((bigint)(B/M-(A-1)/M));
    }
    
    ans += (__builtin_popcountll(bit)&1 ? -1 : 1)*tmp[cnt];
  }

  ans *= coef;

  std::cout << ans << endl;

  return 0;
}