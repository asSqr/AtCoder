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

ll N;
ll X[20], Y[20], Z[20];
ll dp[(1ll<<17)+10][20];

ll dist( ll i, ll j ) {
  return llabs(X[j]-X[i])+llabs(Y[j]-Y[i])+std::max(0ll, Z[j]-Z[i]);
}

int main() {
  std::cin >> N;

  rep( i, N )
    std::cin >> X[i] >> Y[i] >> Z[i];

  rep( i, 1ll<<N ) rep( j, N )
    dp[i][j] = INF;

  dp[1][0] = 0;

  rep( i, 1ll<<N ) rep( j, N ) {
    if( !(i>>j&1) )
      continue;

    rep( k, N ) if( !(i>>k&1) ) {
      chmin( dp[i|1ll<<k][k], dp[i][j]+dist(j,k) );
    }
  }

  ll ans = INF;

  rep( j, N )
    chmin( ans, dp[(1ll<<N)-1][j]+dist(j,0) );

  std::cout << ans << endl;

  return 0;
}