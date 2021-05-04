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
using P = std::pair<ll, char>;

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
std::vector<P> G[1010];
std::vector<ll> adj[1010][30];
bool Adj[1010][1010];
ll dp[1010][1010];

ll f( ll u, ll v ) {
  ll &ret = dp[u][v];

  if( u-v == 0 ) {
    return ret = 0;
  }

  if( Adj[u][v] ) {
    return ret = 1;
  }

  if( ret != -1 )
    return ret;
  
  ret = INF;

  for( auto [s, ch] : G[u] ) {
    for( auto [t, ch2] : G[v] ) if( ch == ch2 ) {
      ll prv = f(s,t);

      if( prv != INF )
        chmin( ret, prv+2 );
    }
  }

  //std::cout << u << ' ' << v << ' ' << ret << endl;

  return ret;
}

int main() {
  std::cin >> N >> M;

  rep( i, M ) {
    ll A, B;
    char C;

    std::cin >> A >> B >> C;

    --A; --B;
    G[A].emplace_back( B, C );
    G[B].emplace_back( A, C );
    Adj[A][B] = Adj[B][A] = true;
    adj[A][C-'a'].emplace_back(B);
    adj[B][C-'a'].emplace_back(A);
  }

  rep( i, 1005 ) rep( j, 1005 )
    dp[i][j] = -1;

  ll ans = f(0, N-1);

  std::cout << (ans>=INF ? -1 : ans) << endl;

  return 0;
}