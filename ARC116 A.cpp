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
#define repi(i,a,b) for(ll i=(a);i<(b);++i)
#define rep(i,a) repi(i,0,a)
#define repdi(i,a,b) for(ll i=(a)-1;i>=(b);--i)
#define repd(i,a) repdi(i,a,0)
#define itr(it,a) for( auto it = (a).begin(); it != (a).end(); ++it )
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define endl '\n'
#define debug(x) std::cerr << #x << " = " << (x) << endl;

using ll = long long;
using P = std::pair<ll, ll>;

constexpr ll INF = 1ll<<60;

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }

template<class S, class T>
std::ostream& operator<< ( std::ostream& out, const std::pair<S,T>& a )
{ std::cout << '(' << a.first << ", " << a.second << ')'; return out; }

template<class T>
std::ostream &operator<< ( std::ostream& out, const std::vector<T>& a )
{ std::cout << '['; rep( i, a.size() ){ std::cout << a[i]; if( i != a.size()-1 ) std::cout << ", "; } std::cout << ']'; return out; }

std::vector<ll> divisors( ll x ) {
  std::vector<ll> ret;

  for( ll i = 1; i*i <= x; ++i ) if( x%i == 0 ) {
    ret.emplace_back( i );

    if( i != x/i )
      ret.emplace_back( x/i );
  }

  return ret;
}

std::map<ll, ll> prime_factor( ll x ) {
  std::map<ll, ll> ret;

  for( ll i = 2; i*i <= x; ++i ) {
    while( x % i == 0 ) {
      ++ret[i];
      x /= i;
    }
  }

  if( x != 1 )  
    ++ret[x];

  return ret;
}

void sieve() {
  
  return;
}

ll T;

int main() {
  std::cin >> T;

  rep( t, T ) {
    ll N;
    std::cin >> N;

    ll cnt = 0;

    while( N%2 == 0 )
      N /= 2, ++cnt;

    if( cnt > 1 )
      std::cout << "Even" << endl;
    else if( cnt == 1 )
      std::cout << "Same" << endl;
    else
      std::cout << "Odd" << endl;
  }

  return 0;
}