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
ll a[510];
ll dp[510][510];

ll zero( ll x ) {
  return x == -INF ? 0 : x;
}

int main() {
  std::cin >> N;

  rep( i, N )
    std::cin >> a[i];

  rep( i, N+5 ) rep( j, N+5 )
    dp[i][j] = i==j ? 0 : -INF;

  repi( w, 1, N+1 ) {
    rep( l, N ) {
      ll r = l+w;

      if( r > N )
        continue;

      repi( i, l+1, r )
        chmax( dp[l][r], zero(dp[l][i])+zero(dp[i][r]) );

      if( (r-l)%3 )
        continue;

      repi( i, l+1, r ) {
        if( (i-l)%3 != 1 )
          continue;

        chmax( dp[l][r], dp[l+1][i]+dp[i+1][r-1]+a[l]+a[i]+a[r-1] );
      }
    }
  }

  //rep( i, N+1 ) rep( j, N+1 ) if( j-i > 0 )
    //printf( "dp[%lld][%lld] = %lld\n", i, j, dp[i][j] );

  std::cout << dp[0][N] << endl;

  return 0;
}