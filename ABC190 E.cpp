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

ll N, M;
ll A[100010], B[100010];
ll K;
ll C[20];
std::vector<ll> G[100010];
ll dist[100010];
ll mp[20][20];
ll dp[(1ll<<17)+10][18];

using St = std::tuple<ll, ll, ll>;

ll bfs( ll v ) {
  rep( i, N+3 )
    dist[i] = INF;

  std::priority_queue<St, std::vector<St>, std::greater<St> > que;
  
  dist[v] = 0;
  
  que.emplace(dist[v],v,0);

  while( !que.empty() ) {
    auto [d, u, mask] = que.top(); que.pop();

    if( dist[u] < d )
      continue;

    for( auto t : G[u] ) {
      if( chmin(dist[t], d+1) )
        que.emplace(dist[t],t,0);
    }
  }

  return INF;
}

int main() {
  std::cin >> N >> M;

  rep( i, M ) {
    std::cin >> A[i] >> B[i];

    --A[i]; --B[i];

    G[A[i]].emplace_back(B[i]);
    G[B[i]].emplace_back(A[i]);
  }

  std::cin >> K;

  rep( i, K )
    std::cin >> C[i], --C[i];

  ll ans = INF;

  rep( i, K ) {
    bfs(C[i]); 

    std::vector<ll> vs;

    rep( j, K )
      mp[i][j] = dist[C[j]];
  }

  rep( i, 1ll<<K ) rep( j, K )
    dp[i][j] = INF;

  rep( i, K )
    dp[1ll<<i][i] = 0;

  rep( i, 1ll<<K ) rep( j, K ) {
    rep( k, K ) if( !(i>>k&1) ) {
      chmin( dp[i|1ll<<k][k], dp[i][j]+mp[j][k] );
    }
  }

  rep( i, K )
    chmin( ans, dp[(1ll<<K)-1][i] );

  std::cout << (ans==INF ? -1 : ans+1) << endl;

  return 0;
}