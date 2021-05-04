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

ll N, X;
ll A[100], c[100];
std::vector<ll> dp(2);

int main() {
  std::cin >> N >> X;

  rep( i, N )
    std::cin >> A[i];

  rep( i, N-1 )
    c[i] = A[i+1]/A[i];

  ll Y = X;
  std::vector<ll> xs;

  repd( i, N ) {
    xs.emplace_back(Y/A[i]);
    Y %= A[i];
  }

  std::reverse(all(xs));

  dp[0] = 1;

  rep( i, N-1 ) {
    std::vector<ll> p(2);
    std::swap( dp, p );

    ll x = xs[i];

    rep( j, 2 ) rep( nj, 2 ) {
      {
        // y = 0
        ll z = 0-x-j+nj*c[i];

        if( 0 <= z && z < c[i] )
          dp[nj] += p[j];
      }
      {
        // z = 0
        ll y = 0+x+j-nj*c[i];

        if( 0 < y && y < c[i] )
          dp[nj] += p[j];
      }
    }
  }

  ll ans = dp[0]+dp[1];

  std::cout << ans << endl;

  return 0;
}