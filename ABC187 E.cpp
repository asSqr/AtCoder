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
std::vector<ll> G[200010];
ll a[200010], b[200010];
ll Q;
ll par[200010];
ll qs[200010];
ll ans[200010];
ll acc;

void dfs( ll v, ll p = -1 ) {
  par[v] = p;
  
  for( auto u : G[v] ) if( u != p )
    dfs( u, v );
}

void dfs2( ll v, ll p = -1 ) {
  acc += qs[v];

  ans[v] = acc;

  for( auto u : G[v] ) if( u != p )
    dfs2( u, v );

  acc -= qs[v];
}

int main() {
  std::cin >> N;

  rep( i, N-1 ) {
    std::cin >> a[i] >> b[i];
    --a[i]; --b[i];

    G[a[i]].emplace_back(b[i]);
    G[b[i]].emplace_back(a[i]);
  }

  dfs(0);

  std::cin >> Q;

  rep( q, Q ) {
    ll t, e, x;
    std::cin >> t >> e >> x;
    --e;

    bool fl = par[a[e]] != b[e];

    if( t == 1 ) {
      if( !fl ) {
        qs[a[e]] += x;
        //printf( "[%lld] +%lld\n", a[e], x );
      } else {
        acc += x;
        qs[b[e]] -= x;
        //printf( "[%lld] %lld\n", b[e], -x );
      }
    } else {
      if( fl ) {
        qs[b[e]] += x;
        //printf( "[%lld] +%lld\n", b[e], x );
      } else {
        acc += x;
        qs[a[e]] -= x;
        //printf( "[%lld] %lld\n", a[e], -x );
      }
    }
  }

  dfs2(0);

  rep( i, N )
    std::cout << ans[i] << endl;

  return 0;
}