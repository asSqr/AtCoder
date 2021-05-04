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

using DP = std::vector<std::vector<ll>>;
using DP1 = std::vector<ll>;

ll N;
ll A[5010];
std::vector<ll> G[5010];
ll dp[5010][5010][2];
ll subtree[5010];

DP upd( ll v, ll u, const DP &sum, ll size ) {
  DP ret( size+subtree[u]+5, DP1( 2, INF ) );

  rep( i, size+1 ) rep( j, subtree[u]+1 ) {
    if( sum[i][1] != INF && dp[u][j][1] != INF )
      chmin( ret[i+j][1], sum[i][1]+dp[u][j][1] );

    if( dp[u][j][0] < INF || dp[u][j][1] < 0 ) {
      chmin( ret[i+j+1][1], sum[i][1] );

      if( A[v] > 0 ) {
        chmin( ret[i+j+1][0], sum[i][0] );
      }
    }

    if( A[v] > 0 ) {
      if( sum[i][0] != INF && dp[u][j][0] != INF )
        chmin( ret[i+j][0], sum[i][0]+dp[u][j][0] );
    }
  }

  return ret;
}

void dfs1( ll v, ll p = -1 ) {
  subtree[v] = 1;

  for( auto u : G[v] ) if( u != p ) {
    dfs1( u, v );

    subtree[v] += subtree[u];
  }

  return;
}

void dfs2( ll v, ll p = -1 ) {
  DP sum( 2, DP1( 2, INF ) );

  sum[0][1] = A[v];

  if( A[v] > 0 )
    sum[0][0] = A[v];

  //std::cout << "s--------------------" << endl;

  //std::cout << "[" << v << "]" << endl;

  ll size = 0;

  for( auto u : G[v] ) if( u != p ) {
    dfs2(u, v);  

    sum = upd( v, u, sum, size );

    size += subtree[u];

    //std::cout << "<" << u << ">" << endl;
    
    //rep( j, subtree[v]+1 )
      //printf( "dp[%lld][0] = %lld, dp[%lld][1] = %lld\n", j, sum[j][0], j, sum[j][1] );
  }

  rep( i, sum.size() ) {
    dp[v][i][0] = sum[i][0];
    dp[v][i][1] = sum[i][1];
  }

  //std::cout << "e--------------------" << endl;

  return;
}

int main() {
  std::cin >> N;

  rep( i, N )
    std::cin >> A[i];

  rep( i, N-1 ) {
    ll U, V;
    std::cin >> U >> V;
    --U; --V;

    G[U].emplace_back(V);
    G[V].emplace_back(U);
  }

  rep( i, N+1 ) rep( j, N+1 ) rep( k, 2 )
    dp[i][j][k] = INF;

  dfs1( 0 );
  dfs2( 0 );

  ll ans = N;

  //rep( i, N ) rep( j, subtree[i]+1 )
    //printf( "dp[%lld][%lld][0] = %lld, dp[%lld][%lld][1] = %lld\n", i, j, dp[i][j][0], i, j, dp[i][j][1] );

  rep( j, N+1 ) {
    if( dp[0][j][0] < INF || dp[0][j][1] < 0 ) {
      ans = j;

      break;
    }
  }

  std::cout << ans << endl;

  return 0;
}