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

ll T;

ll po( char ch ) {
  if( ch == 'T' ) {
    return 0;
  } else if( ch == 'M' ) {
    return 1;
  }
}

template<typename T>
struct BIT {
  int n;
  std::vector<T> d;
  BIT(int n=0):n(n),d(n+1) {}
  void add(int i, T x=1) {
    for (i++; i <= n; i += i&-i) {
      d[i] += x;
    }
  }
  T sum(int i) {
    T x = 0;
    for (i++; i; i -= i&-i) {
      x += d[i];
    }
    return x;
  }
  T sum(int l, int r) {
    return sum(r-1) - sum(l-1);
  }
};

int main() {
  std::cin >> T;

  rep( t, T ) {
    ll n;
    std::cin >> n;

    std::string S;
    std::cin >> S;

    ll fcnt[2] = { 0, 0 };
    rep( i, n ) {
      ++fcnt[po(S[i])];
    }

    if( fcnt[0]%2 != 0 || fcnt[1] != fcnt[0]/2 ) {
      puts("NO");

      continue;
    }

    BIT<ll> bit( n+10 );

    ll l = 0, r = n-1;
    std::queue<P> que;

    while( l < r ) {
      while( l < n && S[l] != 'T' )
        ++l;

      if( l >= r || S[l] != 'T' )
        break;

      while( r >= 0 && S[r] != 'T' )
        --r;

      if( l >= r || S[r] != 'T' )
        break;

      que.emplace(l, r);
      ++l; --r;
    }

    ll cnt = 0;
    bool fl = true;
    ll rest = n;

    rep( i, n ) if( S[i] == 'M' ) {
      auto [l, r] = que.front(); que.pop();

      if( !(l <= i && i <= r) ) {
        fl = false;
        break;
      }

      ++cnt;
      rest -= 3;
    }

    if( rest || !que.empty() )
      fl = false;

    if( fl ) {
      puts("YES");
    } else {
      puts("NO");
    }
  }

  return 0;
}