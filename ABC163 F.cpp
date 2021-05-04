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

template<typename T>
struct BIT {
  int n;
  std::vector<T> d;
  BIT(int n=0):n(n),d(n+1) {}
  void add(int i, T x=1) {
    for (i++; i <= n; i += i&-i) {
      d[i] += x;
    }
  }
  T sum(int i) {
    T x = 0;
    for (i++; i; i -= i&-i) {
      x += d[i];
    }
    return x;
  }
  T sum(int l, int r) {
    return sum(r-1) - sum(l-1);
  }
};

ll N;
ll c[200010];
std::vector<ll> G[200010];
ll tim;
ll in[200010], out[200010];

void dfs( ll v, ll p = -1 ) {
  in[v] = tim++;

  for( auto u : G[v] ) if( u != p ) {
    dfs(u,v);
  }

  out[v] = tim;

  return;
}

ll f( ll x ) {
  return x*(x+1)/2;
}

std::vector<ll> cs[200010];

int main() {
  std::cin >> N;

  rep( i, N )
    std::cin >> c[i], --c[i];

  rep( i, N-1 ) {
    ll a, b;
    std::cin >> a >> b;
    --a; --b;

    G[a].emplace_back(b);
    G[b].emplace_back(a);
  }

  dfs(0);

  rep( i, N )
    cs[c[i]].emplace_back(i);

  BIT<ll> bit(N+10);

  rep( i, N )
    bit.add(i,1);

  rep( k, N ) {
    ll ans = f(N);

    std::vector<ll> &vs = cs[k];

    std::sort( all(vs), [&]( ll a, ll b ) {
      return in[a] > in[b];
    });

    std::vector<P> hist;

    for( auto v : vs ) {
      ll cnt = 1;

      for( ll u : G[v] ) {
        if( in[u] < in[v] )
          continue;

        ll x = bit.sum(in[u], out[u]);
        ans -= f(x);
        cnt += x;
      }

      bit.add( in[v], -cnt );
      hist.emplace_back( in[v], cnt );
    }

    ans -= f(bit.sum(0,N));

    for( auto p : hist )
      bit.add(p.first, p.second);

    std::cout << ans << endl;
  }

  return 0;
}