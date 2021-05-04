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

ll N, Q;
ll C[200010];

struct UnionFind {
  std::vector<int> d;
  std::vector<std::vector<int>> cs;
  std::vector<std::map<ll, ll>> cnt;

  UnionFind(int n=0): d(n+10,-1), cnt(n+10, std::map<ll, ll>()), cs(n+10, std::vector<int>()) {
  }
  void init() {
    rep( i, N ) {
      cs[i].emplace_back(C[i]);
      ++cnt[i][C[i]];
    }
  }
  int find(int x) {
    if (d[x] < 0) return x;
    return d[x] = find(d[x]);
  }
  bool unite(int x, int y) {
    x = find(x); y = find(y);
    if (x == y) return false;
    if (d[x] > d[y]) std::swap(x,y);
    d[x] += d[y];

    for( auto c : cs[y] )
      cs[x].emplace_back(c);

    for( auto c : cs[y] )
      ++cnt[x][c];

    d[y] = x;
    return true;
  }
  bool same(int x, int y) { return find(x) == find(y);}
  int size(int x) { return -d[find(x)];}
};

UnionFind uf(200010);

int main() {
  std::cin >> N >> Q;

  rep( i, N )
    std::cin >> C[i], --C[i];

  uf.init();

  rep( q, Q ) {
    ll t;
    std::cin >> t;

    if( t == 1 ) {
      ll a, b;
      std::cin >> a >> b;
      --a; --b;

      if( !uf.same(a,b) )
        uf.unite(a,b);
    } else {
      ll x, y;
      std::cin >> x >> y;
      --x; --y;
      std::cout << uf.cnt[uf.find(x)][y] << endl;
    }
  }

  return 0;
}