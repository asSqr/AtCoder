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

// <value, begin, isLinear>
using Tup = std::tuple<ll, ll, bool>;

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

ll N, Q;
ll S[200010];
ll a[200010], t[200010], x[200010];

int main() {
  std::cin >> N;

  ll lb = -INF, ub = INF, lv = -INF, uv = INF;
  ll pad = 0;

  rep( i, N ) {
    std::cin >> a[i] >> t[i];

    if( t[i] == 1 ) {
      pad += a[i];
      lv += a[i];
      uv += a[i];
    } else if( t[i] == 2 ) {
      if( lv < a[i] ) {
        lb = a[i]-pad;
        lv = a[i];

        if( uv <= a[i] ) {
          ub = lb;
          uv = a[i];
        }
      }
    } else {
      if( uv > a[i] ) {
        ub = a[i]-pad;
        uv = a[i];
      }

      if( a[i] <= lv ) {
        lb = ub;
        lv = uv;
      }
    }
  }

  std::cin >> Q;

  rep( q, Q ) {
    std::cin >> x[q];

    if( x[q] <= lb ) {
      std::cout << lv << endl;
    } else if( x[q] >= ub ) {
      std::cout << uv << endl;
    } else {
      std::cout << x[q]+pad << endl;
    }
  }

  return 0;
}