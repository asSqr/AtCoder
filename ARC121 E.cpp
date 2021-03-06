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
#include <atcoder/all>
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

using mint = atcoder::modint998244353;

ll N;
ll p[2010];
std::vector<ll> G[2010];
std::vector<mint> dp[2010];
ll subtree[2010];

ll dfs( ll v, ll p = -1 ) {
  dp[v] = { 1 };
  subtree[v] = 1;

  ll ch = 0;

  for( auto u : G[v] ) if( u != p ) {
    subtree[v] += dfs( u, v );

    dp[v] = atcoder::convolution( dp[v], dp[u] );
    ++ch;
  }

  auto pdp = dp[v];
  ll mk = dp[v].size();

  rep( k, mk ) {
    if( k+1 < dp[v].size() ) {
      dp[v][k+1] += pdp[k]*(subtree[v]-1-k);
    } else {
      dp[v].emplace_back(pdp[k]*(subtree[v]-1-k));
    }
  }

  return subtree[v];
}

mint fact[2010];

int main() {
  std::cin >> N;

  rep( i, N-1 ) {
    std::cin >> p[i];
    --p[i];

    G[p[i]].emplace_back(i+1);
  }

  dfs( 0 );

  mint ans = 0;

  //rep( i, N ) rep( j, dp[i].size() )
    //printf( "dp[%lld][%lld] = %lld\n", i, j, dp[i][j].val() );

  fact[0] = 1;

  rep( i, N )
    fact[i+1] = fact[i]*(i+1);

  rep( i, N+1 ) {
    ans += dp[0][i]*(i&1?-1:1)*fact[N-i];
  }

  std::cout << ans.val() << endl;

  return 0;
}