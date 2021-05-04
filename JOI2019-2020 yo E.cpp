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

constexpr ll mod = 1000000007;

ll N;
std::string E, A;
ll p = 0;

// vector size 3 { R, P, S }

std::vector<ll> expr();

std::vector<ll> factor() {
  if( E[p] == 'R' ) {
    ++p;

    return { 1, 0, 0 };
  } else if( E[p] == 'S' ) {
    ++p;

    return { 0, 0, 1 };
  } else if( E[p] == 'P' ) {
    ++p;

    return { 0, 1, 0 };
  } else if( E[p] == '?' ) {
    ++p;

    return { 1, 1, 1 };
  } else if( E[p] == '(' ) {
    ++p;
    auto e = expr();
    ++p;

    return e;
  }
}

std::vector<ll> mul( const std::vector<ll> &lhs, const std::vector<ll> &rhs) {
  auto comp = [&]( ll a, ll b ) {
    rep( i, 3 ) if( i != a && i != b )
      return i;
  };

  std::vector<ll> ret(3);
  
  rep( i, 3 ) rep( j, 3 ) {
    if( i == j ) { 
      ret[i] = (ret[i]+lhs[i]*rhs[j])%mod;

      continue;
    }

    ll k = comp(i,j);

    ret[k] = (ret[k]+lhs[i]*rhs[j])%mod;
  }

  return ret;
}

std::vector<ll> term() {
  auto f = factor();

  while( E[p] == '*' ) {
    ++p;
    f = mul( f, factor() );
  }

  return f;
}

std::vector<ll> add( const std::vector<ll> &lhs, const std::vector<ll> &rhs) {
  auto comp = [&]( ll a, ll b ) {
    ll c = std::min(a,b), d = std::max(a,b);

    if( d-c == 1 )
      return d;
    if( c == 0 && d == 2 )
      return c;
  };

  std::vector<ll> ret(3);
  
  rep( i, 3 ) rep( j, 3 ) {
    if( i == j ) { 
      ret[i] = (ret[i]+lhs[i]*rhs[j])%mod;

      continue;
    }

    ll k = comp(i,j);

    ret[k] = (ret[k]+lhs[i]*rhs[j])%mod;
  }

  return ret;
}

std::vector<ll> sub( const std::vector<ll> &lhs, const std::vector<ll> &rhs) {
  auto comp = [&]( ll a, ll b ) {
    ll c = std::min(a,b), d = std::max(a,b);

    if( d-c == 1 )
      return c;
    if( c == 0 && d == 2 )
      return d;
  };

  std::vector<ll> ret(3);
  
  rep( i, 3 ) rep( j, 3 ) {
    if( i == j ) { 
      ret[i] = (ret[i]+lhs[i]*rhs[j])%mod;

      continue;
    }

    ll k = comp(i,j);

    ret[k] = (ret[k]+lhs[i]*rhs[j])%mod;
  }

  return ret;
}

std::vector<ll> expr() {
  auto t = term();

  while( E[p] == '+' || E[p] == '-' ) {
    if( E[p] == '+' ) {
      ++p;
      t = add(t, term());
    }
    else {
      ++p;
      t = sub(t, term());
    }
  }

  return t;
}

const std::string RPS = "RPS";

int main() {
  std::cin >> N >> E >> A;

  auto dp = expr();

  ll idx = RPS.find(A);

  std::cout << dp[idx]%mod << endl;

  return 0;
}