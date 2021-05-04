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

// (type, max or min)

ll N, K;
std::vector<ll> G[200010];
P dp[200010];
bool used[200010];

void dfs( ll v, ll X, ll p = -1 ) {
  ll rmi = INF, rma = 0;

  std::vector<ll> vs;

  for( auto u : G[v] ) if( u != p ) {
    dfs(u, X, v);
    vs.emplace_back(u);
  }

  if( vs.empty() ) {
    dp[v] = { 0, 0 };

    return;
  }

  for( auto v : vs ) {
      if( dp[v].first == 1 ) {
        chmin( rmi, dp[v].second+1 );
      } else {
        chmax( rma, dp[v].second+1 );
      }
  }

  if( rmi+rma <= X ) {
    dp[v] = { 1, rmi };
  } else {
    dp[v] = { 0, rma };

    if( rma >= X ) {
      used[v] = true;

      dp[v] = { 1, 0 };
    }
  }

  return;
}

bool C( ll X ) {
  rep( i, N ) {
    used[i] = false;
  }

  dfs( 0, X );
  
  if( dp[0].first == 0 )
    used[0] = true;

  ll k = 0;

  rep( i, N )
    k += used[i];

  return k <= K;
}

int main() {
  std::cin >> N >> K;

  rep( i, N-1 ) {
    ll u, v;
    std::cin >> u >> v;
    --u; --v;

    G[u].emplace_back(v);
    G[v].emplace_back(u);
  }

  ll ng = 0, ok = N;

  while( ok-ng > 1 ) {
    ll mid = (ng+ok)>>1;

    (C(mid) ? ok : ng) = mid;
  }

  std::cout << ok << endl;

  return 0;
}