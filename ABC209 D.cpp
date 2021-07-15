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
std::vector<ll> G[100010];
ll dep[100010];

void dfs( ll v, ll p = -1, ll d = 0 ) {
  dep[v] = d;

  for( auto u : G[v] ) if( u != p ) {
    dfs(u,v,d+1);
  }

  return;
}

template<typename T> // T: type of cost
struct lca {
  int n, root, l;
  std::vector<std::vector<int>> to;
  std::vector<std::vector<T>> co;
  std::vector<int> dep;
  std::vector<T> costs;
  std::vector<std::vector<int>> par;
  lca(int n):n(n),to(n),co(n),dep(n),costs(n) {
    l = 0;
    while ((1<<l) < n) ++l;
    par = std::vector<std::vector<int>>(n+1,std::vector<int>(l,n));
  }
  void addEdge(int a, int b, T c=0) {
    to[a].push_back(b); co[a].push_back(c);
    to[b].push_back(a); co[b].push_back(c);
  }
  void dfs(int v, int d=0, T c=0, int p=-1) {
    if (p != -1) par[v][0] = p;
    dep[v] = d;
    costs[v] = c;
    for (int i = 0; i < to[v].size(); ++i) {
      int u = to[v][i];
      if (u == p) continue;
      dfs(u, d+1, c+co[v][i], v);
    }
  }

  void init(int _root=0) {
    root = _root;
    dfs(root);
    for (int i = 0; i < l-1; ++i) {
      for (int v = 0; v < n; ++v) {
        par[v][i+1] = par[par[v][i]][i];
      }
    }
  }
  // LCA
  int operator()(int a, int b) {
    if (dep[a] > dep[b]) std::swap(a,b);
    int gap = dep[b]-dep[a];
    for (int i = l-1; i >= 0; --i) {
      int len = 1<<i;
      if (gap >= len) {
        gap -= len;
        b = par[b][i];
      }
    }
    if (a == b) return a;
    for (int i = l-1; i >= 0; --i) {
      int na = par[a][i];
      int nb = par[b][i];
      if (na != nb) a = na, b = nb;
    }
    return par[a][0];
  }
  int length(int a, int b) {
    int c = (*this)(a,b);
    return dep[a]+dep[b]-dep[c]*2;
  }
  T dist(int a, int b) {
    int c = (*this)(a,b);
    return costs[a]+costs[b]-costs[c]*2;
  }
};

int main() {
  std::cin >> N >> Q;

  lca<ll> lc(N);

  rep( i, N-1 ) {
    ll a, b;
    std::cin >> a >> b;
    --a; --b;

    lc.addEdge(a,b,1);
  }

  lc.init();

  rep( q, Q ) {
    ll c, d;
    std::cin >> c >> d;
    --c; --d;

    std::cout << (lc.dist(c,d)&1 ? "Road" : "Town") << endl;
  }
  
  return 0;
}