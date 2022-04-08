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

struct UnionFind {
  std::vector<int> d;
  UnionFind(int n=0): d(n,-1) {}
  int find(int x) {
    if (d[x] < 0) return x;
    return d[x] = find(d[x]);
  }
  bool unite(int x, int y) {
    x = find(x); y = find(y);
    if (x == y) return false;
    if (d[x] > d[y]) std::swap(x,y);
    d[x] += d[y];
    d[y] = x;
    return true;
  }
  bool same(int x, int y) { return find(x) == find(y);}
  int size(int x) { return -d[find(x)];}
};

ll N, Q;
ll lb[100010], ub[100010];
std::deque<ll> vs[100010];
bool val[100010];

UnionFind uf(100010);

int main() {
  std::cin >> N >> Q;

  rep( i, N )
    lb[i] = ub[i] = i;

  rep( i, N )
    vs[i].emplace_back(i+1);

  rep( q, Q ) {
    ll t;
    std::cin >> t;

    if( t == 1 ) {
      ll x, y;
      std::cin >> x >> y;
      --x; --y;
      ll miN = x;
      ll maX = y;
      x = miN;

      if( vs[maX].size() < vs[miN].size() ) {
        for( auto v : vs[maX] )
          vs[miN].emplace_back(v);

        vs[maX] = vs[miN];
      } else {
        for( auto v : vs[miN] )
          vs[maX].emplace_back(v);

        vs[miN] = vs[maX];
      }

      lb[y] = lb[x];
      ub[x] = ub[y];
    } else if( t == 2 ) {
      ll x, y;
      std::cin >> x >> y;
      --x; --y;

      ll *ptr = val[x] ? ub : lb;

      ll idx = std::lower_bound( all(vs[ptr[x]]), x )-vs[ptr[x]].begin();
      ll n = vs[ptr[x]].size();

      if( idx+1 < n-idx ) {
        std::deque<ll> us;

        rep( i, idx+1 ) {
          us.emplace_back(vs[ptr[x]][i]);
          vs[ptr[x]].pop_front();
          ub[vs[ptr[x]][i]] = x;
          val[vs[ptr[x]][i]] = true;
        }

        vs[y] = vs[ptr[x]];
        vs[ptr[x]] = us;
      } else {
        repi( i, idx+1, n ) {
          vs[y].emplace_back(vs[ptr[x]][i]);
          lb[vs[ptr[x]][i]] = y;
          val[vs[ptr[x]][i]] = false;
        }
        
        repi( i, idx+1, n )
          vs[ptr[x]].pop_back();
      }
    } else {
      ll x;
      std::cin >> x;
      --x;

      ll *ptr = val[x] ? ub : lb;

      if( val[x] )
        std::reverse(all(vs[ptr[x]]));

      std::cout << vs[ptr[x]].size();
      
      for( auto v : vs[ptr[x]] )
        std::cout << " " << v;

      std::cout << endl;
    }
  }

  return 0;
}