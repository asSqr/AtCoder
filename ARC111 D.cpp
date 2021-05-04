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
#define eb emplace_back

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
ll a[10010], b[10010];
ll c[110];
ll ans[10010];
std::vector<P> G[110];
bool used[110];

void dfs( ll v ) {
  used[v] = true;

  for( auto [u, i] : G[v] ) {
    if( ans[i] == -1 )
      ans[i] = v == b[i];

    if( !used[u] ) {
      dfs( u );
    }
  }

  return;
}

int main() {
  std::cin >> N >> M;

  rep( i, M )
    std::cin >> a[i] >> b[i], --a[i], --b[i];

  rep( i, N )
    std::cin >> c[i];

  rep( i, M )
    ans[i] = -1;

  atcoder::dsu d( N );

  rep( i, M ) {
    if( c[a[i]] == c[b[i]] ) {
      d.merge(a[i], b[i]);
    } else if( c[a[i]] > c[b[i]] ) {
      ans[i] = false;
    } else {
      ans[i] = true;
    }
  }

  rep( i, M ) if( c[a[i]] == c[b[i]] ) {
    G[a[i]].eb(b[i], i);
    G[b[i]].eb(a[i], i);
  }

  for( auto vs : d.groups() ) {
    dfs(vs[0]);
  }

  rep( i, M )
    std::cout << (ans[i] ? "<-" : "->") << endl;

  return 0;
}