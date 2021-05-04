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

ll M, R;
std::vector<ll> G[1000010];

ll id( ll x, ll m ) {
  return M*x+m;
}

void add_edge( ll i, ll j ) {
  rep( k, M ) {
    ll u = id(i,k);
    ll v = id(j,k);

    G[u].emplace_back(v);
    G[v].emplace_back(u);
  }

  return;
}

bool used[1000010];

int main() {
  std::cin >> M >> R;

  add_edge( 0, 1 );

  repi( i, 1, 10 ) {
    if( i%3 ) {
      add_edge( i, i+1 );
    }

    if( (i+2)/3 < 3 ) {
      add_edge( i, i+3 );
    }
  }

  rep( i, 10 ) rep( j, M ) {
    ll u = id(i,j);
    ll v = id(i,(j*10+i)%M);

    G[u].emplace_back(v);
  }

  std::queue<P> que;

  que.emplace( 0, id(0,0) );
  used[id(0,0)] = true;

  while( !que.empty() ) {
    auto [dist, v] = que.front(); que.pop();

    used[v] = true;

    if( v%M == R ) {
      std::cout << dist << endl;

      return 0;
    }

    for( auto u : G[v] ) if( !used[u] ) {
      //std::cout << P(v/M, v%M) << " -> " << P(u/M, u%M) << endl;
      que.emplace( dist+1, u );
    }
  }

  return 0;
}